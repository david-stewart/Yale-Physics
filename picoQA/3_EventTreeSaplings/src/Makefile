INC_LIBS = `root-config --cflags --glibs` -lTreePlayer

C_LIBS = `root-config --cflags` 
L_LIBS = `root-config --glibs` -lTreePlayer

CC = g++ --std=c++11
OBJDIR = obj

.SUFFIXES:

.SUFFIXES: .cxx .o

%.o : %.cxx %.h
	${CC} -c $*.cxx ${C_LIBS}

../bin/0_ExploratoryLoop: 0_ExploratoryLoop.o InputBase.o InputSapling.o EventTree.o
	${CC} -o $@ $^ ${INC_LIBS}

# Sapling: Sapling.o InputBase.o InputSapling.o EventTree.o
	# ${CC} -o $@ $^ ${INC_LIBS}

0_ExploratoryLoop.o: 0_ExploratoryLoop.cxx InputBase.o EventTree.o
	${CC} -c $^ ${C_LIBS}

Sapling.o: Sapling.cxx InputSapling.o 
	${CC} -c $^ ${C_LIBS}
