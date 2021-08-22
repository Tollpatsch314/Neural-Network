#include <iostream>
#include <conio.h>
#include "NeuralNetwork.h"


int main() {
	srand(time(NULL));
	std::cout << "Hello Neuronal Network!\n\n";
	std::cout << NeuralNetwork::ActivationFunction<float>(NeuralNetwork::ActivationFunctionType::BinaryStep, 3.0) << "\n";

	_getch();

	return 0;
}