INC_LIBS = `root-config --cflags --glibs` -lTreePlayer

C_LIBS = `root-config --cflags` 
L_LIBS = `root-config --glibs` -lTreePlayer

CC = g++ --std=c++11
OBJDIR = obj

.SUFFIXES:

.SUFFIXES: .cxx .o

%.o : %.cxx %.h
	${CC} -c $*.cxx ${C_LIBS}

../bin/combine: combine.o InputCombine.o RunStats.o InputBase.o
	${CC} -o $@ $^ ${L_LIBS}

InputCombine.o: InputCombine.cxx InputCombine.h  RunStats.o InputBase.o
	${CC} -c $^ ${C_LIBS}

../bin/count: count.o InputCount.o RunStats.o tree.o InputBase.o # dict.cxx
	${CC} -o $@ $^ ${L_LIBS}



RunStats.o: RunStats.cxx RunStats.h #OneVar_root_dict.cxx
	# echo "hi"
	# echo ${CC} -c $^ ${INC_LIBS}
	${CC} -c $^ ${C_LIBS}

InputCount.o: InputCount.cxx InputCount.h RunStats.o InputBase.o tree.o
	${CC} -c $^ ${C_LIBS}

count.o: count.cxx count.h InputCount.o RunStats.o tree.o # dict.cxx
	${CC} -c $^ ${C_LIBS}


count_events_ofiles = count_events.o tree.o StdInp.o TrigCount.o
../bin/count_events : ${count_events_ofiles} MyLoop.h
	${CC} -o $@ ${count_events_ofiles}  ${INC_LIBS}


combine_logs_ofiles = MyInput.o InputBase.o CombineLogs.o TrigCount.o
../bin/combine_logs : ${combine_logs_ofiles} 
	${CC} -o $@ ${combine_logs_ofiles} ${INC_LIBS}


# test : MapFromText.o
# 	${CC} -o ../bin/test MapFromText.o test.cxx ${INC_LIBS}

StdInp.o : StdInp.cxx StdInp.h
	${CC} -c StdInp.cxx ${INC_LIBS}
