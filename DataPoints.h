/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef DATAPOINTS_H
#define	DATAPOINTS_H
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "../proj1.3/Hamming.h"
#include "../proj1.3/CosineSim.h"
#include "../proj1.3/DistanceMatrix.h"
#include "../proj1.3/Euclidean.h"

using namespace std;

Hamming ** CreateHammingPoints(int counter, char *tmp);
Euclidean ** CreateEuclideanPoints(int counter, char *tmp);
CosineSim ** CreateCosinePoints(int counter, char *tmp);
DistanceMatrix * CreateMatrixPoints(int counter, char *tmp, int k);

#endif	/* DATAPOINTS_H */

