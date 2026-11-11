**Title:** z180asci: RX interrupt is edge-triggered; a second byte waiting in the FIFO raises no new interrupt

**Version:** mame0289 (`f34f0250`), `src/devices/cpu/z180/z180asci.cpp`

**Description**

In `z180asci_channel_base`, the receive interrupt is raised only when a byte arrives. `set_fifo_data()` sets `m_irq = 1` if `RIE` is set. The CPU core clears the request when it accepts the interrupt (`z180_device::check_interrupts()` → `clear_interrupt()`).

`rdr_r()` does not raise the request again when more data is still in the FIFO after the read. It does so only for error flags.

The Zilog Z180 Technical Manual (June 1988, pp. 30–31) describes the receiver like this:

- *ASCI Receive Data Register:* "The next incoming data byte can be shifted into RSR while RDR contains the previous received data byte. Thus, the ASCI receiver is double buffered."
- *RDRF:* "RDRF is set to 1 when an incoming data byte is loaded into RDR … RDRF is cleared to 0 by reading RDR."
- *RIE:* "When RIE is 1, if any of the flags RDRF, OVRN, PE, or FE become set to 1, an interrupt request is generated."

So on the real part, a second byte waits in RSR. Reading RDR clears RDRF, the byte moves from RSR to RDR, and RDRF becomes set again, which generates a new interrupt request. MAME models the receiver as a 4-entry FIFO. After `rdr_r()` returns with data still queued, `RDRF` simply stays at 1. There is no new 0→1 transition and no new request, so the queued byte is never signalled.

**Effect**

A common ISR design reads one byte from RDR per interrupt. If interrupt latency is ever longer than one character time, two bytes are in the FIFO when the ISR runs. The ISR reads the first. The second keeps `RDRF` set, but nobody reads it until the next byte arrives and raises a new interrupt. After that the software is always one byte behind.

**Where we hit it**

An out-of-tree driver for a Sony SRX-C61 robot controller. Its teach pendant is an HD64180 with exactly that kind of one-byte-per-interrupt ISR, linked over ASCI0 to the controller CPU.
- After about 10 s of normal operation, one late ISR left a byte in the FIFO.
- From then on, every 3-byte request frame from the host arrived shifted by one byte. The pendant firmware answered "frame timeout" or "bad lead byte", and the keyboard stopped working.
- With the change below, the link stays in sync indefinitely.

**Proposed fix**

```diff
--- a/src/devices/cpu/z180/z180asci.cpp
+++ b/src/devices/cpu/z180/z180asci.cpp
@@ -244,6 +244,8 @@ uint8_t z180asci_channel_base::rdr_r()
 			m_fifo_rd = (m_fifo_rd + 1) & 3;
 			if (m_fifo_rd == m_fifo_wr) // empty
 				m_asci_stat &= ~Z180_STAT_RDRF;
+			else if (m_asci_stat & Z180_STAT_RIE) // RDRF interrupt is a level: more data pending
+				m_irq = 1;
 		}
 	}
 	return m_asci_rdr;
```

This is the minimal change: it re-raises the request when a read leaves a byte in RDR, which is what happens on the chip when the byte waiting in RSR moves into RDR. A fuller fix would derive the request from the current status (`RIE && (RDRF || OVRN || PE || FE)`, and likewise for TIE/TDRE) instead of the latched `m_irq` flag.

The 4-entry FIFO itself is more than the Z80180 has (one RDR plus RSR). It may follow the Z8S180, which does have a FIFO on ASCI0.

**Possibly related, not verified on hardware**

In `set_fifo_data()` (line 543), the no-overrun branch does:

```cpp
m_error_fifo[m_fifo_wr] &= Z180_STAT_OVRN;
```

This clears the `FE`/`PE` bits that were just passed in `error`, so framing and parity errors never reach `STAT`. The manual (p. 31) says PE and FE are set on an incoming byte with a parity error or an invalid stop bit, and stay set until EFR is written. It looks like the line was meant to be `&= ~Z180_STAT_OVRN`.
