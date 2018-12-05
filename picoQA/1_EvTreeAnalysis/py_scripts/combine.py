#!/usr/local/Cellar/python/3.7.1/bin/python3
import uproot
import numpy as np
import pandas as pd

def get_stats_one_param(pname:str, root_file_name:str):
    """Returns a numpy array of the statistics for a parameter.

    Required positional input:
    (1) parameter name
    (2) input file

    Return:
    panda dataframe runId, mean, std, stdmean, min, max, nEntries})
    """

    class VarStats:
        def __init__(self):
            self.is_first = True
            self.kmin = np.nan
            self.kmax = np.nan
            self.sum = np.nan
            self.sum2 = np.nan
            self.nEntries = np.nan
        def add(self, min_:float, max_:float, sum_:float, sum2_:float, nEntries_:int):
            if self.is_first:
                self.is_first = False
                self.kmin = min_
                self.kmax = max_
                self.sum = sum_
                self.sum2 = sum2_
                self.nEntries = nEntries_
            else:
                self.kmin = min(self.kmin, min_)
                self.kmax = min(self.kmax, max_)
                self.sum += sum_
                self.sum2 += sum2_
                self.nEntries += nEntries_

    data = dict()

    tree = uproot.open(root_file_name)['VarStats']
    for runId, ksum, ksum2, knEntries, kmin, kmax in zip(*tree.arrays(
            ['runId','%s_sum'%pname, '%s_sum2'%pname, '%s_nEntries'%pname, 
                '%s_min'%pname, '%s_max'%pname], outputtype=tuple)):

        if runId not in data:
            data[runId] = VarStats()

        data[runId].add(kmin, kmax, ksum, ksum2, knEntries)

    # make the return values
    keys = list(data.keys())
    keys.sort()

    #TODO: learn how to use with pandas; however, for now, return as numpy arrays
    # print(type(np.array([ data[k].sum / data[k].nEntries for k in keys ])));
    # print("bb")
    # print(len(keys))

    return  {
        'i'     : np.arange(len(keys)),
        'runId' : np.array(keys),
        'mean' : np.array([ data[k].sum / data[k].nEntries for k in keys ]),
        'min'  : np.array([ data[k].kmin for k in keys]),
        'max'  : np.array([ data[k].kmax for k in keys]),
        'n'    : np.array([ data[k].nEntries for k in keys]),
        'sum'  : np.array([ data[k].sum      for k in keys]),
        'sum2' : np.array([ data[k].sum2     for k in keys])
        };

if __name__ == '__main__':
    get_stats_one_param('maxpt', 'logs/C_P16.root')

