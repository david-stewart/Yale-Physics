INC_LIBS = `root-config --cflags --glibs` -lTreePlayer
CC = g++ --std=c++11
OBJDIR = obj

.SUFFIXES:

.SUFFIXES: .cxx .o

%.o : %.cxx %.h
	${CC} -c $*.cxx ${INC_LIBS}


# test : OneVarStats.o test.cxx
# 	${CC} -o test test.cxx OneVarStats.o ${INC_LIBS}


# OneVarStats.o : OneVarStats.cxx
# 	${CC} -c OneVarStats.cxx ${INC_LIBS}



combine_logs_ofiles = OneVarStats.o MyInput.o InputBase.o CombineLogs.o TrigCount.o
../bin/combine_logs : ${combine_logs_ofiles} 
	${CC} -o $@ ${combine_logs_ofiles} ${INC_LIBS}

count_events_ofiles = count_events.o tree.o StdInp.o OneVarStats.o TrigCount.o
../bin/count_events : ${count_events_ofiles} MyLoop.h
	${CC} -o $@ ${count_events_ofiles}  ${INC_LIBS}




# test : MapFromText.o
# 	${CC} -o ../bin/test MapFromText.o test.cxx ${INC_LIBS}

StdInp.o : StdInp.cxx StdInp.h
	${CC} -c StdInp.cxx ${INC_LIBS}
