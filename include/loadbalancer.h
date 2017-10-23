#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <stdio.h>     
#include <stdlib.h>

#include "event.h"
#include "controller.h"


//Enum for balancing type ... add types for new benchmark algorithms
enum LoadBalancerType {
	BENCHMARK_RANDOM,
	MACHINE_LEARNING
};

class LoadBalancer {
	public: 
		/*CONSTRUCTORS*/
		LoadBalancer(LoadBalancerType type, int threads, int nodes, int nSize);
		
		void createEvent(int bytes, EventType eventType);
		
	private:
		Controller controller;			//controller for the nodes
		LoadBalancerType balancerType;
		int numNodes;                   // Number of nodes to be simulated by the controller
		
		int getRandomNodeId();
};

#endif