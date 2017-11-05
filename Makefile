CXXFLAGS = -o simulator -I./include -std=c++11 -Wall
LIBS = -lpthread
VPATH = ./src/

all:
	g++ $(CXXFLAGS) $(VPATH)*.cpp $(LIBS)
clean:
	rm -f simulator *.o *.csv
