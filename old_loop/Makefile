INC_LIBS = `root-config --cflags --glibs` -lTreePlayer
CC = g++ --std=c++11


FILES_count_events = src/count_events.cxx src/tree.h src/std_inputs.h  src/TriggerCount.h src/MinMaxMeanVar.h src/MinMax.h src/tree.cxx
count_events: ${ FILES_count_events }
	${CC} ${FILES_count_events} -o bin/count_events ${INC_LIBS}

FILES_run_index = src/run_index.cxx src/map_vals_per_line.h
run_index: ${FILES_run_index}
	${CC} ${FILES_run_index}    -o bin/run_index    ${INC_LIBS}
