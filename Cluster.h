#ifndef CLUSTER_H
#define	CLUSTER_H
#include <vector>
#include <cstdlib>
#include <string>
#include "../proj1.3/Hamming.h"
#include "../proj1.3/CosineSim.h"
#include "../proj1.3/DistanceMatrix.h"
#include "../proj1.3/Euclidean.h"



class Cluster {
public:
    Cluster();
    Cluster(const Cluster& orig);
    virtual string getCentroid() {return centroid;} ;
    virtual int * getCentroidD() {} ;
    virtual ~Cluster();
private:
    string centroid;
};

class ClusterH : public Cluster{
public:
    ClusterH(Hamming *hamming);
    ClusterH(const ClusterH& orig);
    string getCentroid() {return centroid;} ;
    virtual ~ClusterH(){};
private:
    string centroid;
    vector <Hamming> points;
    vector <Hamming> distance;
};

class ClusterE : public Cluster{
public:
    ClusterE(Euclidean *euclidean);
    ClusterE(const ClusterE& orig);
    string getCentroid() {return centroid;} ;
    virtual ~ClusterE(){};
private:
    string centroid;
    vector <Euclidean> points;
};

class ClusterC : public Cluster{
public:
    ClusterC(CosineSim *cosine);
    ClusterC(const ClusterC& orig);
    string getCentroid() {return centroid;} ;
    virtual ~ClusterC(){};
private:
    string centroid;
    vector <CosineSim> points;
};

class ClusterD : public Cluster{
public:
    ClusterD(int *row);
    ClusterD(const Cluster& orig);
    int * getCentroidD() {return centroid;} ;
    virtual ~ClusterD(){};
private:
    int * centroid;
    vector <DistanceMatrix> points;
};

#endif	/* CLUSTER_H */