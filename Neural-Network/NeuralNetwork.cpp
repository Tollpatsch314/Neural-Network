#include "NeuralNetwork.h"

#pragma region Neural Network - member-functions

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::NeuralNetwork(std::initializer_list<SIZE> numNeurons)
{
	this->numNeurons.insert(this->numNeurons.end(), numNeurons.begin(), numNeurons.end());
	*this = NeuralNetwork<TYPE, SIZE>(this->numNeurons);
}

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::NeuralNetwork(std::vector<SIZE> numNeurons)
{
	this->numNeurons = numNeurons;
	this->NeuronsValue.reserve(this->numNeurons.size());
	this->Weigths.reserve(this->numNeurons.size());

	{
		std::vector<TYPE> vec;
		for (SIZE t = 0; t < this->numNeurons[0]; t++) vec.push_back((TYPE)0);
		this->NeuronsValue.push_back(vec);
	}


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
		this->NeuronsValue.push_back(vecN);
	}

}

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::NeuralNetwork(std::vector<std::vector<std::vector<TYPE>>> weigths, std::vector<ActivationFunctionType> afts)
{
	this->Weigths = weigths;
	this->aft = afts;

	this->numNeurons.reserve(this->Weigths.size());

	for (SIZE layer = 0; layer < this->Weigths.size(); layer++) {
		this->numNeurons.push_back(this->Weigths[layer].size());
	}

	this->NeuronsValue.reserve(this->numNeurons.size());
	this->Weigths.reserve(this->numNeurons.size());

	{
		std::vector<TYPE> vec;
		for (SIZE t = 0; t < this->numNeurons[0]; t++) vec.push_back((TYPE)0);
		this->NeuronsValue.push_back(vec);
	}


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
		this->NeuronsValue.push_back(vecN);
	}

}

template<typename TYPE, typename SIZE>
NeuralNetwork::NeuralNetwork<TYPE, SIZE>::~NeuralNetwork()
{

}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setActivationFunctions(std::vector<ActivationFunctionType> afts)
{

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

	// TODO
	if (this->NeuronsValue[/*layer*/ 0].size() != inputs.size()) throw std::invalid_argument("Error in function 'template<typename T, typename SIZE> std::vector<T>* NeuralNetwork::NeuralNetwork<T, SIZE>::calc(std::initializer_list<std::vector<T> inputs)':\n"
		"The size of the transferred vector is not equal to the number of neurons of the class 'InputLayer'.");

	for (size_t t = 0; t < this->NeuronsValue[/*layer*/ 0].size(); t++) {
		this->NeuronsValue[/*layer*/ 0][/*neuron*/ t] = ActivationFunction<TYPE>(this->aft[0], inputs[/*neuron*/ t]);
	}


	/*
	* This for-loops are technically simple matrix-multiplikation, hope it's readable
	*/

	for (SIZE layer = 1, last_layer = 0; layer < this->NeuronsValue.size(); layer++, last_layer++)
	{	// layers - loop

		for (SIZE neuron = 0; neuron < this->NeuronsValue[layer].size(); neuron++)
		{	// neurons at the layer - loop

			this->NeuronsValue[layer][neuron] = 0;	// clearing, very important !!!

			for (SIZE last_neuron = 0; last_neuron < this->NeuronsValue[last_layer].size(); last_neuron++)
			{	// neurons of the last layer - loop

				ActivationFunction<TYPE>(this->aft[layer], &this->NeuronsValue[last_layer][last_neuron]);

				for (SIZE weigths = 0; weigths < this->Weigths[layer][neuron].size(); weigths++)
				{	// every weigth between the tow layers - loop

					this->NeuronsValue[layer][neuron] += this->Weigths[layer][neuron][weigths] * this->NeuronsValue[last_layer][last_neuron];

				}	// end of every weigth between the tow layers - loop

			}	// end of neurons of the last layer - loop

		}	// end of neurons at the layer - loop

	}	// end of layers - loop

	SIZE layer = this->NeuronsValue.size() - 1;

	for (SIZE t = 0; t < this->NeuronsValue[layer].size(); t++) {
		ActivationFunction<TYPE>(this->aft[layer], &this->NeuronsValue[layer][t]);
	}

	return &this->NeuronsValue[layer];
}

