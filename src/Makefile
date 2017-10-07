CXXFILES = Controller.cpp 

CXXFLAGS = -o simulator -L../lib/ -I./ -std=c++11
LIBS = -l../lib/libPocoFoundation.so.49 -lpthread

all:
	g++ $(CXXFILES) $(CXXFLAGS) $(LIBS)
clean:
	rm -f simulator *.o
