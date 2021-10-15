#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

std::vector<double> neoHookean(std::vector<double> trueStrain, double mu)
{
	std::vector<double> stress(trueStrain.size());
	std::vector<double> lam(trueStrain.size());
	
	for (int i = 0; i < trueStrain.size(); i++)
	{
		lam[i] = exp(trueStrain[i]);
	}

	//Tensile
	for (int i = 1; i < trueStrain.size(); i++)
	{
		stress[i] += mu*(lam[i]*lam[i]-1/lam[i]);
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
	double mu = 0.406758;

	double matrix[100][2]; ///

	trueStress = neoHookean(trueStrain, mu);

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
