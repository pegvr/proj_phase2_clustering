#include "Park_Jun.h"


void ParkJun(Cluster **cluster, int k, int N, string method, Hamming **hamming, CosineSim **cosine,Euclidean **euclidean, DistanceMatrix *distance)
{
    int i, j, t, dist, sum[N], sumt, matrix[N][N];

    if (method == "@metric_space hamming")
    {
        for ( i = 0 ; i < N; i++)
        {
            for(j = 0 ; j < N; j++)
            {
                dist = 0;
                for (int z = 0; z < hamming[i]->getId().size() ; z++)          //Find how many bits are different
                    if (hamming[j]->getId() != hamming[i]->getId()) dist++;  
                matrix[i][j] = dist;
            }
        }
        for (i = 0 ; i < N; i++)
        {
            for (j = 0 ; j < N; j++)
            {
                sumt = 0 ;
                for (t = 0 ; t < N; t++)    sumt += matrix[j][t];
                
                sum[i] += matrix [i][j] / sumt;
            
            }
        }

        for (i = 0 ; i < k; i++)
        {
            int minsum = 100000, min_object;
            for (j = 0 ; j < N; j++)
            {
                if (sum[i] < minsum){ minsum = sum[j]; min_object = i;}
            }
            cluster[i] = new ClusterH(hamming[min_object]);
        }
    }           
    else if (method == "@metric euclidean")
    {
        for ( i = 0 ; i < N; i++)
        {
            for(j = 0 ; j < N; j++)
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
                istringstream iss2(euclidean[i]->getId());
              //  cout <<"555" << endl;
                for (auto& t : array2)                          //For every distance, store it
                {
                    iss2 >> t;
                }
                //cout <<"6" << endl;
                for (int i = 0; i < num + 1 ; i++)              //Calculate "almost" euclidean distance 
                    sum += (array1[i] - array2[i]) * ((array1[i] - array2[i]));
  
                matrix[i][j] = sqrt(sum);
            }
        }
        for (i = 0 ; i < N; i++)
        {
            for (j = 0 ; j < N; j++)
            {
                sumt = 0 ;
                for (t = 0 ; t < N; t++)    sumt += matrix[j][t];
                
                sum[i] += matrix [i][j] / sumt;
            
            }
        }

        for (i = 0 ; i < k; i++)
        {
            int minsum = 100000, min_object;
            for (j = 0 ; j < N; j++)
            {
                if (sum[i] < minsum){ minsum = sum[j]; min_object = i;}
            }
            cluster[i] = new ClusterE(euclidean[min_object]);
        }
    }
    else if (method == "@metric cosine")
    {
        for ( i = 0 ; i < N; i++)
        {
            for(j = 0 ; j < N; j++)
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
                istringstream iss2(cosine[i]->getId());
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
                matrix[i][j] = dist;
            }
        }
        for (i = 0 ; i < N; i++)
        {
            for (j = 0 ; j < N; j++)
            {
                sumt = 0 ;
                for (t = 0 ; t < N; t++)    sumt += matrix[j][t];
                
                sum[i] += matrix [i][j] / sumt;
            
            }
        }

        for (i = 0 ; i < k; i++)
        {
            int minsum = 100000, min_object;
            for (j = 0 ; j < N; j++)
            {
                if (sum[i] < minsum){ minsum = sum[j]; min_object = i;}
            }
            cluster[i] = new ClusterC(cosine[min_object]);
        }
    }
    else
    {
        for (i = 0 ; i < N-2; i++)
        {
            for (j = 0 ; j < N-2; j++)
            {
                cout << "1" << endl;
                sumt = 0 ;
                int * dist = distance->getRow(j);
                cout << "2  " << dist[1] << endl;
                
                for (t = 0 ; t < N-2; t++)   
                {  
                    sumt += dist[t];
                    cout << dist[t]<< endl;  
                }
                cout << "3" << endl;
                dist = distance->getRow(i);
                cout << "4" << endl;
                sum[i] += dist[j] / sumt;
                cout << "5" << endl;
            }
        }

        for (i = 0 ; i < k; i++)
        {
            cout << "6" << endl;
            int minsum = 100000, min_object;
            for (j = 0 ; j < N-2; j++)
            {
                cout << "7" << endl;
                if (sum[i] < minsum){ minsum = sum[j]; min_object = i;}
            }
            cout << "8" << endl;
            cluster[i] = new ClusterD(distance->getRow(min_object));
            cout << "9" << endl;
        }
    } 
    //cout <<"1   " << endl;
    
}
