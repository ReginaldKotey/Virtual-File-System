REKAS= g++
REKASFLAGS= -Wall

all:run

run: main.o vfs.o
	$(REKAS) $(REKASFLAGS) main.o vfs.o -o run

main.o: main.cpp 
	$(REKAS) $(REKASFLAGS) -c main.cpp -o main.o

vfs.o: vfs.cpp vfs.hpp inode.hpp stack.hpp vector.hpp queue.hpp
	$(REKAS) $(REKASFLAGS) -c vfs.cpp -o vfs.o

clean:
	del -f *.o *.exe run
