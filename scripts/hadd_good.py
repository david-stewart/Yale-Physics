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

toname = '../../results/%s.root'%name 
if os.path.isfile(toname):
    exit ("file %s already exists"%toname)
else:
    call("hadd %s good_links/*.root"%toname,shell=True)