template<typename TYPE, typename SIZE>
std::vector<SIZE> NeuralNetwork::NeuralNetwork<TYPE, SIZE>::getNumOfNeurons()
{
	return this->numNeurons;
}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigths(std::vector<std::vector<std::vector<TYPE>>>* weigths)
{
	/*num of layers*/
	if (weigths->size() != this->NeuronsValue->size()) goto error;

	for (SIZE layer = 1, last_layer = 0; layer < this->NeuronsValue.size(); layer++, last_layer++) {
		if (weigths->at(layer).size() != this->NeuronsValue[layer].size()) goto error;
		for (SIZE neuron = 0; neuron < weigths->at(layer).size(); neuron++) {
			if (weigths->at(layer)[neuron].size() != this->NeuronsValue[layer].size()) goto error;
		}
	}

	this->Weigths = *weigths;
	return;
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

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigthAt(SIZE layer, SIZE neuron_0, SIZE neuron_1, TYPE weigth)
{
	this->Weigths[layer][neuron_0][neuron_1] = weigth; // TODO: security check / verification
}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigthAt(SIZE layer, SIZE neuron, std::vector<TYPE>* weigths)
{
	this->Weigths[layer][neuron] = weigths; // TODO: security check / verification
}

template<typename TYPE, typename SIZE>
void NeuralNetwork::NeuralNetwork<TYPE, SIZE>::setWeigthAt(SIZE layer, std::vector<std::vector<TYPE>>* weigths)
{
	this->Weigths[layer] = weigths; // TODO: security check / verification
}

#pragma endregion


#pragma region Neural Network - all variations for the compiler

#if defined(COMPILE_FLOAT) & defined(COMPILE_UINT8_T)
template NeuralNetwork::NeuralNetwork<float, uint8_t>::NeuralNetwork(std::initializer_list<uint8_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint8_t>::NeuralNetwork(std::vector<uint8_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint8_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<float, uint8_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<float, uint8_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint8_t>::getActivationFunctions();
template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint8_t>::calc(std::vector<float> inputs);
template std::vector<uint8_t> NeuralNetwork::NeuralNetwork<float, uint8_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<float>>> NeuralNetwork::NeuralNetwork<float, uint8_t>::getWeigths();
#endif	// float & uint8_t

#if defined(COMPILE_FLOAT) & defined(COMPILE_UINT16_T)
template NeuralNetwork::NeuralNetwork<float, uint16_t>::NeuralNetwork(std::initializer_list<uint16_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint16_t>::NeuralNetwork(std::vector<uint16_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint8_t>::NeuralNetwork(std::vector<uint8_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint16_t>::NeuralNetwork(std::vector<uint16_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint16_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<float, uint16_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<float, uint16_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint16_t>::getActivationFunctions();
template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint16_t>::calc(std::vector<float> inputs);
template std::vector<uint16_t> NeuralNetwork::NeuralNetwork<float, uint16_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<float>>> NeuralNetwork::NeuralNetwork<float, uint16_t>::getWeigths();
#endif	// float & uint16_t

#if defined(COMPILE_FLOAT) & defined(COMPILE_UINT32_T)
template NeuralNetwork::NeuralNetwork<float, uint32_t>::NeuralNetwork(std::initializer_list<uint32_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint32_t>::NeuralNetwork(std::vector<uint32_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint32_t>::NeuralNetwork(std::vector<uint32_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint32_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<float, uint32_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<float, uint32_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint32_t>::getActivationFunctions();
template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint32_t>::calc(std::vector<float> inputs);
template std::vector<uint32_t> NeuralNetwork::NeuralNetwork<float, uint32_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<float>>> NeuralNetwork::NeuralNetwork<float, uint32_t>::getWeigths();
#endif	// float & uint32_t

#if defined(COMPILE_FLOAT) & defined(COMPILE_UINT64_T)
template NeuralNetwork::NeuralNetwork<float, uint64_t>::NeuralNetwork(std::initializer_list<uint64_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint64_t>::NeuralNetwork(std::vector<uint64_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint64_t>::NeuralNetwork(std::vector<uint64_t> numNeurons);
template NeuralNetwork::NeuralNetwork<float, uint64_t>::NeuralNetwork(std::vector<std::vector<std::vector<float>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<float, uint64_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<float, uint64_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<float, uint64_t>::getActivationFunctions();
template std::vector<float>* NeuralNetwork::NeuralNetwork<float, uint64_t>::calc(std::vector<float> inputs);
template std::vector<uint64_t> NeuralNetwork::NeuralNetwork<float, uint64_t>::getNumOfNeurons();
#endif	// float & uint64_t

#if defined(COMPILE_DOUBLE) & defined(COMPILE_UINT8_T)
template NeuralNetwork::NeuralNetwork<double, uint8_t>::NeuralNetwork(std::initializer_list<uint8_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint8_t>::NeuralNetwork(std::vector<uint8_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint8_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<double, uint8_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<double, uint8_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint8_t>::getActivationFunctions();
template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint8_t>::calc(std::vector<double> inputs);
template std::vector<uint8_t> NeuralNetwork::NeuralNetwork<double, uint8_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint8_t>::getWeigths();
#endif	// double & uint8_t

#if defined(COMPILE_DOUBLE) & defined(COMPILE_UINT16_T)
template NeuralNetwork::NeuralNetwork<double, uint16_t>::NeuralNetwork(std::initializer_list<uint16_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint16_t>::NeuralNetwork(std::vector<uint16_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint16_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<double, uint16_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<double, uint16_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint16_t>::getActivationFunctions();
template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint16_t>::calc(std::vector<double> inputs);
template std::vector<uint16_t> NeuralNetwork::NeuralNetwork<double, uint16_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint16_t>::getWeigths();
#endif	// double & uint16_t

#if defined(COMPILE_DOUBLE) & defined(COMPILE_UINT32_T)
template NeuralNetwork::NeuralNetwork<double, uint32_t>::NeuralNetwork(std::initializer_list<uint32_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint32_t>::NeuralNetwork(std::vector<uint32_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint32_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<double, uint32_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<double, uint32_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint32_t>::getActivationFunctions();
template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint32_t>::calc(std::vector<double> inputs);
template std::vector<uint32_t> NeuralNetwork::NeuralNetwork<double, uint32_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint32_t>::getWeigths();
#endif	// double & uint32_t

#if defined(COMPILE_DOUBLE) & defined(COMPILE_UINT64_T)
template NeuralNetwork::NeuralNetwork<double, uint64_t>::NeuralNetwork(std::initializer_list<uint64_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint64_t>::NeuralNetwork(std::vector<uint64_t> numNeurons);
template NeuralNetwork::NeuralNetwork<double, uint64_t>::NeuralNetwork(std::vector<std::vector<std::vector<double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<double, uint64_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<double, uint64_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<double, uint64_t>::getActivationFunctions();
template std::vector<double>* NeuralNetwork::NeuralNetwork<double, uint64_t>::calc(std::vector<double> inputs);
template std::vector<uint64_t> NeuralNetwork::NeuralNetwork<double, uint64_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<double>>> NeuralNetwork::NeuralNetwork<double, uint64_t>::getWeigths();
#endif	// double & uint64_t

#if defined(COMPILE_LONG_DOUBLE) & defined(COMPILE_UINT8_T)
template NeuralNetwork::NeuralNetwork<long double, uint8_t>::NeuralNetwork(std::initializer_list<uint8_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint8_t>::NeuralNetwork(std::vector<uint8_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint8_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<long double, uint8_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<long double, uint8_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint8_t>::getActivationFunctions();
template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint8_t>::calc(std::vector<long double> inputs);
template std::vector<uint8_t> NeuralNetwork::NeuralNetwork<long double, uint8_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint8_t>::getWeigths();
#endif	// long double & uint8_t

#if defined(COMPILE_LONG_DOUBLE) & defined(COMPILE_UINT16_T)
template NeuralNetwork::NeuralNetwork<long double, uint16_t>::NeuralNetwork(std::initializer_list<uint16_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint16_t>::NeuralNetwork(std::vector<uint16_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint16_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<long double, uint16_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<long double, uint16_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint16_t>::getActivationFunctions();
template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint16_t>::calc(std::vector<long double> inputs);
template std::vector<uint16_t> NeuralNetwork::NeuralNetwork<long double, uint16_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint16_t>::getWeigths();
#endif	// long double & uint16_t

#if defined(COMPILE_LONG_DOUBLE) & defined(COMPILE_UINT32_T)
template NeuralNetwork::NeuralNetwork<long double, uint32_t>::NeuralNetwork(std::initializer_list<uint32_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint32_t>::NeuralNetwork(std::vector<uint32_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint32_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<long double, uint32_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<long double, uint32_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint32_t>::getActivationFunctions();
template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint32_t>::calc(std::vector<long double> inputs);
template std::vector<uint32_t> NeuralNetwork::NeuralNetwork<long double, uint32_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint32_t>::getWeigths();
#endif	// long double & uint32_t

#if defined(COMPILE_LONG_DOUBLE) & defined(COMPILE_UINT64_T)
template NeuralNetwork::NeuralNetwork<long double, uint64_t>::NeuralNetwork(std::initializer_list<uint64_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint64_t>::NeuralNetwork(std::vector<uint64_t> numNeurons);
template NeuralNetwork::NeuralNetwork<long double, uint64_t>::NeuralNetwork(std::vector<std::vector<std::vector<long double>>> weigths, std::vector<ActivationFunctionType> afts);
template NeuralNetwork::NeuralNetwork<long double, uint64_t>::~NeuralNetwork();
template void NeuralNetwork::NeuralNetwork<long double, uint64_t>::setActivationFunctions(std::vector<ActivationFunctionType> afts);
template std::vector<NeuralNetwork::ActivationFunctionType> NeuralNetwork::NeuralNetwork<long double, uint64_t>::getActivationFunctions();
template std::vector<long double>* NeuralNetwork::NeuralNetwork<long double, uint64_t>::calc(std::vector<long double> inputs);
template std::vector<uint64_t> NeuralNetwork::NeuralNetwork<long double, uint64_t>::getNumOfNeurons();
template std::vector<std::vector<std::vector<long double>>> NeuralNetwork::NeuralNetwork<long double, uint64_t>::getWeigths();
#endif	// long double & uint64_t

#pragma endregion
