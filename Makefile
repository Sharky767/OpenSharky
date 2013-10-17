CC=i586-mingw32msvc-g++
CFLAGS=-std=c++0x -Wall -Wextra -mthreads -mwindows -O2
LFLAGS=-static-libgcc -static-libstdc++ -Wall -Wextra
OBJS=obj/GLBase.o obj/main.o
SRC=src/GLBase.cpp src/main.cpp
INC=src/GLBase.h

bin/GLBase.exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o bin/GLBase.exe

obj/GLBase.o: src/GLBase.cpp src/GLBase.h
	$(CC) $(CFLAGS) -c src/GLBase.cpp -o obj/GLBase.o

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/main.o


clean:
	$(RM) obj/*.o *~ bin/GLBase.exe
	

