#define DEBUG
#include <iostream>
#include <conio.h>
#include "NeuralNetwork.h"


int main() {
	srand(time(NULL));
	std::cout << "Hello Neuronal Network!\n\n";
	std::cout << NeuralNetwork::ActivationFunction<float>(NeuralNetwork::ActivationFunctionType::BinaryStep, 3.0) << "\n";

	NeuralNetwork::NeuralNetwork<float, uint8_t> nn = NeuralNetwork::NeuralNetwork<float, uint8_t>({ 3, 4, 3 });
	NeuralNetwork::NeuralNetwork<float, uint8_t> n2 = NeuralNetwork::NeuralNetwork<float, uint8_t>({ 3, 4, 4, 2 , 2 });

	nn.setActivationFunctions({ NeuralNetwork::ActivationFunctionType::Identity, NeuralNetwork::ActivationFunctionType::Sigmoid, NeuralNetwork::ActivationFunctionType::Identity });

	nn.setWeigthAt(0, 0, 0, 0.5);
	nn.setWeigthAt(0, 0, 1, 0.5);
	nn.setWeigthAt(0, 0, 2, 0.5);

	nn.setWeigthAt(0, 1, 0, 0.5);
	nn.setWeigthAt(0, 1, 1, 0.5);
	nn.setWeigthAt(0, 1, 2, 0.5);

	nn.setWeigthAt(0, 2, 0, 0.5);
	nn.setWeigthAt(0, 2, 1, 0.5);
	nn.setWeigthAt(0, 2, 2, 0.5);


	nn.setWeigthAt(1, 0, 0, 0.5);
	nn.setWeigthAt(1, 0, 1, 0.5);
	nn.setWeigthAt(1, 0, 2, 0.5);

	nn.setWeigthAt(1, 1, 0, 0.5);
	nn.setWeigthAt(1, 1, 1, 0.5);
	nn.setWeigthAt(1, 1, 2, 0.5);

	nn.setWeigthAt(1, 2, 0, 0.5);
	nn.setWeigthAt(1, 2, 1, 0.5);
	nn.setWeigthAt(1, 2, 2, 0.5);

	std::vector<float>* erg = {};

	try {
		erg = nn.calc({ 2, 4, 5 });
	}
	catch (std::exception e) {
		std::cerr << e.what();
	}
	std::cout << erg->at(0) << ", " << erg->at(1) << ", " << erg->at(2) << std::endl;

	//nn.calc({,,,,}, NeuralNetwork::ActivationFunctionType::BinaryStep)


	//train1(&nn, 1.f, {});
	//train2(&nn, 1.f, {});
	//train3(&nn, 1.f, {});

	_getch();

	return 0;
}