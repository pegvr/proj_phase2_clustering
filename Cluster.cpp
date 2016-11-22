
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