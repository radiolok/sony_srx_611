// Label the controller-side host protocol in ROM1-C.bin (Ghidra program based at 0xFFE00000).
// See doc/SRXWIN_protocol.md §9. Addresses below are FILE offsets; BASE is added.
// @category SRX611
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.PointerDataType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;

public class LabelSrxProtocol extends GhidraScript {
    static final long BASE = 0xFFE00000L;

    Address a(long fileOff) { return toAddr(BASE + fileOff); }

    void fn(long off, String name, String comment) throws Exception {
        Address ad = a(off);
        Function f = getFunctionAt(ad);
        if (f == null) { disassemble(ad); f = createFunction(ad, name); }
        if (f != null) f.setName(name, SourceType.USER_DEFINED);
        if (comment != null) setPlateComment(ad, comment);
    }

    @Override
    protected void run() throws Exception {
        fn(0x50D00, "host_cmd_server_task",
           "Host (PC) command server task on OS serial channel 0x10002.\n"
         + "Loop: receive ESC frame, cmd byte > 0xAB -> status 3, else call host_cmd_table[cmd].\n"
         + "Handler returns 0 = replied itself, else server sends 1B 05 cmd status SUM.");
        fn(0x50EA8, "host_rx_wait_frame", "Wait for / read frame start on channel 0x10002 (returns 5 on timeout)");
        fn(0x50F78, "host_rx_frame_body", "Read rest of a host frame on channel 0x10002");
        fn(0x51088, "host_rx_frame_retry", "rx_frame with up to 3 retries; on checksum error replies 1B 05 cmd 01 SUM");
        fn(0x51180, "host_rx_frame",
           "Read ESC frame: timeout->5, byte0!=1B->2, LEN<=4->4, bad sum->1, OS error->100 (= E4000+s on the PC)");
        fn(0x512A0, "host_send_reply", "Finish (checksum) and send a reply frame on channel 0x10002");
        fn(0x51328, "frame_set_checksum", "byte[LEN-1] = sum(byte[0..LEN-2])");
        fn(0x51360, "host_cmd_unknown", "Default handler for unassigned command numbers");
        fn(0xBB5EC, "peer_request",
           "ESC-frame request/response client on OS serial channel 0x10001 (NOT a database accessor;\n"
         + "IDA name db_access). Callers build 1B LEN CMD ... frames and map status s to 20000+s.");

        Address tab = a(0x51828);
        createLabel(tab, "host_cmd_table", true);
        int named = 0;
        for (int i = 0; i < 0xAC; i++) {
            Address slot = tab.add(4L * i);
            clearListing(slot, slot.add(3));
            createData(slot, PointerDataType.dataType);
            long target = getInt(slot) & 0xFFFFFFFFL;
            if (target == BASE + 0x51360) continue;
            fn(target - BASE, String.format("host_cmd_%02X", i), null);
            named++;
        }
        println("LabelSrxProtocol: labelled " + named + " command handlers");
    }
}
