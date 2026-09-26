#!/bin/sh
# Create a Ghidra project with ROM1-C.bin loaded at its link address 0xFFE00000 as 32-bit x86.
# Usage: tools/ghidra/import_rom1c.sh [project_dir]   (default: ~/ghidra_projects)
# Needs GHIDRA_HOME (default ~/opt/ghidra_12.1.4_PUBLIC) and a JDK 21 (JAVA_HOME or ~/opt/jdk-21*).
set -e
REPO=$(cd "$(dirname "$0")/../.." && pwd)
GHIDRA_HOME=${GHIDRA_HOME:-$HOME/opt/ghidra_12.1.4_PUBLIC}
[ -n "$JAVA_HOME" ] || JAVA_HOME=$(ls -d "$HOME"/opt/jdk-21* | head -1)
export JAVA_HOME PATH="$JAVA_HOME/bin:$PATH"
PROJ=${1:-$HOME/ghidra_projects}
mkdir -p "$PROJ"
"$GHIDRA_HOME/support/analyzeHeadless" "$PROJ" SRX611 \
  -import "$REPO/FW/SRX6-CPU/2/ROM1-C.bin" -overwrite \
  -processor x86:LE:32:default -loader BinaryLoader -loader-baseAddr 0xFFE00000 \
  -scriptPath "$REPO/tools/ghidra" -preScript SeedSrxFunctions.java \
  -analysisTimeoutPerFile 3600
