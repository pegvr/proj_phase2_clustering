#include "PAM.h"
#include "Cluster.h"


 
void PAM(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance, int *objectivefunction, float * ObjectiveFunctionF)
{
    int i, j, dist, min_dist, min_k;
    float distf;
    for (i = 0; i < N; i++)
    {
        min_dist = 100000;
        for (j = 0; j < k; j++)
        {
            if (method == "@metric_space hamming")
            {
                dist = 0;
                
                string temp1 = cluster[j]->getCentroid();
                string temp2 = hamming[i]->getId();
                for (int z = 0; z < hamming[i]->getId().size() ; z++)          //Find how many bits are different
                    if (temp1[z] != temp2[z]) dist++;               
                cout <<"3   " << dist<< endl;
                //cout << (cluster[j]->getCentroid()
                                             
            }                
            else if (method == "@metric euclidean")
            {
                int num = 0, sum = 0;
                string temp2 = euclidean[i]->getId(), h;
                for(int t = 0; t < temp2.length(); t++)                     //Count how many dimensions the point has
                {
                    h = temp2[t];
                    if(h == "\t")   num++;
                }
                //cout <<"3" << endl;
                double array1[num + 1];                         //Array to store each distance of bucket point
                istringstream iss(temp2);
               // cout <<"4" << endl;
                for (auto& t : array1)                          //For every distance, store it
                {
                    iss >> t;
                }
               // cout <<"5" << endl;
                double array2[num + 1];                         //Array to store each distance of query point
               // cout <<"55" << endl;
                istringstream iss2(cluster[j]->getCentroid());
              //  cout <<"555" << endl;
                for (auto& t : array2)                          //For every distance, store it
                {
                    iss2 >> t;
                }
                //cout <<"6" << endl;
                for (int i = 0; i < num + 1 ; i++)              //Calculate "almost" euclidean distance 
                    sum += (array1[i] - array2[i]) * ((array1[i] - array2[i]));
                distf = sqrt(sum);
                cout << "mpeka" << endl;
            }
            else if (method == "@metric cosine")
            {
                int num = 0, norma1 = 0, norma2 = 0, inner_product = 0;
                string temp2 = cosine[i]->getId(), h;
                for(int t = 0; t < temp2.length(); t++)                     //Count how many dimensions the point has
                {
                    h = temp2[t];
                    if(h == "\t")   num++;
                }
                double array1[num + 1];                         //Array to store each dimension of bucket point
                istringstream iss(temp2);
                for (auto& t : array1)                          //For every dimension, store it
                {
                    iss>> t;
                }
                for(int t = 0; t < num + 1; t++)
                    norma1 += array1[t] * array1[t];           //norma of bucket point
                norma1 = sqrt(norma1);
                double array2[num + 1];                         //Array to store each dimension of query point
                istringstream iss2(cluster[j]->getCentroid());
                for (auto& i : array2)                          //For every dimension, store it
                {
                    iss2>> i;
                }
                for(i = 0; i < num + 1; i++)
                    norma2 += array2[i] * array2[i];        //norma of query point
                norma2 = sqrt(norma2); 
                for(i = 0; i < num + 1; i++)
                    inner_product += array1[i] * array2[i];          //inner product of query and bucket point
                dist = 1 - (inner_product / (norma1 * norma2));
            }
            else
            {   
                int *row = distance->getRow(j);
                dist = row[j];
            }  
            cout << "1" << endl;
            if (dist < min_dist && dist != 0)
            {
                min_dist = dist;
                min_k = j;
            }  
            objectivefunction[j] += dist;
            ObjectiveFunctionF[j] += distf;
            cout <<"8" << endl;
        }
        cout <<"8   " << min_k << "     " << min_dist << endl;
        if (method == "@metric_space hamming")
            cluster[min_k]->InsertPointH(hamming[i], min_dist);
        else if (method == "@metric euclidean")
            cluster[min_k]->InsertPointE(euclidean[i], min_dist);
        else if (method == "@metric cosine")
            cluster[min_k]->InsertPointC(cosine[i], min_dist);
        else
           cluster[min_k]->InsertPointD(distance->getRow(i), min_dist);
        cout << "objective  " << j << "     " << ObjectiveFunctionF[j] << endl;
    }
    cout <<"!!!!!!!!!!" << endl;
    cluster[0]->PrintCluster();
    cluster[1]->PrintCluster();
    cout <<"telos" << endl;
}
