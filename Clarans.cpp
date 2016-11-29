#include "Clarans.h"

void Clarans(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF, int Q, int choice, int NumofHashFUnctions, int L)
{
    int i, j, t, z, dist, OF[k],min_OF[k] , medoid[k], min_k[k];
    float OFF[k], min_OFF[k], distf;
    for(int s = 0; s < 2; s++ )
    {
        if (choice == 6)       //Ypu chose PAM Assignment
        {
            for (i = 0; i < k; i++) objectivefunction[i] = 0;
            for (i = 0; i < k; i++) ObjectiveFunctionF[i] = 0;
            if(method == "@metric_space hamming" || method == "@metric_space matrix")                    
            {
                if(s == 0) PAM(cluster, k, N, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);
                else  PAM_Update(cluster, k, N, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);    
                for (i = 0; i < k; i++) cout << objectivefunction[i] << endl;
            }
            else
            {
                if(s == 0) PAM(cluster, k, N, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);
                else  PAM_Update(cluster, k, N, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);                        
                for (i = 0; i < k; i++) cout << ObjectiveFunctionF[i] << endl;
            }
        }
        else        //you chose LSH Assignment
        {
            if(s == 0) LSH(cluster,  k,  N,  method, hamming, cosine, euclidean, distance,  NumofHashFUnctions,  L, 4);
            else LSH(cluster,  k,  N,  method, hamming, cosine, euclidean, distance,  NumofHashFUnctions,  L, choice);
            for ( i = 0; i < k; i++)    //For every cluster compute each objective function
            {
                for(j = 0; j < cluster[i]->GetSize(); j++)
                {                   
                    if (method == "@metric_space hamming")
                    {
                        dist = DistanceHamming(cluster[i]->getCentroid(), cluster[i]->GetPointH(j)->getId());

                    }                
                    else if (method == "@metric euclidean")
                    {
                        distf = DistanceEuclidean(cluster[i]->getCentroid(), cluster[i]->GetPointE(j)->getId());
                        //cout << "mpeka" << endl;
                    }
                    else if (method == "@metric cosine")
                    {
                        distf = DistanceEuclidean(cluster[i]->getCentroid(), cluster[i]->GetPointC(j)->getId());
                    }
                    else
                    {   
                        int *row = distance->getRow(j);
                        dist = row[j];
                    }  
 
                    objectivefunction[i] += dist;
                    ObjectiveFunctionF[i] += distf;
                }
            }
        }
        for (i = 0; i < k; i++) OF[i] = 0;
        for (i = 0; i < k; i++) OFF[i] = 0;
        
        for (i = 0; i < Q; i++)         //For every pair (m,t)
        {
            int x = (rand() / (RAND_MAX + 1.0))*k*N ;   
            int m = mod(x, k);
            int T = x / k;

            int min_dist = 100000;
            float min_distf = 100000.0;
            for (j = 0; j < k; j++)         //Check where T point belongs
            {
                if (method == "@metric_space hamming")
                {
                    dist = DistanceHamming(cluster[j]->getCentroid(), hamming[T]->getId());

                }                
                else if (method == "@metric euclidean")
                {
                    distf = DistanceEuclidean(euclidean[T]->getId(), cluster[j]->getCentroid());

                }
                else if (method == "@metric cosine")
                {
                    distf = DistanceEuclidean(cosine[T]->getId(), cluster[j]->getCentroid());
                }
                else
                {   
                    int *row = distance->getRow(j);
                    dist = row[j];
                }  
                if ((dist < min_dist && dist != 0) || (distf < min_distf && distf != 0))
                {
                    min_dist = dist;
                    min_distf = distf;
                    min_k[m] = j;
                }  

            }
            
            for (t = 0; t < cluster[min_k[m]]->GetSize(); t++)  //Check position of T in cluster
            {
                if (method == "@metric_space hamming")
                {
                    if (cluster[min_k[m]]->GetPointH(t)->getId() == hamming[T]->getId())
                    {
                        T = t;
                        break;
                    }

                }                
                else if (method == "@metric euclidean")
                {
                    if (cluster[min_k[m]]->GetPointE(t)->getId() == euclidean[T]->getId())
                    {
                        T = t;
                        break;
                    }

                }
                else if (method == "@metric cosine")
                {

                    if (cluster[min_k[m]]->GetPointC(t)->getId() == cosine[T]->getId())
                    {
                        T = t;
                        break;
                    }
                }
                else
                {   
                    if (cluster[min_k[m]]->GetPointD(t) == distance[T].getRow(j))
                    {
                        T = t;
                        break;
                    }
                }  
            }

            min_OF[m] = objectivefunction[m];
            min_OFF[m] = ObjectiveFunctionF[m];
            int newdistances[cluster[m]->GetSize()];
            float newdistancesf[cluster[m]->GetSize()];
            OF[m] = 0;
            OFF[m] = 0;
            for (t = 0; t < cluster[m]->GetSize(); t++)      //Compute objective function of new possible centroid t in cluster m
            {
                if (method == "@metric_space hamming")
                {
                    if(T < cluster[min_k[m]]->GetSize()){
                        dist = DistanceHamming(cluster[min_k[m]]->GetPointH(T)->getId(), cluster[m]->GetPointH(t)->getId());
                        newdistances[t] = dist;    
                    } 
                }
                else if (method == "@metric euclidean")
                {
                    distf = DistanceEuclidean(cluster[min_k[m]]->GetPointE(T)->getId(), cluster[m]->GetPointE(t)->getId());
                    newdistancesf[t] = distf;  
                }
                else if (method == "@metric cosine")
                {        
                    distf = DistanceEuclidean(cluster[min_k[m]]->GetPointC(T)->getId(), cluster[m]->GetPointC(t)->getId());                    
                    newdistancesf[t] = distf;
                }
                else
                {   
                    int *row = distance->getRow(t);
                    dist = row[t];
                    newdistances[t] = dist;
                }  
                if(T < cluster[min_k[m]]->GetSize()){
                OF[m] += dist;
                OFF[m] += distf;}
            }
            /*If objective function of t is better than m we need to swap centroid*/
            if (OF[m] < min_OF[m] || OFF[m] < min_OFF[m])
            {
                min_OF[m] = OF[m];
                min_OFF[m] = OFF[m];
                medoid[m] = T;

            }          
        }

        for (i = 0; i < k; i++)   //For every cluster check if we need to do the swap of centroid
        {
            if (min_OF[i] < objectivefunction[i] || min_OFF[i] < ObjectiveFunctionF[i])
            {
                if (method == "@metric_space hamming")
                    cluster[i]->UpdateCentroid(cluster[min_k[i]]->GetPointH(medoid[i])->getId());
                else if (method == "@metric euclidean")
                    cluster[i]->UpdateCentroid(cluster[min_k[i]]->GetPointE(medoid[i])->getId());
                else if (method == "@metric cosine")
                    cluster[i]->UpdateCentroid(cluster[min_k[i]]->GetPointC(medoid[i])->getId());
                else
                    cluster[i]->UpdateCentroid(distance->getName());
                objectivefunction[i] = min_OF[i];
                ObjectiveFunctionF[i] = min_OFF[i];

                if (choice == 6) PAM_Update(cluster, k, N, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);
                else LSH(cluster,  k,  N,  method, hamming, cosine, euclidean, distance,  NumofHashFUnctions,  L, choice);
            } 
        }
        
    }
}
