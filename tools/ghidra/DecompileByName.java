// Print decompiled C for functions given by name (or 0x file offset) as script arguments.
// Headless: analyzeHeadless <proj> SRX611 -process ROM1-C.bin -noanalysis -readOnly \
//           -scriptPath tools/ghidra -postScript DecompileByName.java host_cmd_server_task 0x51180
// @category SRX611
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;

public class DecompileByName extends GhidraScript {
    @Override
    protected void run() throws Exception {
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        for (String arg : getScriptArgs()) {
            Function f = null;
            if (arg.startsWith("0x")) {
                f = getFunctionAt(toAddr(0xFFE00000L + Long.parseLong(arg.substring(2), 16)));
            } else {
                for (Function g : currentProgram.getFunctionManager().getFunctions(true))
                    if (g.getName().equals(arg)) { f = g; break; }
            }
            if (f == null) { println("// not found: " + arg); continue; }
            DecompileResults r = d.decompileFunction(f, 120, monitor);
            println("// ===== " + f.getName() + " @ " + f.getEntryPoint() + "\n"
                    + (r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed: " + r.getErrorMessage()));
        }
        d.dispose();
    }
}
