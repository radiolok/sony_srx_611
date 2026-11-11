#!/bin/sh
# usage: TP_WORK=<dir mounted as /work> tp.sh <logfile> <cmd lines...>
SP=${TP_WORK:?set TP_WORK to the dir mounted as /work (contains cmd/out)}
log=$1; shift
: > $SP/out
m="mark$$"
{ for c in "$@"; do echo "$c"; done; echo "dump $m"; } > $SP/cmd
timeout 300 sh -c "until grep -q '== $m' $SP/out 2>/dev/null; do sleep 1; done"
grep -v "== $m" $SP/out | awk -v m="$m" 'BEGIN{skip=0} /^== /{skip=($2==m)} !skip' >> "$log"
python3 "$(dirname "$0")/tpfmt.py" $SP/out
