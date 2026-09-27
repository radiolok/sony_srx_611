import pytest

from srx_link import frame


def test_delete_example_from_protocol_doc() -> None:
    # doc/SRXWIN_protocol.md §2: delete LUNA type 3 -> 1B 06 06 03 5C 86
    assert frame.build(0x06, bytes([3, 0x5C])) == bytes.fromhex("1B0606035C86")


def test_parse_roundtrip_and_fields() -> None:
    raw = frame.build_reply(0x05, 0x0A)
    f = frame.parse(raw)
    assert (f.length, f.cmd, f.status, f.payload) == (5, 5, 10, b"")


@pytest.mark.parametrize("raw", [b"\x1a\x05\x05\x00\x24", b"\x1b\x06\x05\x00\x25",
                                 b"\x1b\x05\x05\x00\x00"])
def test_parse_rejects_bad_frames(raw: bytes) -> None:
    with pytest.raises(frame.FrameError):
        frame.parse(raw)


def test_reader_resyncs_after_junk_and_split_input() -> None:
    r = frame.FrameReader()
    a, b = frame.build(0x15), frame.build(0x14, b"\x03")
    assert r.feed(b"\x00\x41" + a[:3]) == []
    assert r.feed(a[3:] + b) == [a, b]
