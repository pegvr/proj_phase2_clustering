#include "Cluster.h"


Cluster::Cluster() 
{
    
}

Cluster::Cluster(const Cluster& orig) 
{
    return;
}

Cluster::~Cluster() 
{
    
}

ClusterH :: ClusterH(Hamming *hamming)
{
    centroid = hamming->getId();
    
}

ClusterE :: ClusterE(Euclidean *euclidean)
{
    centroid = euclidean->getId();
}

ClusterC :: ClusterC(CosineSim *cosine)
{
    centroid = cosine->getId();
}

ClusterD::ClusterD(int* row)
{
    centroid = row;
}


void ClusterH :: InsertPointH(Hamming *point, int dist)
{
    points.push_back(point);
    distance.push_back(dist);
    
}

void ClusterE :: InsertPointE(Euclidean *point, int dist)
{
    points.push_back(point);
    distance.push_back(dist);
}

void ClusterC :: InsertPointC(CosineSim *point, int dist)
{
    points.push_back(point);
    distance.push_back(dist);
}

void ClusterD::InsertPointD(int* point, int dist)
{
    points.push_back(point);
}

void Cluster:: PrintCluster()
{
    cout<< "here" << endl;
}

void ClusterH:: PrintCluster()
{
    cout << "point  " << points.size() << endl;
    /*for(int i = 0; i < points.size(); i++)
    {
        cout << "point  " << i << " =    " << points[i]->getId() << endl;
    }*/
}

void ClusterC:: PrintCluster()
{
    for(int i = 0; i < points.size(); i++)
    {
        cout << "point  " << i << " =    " << points[i]->getId() << endl;
    }
}

void ClusterD:: PrintCluster()
{
    for(int i = 0; i < points.size(); i++)
    {
        cout << "point  " << i << " =    " << points[i] << endl;
    }
}

void ClusterE:: PrintCluster()
{
    for(int i = 0; i < points.size(); i++)
    {
        cout << "point  " << i << " =    " << points[i]->getId() << endl;
    }
}

