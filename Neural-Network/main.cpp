#define DEBUG
#include <iostream>
#include <conio.h>
#include "NeuralNetwork.h"


int main() {
	srand(time(NULL));
	std::cout << "Hello Neuronal Network!\n\n";
	std::cout << NeuralNetwork::ActivationFunction<float>(NeuralNetwork::ActivationFunctionType::BinaryStep, 3.0) << "\n";

	NeuralNetwork::NeuralNetwork<float, uint8_t> nn = NeuralNetwork::NeuralNetwork<float, uint8_t>({ 3, 3, 3 });
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

	_getch();

	return 0;
}