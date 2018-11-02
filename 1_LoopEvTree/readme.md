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
