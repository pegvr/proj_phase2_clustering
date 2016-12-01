/* 
 * File:   Clarans.h
 * Author: angelique
 *
 * Created on November 23, 2016, 7:37 PM
 */

#ifndef CLARANS_H
#define	CLARANS_H
#include "Cluster.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include <math.h>
#include "Distances.h"
#include "randomfunc.h"
#include "PAM.h"
#include "LSH.h"

void Clarans(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF, int Q, int choice, int NumofHashFUnctions, int L);



#endif	/* CLARANS_H */

