#!/usr/bin/sh

rm P$1.list
touch P$1.list
# set -x
to_file="`pwd -P`/P$1.list"
rm    $to_file
touch $to_file
echo  $to_file

here=`pwd -P`

line="/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/picoQA/2_EventTrees/root/ln_P$1"
# line="/gpfs/mnt/gpfs01/star/pwg/dstewart/scratch/Yale-Physics/picoQA/0_picoToEvTree/root/P"$1"id/good_links"
cd $line

for f in `ls -1`; do
    if [ ${f: -5} == ".root" ]; then
        echo $line/$f >> $to_file
    fi
done
