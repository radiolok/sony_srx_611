"""Spec §2: the original SRXWIN files must match the MD5s in doc/SRXWIN_tools_report.md §8."""

import hashlib

import pytest

from srx_dosbox.runner import find_srxwin

MD5 = {
    "ANNUL.EXE": "aa444e060f809cfe20ea703a05b66a29",
    "FILES.EXE": "4973b97ee0bfed63580d44c768619b77",
    "DISPON.EXE": "7472579b97cc8a9c4474473615abde3e",
    "HIST.EXE": "a6ec1bc7b4b655174dfe7e60b7ee58bb",
    "DPLC.EXE": "d5b949dffddb5a11ab47755d54f20020",
    "INI_RS.EXE": "4a4722cbaab7112b00dc9ad4fef2ee11",
    "FDEL.EXE": "a40dc3e5951d014ac3fdaf6048df0a88",
    "INI_RS98.EXE": "9e803c2f7639a7ccad376ce17901d8ec",
    "INSTALLE.EXE": "90579a37e48df6253e72344788bd2631",
    "LUNAPR.EXE": "ea5479f62110e786945be9ed7e6e67eb",
    "LUNNA.EXE": "eabbc3f0ca01b733cbd37c0efd11919c",
    "MONIT.EXE": "30b88ef336cd4ca42e01b223b6965716",
    "PLC.EXE": "10bf67fa31f89cb6ab6c03b208555214",
    "POINT.EXE": "653a5990ced73a77119ab9a3a6545724",
    "RECALL.EXE": "44663db7a68ac50f479d9e3afcd1341e",
    "SEND.EXE": "27fac6b3deb840c4e75da228d78eed45",
    "SRXMONI.ICO": "d074da74be8627c1e6ccf96645bc7f50",
    "SRXMONIE.EXE": "bc038614fc555304c51202e60b8f9579",
    "SRXMONIE.HLP": "832575a4ff730cbbd452a9f828c31d79",
}


@pytest.mark.parametrize("name", sorted(MD5))
def test_md5(name: str) -> None:
    d = find_srxwin()
    if d is None:
        pytest.skip("SRXWIN directory not found")
    assert hashlib.md5((d / name).read_bytes()).hexdigest() == MD5[name]
