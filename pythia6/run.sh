starver SL18b
line="$*"
argv=`sed 's/ /:/g' <<< "$line"`
root4star -q -b /gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/pythia6/run.C\(\"$argv\"\);
