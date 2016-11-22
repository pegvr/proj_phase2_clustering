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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) 
{
    unsigned int time_ui = static_cast<unsigned int>( time(NULL) % 1000 );
    int choice, k, L,NumofHashFUnctions, clarans_set_fraction, clarans_iterations, N, i;
    bool gameOn = true;
    string line, temp, method;
    ifstream inputfile(argv[2]);
    if (inputfile.is_open())
    {
        getline (inputfile,line);          //First line of file shows which method to implement 
        cout << line << '\n';
        //line.erase(line.size()-1);  
        method = line;
        if (line != "@metric_space hamming") getline (inputfile,line);
        //cout << line << '\n';
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
                if (i == 3)  clarans_set_fraction = stoi(temp, nullptr, 10);
                if (i == 4)  clarans_iterations = stoi(temp, nullptr, 10);
            }
        }  
        configurationfile.close();
    }
    else 
    {
        k = 2;
        NumofHashFUnctions = 4;
        L = 5;
        clarans_set_fraction = ((0.12 * k * (N - k )) < 250) ? 250 : (0.12 * k*(N - k )) ;
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
    srand(time(0));
    while (gameOn != false)
    {
        cout << "*******************************\n";
        cout << " 1 - K-medoids++\n";
        cout << " 2 - Concentrate (Park-Jun)\n";
        cout << " 3 - PAM assignment (simplest approach)\n";
        cout << " 4 - Assignment by LSH/DBH: Reverse Approach\n";
        cout << " 5 - Update a la Lloyd’s (improved PAM) \n";
        cout << " 6 - CLARANS Update \n";
        cout << " Enter your choice and press return: ";

        cin >> choice;
        
        cout << "*******************************\n\n";
        
        
        switch (choice)
        {
            
            case 1:            
            // K-medoids++

                k_medoidspp( cluster, k, N, method, hamming, cosine, euclidean, distancematrix);
                //for (i = 0; i < k; i++) cout << cluster[i]->getCentroidD() << endl;
                
            break;
            case 2:
            // Concentrate (Park-Jun)
                ParkJun( cluster, k, N, method, hamming, cosine, euclidean, distancematrix);
                //  for (i = 0; i < k; i++) cout << cluster[i]->getCentroid() << endl;
            break;
            case 3:
            // PAM assignment (simplest approach)
                
            break;
            case 4:
            //Assignment by LSH/DBH: Reverse Approach
                
            break;
            case 5:
            //Update a la Lloyd’s (improved PAM)
            gameOn = false;
            
            break;
            case 6:
            //CLARANS Update
            gameOn = false;
            
            
            break;
            default:
            cout << "Not a Valid Choice.Choose again.\n";           
            cin >> choice;
            break;
        }

    }
    for (i = 0; i < k; i++) delete cluster[i];
        
    if (method == "@metric_space hamming")
       for (i = 0; i < L; i++)  delete hamming[i]; 
    else if (method == "@metric_space euclidean")
        for (i = 0; i < L; i++)  delete euclidean[i];
    else if (method == "@metric_space cosine")
        for (i = 0; i < L; i++)  delete cosine[i];
    else
       delete distancematrix;
    
    return 0;
}



//DataHamming_5_1000x64.csv