INC_LIBS = `root-config --cflags --glibs` -lTreePlayer

C_LIBS = `root-config --cflags` 
L_LIBS = `root-config --glibs` -lTreePlayer

CC = g++ --std=c++11
OBJDIR = obj

.SUFFIXES:

.SUFFIXES: .cxx .o

%.o : %.cxx %.h
	${CC} -c $*.cxx ${C_LIBS}

Sapling: Sapling.o InputBase.o InputSapling.o EventTree.o
	${CC} -o $@ $^ ${INC_LIBS}

InputSapling.o: InputSapling.cxx InputBase.o EventTree.o
	${CC} -c $^ ${C_LIBS}

Sapling.o: Sapling.cxx InputSapling.o 
	${CC} -c $^ ${C_LIBS}
