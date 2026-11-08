import re,sys
GLYPH={0x02:'↑',0x03:'↓',0x04:'│',0x05:'▶',0x7f:'←',0x7e:'→'}
def dec(line):
    out=''
    for m in re.finditer(r'\{([0-9a-f]{2})\}|(.)',line):
        if m.group(1):
            b=int(m.group(1),16)
            if b in GLYPH: out+=GLYPH[b]
            elif 0xa1<=b<=0xdf: out+=bytes([b]).decode('cp932')
            else: out+='·'
        else: out+=m.group(2)
    return out
def screens(path):
    cur=None
    for l in open(path,encoding='latin1'):
        l=l.rstrip('\n')
        if l.startswith('== '):
            cur=[l[3:].split(' t=')[0],[]]
        elif l.startswith('|') and cur is not None:
            cur[1].append(dec(l[1:-1]))
            if len(cur[1])==4: yield cur; cur=None
if __name__=='__main__':
    for tag,lines in screens(sys.argv[1]):
        print('**%s**\n```\n┌────────────────────┐\n%s\n└────────────────────┘\n```'%(tag,'\n'.join('│'+x+'│' for x in lines)))
