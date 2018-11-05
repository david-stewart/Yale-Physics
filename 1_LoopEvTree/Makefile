INC_LIBS = `root-config --cflags --glibs` -lTreePlayer

FILES_count_events = src/count_events.cxx src/tree.h src/std_inputs.h  src/TriggerCount.h 
count_events: ${ FILES_count_events }
	g++ --std=c++11 ${FILES_count_events} -o bin/count_events ${INC_LIBS}

run_index: src/map_vals_per_line.h src/run_index.cxx
	g++ --std=c++11 src/map_vals_per_line.h src/run_index.cxx -o bin/run_index `root-config --cflags --glibs` -lTreePlayer
