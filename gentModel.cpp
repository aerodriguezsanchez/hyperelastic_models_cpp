#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

std::vector<double> Gent(std::vector<double> trueStrain, double Mu, double Jm, double kappa)
{
	int a = trueStrain.size();
	
	std::vector<double> stress(a);
	std::vector<double> lam(a);

	double matrix[100][2]; ///

	for (int i = 0; i < a; i++)
	{
		lam[i] = exp(trueStrain[i]);
	}

	for (int i = 0; i < a; i++)
	{
		stress[i] += Mu * ((lam[i] * lam[i]) - (1 / lam[i])) * (Jm) / (Jm - (lam[i] * lam[i]) + (2 / lam[i]) - 3);
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

	double Mu = 0.291563;
	double Jm = 86.2304;
	double kappa = 1000;
	std::vector<double> trueStress(trueStrain.size());

	trueStress = Gent(trueStrain, Mu, Jm, kappa);
	for (int i = 0; i < trueStrain.size(); i++) {
		Epsilon << trueStrain[i] << "\n";
		Sigma << trueStress[i] << "\n";
	}

	Epsilon.close();
	Sigma.close();
}