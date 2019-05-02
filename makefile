CC = g++ -std=c++11
CXXFLAGS = -Wall -g

all:ZooTycoon

ZooTycoon: zooTycoon.o animal.o monkey.o otter.o sloth.o zoo.o
	$(CC) $(CXXFLAGS) -o ZooTycoon zooTycoon.o animal.o monkey.o otter.o sloth.o zoo.o

zooTycoon.o: animal.hpp monkey.hpp sloth.hpp otter.hpp zoo.hpp animal.cpp monkey.cpp otter.cpp sloth.cpp zooTycoon.cpp
	$(CC) $(CXXFLAGS) -c animal.cpp monkey.cpp otter.cpp sloth.cpp zoo.cpp zooTycoon.cpp

animal.o: animal.cpp animal.hpp
	$(CC) $(CXXFLAGS) -c animal.cpp

monkey.o: monkey.cpp monkey.hpp animal.hpp
	$(CC) $(CXXFLAGS) -c monkey.cpp animal.cpp

otter.o: otter.cpp otter.hpp animal.hpp
	$(CC) $(CXXFLAGS) -c otter.cpp animal.cpp

sloth.o: sloth.cpp sloth.hpp animal.hpp
	$(CC) $(CXXFLAGS) -c sloth.cpp animal.cpp

zoo.o: zoo.cpp zoo.hpp
	$(CC) $(CXXFLAGS) -c zoo.cpp

clean:
	rm -rf *.o
