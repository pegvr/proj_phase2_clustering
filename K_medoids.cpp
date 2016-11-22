#include "K_medoids.h"

void k_medoidspp(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance)
{
    int sum = 0, r = 0, dist, j; 
    float P[N];
    int rand_num = (rand() / (RAND_MAX + 1.0))* N; 
    if (method == "@metric_space hamming")
        cluster[0] = new ClusterH(hamming[rand_num]);
    else if (method == "@metric euclidean")
        cluster[0] = new ClusterE(euclidean[rand_num]);
    else if (method == "@metric cosine")
        cluster[0] = new ClusterC(cosine[rand_num]);
    else
        cluster[0] = new ClusterD(distance->getRow(rand_num)); 
    //cout <<"1   " << endl;
    for( int i = 0; i < k-1; i++) //for every cluster
    {
        //cout <<"2" << endl;
        for ( j = 0; j < N; j++)         //for every point
        {
            
            if (method == "@metric_space hamming")
            {
                dist = 0;
                for (int z = 0; z < hamming[i]->getId().size() ; z++)          //Find how many bits are different
                    if (cluster[i]->getCentroid() != hamming[z]->getId()) dist++;               
                //cout <<"3" << endl;
            }                
            else if (method == "@metric euclidean")
            {
                int num = 0, sum = 0;
                string temp2 = euclidean[j]->getId(), h;
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
                istringstream iss2(cluster[i]->getCentroid());
              //  cout <<"555" << endl;
                for (auto& t : array2)                          //For every distance, store it
                {
                    iss2 >> t;
                }
                //cout <<"6" << endl;
                for (int i = 0; i < num + 1 ; i++)              //Calculate "almost" euclidean distance 
                    sum += (array1[i] - array2[i]) * ((array1[i] - array2[i]));
                dist = sqrt(sum);
               // cout << "mpeka" << endl;
            }
            else if (method == "@metric cosine")
            {
                int num = 0, norma1 = 0, norma2 = 0, inner_product = 0;
                string temp2 = cosine[j]->getId(), h;
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
                istringstream iss2(cluster[i]->getCentroid());
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
                if (j < N-2)
                {
                    int *row = distance->getRow(j);
                    dist = row[r];
                    cout << dist << endl;
                }
            }  
            //cout <<"7" << endl;
            sum += dist;
            P[j] = sum;
            //cout <<"8" << endl;
        }
        float x = (rand() / (RAND_MAX + 1.0))* P[j-1];
        //cout <<"9" << endl;
        for (int j = 0; j < N; j++)         //for every point
            if (x < P[j])   r = j;
        //cout <<"10  " << r << endl;
        if (method == "@metric_space hamming")
            cluster[i+1] = new ClusterH(hamming[r]);
        else if (method == "@metric euclidean")
            cluster[i+1] = new ClusterE(euclidean[r]);
        else if (method == "@metric cosine")
            cluster[i+1] = new ClusterC(cosine[r]);
        else
            cluster[i+1] = new ClusterD(distance->getRow(r));  
        //cout <<"11   " << cluster[i+1]->getCentroid() << endl;
    }
    
   
}