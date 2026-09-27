from conftest import CORPUS

from srx_formats.header import END_MARK, Kind, parse_header, wire_image


def test_lunna_output_header() -> None:
    d = (CORPUS / "golden/lun/T1.OBJ").read_bytes()
    h = parse_header(d)
    assert (h.kind, h.size1, h.name, h.size2) == (Kind.OBJ, 80, "T1", 34)
    assert h.total == len(d) and d[-1] == END_MARK and wire_image(d) == d


def test_point_output_header() -> None:
    d = (CORPUS / "golden/pon/T1.DAT").read_bytes()
    h = parse_header(d)
    assert (h.kind, h.size1, h.name, h.size2) == (Kind.DAT, 35, "T1", 0)
    assert h.total == len(d) and d[-1] == END_MARK
