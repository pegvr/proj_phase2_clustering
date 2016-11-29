#include "CLARA.h"

void CLARA(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF)
{
    int numb_of_it = 5;
    int n = 40 + 2*k , i, OF,  dist,  medoid[k], min_OF[k], min_k[k];
    float min_OFF[k], OFF, distf;

    for(int s = 0; s < numb_of_it; s++ )
    {
        for (i = 0; i < k; i++) objectivefunction[i] = 0;
        for (i = 0; i < k; i++) ObjectiveFunctionF[i] = 0;
        if(method == "@metric_space hamming")
        {
            for (int t = 0; t < n; t++  )
            {
                int x = (rand() / (RAND_MAX + 1.0))*N ;
                hamming[t] = hamming[x]; 
            }
        }
        else if(method == "@metric cosine")
        {
            for (int t=0; t < n; t++  )
            {
                int x = (rand() / (RAND_MAX + 1.0))*N ;
                cosine[t] = cosine[x]; 
            }
        }
        else if(method == "@metric_space matrix")
           {
               for (int t=0; t < n; t++  )
               {
                    int x = (rand() / (RAND_MAX + 1.0))*N ;
                    distance[t] =distance[x]; 
               }
           }
        else
           {
               for (int t = 0; t < n; t++  )
               {
                    int x = (rand() / (RAND_MAX + 1.0))*N ;
                    euclidean[t] =euclidean[x]; 
               }
           }

           /*Initialization*/
        for( int i = 0; i < k; i++) //for every cluster
        {
            int rand_num = (rand() / (RAND_MAX + 1.0))* n;
            if (method == "@metric_space hamming")
                cluster[i] = new ClusterH(hamming[rand_num]);
            else if (method == "@metric euclidean")
                cluster[i] = new ClusterE(euclidean[rand_num]);
            else if (method == "@metric cosine")
                cluster[i] = new ClusterC(cosine[rand_num]);
            else
                cluster[i] = new ClusterD(distance->getRow(rand_num)); 
        }
       
            /*Assign - Update*/
        if(method == "@metric_space hamming" || method == "@metric_space matrix")                    
            if(s == 0) PAM(cluster, k, n, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);
        else
            if(s == 0) PAM(cluster, k, n, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);
           

            for ( i = 0; i < k; i++)
            {
                min_OF[i] = objectivefunction[i];
                min_OFF[i] = ObjectiveFunctionF[i];
                for (int t = 0; t < n; t++)         
                {
                    OF = 0;
                    OFF = 0;
                    for (int j = 0; j < cluster[i]->GetSize(); j++)
                    {
                        if (method == "@metric_space hamming")
                        {
                            dist = DistanceHamming(cluster[i]->GetPointH(j)->getId(), hamming[t]->getId());
                        }                
                        else if (method == "@metric euclidean")
                        {
                            distf = DistanceEuclidean(cluster[i]->GetPointE(j)->getId(),euclidean[t]->getId());
                        }
                        else if (method == "@metric cosine")
                        {                    
                            distf = DistanceEuclidean(cluster[i]->GetPointC(j)->getId(), cosine[t]->getId());

                        }
                        else
                        {   
                            int *row = distance->getRow(j);
                            dist = row[t];
                        }  

                        OF += dist;
                        OFF += distf;

                    }
                    if (OF < min_OF[i] || OFF < min_OFF[i])
                    {
                        min_OF[i] = OF;
                        min_OFF[i] = OFF;
                        int min_dist = 100000;
                        float min_distf = 100000.0;
                        for (int j = 0; j < k; j++)         //Check where T belongs
                        {
                            if (method == "@metric_space hamming")
                            {
                                dist = DistanceHamming(cluster[j]->getCentroid(), hamming[t]->getId());

                            }                
                            else if (method == "@metric euclidean")
                            {
                                distf = DistanceEuclidean(euclidean[t]->getId(), cluster[j]->getCentroid());
                            }
                            else if (method == "@metric cosine")
                            {

                                distf = DistanceEuclidean(cosine[t]->getId(), cluster[j]->getCentroid());
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
                                min_k[i] = j;
                            }  

                        }

                        for (t = 0; t < cluster[min_k[i]]->GetSize(); t++)  
                        {
                            if (method == "@metric_space hamming")
                            {
                                if (cluster[min_k[i]]->GetPointH(t)->getId() == hamming[t]->getId())
                                {
                                    medoid[i] = t;
                                    break;
                                }

                            }                
                            else if (method == "@metric euclidean")
                            {
                                if (cluster[min_k[i]]->GetPointE(t)->getId() == euclidean[t]->getId())
                                {
                                    medoid[i] = t;
                                    break;
                                }
                            }
                            else if (method == "@metric cosine")
                            {

                                if (cluster[min_k[i]]->GetPointC(t)->getId() == cosine[t]->getId())
                                {
                                    medoid[i] = t;
                                    break;
                                }
                            }
                            else
                            {   
                                int *row = distance->getRow(i);
                                dist = row[i];
                            }  
                        }
                         

                    }

                }
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
                        objectivefunction[i] = min_OF[s];
                        ObjectiveFunctionF[i] = min_OFF[s];
                        PAM_Update(cluster, k, n, method, hamming, cosine, euclidean, distance, objectivefunction, ObjectiveFunctionF);

                    }   
            }
    }
    
    float min = 100000000000000.0000;
    for (int s = 0;  s < numb_of_it; s++)
    {
        if(method == "@metric_space hamming" || method == "@metric_space matrix" )                    
        {
            if(min_OF[s] < min)
            {
                min = min_OF[s];
            }
        }
        else
        {
           if(min_OFF[s] < min)
            {
                min = min_OFF[s];
            }
        }
    }
    
    
}