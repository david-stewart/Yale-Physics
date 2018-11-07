directory contents:

[1] links to roots files in ../0_picoToEvTree/ root files:
    * `short.root` : as indicated, a short input file, good for making tests
    * `raw.root`   : the whole shabang (big input file)

[2] `scripts/`

[3] `Makefile` : make file for the various programs in `bin/`

[4] `bin/` : compiled programs results

[5] `src/` : source code for the compiled programs
    * `src/tree.h`       : the common header file to read the ROOT TTree file in the input files
    * [6] `count_events.cxx` 
      input: <nEvents> <log out file name> <input root file>
      output: `<count_events_log>` : a test file of how many triggered event in each run
    * [7] 



Tue Nov  6 15:20:19 EST 2018
Shorter and sweeter:

* ./bin/ : executables
* ./src/ : source code (for files in ./bin/)
* ./Makefile : makes files in ./bin/
* ./xml/ : files to run ./bin/ files with star-submit
* ./log/ : output files for some of ./bin/ files
* ./scrips/ : scripts

Specifically:
* ./scripts/clear.sh : clear out the .session.xml files and sced* files
* ./src/count_events.cxx 
    <- src/tree.h
    <- src/std_inputs.h
    <- src/TriggerCount.h : the structure that holds the numbers of triggers
    : made to look through events in ../0_picoToEvTree/root/ files and generate an output file
      of all the run data.
* ./src/
