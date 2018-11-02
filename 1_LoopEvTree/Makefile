count_events: src/count_events.cxx src/tree.h src/map_vals_per_line.h src/TriggerCount.h
	g++ --std=c++11 src/TriggerCount.h src/count_events.cxx src/tree.h src/map_vals_per_line.h -o bin/count_events `root-config --cflags --glibs` -lTreePlayer

run_index: src/map_vals_per_line.h src/run_index.cxx
	g++ --std=c++11 src/map_vals_per_line.h src/run_index.cxx -o bin/run_index `root-config --cflags --glibs` -lTreePlayer
