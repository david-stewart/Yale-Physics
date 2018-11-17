starver SL18b
# inputs:
# [0] number of events
# [1] pt min hat
# [2] pt max hat
# [3] output file name
nEvents=${1:-100}
minHat=${2:-5.}
maxHat=${3:-7.}
outFile=${4:-pythia.root}
seed=${5:--1}
root4star -q -b /gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/pythia6/run.C\($nEvents,$minHat,$maxHat,\"$outFile\",$seed\)
# root4star -q -b ./run.C\(\)
