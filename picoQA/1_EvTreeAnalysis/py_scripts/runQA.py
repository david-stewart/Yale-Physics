#!/usr/bin/python
import matplotlib.pyplot as plt
import numpy as np
from  combine import get_stats_one_param
from sys import exit, argv
# from plot_to_numpy import read_data_from_table as read_data
# from sys import argv


# make a generic plot
def pass_fail_plot(title, x, y, y_title, filter_pass, prior_pass, log=False):
    """ plot x, y along with fails to the prior pass:

    data: contains x and y values and runIds
    x: x values to plot
    y: y values to plot
    filter_pass: TF array which is T where y passes

    plot whole dots for x-pass, y-pass
    plot empty dots for x-fail, y-fail
    cross out, with magenta x's, where ~prior_pass
    update prior pass w/ ~fn_pass
    """

    fix, ax = plt.subplots(1,1)
    i_buffer = 10;
    ax.set_title(title)
    ax.set_xlabel(r'$\mathrm{index}$')
    ax.set_ylabel(y_title)
    xrange_ = (x.min()-i_buffer, x.max()+i_buffer)
    ax.set_xlim(xrange_)

    ax.plot(x[ filter_pass], y[ filter_pass], 'o', marker="o", markerfacecolor='black', markersize=5, markeredgecolor='black', label=r'pass criteria')
    ax.plot(x[~filter_pass], y[~filter_pass], 'o', marker="o", markerfacecolor='none',  markeredgecolor='red',                 label=r'fail criteria')
    if log:
        ax.set_yscale("log", nonposy='clip')

    if (sum(prior_pass == False) > 0):
        ax.plot(x[~prior_pass], y[~prior_pass], 'o', marker="x", markerfacecolor='magenta',  
                                markeredgewidth=1, markeredgecolor='magenta', markersize=7,
                                label=r'Runs which failed prior criteria')

    ax.legend()
    plt.show()

    return prior_pass & filter_pass
    prior_pass = prior_pass & filter_pass

if (len(argv)<3):
    print("Required arguments: [in-file-name] [figure-prefix]")
    exit(1)

file_in = argv[1]
prefix  = argv[2]

# to do:
#  0. make cut on nEvents
#  1. make cut based on runId
#     make plot
#     update bad_runs[]
#  2. make plot on time showing events cut
#  3. make plot on zdcX
#     add cuts (if necessary)
#  4. make plot on <x>, <y>, <z>
#  5. make plot on etaTrkMean
#  6. make plot on phiTrkMean


# fix, ax = plt.subplots(1,1)

# name = 'Number\ of\  Events'
# i_buffer = 10;
# ax.set_xlabel(r'$\mathrm{index}$')
# ax.set_ylabel(r'$\mathrm{%s}$'%name)

# cuts
data = get_stats_one_param('refmult', file_in)
good_runs_TF = data['n'][1:] != np.nan

###-------------------------------------------
### calculate small runs
###-------------------------------------------
x = data['i'][1:]
y = data['n'][1:]
good_runs_TF = pass_fail_plot(r"Run's cut for less than 10k events", x, y, r'number of events', y > 10000, good_runs_TF, log=True)
plt.savefig('%s_nevents.pdf'%prefix)

###-------------------------------------------
### calculate bad runs from refmult
###-------------------------------------------
# y = data['mean'][1:]
y = data['mean'][1:]
y_prior = y[good_runs_TF]
n_sigma = 2
sig_lo = y_prior.mean()-n_sigma*y_prior.std();
sig_hi = y_prior.mean()+n_sigma*y_prior.std();
test = (y>sig_lo) & (y<sig_hi)
good_runs_TF = pass_fail_plot(
        r"Run's cut for $|\langle\mathrm{refMult}\rangle-\langle\langle\mathrm{refmult}\rangle\rangle|>2\sigma_{\langle\mathrm{refmult}\rangle}$",
        x, y, r'$\mathrm{\langle{refmult}\rangle}$', (y>sig_lo) & (y<sig_hi), good_runs_TF, log=False)
plt.savefig('%s_refmult.pdf'%prefix)

###-------------------------------------------
### calculate bad runs from zdcX
###-------------------------------------------
data = get_stats_one_param('zdcX', file_in)
y = data['mean'][1:]
y_prior = y[good_runs_TF]
n_sigma = 2
sig_lo = y_prior.mean()-n_sigma*y_prior.std();
sig_hi = y_prior.mean()+n_sigma*y_prior.std();
test = (y>sig_lo) & (y<sig_hi)
good_runs_TF = pass_fail_plot(
        r"Run's cut for $|\langle\mathrm{zdcX}\rangle-\langle\langle\mathrm{zdcX}\rangle\rangle|>2\sigma_{\langle\mathrm{zdcX}\rangle}$",
        x, y, r'$\mathrm{\langle{zdcX}\rangle}$', (y>sig_lo) & (y<sig_hi), good_runs_TF, log=False)
plt.savefig('%s_zdcX.pdf'%prefix)


#---------------------------
#   BBCx_East results #
#---------------------------

data = get_stats_one_param('bbcAdcES', file_in)
y = data['mean'][1:]
y_pass= y > 11500
good_runs_TF = pass_fail_plot(r"Runs cut for $\langle\Sigma\mathrm{BBC_{AdcES}}\rangle<11500$",
        x, y, r'$\langle\Sigma\mathrm{BBC_{AdcES}}\rangle$', y_pass, good_runs_TF, log=False)
plt.savefig('%s_BbcES.pdf'%prefix)

##------------------
## Vz cut
##------------------

data = get_stats_one_param('zPV',file_in)
y = data['mean'][1:]
y_pass= abs(y)<10
good_runs_TF = pass_fail_plot(r"Runs cut for $|\langle\mathrm{PV_Z}\rangle|<10\mathrm{(cm)}$",
        x, y, r'$|\langle\mathrm{PV_z}\rangle|\mathrm{(cm)}$', y_pass, good_runs_TF, log=False)
plt.savefig('%s_Vz.pdf'%prefix)

#---------------------------
# write out the bad run list
#---------------------------
with open('%s_bad_runs.list'%prefix,'w') as file:
    for x in data['runId'][1:][~good_runs_TF]:
        file.write('%i\n'%x)

with open('%s_good_runs.list'%prefix,'w') as file:
    for x in data['runId'][1:][good_runs_TF]:
        file.write('%i\n'%x)
