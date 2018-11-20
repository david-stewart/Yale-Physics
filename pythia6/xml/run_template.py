#!/usr/bin/python
from subprocess import call

import random

for x in ((5,7,199), (5,7,201), (7,9,200), (9,11,100), (11,15,150), (15,25,249), (15,25, 251), (25,35, 150), (35,45,20), (45,55,20)):
    print random.randint(1000000000,9000000000)
    call (['star-submit-template','-template', 'xml/pythia6_template.xml',
        '-entities', 'min=%.1f,max=%.1f,nEvents=%i,seed=%i'%(x[0],x[1],x[2]*1000,
           random.randint(1000000000,9000000000))])
