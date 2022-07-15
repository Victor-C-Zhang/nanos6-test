#NANOS6_LIBDIR = $(shell nanos6-info --runtime-path | awk '{ print $$3; }' | sed 's@/libnanos6-.*.so.*@@')
#NANOS6_INCDIR = $(shell dirname $(NANOS6_LIBDIR))/include
NANOS6_ROOTDIR = /home/victor/KICKSTARTER/tools
NANOS6_LIBDIR = $(NANOS6_ROOTDIR)/lib
NANOS6_INCDIR = $(NANOS6_ROOTDIR)/include


# Compilers
CC = gcc -I$(NANOS6_INCDIR)
CXX = g++ -I$(NANOS6_INCDIR)
MCC = /home/victor/KICKSTARTER/tools/bin/mcc --ompss-2
MCXX = /home/victor/KICKSTARTER/tools/bin/mcxx --ompss-2 -I$(NANOS6_INCDIR)

# Compiler flags
CFLAGS = -g2 -O2 -Wall
CXXFLAGS = -g2 -O2 -Wall

# The RPATH is only required when Nanos6 is not in LD_LIBRARY_PATH
RPATH = -Wl,-rpath $(NANOS6_LIBDIR)

# Libraries
LIBS = -L$(NANOS6_LIBDIR) $(RPATH) $(NANOS6_LIBDIR)/nanos6-library-mode.o -lnanos6 -lpthread -ldl -Wl,-z,lazy

RUN_PARAMETER = 4


BIN = \
	test1

all: $(BIN)

# Main code
main.o : main.cpp big_allocation.h hash_func.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

hash_func.o : hash_func.cpp hash_func.h
	$(CXX) $(CXXFLAGS) -c hash_func.cpp -o $@

# Nanos6 part
big_allocation.o :  big_allocation.cpp big_allocation.h hash_func.h
	$(MCXX) $(CXXFLAGS) -c  big_allocation.cpp -o $@

# Linking
test1: main.o hash_func.o big_allocation.o
	$(CXX) $^ -o $@ $(LIBS)


run: all
	mpirun -np $(RUN_PARAMETER) ./test1

clean:
	rm -f $(BIN) *.o

