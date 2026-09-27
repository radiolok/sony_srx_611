import pytest

from srx_link import errors


def test_status_maps_to_typed_exception_with_gui_code() -> None:
    with pytest.raises(errors.ProgramRunningError) as e:
        errors.raise_for_status(11, 0x06)
    assert e.value.code == 4011 and e.value.cmd == 6


def test_unknown_status_is_generic() -> None:
    with pytest.raises(errors.ControllerError) as e:
        errors.raise_for_status(0x20, 0x30)
    assert type(e.value) is errors.ControllerError and e.value.code == 4032


def test_zero_is_ok() -> None:
    errors.raise_for_status(0, 1)
