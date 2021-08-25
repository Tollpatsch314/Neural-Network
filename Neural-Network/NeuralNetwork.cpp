#include "NeuralNetwork.h"


#pragma region variables
std::random_device rd();
#pragma endregion


#pragma region Neural Network - member-functions

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::NeuralNetwork(std::initializer_list<SIZE> numNeurons)
{
	this->numNeurons.insert(this->numNeurons.end(), numNeurons.begin(), numNeurons.end());
	*this = NeuralNetwork<TYPE, SIZE>(this->numNeurons);
}

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::NeuralNetwork(std::vector<SIZE> numNeurons)// {1, 2, 3}
{
	this->numNeurons = numNeurons;
	this->Weigths.reserve(this->numNeurons.size());

	for (SIZE x = 1; x < this->numNeurons.size(); x++) {
		std::vector<std::vector<TYPE>> vecW0;
		vecW0.reserve(this->numNeurons[x - 1]);

		for (SIZE y = 0; y < this->numNeurons[x - 1]; y++) {

			std::vector<TYPE> vecW1;
			vecW1.reserve(this->numNeurons[x]);

			for (SIZE z = 0; z < this->numNeurons[x]; z++) vecW1.push_back((TYPE)0);

			vecW0.push_back(vecW1);
		}

		this->Weigths.push_back(vecW0);
	}

}

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::NeuralNetwork(std::vector<std::vector<std::vector<TYPE>>> weigths, std::vector<ActivationFunctionType> afts)
{
	this->Weigths = weigths;
	this->aft = afts;

	for (SIZE x = 1; x < this->numNeurons.size(); x++) {

		std::vector<TYPE> vecN;
		vecN.reserve(this->numNeurons[x]);

		std::vector<std::vector<TYPE>> vecW0;
		vecW0.reserve(this->numNeurons[x]);

		for (SIZE y = 0; y < this->numNeurons[x]; y++) {

			std::vector<TYPE> vecW1;
			vecW1.reserve(this->numNeurons[x - 1]);

			for (SIZE z = 0; z < this->numNeurons[x - 1]; z++) vecW1.push_back((TYPE)0);

			vecW0.push_back(vecW1);
			vecN.push_back((TYPE)0);
		}

		this->Weigths.push_back(vecW0);
	}

}

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::~NeuralNetwork()
{

}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setActivationFunctions(std::vector<ActivationFunctionType> afts)
{
	if (afts.size() - 1 == this->Weigths.size()) this->aft = afts;
	else throw std::invalid_argument(
		"Error at `NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setActivationFunctions(std::vector<ActivationFunctionType> afts)`:\n"
		"the count of activation-functions-vector isn't equal to the count of the layers of the neural-network!");
}

template<typename TYPE, typename SIZE>
std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<TYPE, SIZE>::getActivationFunctions()
{
	return std::vector<ActivationFunctionType>();
}

template<typename TYPE, typename SIZE>
std::vector<TYPE>* NeuralNetwork::NeuralNetwork<TYPE, SIZE>::calc(std::vector<TYPE> inputs)
{
	//this->aft.insert(this->aft.end(), afts.begin(), afts.end());

	std::vector<TYPE>* neuronsValue = new std::vector<TYPE>;
	std::vector<TYPE>* lastNeuronsValue = new std::vector<TYPE>;

	// TODO
	if (this->Weigths[0].size() != inputs.size()) throw std::invalid_argument("Error in function 'template<typename T, typename SIZE> std::vector<T>* NeuralNetwork::NeuralNetwork<T, SIZE>::calc(std::initializer_list<std::vector<T> inputs)':\n"
		"The size of the transferred vector is not equal to the number of neurons of the class 'InputLayer'.");

	for (size_t t = 0; t < this->Weigths[0].size(); t++) {
		neuronsValue->push_back(ActivationFunction<TYPE>(this->aft[0], inputs[t]));
	}


	/*
	* This for-loops are technically simple matrix-multiplikation, hope it's readable
	*/

	for (SIZE layer = 1; layer < this->Weigths.size(); layer++) {	// layers - loop

		// clearing / changing, very important !!!
		delete lastNeuronsValue;
		lastNeuronsValue = neuronsValue;
		neuronsValue = new std::vector<TYPE>;

		for (SIZE s = 0; s < this->Weigths[layer - 1][0].size(); s++) neuronsValue->push_back(0);

		for (SIZE last_neuron = 0; last_neuron < this->Weigths[layer - 1].size(); last_neuron++)
		{	// neurons at the layer - loop

			ActivationFunction<TYPE>(this->aft[layer], &lastNeuronsValue->at(last_neuron));

			for (SIZE next_neuron = 0; next_neuron < this->Weigths[layer - 1][last_neuron].size(); next_neuron++)
			{	// neurons of the last layer - loop

				neuronsValue->at(next_neuron) += this->Weigths[layer - 1][last_neuron][next_neuron] * lastNeuronsValue->at(last_neuron);

			}	// end of neurons of the last layer - loop

		}	// end of neurons at the layer - loop

	}	// end of layers - loop

	for (SIZE t = 0; t < neuronsValue->size(); t++) {
		ActivationFunction<TYPE>(this->aft[this->Weigths.size() - 1], &neuronsValue->at(t));
	}

	return neuronsValue;
}

