#ifndef LSH_H
#define LSH_H

#include <vector>
#include <cstdlib>
#include <string>
#include <time.h>
#include "Cluster.h"
#include "Distances.h"
#include "../proj1.3/Hamming.h"
#include "../proj1.3/CosineSim.h"
#include "../proj1.3/DistanceMatrix.h"
#include "../proj1.3/Euclidean.h"
#include "../proj1.3/NeighbourSearch.h"
#include "../proj1.3/Hashtable.h"
#endif /* LSH_H */

void LSH(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int NumofHashFUnctions, int L, int choice);

