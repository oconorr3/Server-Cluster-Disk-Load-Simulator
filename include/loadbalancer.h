#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <stdio.h>     
#include <stdlib.h>

#include "event.h"
#include "controller.h"

void seedRandomNumbers();

int generateNodeID(int numNodes);

#endif