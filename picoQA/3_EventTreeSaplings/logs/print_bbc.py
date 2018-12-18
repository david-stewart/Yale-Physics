# to be run from inside of ipython (which will therefore get the versioning of python correct"
import uproot as up
import numpy as np

# get the data for the triggers
triggernames = ('500001', '500006', '500018', '500202', '500206', '500215', '500904')

data_16 = up.open('16.root')
data_17 = up.open('17.root')

bbc16 = {}
bbc17 = {}

for data_in, data_out in zip((data_16, data_17),(bbc16, bbc17)):
    first = True
    for x in triggernames:
        data = data_in['h_bbcES_%s'%x].numpy()
        if first:
            first = False
            data_out['x-axis'] = (data[1][1:]+data[1][:-1])/2.
        data_out[x] = data[0]
        # print (bbc16[x])
        # print (bbc16[x].mean())

print (bbc16.keys())

print (bbc16['500018'][0])
print (bbc17['500018'][0])
print (bbc17['500018'].mean())
print (bbc17['500018'].sum())

