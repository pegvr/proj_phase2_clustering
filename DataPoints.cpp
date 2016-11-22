#include "DataPoints.h"
using namespace std;




Hamming ** CreateHammingPoints(int counter, char *tmp)
{
    string line, temp;
    int i, j = 0;
    size_t pos;
    Hamming **hamming = new Hamming*[counter];              //Construct as many pointers to Hamming Classes as the num of points in given file
    ifstream inputfile(tmp);
    getline (inputfile,line);
    while ( getline (inputfile,line) )                         //Read file line by line
    {
        pos = line.find("\t");
        string temp1 = line.substr(0, pos);                 //Name of point: itemY 
        temp = line.substr(pos, line.size()-2);               
        hamming[j] = new Hamming(temp,temp1);     //Construct hamming class for point j
        j++;
    }
    return hamming;
}

Euclidean ** CreateEuclideanPoints(int counter, char *tmp)
{
    string line, temp;
    int i, j = 0;
    size_t pos;
    Euclidean **euclidean = new Euclidean*[counter];              //Construct as many pointers to euclidean Classes as the num of points in given file
    ifstream inputfile(tmp);
    getline (inputfile,line);
    while ( getline (inputfile,line) )                         //Read file line by line
    {
        pos = line.find("\t");
        string temp1 = line.substr(0, pos);                 //Name of point: itemY 
        temp = line.substr(pos, line.size()-2);               
        euclidean[j] = new Euclidean(temp,temp1);     //Construct euclidean class for point j
        j++;
    }
    return euclidean;
}

CosineSim ** CreateCosinePoints(int counter, char *tmp)
{
    string line, temp;
    int i, j = 0;
    size_t pos;
    CosineSim **cosine = new CosineSim*[counter];              //Construct as many pointers to euclidean Classes as the num of points in given file
    ifstream inputfile(tmp);
    getline (inputfile,line);
    while ( getline (inputfile,line) )                         //Read file line by line
    {
        pos = line.find("\t");
        string temp1 = line.substr(0, pos);                 //Name of point: itemY 
        temp = line.substr(pos, line.size()-2);               
        cosine[j] = new CosineSim(temp,temp1);     //Construct Cosine class for point j
        j++;
    }
    return cosine;
}

DistanceMatrix * CreateMatrixPoints(int counter, char *tmp, int k)
{
    string line, temp;
    int i, j = 0;
               
    DistanceMatrix *distancematrix = new DistanceMatrix(tmp,counter-1, k);     //Construct Cosine class for point j
    
    return distancematrix;
}