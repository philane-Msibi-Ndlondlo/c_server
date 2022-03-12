compiler = gcc
include = include/*.h
sources = *.c
libs = 
flags = -o

all:
	$(compiler) $(sources) $(flags) a.out

clean:
	rm -rf a.out *.o
