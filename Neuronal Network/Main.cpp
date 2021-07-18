#include <iostream>
#include <conio.h>
#include <random>

#include "NeuronalNetwork.h"

int main() {
	
	NeuronalNetwork nn = NeuronalNetwork(3, 3, 3, 0.3f);
	std::cout << nn.info() << std::endl;

	/*std::random_device rd{};
	std::default_random_engine generator(rd());
	std::normal_distribution<double> n = std::normal_distribution<double>(0.0, std::pow(10, -0.5));


	for (int j = 0; j < 100; j++) {

		double f = n(generator);
		int i = 0;
		while (not f < -0.5f && f > 0.5f) f = n(generator), i++;
		std::cout << "Rand: " << n(generator) << "; i = " << i << ";\n";

	}*/

	std::cout << "\nsigmoid(0.2) = " << nn.sigmoid(0.2);
	
	_getch();

	return 0;
}