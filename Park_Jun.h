/* 
 * File:   Park_Jun.h
 * Author: angelique
 *
 * Created on November 21, 2016, 8:26 PM
 */

#ifndef PARK_JUN_H
#define	PARK_JUN_H
#include "Cluster.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>

using namespace std;
void ParkJun(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance);


#endif	/* PARK_JUN_H */

