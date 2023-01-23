CC=g++
CFLAGS=-std=c++17 -g
LIBPATH=./lib

all: main

main: lib sort
	$(CC) $(CFLAGS) -o sort sort.o -L$(LIBPATH) $(LIBPATH)/SortLib.a

lib: SortLib.a

SortLib.a: lib/*Sort.cpp
	cd $(LIBPATH) && $(CC) $(CFLAGS) -c *Sort.cpp && \
		ar rvs SortLib.a *Sort.o

sort: sort.cpp
	$(CC) $(CFLAGS) -I$(LIBPATH) -c sort.cpp

clean:
	rm -f sort sort.o $(LIBPATH)/SortLib.a $(LIBPATH)/*.o