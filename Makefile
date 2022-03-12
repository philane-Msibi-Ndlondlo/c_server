compiler = gcc
include = include/*.h
sources = *.c
libs = 
flags = -ggdb3 -o

all:
	$(compiler) $(sources) $(flags) a.out

clean:
	rm -rf a.out *.o
