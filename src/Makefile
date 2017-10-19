CXXFILES = Controller.cpp Node.cpp Event.cpp

CXXFLAGS = -o simulator -I../include -I./ -std=c++11 -Wall
LIBS = -lpthread

all:
	g++ $(CXXFILES) $(CXXFLAGS) $(LIBS)
clean:
	rm -f simulator *.o
