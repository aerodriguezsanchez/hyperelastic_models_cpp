#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

std::vector<double> ExtendedTube(std::vector<double> trueStrain, double Ge, double Gc, double delta, double beta)
{
	std::vector<double> stress(trueStrain.size());
	std::vector<double> lam(trueStrain.size());
	double A = 0;
	double B = 0;
	double C = 0;
	double I1 = 0;

	for (int i = 0; i < trueStrain.size(); i++)
	{
		lam[i] = exp(trueStrain[i]);
	}

	//Tensile
	for (int i = 0; i < trueStrain.size(); i++)
	{	
		I1 = (pow(lam[i], 2) + (2 / lam[i])) * pow(1, (2 / 3));
		A = (1+(1+pow(I1,2)-4*I1)*pow(delta,2)+(5*I1-pow(I1,2)-6)*pow(delta,4))/(pow((1 - (I1 - 3) * pow(delta, 2)), 2));
		B = (pow(lam[i],2) - (1 / lam[i]));
		C= (2 * Ge / beta)*(pow(lam[i],(-beta))-pow((1/(sqrt(lam[i]))),(-beta)));
		stress[i] += Gc*A*B-C;
	}
	return stress;
}

void main() {

	ofstream Sigma;
	Sigma.open("Sigma.csv");
	ofstream Epsilon;
	Epsilon.open("Epsilon.csv");
	
	std::vector<double> trueStrain(100);
	for (int i = 0; i < trueStrain.size(); i++) {
		trueStrain[i] = (0.022) * i;
	}

	std::vector<double> trueStress(trueStrain.size());
	double Ge = 0.153;
	double Gc = 0.202;
	double delta = 0.0856;
	double beta = 0.178;

	double matrix[100][2]; ///

	trueStress = ExtendedTube(trueStrain, Ge, Gc, delta, beta);

	for (int i = 0; i < trueStrain.size(); i++) {
		Epsilon << trueStrain[i] << "\n";
		Sigma << trueStress[i] << "\n";

		///------------------------- Test to see if a matrix can be saved into a CSV file
		matrix[i][0] = exp(trueStrain[i]) - 1; //From true strain to engineering strain
		matrix[i][1] = (trueStress[i]) / exp(trueStrain[i]); // From true stress to engineering stress
	}
	///------------------------- Test to see if a matrix can be saved into a CSV file

	ofstream Matrix;
	Matrix.open("Matrix.csv");

	for (auto& row : matrix) {
		for (auto col : row)
			Matrix << col << ',';
		Matrix << '\n';
	}

	Epsilon.close();
	Sigma.close();
	Matrix.close();
}
