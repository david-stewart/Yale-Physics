INC_LIBS = `root-config --cflags --glibs` -lTreePlayer
CC = g++ --std=c++11
OBJDIR = obj

.SUFFIXES:

.SUFFIXES: .cxx .o

%.o : %.cxx %.h
	${CC} -c $*.cxx ${INC_LIBS}



count_events_ofiles = count_events.o tree.o StdInp.o MinMaxProf.o 
# count_events_libs   = MyLoop.h MinMaxProf.h tree.h StdInp.h
../bin/count_events : ${count_events_ofiles} MyLoop.h
	${CC} -o ../bin/$@ ${count_events_ofiles}  ${INC_LIBS}

count_events.o : count_events.cxx MyLoop.h
	${CC} -c count_events.cxx ${INC_LIBS}
