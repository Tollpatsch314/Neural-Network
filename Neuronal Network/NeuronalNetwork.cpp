#include "NeuronalNetwork.h"

std::random_device* rd;
std::normal_distribution<double>* distribution;

NeuronalNetwork::NeuronalNetwork(int inputnodes, int hiddennodes, int outputnodes, float learningrate)
{
	this->inputnodes = inputnodes;
	this->hiddennodes = hiddennodes;
	this->outputnodes = outputnodes;
	this->learningrate = learningrate;

	// memory reserving
	this->wih = new double*[this->hiddennodes];
	for (int i = 0; i < this->hiddennodes; i++) this->wih[i] = new double[inputnodes];

	this->who = new double*[this->outputnodes];
	for (int i = 0; i < this->outputnodes; i++) this->who[i] = new double[hiddennodes];



	// "random" definition of the dynamik array
	rd = new std::random_device(); // I may need it later, hence it is a pointer
	distribution = new std::normal_distribution<double>(0.0, std::pow(this->hiddennodes, -0.5)); // the same reason
	std::default_random_engine generator = std::default_random_engine((unsigned int)rd->operator()()); // unfortunately that can't be a pointer (ask the devs, there lot of errors)

	for (int x = 0; x < this->hiddennodes; x++) {
		for (int y = 0; y < this->inputnodes; y++) {
			again0:
			this->wih[x][y] = distribution->operator()(generator);
			if (this->wih[x][y] > 0.5 || this->wih[x][y] < -0.5) goto again0;
		}
	}

	generator.seed((unsigned int)rd->operator()());
	delete distribution;
	distribution = new std::normal_distribution<double>(0.0, std::pow(this->outputnodes, -0.5));

	for (int x = 0; x < this->outputnodes; x++) {
		for (int y = 0; y < this->hiddennodes; y++) {
			again1:
			this->who[x][y] = distribution->operator()(generator);
			if (this->who[x][y] > 0.5 || this->who[x][y] < -0.5) goto again1;
		}
	}


}

NeuronalNetwork::~NeuronalNetwork()
{
	// important!!!
	delete distribution;
	delete rd;

	for (int i = 0; i < this->hiddennodes; i++) delete[] this->wih[i];
	delete[] this->wih;

	for (int i = 0; i < this->outputnodes; i++) delete[] this->who[i];
	delete[] this->who;
}

std::string NeuronalNetwork::info()
{

	std::string nnInfo = "\nweigth input- to hidden-nodes:\n\n{";

	for (int x = 0; x < this->hiddennodes; x++) {
		nnInfo += "\n   [ ";
		for (int y = 0; y < this->inputnodes - 1; y++) {
			nnInfo += (wih[x][y] > 0 ? " " : "") + std::to_string(this->wih[x][y]) + ", ";
		}
		nnInfo += (wih[x][this->inputnodes - 1] > 0 ? " " : "") + std::to_string(this->wih[x][this->inputnodes - 1]) + " ],";
	}

	nnInfo += "\b \n}\n\nweigth hidden- to output-nodes:\n\n{";

	for (int x = 0; x < this->outputnodes; x++) {
		nnInfo += "\n   [ ";
		for (int y = 0; y < this->hiddennodes - 1; y++) {
			nnInfo += (who[x][y] > 0 ? " " : "") + std::to_string(this->who[x][y]) + ", ";
		}
		nnInfo += (who[x][this->inputnodes - 1] > 0 ? " " : "") + std::to_string(this->who[x][this->inputnodes - 1]) + " ],";
	}

	nnInfo += "\b \n}\n";
	

	return	" \xFE inputnodes: " + std::to_string(this->inputnodes) +
			"\n \x19 hiddennodes: " + std::to_string(this->hiddennodes) +
			"\n \xFE outputnodes: " + std::to_string(this->outputnodes) +
			"\n   learningrate: " + std::to_string(this->learningrate) + 
			"\n\n" + nnInfo;
}

double NeuronalNetwork::sigmoid(double x)
{
	return 1 / (1 + std::pow(std::exp(1.0), -x));
}
