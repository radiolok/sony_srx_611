"""Controller status codes -> typed exceptions (PROTOCOL.md §3, requirement LNK-06)."""

from __future__ import annotations


class LinkError(Exception):
    """Communication failure on the host side (timeout, bad frame, cable)."""


class LinkTimeout(LinkError):
    pass


class ControllerError(Exception):
    """Controller replied with a non-zero status; ``code`` is the GUI E-number."""

    status: int = 0
    text: str = "Controller response error"

    def __init__(self, status: int | None = None, cmd: int | None = None) -> None:
        if status is not None:
            self.status = status
        self.cmd = cmd
        super().__init__(f"E{self.code} {self.text} (cmd {cmd:02X})" if cmd is not None
                         else f"E{self.code} {self.text}")

    @property
    def code(self) -> int:
        return 4000 + self.status


class SafetyError(Exception):
    """Session refused an operation because of its danger class (spec §8)."""


def _mk(name: str, status: int, text: str) -> type[ControllerError]:
    return type(name, (ControllerError,), {"status": status, "text": text})


ChecksumError = _mk("ChecksumError", 1, "SEND check sum error")
EscCodeError = _mk("EscCodeError", 2, "SEND ESC code error")
CommandNumberError = _mk("CommandNumberError", 3, "Command number error")
SizeError = _mk("SizeError", 4, "SEND size error")
ControllerTimeoutError = _mk("ControllerTimeoutError", 5, "SEND time out error")
ExecuteError = _mk("ExecuteError", 6, "SEND execute error")
BlockError = _mk("BlockError", 7, "RECALL block receive error")
NoProgramError = _mk("NoProgramError", 8, "No program error")
ProgramKindError = _mk("ProgramKindError", 9, "Program kind error")
EmptySlotError = _mk("EmptySlotError", 10, "No task program error")
ProgramRunningError = _mk("ProgramRunningError", 11, "Program executing error")
MemoryFullError = _mk("MemoryFullError", 12, "Program memory area error")
MemoryError_ = _mk("MemoryError_", 13, "Program memory error")
TaskError = _mk("TaskError", 14, "Task error")
NoHistoryError = _mk("NoHistoryError", 15, "No error history")

BY_STATUS: dict[int, type[ControllerError]] = {
    c.status: c
    for c in (ChecksumError, EscCodeError, CommandNumberError, SizeError,
              ControllerTimeoutError, ExecuteError, BlockError, NoProgramError,
              ProgramKindError, EmptySlotError, ProgramRunningError, MemoryFullError,
              MemoryError_, TaskError, NoHistoryError)
}


def raise_for_status(status: int, cmd: int) -> None:
    if status:
        raise BY_STATUS.get(status, ControllerError)(status, cmd)
