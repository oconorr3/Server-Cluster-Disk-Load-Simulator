#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iterator>

/**
 * Best fit for a load balancer
 */

int main() {
    // Find all permutations given a set of requests
    PickleData data = itemAtIndex(data_file, num);
    int numEvents = data.size;
    bestEventPerm = *array of same size as data*
    
    float bestVariance = 0;
    int start_comparison = 1;
    
    int numNodes = controller.getNumNodes();
    int currentNodePerm[numEvents];
    int bestNodePerm[numEvents];
    int zeroes[numEvents];
    float curVariance;
    
    do {
        do {
            for (int i; i < numEvents; i++) {
                controller.addEvent(Event(data[i]['size'], currentNodePerm[i], data[i]['ioType']))
            }
            curVariance = controller.getVariance;
            if (curVariance < bestVariance || start_comparison) {
                bestVariance = curVariance;
                bestEventPerm = data;
                bestNodePerm = currentNodePerm;
                start_comparison = 0;
            }
        } while (std::next_permutation(data, data+numEvents));
        nextPermWithRepetitions(currentNodePerm, numNodes);
    } while (!arrayEquals(currentNodePerm, zeroes));
}

/**
 * Calculate the population variance of a load
 */
float population_variance(float load[]) {
    int size = sizeof(load);
    float variance = 0;
    float mean = 0;
    int i;
    for (i = 0; i < size; i++) {
        mean += load[i];
    }
    mean /= size;
    int j;
    for (j = 0; j < size; j++) {
        variance += pow((load[j] - mean), 2);
    }
    variance *= (1/size);
    return variance;
}

int nextPermWithRepetitions(int perm[], int numOptions) {
	bool finished = false;
	int i = 0;
	while(!finished) {
		perm[i] = (perm[i] + 1) % numOptions;
		if (perm[i] != 0) {
            finished = true;
        }
		i++;
    }
    return 1;
}

bool arrayEquals(int first[], int second[]) {
    int i;
    if (sizeof(first) != sizeof(second)) {
        return false;
    }
    for (int i = 0; i < sizeof(first); i++) {
        if (first[i] != second[i]) {
            return false;
        }
    }
    return true;
}