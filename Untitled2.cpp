#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <time.h>
#include "histogram.h"

double Monte_Pi(int N,std::mt19937_64 &gen){
    //Setup random number generator
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    long N_in = 0;
    double N_tot =  1000;
    for (int i = 0;i < N_tot;++i) {
        double x = dist(gen);
        double y = dist(gen);
        double r = std::sqrt(x*x + y*y);
        if (r <= 1.0) {
            N_in++;
        }
  }
return 4.0*N_in/N_tot;
}

int main() {
    int N = 100; // The number of random points to estimate for Pi
    int N_est = 1000; //The number of random points to generate an estimate of Pi

    //Create an array with N_est elements
    std::vector<double> pis;

    //Get some input
    std::cout<<"Enter The number of random points to estimate Pi: ";
    std::cin>> N;
    std::cout<<"Enter the number of times to generate an estimate of Pi: ";
    std::cin>> N_est;
    double pi_avg = 0.0;

    std::mt19937_64 gen(time(0));

    //Loop over the number of steps
    double Pi_est(int N);
        for (int i = 0; i < N_est; ++i) {
            pis.push_back(Monte_Pi(N,gen)); //We want to save these to do more with them later.
            pi_avg += pis[i];
            std::cout<<pis[i]<<"\n";
        }
        float sum = 0.0, standardDeviation = 0.0;
        for (int i = 0; i < N_est; ++i) {
            sum += pow((pis[i] - (pi_avg/N_est)),2);
        }
        standardDeviation = sqrt(sum / (N_est - 1));
    std::cout<<"Your estimate of Pi is: "<< pi_avg/(double(N_est))<<"\n";
    std::cout<<"Standard deviation of Pi is: "<< sqrt(sum / (N_est - 1));

    std::vector<double> bins;
    std::vector<int> hist;

    histogram(bins, hist, pis);

    std::ofstream fout("hist.txt");
    fout.precision(15);
    for (size_t i = 0; i < bins.size(); ++i) {
        fout << bins[i] << " " << hist[i] << "\n";
    }
    fout.close();
    return 0;
}
