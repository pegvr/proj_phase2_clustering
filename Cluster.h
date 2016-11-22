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
    virtual void InsertPointE(Euclidean *point, int dist){};
    virtual void InsertPointC(CosineSim *point, int dist){};
    virtual void InsertPointD(int *point, int dist){};
    virtual void InsertPointH(Hamming *point, int dist){};
    virtual void PrintCluster();
    virtual ~Cluster();
private:   
    string centroid;
    //vector <> points;
};

class ClusterH : public Cluster{
public:
    ClusterH(Hamming *hamming);
    ClusterH(const ClusterH& orig);
    string getCentroid() {return centroid;} ;
    void InsertPointH(Hamming *point, int dist);
    void PrintCluster();
    virtual ~ClusterH(){};
private:
    string centroid;
    vector <Hamming *> points;
    vector <int> distance;
};

class ClusterE : public Cluster{
public:
    ClusterE(Euclidean *euclidean);
    ClusterE(const ClusterE& orig);
    string getCentroid() {return centroid;} ;
    void InsertPointE(Euclidean *point, int dist);
    void PrintCluster();
    virtual ~ClusterE(){};
private:
    string centroid;
    vector <Euclidean*> points;
    vector <int> distance;
};

class ClusterC : public Cluster{
public:
    ClusterC(CosineSim *cosine);
    ClusterC(const ClusterC& orig);
    string getCentroid() {return centroid;} ;
    void InsertPointC(CosineSim *point, int dist);
    void PrintCluster();
    virtual ~ClusterC(){};
private:
    string centroid;
    vector <CosineSim*> points;
    vector <int> distance;
};

class ClusterD : public Cluster{
public:
    ClusterD(int *row);
    ClusterD(const Cluster& orig);
    int * getCentroidD() {return centroid;} ;
    void InsertPointD(int *point, int dist);
    void PrintCluster();
    virtual ~ClusterD(){};
private:
    int * centroid;
    vector <int*> points;
};

#endif	/* CLUSTER_H */
