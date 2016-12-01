#ifndef CLARA_H
#define CLARA_H
#include "Cluster.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <math.h>
#include "Distances.h"
#include "PAM.h"
#include "randomfunc.h"

void CLARA(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF);


#endif /* CLARA_H */

