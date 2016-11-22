/* 
 * File:   PAM.h
 * Author: angelique
 *
 * Created on November 22, 2016, 5:18 PM
 */

#ifndef PAM_H
#define	PAM_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "Cluster.h"

using namespace std;

//template <typename type> 
void PAM(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance,int * objectivefunction, float * ObjectiveFunctionF);



#endif	/* PAM_H */

