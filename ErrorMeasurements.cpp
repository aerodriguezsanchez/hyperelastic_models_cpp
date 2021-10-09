/* © 2020 Alejandro E. Rodriguez-Sanchez.  All rights reserved. //For personal use only.
It is not permitted to distribute verbatim copies of this document,
and changing it is not allowed. Contact the owner of the code at arodsn.com blog
for further permissions.*/

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream> 
#include<algorithm>
using namespace std;

// Function prototypes START HERE
std::vector<std::vector<double>> read(char file[]);
double RMSE(std::vector<std::vector<double>> matrix);
double R2(std::vector<std::vector<double>> matrix);
std::vector<double> AE(std::vector<std::vector<double>> matrix);
double MAX(std::vector<double> AE);
void save(double rmse, double r2, std::vector<double> ae, double max);
// Function prototypes END HERE


void main() {
    char file[] = "input.csv";
    std::vector<std::vector<double>> matrix = read(file);
    double rmse = RMSE(matrix);
    double r2 = R2(matrix);
    std::vector<double> ae = AE(matrix);
    double max = MAX(ae);
    save(rmse,  r2, ae, max);
}


void save(double rmse, double r2, std::vector<double> ae, double max) {
    /*to save error measures in csv files*/
    ofstream abserror;
    abserror.open("abserror.csv");
    ofstream errormeasures;
    errormeasures.open("errormeasures.csv");

    for (int i = 0; i < ae.size(); i++) {
        abserror << ae[i] << "\n";
    }

    errormeasures << r2 << "\n";
    errormeasures << rmse << "\n";
    errormeasures << max << "\n";

    abserror.close();
    errormeasures.close();
}

std::vector<std::vector<double>> read(char file[]) {
    /* Reads the csv file called input */
    std::ifstream f;
    f.open(file);   /* open file */
    std::string line, val;                  /* string for line & value */
    std::vector<std::vector<double>> matrix;    /* vector of vector<int>  */
    while (std::getline(f, line)) {        /* read each line */
        std::vector<double> v;                 /* row vector v */
        std::stringstream s(line);         /* stringstream line */
        while (getline(s, val, ','))       /* get each value (',' delimited) */
            v.push_back(std::stod(val));  /* add to row vector */
        matrix.push_back(v);                /* add row vector to array */
    }
    /* Ends reading the csv which now is stored into the array called matrix*/
    return matrix;
}

double RMSE(std::vector<std::vector<double>> matrix)
{
    double RMSE = 0;
    double sum1 = 0;
    for (int i = 0; i < matrix.size(); i++) {
        sum1 += pow((matrix[i][1] - matrix[i][0]), 2);
    }
    RMSE = sqrt(sum1 / matrix.size());
    return RMSE;
}

double R2(std::vector<std::vector<double>> matrix) {
    /* Error measurement functions*/
    std::vector<double> AE(matrix.size());
    double R2 = 0;
    double sum1 = 0;
    double sum2 = 0;
    double sum3 = 0;
    double mean = 0;
    for (int i = 0; i < matrix.size(); i++) {
        sum1 += pow((matrix[i][1] - matrix[i][0]), 2);
        for (int j = 0; j < matrix.size(); j++) {
            sum2 += matrix[i][0];
        }
    }
    mean = sum2 / matrix.size();
    for (int i = 0; i < matrix.size(); i++) {
        sum3 += pow((matrix[i][0] - mean), 2);
    }
    R2 = 1 - (sum1 / sum3);
    return R2;
}

std::vector<double> AE(std::vector<std::vector<double>> matrix) {
    std::vector<double> AE(matrix.size());
    for (int i = 0; i < matrix.size(); i++) {
        AE[i] = abs(matrix[i][1] - matrix[i][0]);
    }
    return AE;
}

double MAX(std::vector<double> AE) {
    double MAX = 0;
    MAX = *max_element(AE.begin(), AE.end());
    return MAX;
}
