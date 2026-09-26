// Pre-analysis seed for ROM1-C.bin (32-bit, loaded at 0xFFE00000): disassemble from the reset
// entry and create functions at every "push ebp; mov ebp,esp" prologue (55 8B EC / 55 89 E5)
// so that auto-analysis has something to start from. Used by tools/ghidra/import_rom1c.sh.
// @category SRX611
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.mem.Memory;

public class SeedSrxFunctions extends GhidraScript {
    @Override
    protected void run() throws Exception {
        Memory mem = currentProgram.getMemory();
        Address start = mem.getMinAddress();
        Address end = mem.getMaxAddress();
        byte[][] prologues = { {0x55, (byte) 0x8B, (byte) 0xEC}, {0x55, (byte) 0x89, (byte) 0xE5} };
        int created = 0;
        new DisassembleCommand(start, null, true).applyTo(currentProgram, monitor);
        for (byte[] pat : prologues) {
            Address a = start;
            while (a != null && a.compareTo(end) < 0 && !monitor.isCancelled()) {
                a = mem.findBytes(a, end, pat, null, true, monitor);
                if (a == null) break;
                if (getInstructionContaining(a) == null || getInstructionAt(a) != null) {
                    new DisassembleCommand(a, new AddressSet(a, a.add(2)), true).applyTo(currentProgram, monitor);
                    if (getFunctionAt(a) == null && createFunction(a, null) != null) created++;
                }
                a = a.add(1);
            }
        }
        println("SeedSrxFunctions: created " + created + " functions");
    }
}
