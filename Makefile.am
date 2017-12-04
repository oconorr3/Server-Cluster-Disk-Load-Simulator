bin_PROGRAMS = simulator
simulator_SOURCES = src/controller.cpp src/databank.cpp src/disknode.cpp src/event.cpp \
src/loadbalancer.cpp src/pickleloader.cpp src/pyutils.cpp src/randomlb.cpp src/roundrobinlb.cpp \
src/simulator.cpp src/sklearn.cpp src/variance_fit.cpp
simulator_LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lpthread -lboost_python -lpython2.7 -pthread
simulator_CXXFLAGS = -I./include -I/usr/include/ -I/usr/include/python2.7 -std=c++11 -Wall
