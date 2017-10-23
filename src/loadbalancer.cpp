#include "loadbalancer.h"


 //Controller(int threads, int nodes, int nSize);
LoadBalancer::LoadBalancer(LoadBalancerType type, int threads, int nodes, int nSize) 
	: controller(threads, nodes, nSize) {
	
	balancerType = type;
	numNodes = nodes;
}

//Create event and give it to the controller
void LoadBalancer::createEvent(int bytes, EventType eventType) {
	
	if (balancerType == MACHINE_LEARNING) {
		//make decision for nodeId based off ML information
		
	} else if (balancerType == BENCHMARK_RANDOM) {
		controller.addEvent(Event(bytes, getRandomNodeId(), eventType));
	} else {
		
		//who gives a hoot what we do in this case 
		
	}
}

//generate number between 0 and numNodes
int LoadBalancer::getRandomNodeId() {
	return rand() % numNodes;
}



// int main() {
// 	LoadBalancer lb(BENCHMARK_RANDOM, 1, 2, 1024);
// 	lb.createEvent(256, DISKREAD);
// 	return 1;
// }