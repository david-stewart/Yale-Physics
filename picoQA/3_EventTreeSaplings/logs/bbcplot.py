import uproot as up
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors

def get_axis(th1d):
    """return x-axis of a th1d for plotting"""
    x_axis = np.linspace(th1d.low, th1d.high, th1d.numbins+1)
    return (x_axis[:-1]+x_axis[1:])/2

def norm(th1d):
    vals = th1d.allvalues[1:-1]
    errs = np.sqrt(vals)
    return vals / np.sum(vals), errs / np.sum(vals)


h16_001 = up.open('16.root')['h_bbcES_500001']
h16_202 = up.open('16.root')['h_bbcES_500202']
h16_206 = up.open('16.root')['h_bbcES_500206']
h16_215 = up.open('16.root')['h_bbcES_500215']

h17_001 = up.open('17.root')['h_bbcES_500001']
h17_202 = up.open('17.root')['h_bbcES_500202']
h17_206 = up.open('17.root')['h_bbcES_500206']
h17_215 = up.open('17.root')['h_bbcES_500215']

size = 4

plt, ax = plt.subplots()

ax.errorbar(get_axis(h16_001),*norm(h16_001), 
         linestyle='None',
         marker='o',
         color='black', 
         markersize=size,
         markeredgecolor='black',
         markerfacecolor='none',
         label='P16id %s %s'%(
             h16_001.name.decode('utf-8').split('_')[-1],
             h16_001.title.decode('utf-8'))
         )

ax.errorbar(get_axis(h16_202),*norm(h16_202),
         linestyle='None',
         marker='o',
         color='blue', 
         markersize=size,
         markeredgecolor='blue',
         markerfacecolor='none',
         label='P16id %s %s'%(
             h16_202.name.decode('utf-8').split('_')[-1],
             h16_202.title.decode('utf-8'))
         )

ax.errorbar(get_axis(h16_206),*norm(h16_206), 
         linestyle='None',
         marker='o',
         color='red', 
         markersize=size,
         markeredgecolor='red',
         markerfacecolor='none',
         label='P16id %s %s'%(
             h16_206.name.decode('utf-8').split('_')[-1],
             h16_206.title.decode('utf-8'))
         )

ax.errorbar(get_axis(h16_215),*norm(h16_215), 
         linestyle='None',
         marker='o',
         color='green', 
         markersize=size,
         markeredgecolor='green',
         markerfacecolor='none',
         label='P16id %s %s'%(
             h16_215.name.decode('utf-8').split('_')[-1],
             h16_215.title.decode('utf-8'))
         )


#---------------------------
#---------------------------
# 
#---------------------------
#---------------------------



ax.errorbar(get_axis(h17_001),*norm(h17_001), 
         linestyle='None',
         marker='x',
         color='grey', 
         markersize=size,
         markeredgecolor='gray',
         markerfacecolor='none',
         label='P17id %s %s'%(
             h17_001.name.decode('utf-8').split('_')[-1],
             h17_001.title.decode('utf-8'))
         )

ax.errorbar(get_axis(h17_202),*norm(h17_202), 
         linestyle='None',
         marker='x',
         color='cyan', 
         markersize=size,
         markeredgecolor='cyan',
         markerfacecolor='none',
         label='P17id %s %s'%(
             h17_202.name.decode('utf-8').split('_')[-1],
             h17_202.title.decode('utf-8'))
         )

ax.errorbar(get_axis(h17_206),*norm(h17_206), 
         linestyle='None',
         marker='x',
         color='magenta', 
         markersize=size,
         markeredgecolor='magenta',
         markerfacecolor='none',
         label='P17id %s %s'%(
             h17_206.name.decode('utf-8').split('_')[-1],
             h17_206.title.decode('utf-8'))
         )

ax.errorbar(get_axis(h17_215),*norm(h17_215), 
         linestyle='None',
         marker='x',
         color=colors.CSS4_COLORS['violet'], 
         markersize=size,
         markeredgecolor=colors.CSS4_COLORS['violet'],
         markerfacecolor='none',
         label='P17id %s %s'%(
             h17_215.name.decode('utf-8').split('_')[-1],
             h17_215.title.decode('utf-8'))
         )

ax.set_xlabel('BBC East Sum Inner Tiles')
ax.set_ylabel('$\mathrm{N/N_{total}}$')
ax.set_yscale('log')
ax.legend()
plt.show()


print('hi')
