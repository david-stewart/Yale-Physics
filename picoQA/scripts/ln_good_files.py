#!/usr/bin/python

# run this file from kate/root/[name]
from glob import glob
import subprocess
from subprocess import call
from os import path
from os import getcwd
import os

# ln each file in root/[name] that has an We END in out/[name]

name = getcwd().split('/')[-1]
print 'my name: %s'%name

if not os.path.isdir('good_links'):
    os.mkdir('good_links')
else:
    call ("rm good_links/*", shell=True)

nbad = 0
ngood = 0
for fname in glob("../../out/%s/*"%name):
    endline = subprocess.check_output(["tail","-n","1",fname])
    e_name = fname.split('/')[-1]
    if 'We END' in endline:
        call(['ln','%s.root'%e_name,'good_links/%s.root'%e_name])
        ngood += 1
    else:
        print '"We END" not found in ../out/%s: %s'%(name, e_name)
        nbad += 1

fout = open('good_links/readme.md','w')
fout.write("Total files:  %i\n"%(ngood + nbad))
fout.write("n files bad:  %i\n"%nbad)
fout.write("n files good: %i\n"%ngood)

print "Total files:  %i"%(ngood + nbad)
print "n files bad:  %i"%nbad
print "n files good: %i"%ngood

# if len(argv) == 1:
#     exit("error, need name of directory")

# name = argv[1]
# dname = "%s/good_ln"%name

# if path.isdir("
# print

# print 'hi'