template<typename TYPE, typename SIZE>
std::vector<SIZE> NeuralNetwork::NeuralNetwork<TYPE, SIZE>::getNumOfNeurons()
{
	return this->numNeurons;
}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigths(std::vector<std::vector<std::vector<TYPE>>>* weigths)
{
	/*num of layers*
	if (weigths->size() != this->NeuronsValue->size()) goto error;

	for (SIZE layer = 1, last_layer = 0; layer < this->NeuronsValue.size(); layer++, last_layer++) {
		if (weigths->at(layer).size() != this->NeuronsValue[layer].size()) goto error;
		for (SIZE last_neuron = 0; last_neuron < weigths->at(layer).size(); last_neuron++) {
			if (weigths->at(layer)[last_neuron].size() != this->NeuronsValue[layer].size()) goto error;
		}
	}

	this->Weigths = *weigths;
	return;*/
}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigthAt(SIZE layer, SIZE neuron_0, SIZE neuron_1, TYPE weigth)
{
	this->Weigths[layer][neuron_0][neuron_1] = weigth; // TODO: security check / verification
}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigthAt(SIZE layer, SIZE neuron, std::vector<TYPE>* weigths)
{
	this->Weigths[layer][neuron] = *weigths; // TODO: security check / verification
}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigthAt(SIZE layer, std::vector<std::vector<TYPE>>* weigths)
{
	this->Weigths[layer] = *weigths; // TODO: security check / verification
}

template<typename TYPE, typename SIZE>
std::vector<std::vector<std::vector<TYPE>>> NeuralNetwork::NeuralNetwork<TYPE, SIZE>::getWeigths()
{
	return this->Weigths;
}

template<typename TYPE, typename SIZE>
TYPE NeuralNetwork::NeuralNetwork<TYPE, SIZE>::getWeigthAt(SIZE layer, SIZE neuron_0, SIZE neuron_1)
{
	return this->Weigths[layer][neuron_0][neuron_1];
}

template<typename TYPE, typename SIZE>
std::vector<TYPE> NeuralNetwork::NeuralNetwork<TYPE, SIZE>::getWeigthAt(SIZE layer, SIZE neuron)
{
	return this->Weigths[layer][neuron];
}

template<typename TYPE, typename SIZE>
std::vector<std::vector<TYPE>> NeuralNetwork::NeuralNetwork<TYPE, SIZE>::getWeigthAt(SIZE layer)
{
	return this->Weigths[layer];
}

#pragma endregion


template<typename TYPE, typename SIZE>
std::string NeuralNetwork::print(NeuralNetwork<TYPE, SIZE>& nn)
{

}

template<typename TYPE, typename SIZE>
void NeuralNetwork::normal_init(NeuralNetwork<TYPE, SIZE>* nn)
{
	std::random_device rand_device = std::random_device();
	std::normal_distribution<TYPE> norm_distri = std::normal_distribution<TYPE>(0.0, std::pow(0, -0.5));
	std::default_random_engine generator = std::default_random_engine(rand_device());

	//for(SIZE s = 0; s < nn)
}


#pragma region Neural Network - all variations for the compiler

