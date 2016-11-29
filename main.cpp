#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <ctime>
#include "DataPoints.h"
#include "Cluster.h"
#include "K_medoids.h"
#include "Park_Jun.h"
#include "PAM.h"
#include "Clarans.h"
#include "alaLloyds.h"
#include "LSH.h"
#include "CLARA.h"
#include "Silhouette.h"

using namespace std;

/*DataHamming_5_1000x64.csv
 * DataEuclidean_5_500x100.csv
 */
int main(int argc, char** argv) 
{
    unsigned int time_ui = static_cast<unsigned int>( time(NULL) % 1000 );
    int choice, k, L,NumofHashFUnctions, Q, clarans_iterations, N, i;
    bool gameOn = true;
    string line, temp, method;
    ifstream inputfile(argv[2]);
    if (inputfile.is_open())
    {
        getline (inputfile,line);          //First line of file shows which method to implement 
        cout << line << '\n'; 
        method = line;
        if (line != "@metric_space hamming") getline (inputfile,line);

        method = line;
        int counter = 0;
        while ( getline (inputfile,line) ) counter++;    
        N = counter;
    }
    else cout << "Unable to input file"; 
    inputfile.close();
    
    if (argv[3] == "-c")
    {
        ifstream configurationfile(argv[4]);
        if (configurationfile.is_open())
        {
            for(int i = 0; i < 5; i++ )
            {
                getline (configurationfile,line); 
                size_t pos = line.find(":");
                temp = line.substr(pos+2, line.size());
                if (i == 0)  k = stoi(temp, nullptr, 10);
                if (i == 1)  NumofHashFUnctions = stoi(temp, nullptr, 10);
                if (i == 2)  L = stoi(temp, nullptr, 10);
                if (i == 3)  Q = stoi(temp, nullptr, 10);
                if (i == 4)  clarans_iterations = stoi(temp, nullptr, 10);
            }
        }  
        configurationfile.close();
    }
    else 
    {
        k = 10;
        NumofHashFUnctions = 4;
        L = 5;
        Q = ((0.12 * k * (N - k )) < 250) ? 250 : (0.12 * k*(N - k )) ;
        clarans_iterations = 2;
    }
    
    Hamming **hamming = NULL; Euclidean **euclidean = NULL; CosineSim  **cosine = NULL; DistanceMatrix *distancematrix = NULL;
    
    if (method == "@metric_space hamming")
        hamming = CreateHammingPoints(N, argv[2]);
    else if (method == "@metric euclidean")
        euclidean = CreateEuclideanPoints(N, argv[2]);
    else if (method == "@metric cosine")
        cosine = CreateCosinePoints(N, argv[2]);
    else
       distancematrix = CreateMatrixPoints(N-1, argv[2], NumofHashFUnctions);
    
    Cluster **cluster = new Cluster*[k];
    int ObjectiveFunction[k];
    float ObjectiveFunctionF[k];
    ofstream outputFile("Results.txt");
    
    
    clock_t start;
    double duration;
    start = clock();

    while (gameOn != false)
    {
        cout << "*******************************\n";
        cout << " 1 - K-medoids++\n";
        cout << " 2 - Concentrate (Park-Jun)\n";
        cout << " 3 - PAM assignment (simplest approach)\n";
        cout << " 4 - Assignment by LSH/DBH: Reverse Approach\n";
        cout << " 5 - Update a la Lloyd’s (improved PAM) \n";
        cout << " 6 - CLARANS Update  with PAM\n";
        cout << " 7 - CLARANS Update  with LSH/DBH\n";
        cout << " 8 - CLARA\n";
        cout << " Enter your choice and press return: ";

        cin >> choice;
        
        cout << "*******************************\n\n";
        
        
        switch (choice)
        {
            
            case 1:            
            // K-medoids++
                outputFile << "Algorithm: I1" ;
                k_medoidspp( cluster, k, N, method, hamming, cosine, euclidean, distancematrix);
                for (i = 0; i < k; i++) cout << cluster[i]->getCentroid() << endl;
                
            break;
            case 2:
            // Concentrate (Park-Jun)
                outputFile << "Algorithm: I2" ;
                cout << "lala" << endl;
                ParkJun( cluster, k, N, method, hamming, cosine, euclidean, distancematrix);
                cout << "lala2" << endl;
                //for (i = 0; i < k; i++) cout << cluster[i]->getCentroid() << endl;
            break;
            case 3:
            // PAM assignment (simplest approach)
                outputFile << "A1" ;
                for (i = 0; i < k; i++) ObjectiveFunction[i] = 0;
                for (i = 0; i < k; i++) ObjectiveFunctionF[i] = 0;
                if(method == "@metric_space hamming" || method == "@metric_space matrix" || method == "@metric cosine")                    
                {
                    PAM(cluster, k, N, method, hamming, cosine, euclidean, distancematrix, ObjectiveFunction, ObjectiveFunctionF);
                    for (i = 0; i < k; i++) cout << ObjectiveFunction[i] << endl;
                }
                else
                {
                    PAM(cluster, k, N, method, hamming, cosine, euclidean, distancematrix, ObjectiveFunction, ObjectiveFunctionF);
                    //for (i = 0; i < k; i++) cout << ObjectiveFunctionF[i] << endl;
                }
                
                break;
            case 4:
            //Assignment by LSH/DBH: Reverse Approach
                outputFile << "A2" ;
                LSH(cluster,  k,  N,  method, hamming, cosine, euclidean, distancematrix,  NumofHashFUnctions,  L, 4);

            break;
            case 5:
            //Update a la Lloyd’s (improved PAM)
                outputFile << "U1" << endl;
                alalloyds(cluster, k, N, method, hamming, cosine, euclidean, distancematrix, ObjectiveFunction, ObjectiveFunctionF);
                gameOn = false;
            
            break;
            case 6:
            //CLARANS Update
                outputFile << "A1U2" << endl;
                Clarans(cluster, k, N, method, hamming, cosine, euclidean, distancematrix, ObjectiveFunction, ObjectiveFunctionF, Q, 6,  NumofHashFUnctions,  L);      
                gameOn = false;     
            break;
            case 7:
            //CLARANS Update
                outputFile << "A2U2" << endl;
                Clarans(cluster, k, N, method, hamming, cosine, euclidean, distancematrix, ObjectiveFunction, ObjectiveFunctionF, Q, 6, NumofHashFUnctions,  L);
                gameOn = false;     
            break;
            case 8:
            //CLARA 
                outputFile << "CLARA" << endl;
                cout << "ys" << endl ;
                CLARA(cluster,  k,  N,  method, hamming, cosine,euclidean,  distancematrix, ObjectiveFunction, ObjectiveFunctionF);
                cout << "ys2" << endl ;
                gameOn = false;     
            break;
            default:
            cout << "Not a Valid Choice.Choose again.\n";           
            cin >> choice;
            break;
        }

    }

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    outputFile << "clustering_time: " << duration << endl;
    
    for (i = 0; i < k; i++)
        outputFile << "CLUSTER-" << i+1 << "{size: "<< cluster[i]->GetSize()<< ", medoid: " << cluster[i]->getCentroid()<< " }"<< endl;
    
    float s[k], sum = 0;
    Silhouette(cluster,  k,  N,  method, s);
    outputFile << "Silhouette: [ " ;
    for (i = 0; i < k; i++)
    {
        sum += s[i];
        outputFile << s[i] << " , ";
    }       
    outputFile <<  " ] "<< endl;
    outputFile <<  " Sum: "<< sum << endl;
    
    for (i = 0; i < k; i++) delete cluster[i];
    
    //cout << "THE END" << endl;
    return 0;
}

