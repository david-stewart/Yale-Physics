starver SL18b
# inputs:
# [0] number of events
# [1] pt min hat
# [2] pt max hat
# [3] output file name
root4star -q -b /gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/pythia6/run.C\($nEvents,$minHat,$maxHat,\"$outFile\",$seed\)
# root4star -q -b ./run.C\(\)