#if defined(NN_COMPILE_FLOAT) & defined(NN_COMPILE_UINT8_T)
/*01*/template NeuralNetwork::NeuralNetwork<float, uint8_t>::NeuralNetwork(std::initializer_list<uint8_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<float, uint8_t>::NeuralNetwork(std::vector<uint8_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<float, uint8_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<float, uint8_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<float, uint8_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint8_t>::getActivationFunctions();
/*07*/template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint8_t>::calc(std::vector<float> inputs);
/*08*/template std::vector<uint8_t> NeuralNetwork::NeuralNetwork<float, uint8_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<float, uint8_t>::setWeigths(std::vector<std::vector<std::vector<float>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<float, uint8_t>::setWeigthAt(uint8_t layer, uint8_t neuron_0, uint8_t neuron_1, float weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<float, uint8_t>::setWeigthAt(uint8_t layer, uint8_t neuron, std::vector<float>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<float, uint8_t>::setWeigthAt(uint8_t layer, std::vector<std::vector<float>>* weigths);
/*13*/template std::vector<std::vector<std::vector<float>>> NeuralNetwork::NeuralNetwork<float, uint8_t>::getWeigths();
#endif	// float & uint8_t

#if defined(NN_COMPILE_FLOAT) & defined(NN_COMPILE_UINT16_T)
/*01*/template NeuralNetwork::NeuralNetwork<float, uint16_t>::NeuralNetwork(std::initializer_list<uint16_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<float, uint16_t>::NeuralNetwork(std::vector<uint16_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<float, uint16_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<float, uint16_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<float, uint16_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint16_t>::getActivationFunctions();
/*07*/template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint16_t>::calc(std::vector<float> inputs);
/*08*/template std::vector<uint16_t> NeuralNetwork::NeuralNetwork<float, uint16_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<float, uint16_t>::setWeigths(std::vector<std::vector<std::vector<float>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<float, uint16_t>::setWeigthAt(uint16_t layer, uint16_t neuron_0, uint16_t neuron_1, float weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<float, uint16_t>::setWeigthAt(uint16_t layer, uint16_t neuron, std::vector<float>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<float, uint16_t>::setWeigthAt(uint16_t layer, std::vector<std::vector<float>>* weigths);
/*13*/template std::vector<std::vector<std::vector<float>>> NeuralNetwork::NeuralNetwork<float, uint16_t>::getWeigths();
#endif	// float & uint16_t

#if defined(NN_COMPILE_FLOAT) & defined(NN_COMPILE_UINT32_T)
/*01*/template NeuralNetwork::NeuralNetwork<float, uint32_t>::NeuralNetwork(std::initializer_list<uint32_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<float, uint32_t>::NeuralNetwork(std::vector<uint32_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<float, uint32_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<float, uint32_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<float, uint32_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint32_t>::getActivationFunctions();
/*07*/template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint32_t>::calc(std::vector<float> inputs);
/*08*/template std::vector<uint32_t> NeuralNetwork::NeuralNetwork<float, uint32_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<float, uint32_t>::setWeigths(std::vector<std::vector<std::vector<float>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<float, uint32_t>::setWeigthAt(uint32_t layer, uint32_t neuron_0, uint32_t neuron_1, float weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<float, uint32_t>::setWeigthAt(uint32_t layer, uint32_t neuron, std::vector<float>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<float, uint32_t>::setWeigthAt(uint32_t layer, std::vector<std::vector<float>>* weigths);
/*13*/template std::vector<std::vector<std::vector<float>>> NeuralNetwork::NeuralNetwork<float, uint32_t>::getWeigths();
#endif	// float & uint32_t

#if defined(NN_COMPILE_FLOAT) & defined(NN_COMPILE_UINT64_T)
/*01*/template NeuralNetwork::NeuralNetwork<float, uint64_t>::NeuralNetwork(std::initializer_list<uint64_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<float, uint64_t>::NeuralNetwork(std::vector<uint64_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<float, uint64_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<float, uint64_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<float, uint64_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint64_t>::getActivationFunctions();
/*07*/template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint64_t>::calc(std::vector<float> inputs);
/*08*/template std::vector<uint64_t> NeuralNetwork::NeuralNetwork<float, uint64_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<float, uint64_t>::setWeigths(std::vector<std::vector<std::vector<float>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<float, uint64_t>::setWeigthAt(uint64_t layer, uint64_t neuron_0, uint64_t neuron_1, float weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<float, uint64_t>::setWeigthAt(uint64_t layer, uint64_t neuron, std::vector<float>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<float, uint64_t>::setWeigthAt(uint64_t layer, std::vector<std::vector<float>>* weigths);
/*13*/template std::vector<std::vector<std::vector<float>>> NeuralNetwork::NeuralNetwork<float, uint64_t>::getWeigths();
#endif	// float & uint64_t

#if defined(NN_COMPILE_DOUBLE) & defined(NN_COMPILE_UINT8_T)
/*01*/template NeuralNetwork::NeuralNetwork<double, uint8_t>::NeuralNetwork(std::initializer_list<uint8_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<double, uint8_t>::NeuralNetwork(std::vector<uint8_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<double, uint8_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<double, uint8_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<double, uint8_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint8_t>::getActivationFunctions();
/*07*/template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint8_t>::calc(std::vector<double> inputs);
/*08*/template std::vector<uint8_t> NeuralNetwork::NeuralNetwork<double, uint8_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<double, uint8_t>::setWeigths(std::vector<std::vector<std::vector<double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<double, uint8_t>::setWeigthAt(uint8_t layer, uint8_t neuron_0, uint8_t neuron_1, double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<double, uint8_t>::setWeigthAt(uint8_t layer, uint8_t neuron, std::vector<double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<double, uint8_t>::setWeigthAt(uint8_t layer, std::vector<std::vector<double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint8_t>::getWeigths();
#endif	// double & uint8_t

#if defined(NN_COMPILE_DOUBLE) & defined(NN_COMPILE_UINT16_T)
/*01*/template NeuralNetwork::NeuralNetwork<double, uint16_t>::NeuralNetwork(std::initializer_list<uint16_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<double, uint16_t>::NeuralNetwork(std::vector<uint16_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<double, uint16_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<double, uint16_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<double, uint16_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint16_t>::getActivationFunctions();
/*07*/template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint16_t>::calc(std::vector<double> inputs);
/*08*/template std::vector<uint16_t> NeuralNetwork::NeuralNetwork<double, uint16_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<double, uint16_t>::setWeigths(std::vector<std::vector<std::vector<double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<double, uint16_t>::setWeigthAt(uint16_t layer, uint16_t neuron_0, uint16_t neuron_1, double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<double, uint16_t>::setWeigthAt(uint16_t layer, uint16_t neuron, std::vector<double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<double, uint16_t>::setWeigthAt(uint16_t layer, std::vector<std::vector<double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint16_t>::getWeigths();
#endif	// double & uint16_t

#if defined(NN_COMPILE_DOUBLE) & defined(NN_COMPILE_UINT32_T)
/*01*/template NeuralNetwork::NeuralNetwork<double, uint32_t>::NeuralNetwork(std::initializer_list<uint32_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<double, uint32_t>::NeuralNetwork(std::vector<uint32_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<double, uint32_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<double, uint32_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<double, uint32_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint32_t>::getActivationFunctions();
/*07*/template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint32_t>::calc(std::vector<double> inputs);
/*08*/template std::vector<uint32_t> NeuralNetwork::NeuralNetwork<double, uint32_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<double, uint32_t>::setWeigths(std::vector<std::vector<std::vector<double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<double, uint32_t>::setWeigthAt(uint32_t layer, uint32_t neuron_0, uint32_t neuron_1, double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<double, uint32_t>::setWeigthAt(uint32_t layer, uint32_t neuron, std::vector<double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<double, uint32_t>::setWeigthAt(uint32_t layer, std::vector<std::vector<double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint32_t>::getWeigths();
#endif	// double & uint32_t

#if defined(NN_COMPILE_DOUBLE) & defined(NN_COMPILE_UINT64_T)
/*01*/template NeuralNetwork::NeuralNetwork<double, uint64_t>::NeuralNetwork(std::initializer_list<uint64_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<double, uint64_t>::NeuralNetwork(std::vector<uint64_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<double, uint64_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<double, uint64_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<double, uint64_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint64_t>::getActivationFunctions();
/*07*/template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint64_t>::calc(std::vector<double> inputs);
/*08*/template std::vector<uint64_t> NeuralNetwork::NeuralNetwork<double, uint64_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<double, uint64_t>::setWeigths(std::vector<std::vector<std::vector<double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<double, uint64_t>::setWeigthAt(uint64_t layer, uint64_t neuron_0, uint64_t neuron_1, double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<double, uint64_t>::setWeigthAt(uint64_t layer, uint64_t neuron, std::vector<double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<double, uint64_t>::setWeigthAt(uint64_t layer, std::vector<std::vector<double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint64_t>::getWeigths();
#endif	// double & uint64_t

#if defined(NN_COMPILE_LONG_DOUBLE) & defined(NN_COMPILE_UINT8_T)
/*01*/template NeuralNetwork::NeuralNetwork<long double, uint8_t>::NeuralNetwork(std::initializer_list<uint8_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<long double, uint8_t>::NeuralNetwork(std::vector<uint8_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<long double, uint8_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<long double, uint8_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<long double, uint8_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint8_t>::getActivationFunctions();
/*07*/template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint8_t>::calc(std::vector<long double> inputs);
/*08*/template std::vector<uint8_t> NeuralNetwork::NeuralNetwork<long double, uint8_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<long double, uint8_t>::setWeigths(std::vector<std::vector<std::vector<long double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<long double, uint8_t>::setWeigthAt(uint8_t layer, uint8_t neuron_0, uint8_t neuron_1, long double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<long double, uint8_t>::setWeigthAt(uint8_t layer, uint8_t neuron, std::vector<long double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<long double, uint8_t>::setWeigthAt(uint8_t layer, std::vector<std::vector<long double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint8_t>::getWeigths();
#endif	// long double & uint8_t

#if defined(NN_COMPILE_LONG_DOUBLE) & defined(NN_COMPILE_UINT16_T)
/*01*/template NeuralNetwork::NeuralNetwork<long double, uint16_t>::NeuralNetwork(std::initializer_list<uint16_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<long double, uint16_t>::NeuralNetwork(std::vector<uint16_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<long double, uint16_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<long double, uint16_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<long double, uint16_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint16_t>::getActivationFunctions();
/*07*/template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint16_t>::calc(std::vector<long double> inputs);
/*08*/template std::vector<uint16_t> NeuralNetwork::NeuralNetwork<long double, uint16_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<long double, uint16_t>::setWeigths(std::vector<std::vector<std::vector<long double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<long double, uint16_t>::setWeigthAt(uint16_t layer, uint16_t neuron_0, uint16_t neuron_1, long double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<long double, uint16_t>::setWeigthAt(uint16_t layer, uint16_t neuron, std::vector<long double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<long double, uint16_t>::setWeigthAt(uint16_t layer, std::vector<std::vector<long double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint16_t>::getWeigths();
#endif	// long double & uint16_t

#if defined(NN_COMPILE_LONG_DOUBLE) & defined(NN_COMPILE_UINT32_T)
/*01*/template NeuralNetwork::NeuralNetwork<long double, uint32_t>::NeuralNetwork(std::initializer_list<uint32_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<long double, uint32_t>::NeuralNetwork(std::vector<uint32_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<long double, uint32_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<long double, uint32_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<long double, uint32_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint32_t>::getActivationFunctions();
/*07*/template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint32_t>::calc(std::vector<long double> inputs);
/*08*/template std::vector<uint32_t> NeuralNetwork::NeuralNetwork<long double, uint32_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<long double, uint32_t>::setWeigths(std::vector<std::vector<std::vector<long double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<long double, uint32_t>::setWeigthAt(uint32_t layer, uint32_t neuron_0, uint32_t neuron_1, long double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<long double, uint32_t>::setWeigthAt(uint32_t layer, uint32_t neuron, std::vector<long double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<long double, uint32_t>::setWeigthAt(uint32_t layer, std::vector<std::vector<long double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint32_t>::getWeigths();
#endif	// long double & uint32_t

#if defined(NN_COMPILE_LONG_DOUBLE) & defined(NN_COMPILE_UINT64_T)
/*01*/template NeuralNetwork::NeuralNetwork<long double, uint64_t>::NeuralNetwork(std::initializer_list<uint64_t> numNeurons);
/*02*/template NeuralNetwork::NeuralNetwork<long double, uint64_t>::NeuralNetwork(std::vector<uint64_t> numNeurons);
/*03*/template NeuralNetwork::NeuralNetwork<long double, uint64_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
/*04*/template NeuralNetwork::NeuralNetwork<long double, uint64_t>::~NeuralNetwork();
/*05*/template void NeuralNetwork::NeuralNetwork<long double, uint64_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
/*06*/template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint64_t>::getActivationFunctions();
/*07*/template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint64_t>::calc(std::vector<long double> inputs);
/*08*/template std::vector<uint64_t> NeuralNetwork::NeuralNetwork<long double, uint64_t>::getNumOfNeurons();
/*09*/template void NeuralNetwork::NeuralNetwork<long double, uint64_t>::setWeigths(std::vector<std::vector<std::vector<long double>>>* weigths);
/*10*/template void NeuralNetwork::NeuralNetwork<long double, uint64_t>::setWeigthAt(uint64_t layer, uint64_t neuron_0, uint64_t neuron_1, long double weigth);
/*11*/template void NeuralNetwork::NeuralNetwork<long double, uint64_t>::setWeigthAt(uint64_t layer, uint64_t neuron, std::vector<long double>* weigths);
/*12*/template void NeuralNetwork::NeuralNetwork<long double, uint64_t>::setWeigthAt(uint64_t layer, std::vector<std::vector<long double>>* weigths);
/*13*/template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint64_t>::getWeigths();
#endif	// long double & uint64_t

#pragma endregion
