#ifndef K_MEDOIDS_H
#define	K_MEDOIDS_H
#include "Cluster.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

void k_medoidspp(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance);


#endif	/* K_MEDOIDS_H */

