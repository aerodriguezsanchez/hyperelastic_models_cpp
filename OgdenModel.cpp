#include <math.h>
#include <fstream>
#include <vector>
using namespace std;

std::vector<double> Ogden(std::vector<double> trueStrain, std::vector<double> muVec, std::vector<double> alphaVec)
{	
	std::vector<double> stress(trueStrain.size());
	std::vector<double> lam(trueStrain.size());
	std::vector<double> mu(muVec.size());
	std::vector<double> alpha(muVec.size());

	for (int i = 0; i < trueStrain.size(); i++)
	{
		lam[i] = exp(trueStrain[i]);
	}

	for (int i = 0; i < muVec.size(); i++)
	{
		mu[i] = muVec[i];
		alpha[i] = alphaVec[i];
	}

	////shear
	//for (int i = 0; i < trueStrain.size(); i++)
	//{
	//	for (int j = 0; j < muVec.size(); j++)
	//	{
	//		stress[i] += (2 * mu[j] / alpha[j]) * ((pow(lam[i], alpha[j])) - pow((1 / (lam[i]*lam[i])), alpha[j]));
	//	}
	//}

	////Planar
	//for (int i = 0; i < trueStrain.size(); i++)
	//{
	//	for (int j = 0; j < muVec.size(); j++)
	//	{
	//		stress[i] += (2*mu[j]/alpha[j])*((pow(lam[i], alpha[j]))-pow((1 /lam[i]),alpha[j]));
	//	}
	//}

	//Tensile
	for (int i = 0; i < trueStrain.size(); i++)
	{
		for (int j = 0; j < muVec.size(); j++)
		{
			stress[i] += (2 * mu[j] / alpha[j]) * ((pow(lam[i], alpha[j])) - pow((1 / sqrt(lam[i])), alpha[j]));
		}
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
		trueStrain[i] = (0.0065)*i;
	}

	
	std::vector<double> muVec{ -0.330628743, 1.53931622e-2, 0.724052710 }; //Treloar
	std::vector<double> alphaVec{ 10.557649, 13.2929248, -20.0136033};
	std::vector<double> trueStress(trueStrain.size());
	
	double matrix[100][2]; ///

	trueStress = Ogden(trueStrain, muVec, alphaVec);

	for (int i = 0; i < trueStrain.size(); i++) {
		Epsilon << trueStrain[i] << "\n";
		Sigma << trueStress[i] << "\n";

		///------------------------- Test to see if a matrix can be saved into a CSV file
		matrix[i][0] = exp(trueStrain[i])-1; //From true strain to engineering strain
		matrix[i][1] = (trueStress[i])/exp(trueStrain[i]); // From true stress to engineering stress
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