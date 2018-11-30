INC_LIBS = `root-config --cflags --glibs` -lTreePlayer
CC = g++ --std=c++11
OBJDIR = obj

.SUFFIXES:

.SUFFIXES: .cxx .o


%.o : %.cxx
	${CC} -c $< $^ ${INC_LIBS}


# vpath %.o obj
# VPATH = obj

# .cxx.o:; ${CC} -o obj/$*.o -c $*.cxx ${INC_LIBS}

main_obj = main.o tree.o thinking.o
main : ${main_obj} main.h
	${CC} -o ../bin/$@ ${main_obj}  ${INC_LIBS}

# main.o : main.cxx main.h thinking.h
	# ${CC} -c $< ${INC_LIBS}

# tree.o : tree.cxx tree.h
	# ${CC} -c tree.cxx ${INC_LIBS}
