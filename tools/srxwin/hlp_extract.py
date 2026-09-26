#!/usr/bin/env python3
"""Minimal WinHelp 3.x (.HLP) text extractor, written for SRXWIN/SRXMONIE.HLP.

Usage: hlp_extract.py SRXMONIE.HLP [out.json]
       hlp_extract.py --md SRXMONIE.HLP out.md
Prints/returns topics as {"title", "keywords", "text"}. Pure Python, no deps.
Supports: internal file-system B+ tree, |SYSTEM, LZ77 topic blocks,
|Phrases compression (HC 3.0/3.1), topic records 0x02 (header) / 0x20 (text) / 0x23 (table).
"""
import json, struct, sys


def lz77(src, limit=None):
    out = bytearray(); i = 0
    while i < len(src):
        bits = src[i]; i += 1
        for b in range(8):
            if i >= len(src): break
            if bits & (1 << b):
                w = src[i] | (src[i + 1] << 8); i += 2
                pos, ln = (w & 0x0FFF) + 1, (w >> 12) + 3
                for _ in range(ln): out.append(out[-pos])
            else:
                out.append(src[i]); i += 1
            if limit and len(out) >= limit: return bytes(out[:limit])
    return bytes(out)


class HLP:
    def __init__(self, path):
        self.d = d = open(path, 'rb').read()
        magic, dirstart = struct.unpack('<II', d[:8])
        assert magic == 0x35F3F, 'not a WinHelp file'
        self.files = self._btree(dirstart + 9, key=lambda b, p: self._cstr(b, p), val=4)
        self._system()
        self._phrases()

    @staticmethod
    def _cstr(b, p):
        e = b.index(b'\0', p); return b[p:e].decode('latin1'), e + 1

    def _btree(self, at, key, val):
        d = self.d
        pagesize = struct.unpack('<H', d[at + 4:at + 6])[0]
        root, _, _, nlev, nent = struct.unpack('<HhHHI', d[at + 26:at + 38])
        pages = at + 38; pg = root
        for _ in range(nlev - 1):
            pg = struct.unpack('<H', d[pages + pg * pagesize + 4:pages + pg * pagesize + 6])[0]
        out = {}
        while pg != 0xFFFF and len(out) < nent:
            b = d[pages + pg * pagesize:pages + (pg + 1) * pagesize]
            n, _, nxt = struct.unpack('<hhH', b[2:8]); p = 8
            for _ in range(n):
                k, p = key(b, p)
                out[k] = b[p:p + val]; p += val
            pg = nxt
        return out

    def file(self, name):
        off = struct.unpack('<I', self.files[name])[0]
        _, used = struct.unpack('<II', self.d[off:off + 8])
        return self.d[off + 9:off + 9 + used]

    def _system(self):
        s = self.file('|SYSTEM')
        _, self.minor, _, _, self.flags = struct.unpack('<HHHIH', s[:12])
        self.title = ''
        if self.minor > 16:
            p = 12
            while p + 4 <= len(s):
                rt, ln = struct.unpack('<HH', s[p:p + 4]); data = s[p + 4:p + 4 + ln]; p += 4 + ln
                if rt == 1: self.title = data.split(b'\0')[0].decode('cp932', 'replace')
        else:
            self.title = s[12:].split(b'\0')[0].decode('cp932', 'replace')
        self.compressed = self.minor > 16 and self.flags in (4, 8)
        self.blocksize = 2048 if (self.minor <= 16 or self.flags == 8) else 4096

    def _phrases(self):
        self.phr = []
        if '|Phrases' not in self.files: return
        s = self.file('|Phrases')
        n, one = struct.unpack('<HH', s[:4])
        if self.minor <= 16:
            offs = struct.unpack('<%dH' % (n + 1), s[4:4 + 2 * (n + 1)])
            base = 4; data = s
        else:
            dsize = struct.unpack('<I', s[4:8])[0]
            offs = struct.unpack('<%dH' % (n + 1), s[8:8 + 2 * (n + 1)])
            raw = s[8 + 2 * (n + 1):]
            data = lz77(raw, dsize) if self.compressed else raw
            base = 8; offs = [o - offs[0] for o in offs]
            self.phr = [data[offs[i]:offs[i + 1]] for i in range(n)]; return
        self.phr = [data[offs[i]:offs[i + 1]] for i in range(n)]

    def _unphrase(self, b):
        if not self.phr: return b
        out = bytearray(); i = 0
        while i < len(b):
            c = b[i]
            if 0 < c < 0x10 and i + 1 < len(b):
                n = 256 * (c - 1) + b[i + 1]; i += 2
                out += self.phr[n >> 1]
                if n & 1: out += b' '
            else:
                out.append(c); i += 1
        return bytes(out)

    def topics(self):
        t = self.file('|TOPIC'); bs = self.blocksize
        stream = bytearray()
        for p in range(0, len(t), bs):
            blk = t[p:p + bs][12:]
            stream += lz77(blk, 16384 - 12) if self.compressed else blk
            # decompressed topic blocks are 16 KiB windows; pad so offsets stay consistent
            if self.compressed and len(stream) % (16384 - 12):
                stream += b'\0' * ((16384 - 12) - len(stream) % (16384 - 12))
        topics = []; cur = None; p = 0
        while p + 21 <= len(stream):
            bsz, dl2, prev, nxt, dl1, rtype = struct.unpack('<IIIIIB', stream[p:p + 21])
            if bsz < 21 or bsz > 0x10000:
                # jump to next 16K window (padding at block end)
                w = 16384 - 12; p = (p // w + 1) * w; continue
            ld1 = stream[p + 21:p + dl1]
            ld2 = stream[p + dl1:p + bsz]
            if dl2 > len(ld2): ld2 = self._unphrase(ld2)
            if rtype == 0x02:
                cur = {'title': ld2.split(b'\0')[0].decode('cp932', 'replace'), 'text': []}
                topics.append(cur)
            elif rtype in (0x20, 0x23) and cur is not None:
                txt = ld2.replace(b'\0', b' ').decode('cp932', 'replace').strip()
                if txt: cur['text'].append(txt)
            p += bsz
        for tp in topics: tp['text'] = '\n'.join(tp['text'])
        return topics


SECTIONS = [  # (first topic title, section heading) in SRXMONIE.HLP topic order
    ('', 'Platform overview'), ('LUNA Command List', 'LUNA language reference'),
    ('PLC Command List', 'PLC language reference'), ('System', 'SRX Platform GUI (menus and windows)'),
    ('Error Code Lists', 'Error codes'),
]


def md_escape(line):
    line = line.replace('\\', '\\\\').replace('*', '\\*').replace('_', '\\_').replace('<', '&lt;').replace('|', '\\|')
    return ('\\' + line) if line[:1] in '#>-+' or line[:2].rstrip('.').isdigit() and line[1:2] == '.' else line


def to_markdown(h, tps):
    out = ['# SRXMONIE.HLP — extracted help text', '',
           '> Generated by `tools/srxwin/hlp_extract.py --md` from `SRXWIN/SRXMONIE.HLP` '
           '(%s, WinHelp 3.1, %d topics). Sony copyright text, kept for interoperability research only — '
           'do not paste into SRXWIN-NG sources (see `doc/SRXWIN-NG.md` §2).' % (h.title, len(tps)), '']
    heads = dict(SECTIONS)
    for i, tp in enumerate(tps):
        title = tp['title'] or tp['text'].split('\n')[0]
        key = '' if i == 0 else tp['title']
        if key in heads and (i == 0 or key):
            out += ['', '## ' + heads[key], '']
        out += ['### ' + md_escape(title), '']
        out += [md_escape(l.strip()) + '  ' for l in tp['text'].split('\n') if l.strip()]
        out.append('')
    return '\n'.join(out) + '\n'


if __name__ == '__main__':
    args = [a for a in sys.argv[1:] if a != '--md']
    h = HLP(args[0])
    tps = h.topics()
    print('title=%r minor=%d flags=%d topics=%d phrases=%d' % (h.title, h.minor, h.flags, len(tps), len(h.phr)), file=sys.stderr)
    if '--md' in sys.argv:
        open(args[1], 'w', encoding='utf-8').write(to_markdown(h, tps))
    elif len(args) > 1:
        json.dump(tps, open(args[1], 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    else:
        for tp in tps[:5]: print(tp)
