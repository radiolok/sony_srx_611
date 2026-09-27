"""Common header of every transferable program file (PROTOCOL.md §5)."""

from __future__ import annotations

import struct
from dataclasses import dataclass
from enum import IntEnum

HEADER_LEN = 14
END_MARK = 0xED  # last byte of LUNNA/POINT output


class Kind(IntEnum):
    CDT = 0x5A  # common data
    CTR = 0x5B  # robot parameters (write-protected by policy)
    OBJ = 0x5C  # LUNA object
    DAT = 0x5D  # point data
    COD = 0x5E  # PLC object
    SYS = 0x5F  # system program (type 100)

    @property
    def ext(self) -> str:
        return {0x5A: ".CDT", 0x5B: ".CTR", 0x5C: ".OBJ", 0x5D: ".DAT", 0x5E: ".COD",
                0x5F: ".OBJ"}[self.value]


EXT_TO_KIND = {".CDT": Kind.CDT, ".CTR": Kind.CTR, ".OBJ": Kind.OBJ, ".DAT": Kind.DAT,
               ".COD": Kind.COD}


@dataclass(frozen=True)
class Header:
    kind: int
    size1: int
    name: str
    size2: int

    @property
    def total(self) -> int:
        """Bytes transferred on the wire (SEND ``total32``, RECALL length)."""
        return self.size1 + self.size2


def parse_header(data: bytes) -> Header:
    if len(data) < HEADER_LEN:
        raise ValueError(f"file too short for a header: {len(data)} bytes")
    kind, _, size1 = struct.unpack_from("<BBH", data, 0)
    name = data[4:12].decode("ascii", "replace").rstrip(" \0")
    size2 = struct.unpack_from("<H", data, 12)[0] if kind in (Kind.OBJ, Kind.SYS) else 0
    return Header(kind, size1, name, size2)


def wire_image(data: bytes) -> bytes:
    """The part of a file that is sent to / recalled from the controller."""
    return data[: parse_header(data).total]
