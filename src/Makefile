CXXFILES = Controller.cpp Node.cpp

CXXFLAGS = -o simulator -I../include -I./ -std=c++11
LIBS = -lpthread

all:
	g++ $(CXXFILES) $(CXXFLAGS) $(LIBS)
clean:
	rm -f simulator *.o
