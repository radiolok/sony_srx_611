# MAME patches for the SRX-C61 driver

`build.sh` and the `Dockerfile` apply these patches to the pinned MAME checkout
(`mame0289`) before they build.

| Patch | Device | Why |
|---|---|---|
| `0001-z180asci-rdrf-level-irq.patch` | Z180 ASCI | In MAME, the receive interrupt is raised once per received byte and cleared when the CPU takes it. On the real Z180/HD64180 the RDRF interrupt is a **level**: it stays active while received data is waiting. Without the patch, if the pendant ISR is ever late by more than one byte time, one byte stays in the FIFO for good. Every later CPU→TP frame is then shifted by one byte: the pendant answers status 4 (frame timeout) or 5 (first byte not `1B`), and the CPU stops handling keys. In our runs this happened after about 10 s. The patch re-raises the interrupt after an RDR read while the FIFO is still not empty. Worth upstreaming. |

Not fixed, noted only: in `set_fifo_data`, the no-overrun branch does
`m_error_fifo[...] &= Z180_STAT_OVRN`. That drops the FE/PE flags of a received
byte; it probably should be `&= ~Z180_STAT_OVRN`. The pendant firmware does not
depend on this.
