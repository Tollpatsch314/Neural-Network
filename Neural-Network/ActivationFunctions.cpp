#include "ActivationFunctions.h"

const char* NeuralNetwork::ActivationFunctionTypeDescription[] = {

	"identity function",
	"unit step function / binary step",
	"sigmoid / logistic / soft step",
	"hyperbolic tangent",
	"rectified linear unit (ReLU)",
	"gaussian error linear unit (GELU)",
	"softplus",
	"scaled exponential linear unit (SELU)",
	"leaky rectified linear unit (Leaky ReLU)",
	"sigmoid linear unit (SiLU) / sigmoid shrinkage / SiL / Swish-1",
	"Mish",
	"gaussian"

};

template<typename TYPE> void NeuralNetwork::ActivationFunction(NeuralNetwork::ActivationFunctionType aft, TYPE* value)
{
	switch (aft) {

	case ActivationFunctionType::Identity:
		return;

	case ActivationFunctionType::BinaryStep:
		*value = (TYPE)*value >= (TYPE)1;
		return;

	case ActivationFunctionType::Sigmoid:
		*value = (TYPE)1 / ((TYPE)1 + std::pow((TYPE)std::exp((TYPE)1.0), -*value));
		return;

	case ActivationFunctionType::tanh: 
		*value = std::tanh(*value);
		return;

	case ActivationFunctionType::ReLU:
		*value = std::fmax((TYPE)0, *value);
		return;

	case ActivationFunctionType::GELU:
		*value = *value / (TYPE)2 * ((TYPE)1 + std::erf(*value / std::sqrt((TYPE)2)));
		return;

	case ActivationFunctionType::Softplus:
		*value = std::log((TYPE)1 + std::pow((TYPE)std::exp((TYPE)1), *value));
		return;

	case ActivationFunctionType::SELU:
		*value = ((*value < (TYPE)0) ? (1.67326 * ((TYPE)(std::exp((TYPE)1)) - (TYPE)1)) : *value);
		return;

	case ActivationFunctionType::LeakyReLU:
		*value = (*value < 0 ? ((TYPE)0.01 * *value) : *value);
		return;

	case ActivationFunctionType::SiLU:
		*value = *value / ((TYPE)1 + std::pow((TYPE)std::exp((TYPE)1), -*value));
		return;

	case ActivationFunctionType::Mish:
		*value = *value * (TYPE)std::tanh(std::log((TYPE)1 + std::pow((TYPE)std::exp((TYPE)1), *value)));
		return;

	case ActivationFunctionType::Gaussian:
		*value = std::pow((TYPE)std::exp((TYPE)1), -(*value * *value));
		return;

	}
}

template<typename TYPE> TYPE NeuralNetwork::ActivationFunction(NeuralNetwork::ActivationFunctionType aft, TYPE value)
{
	NeuralNetwork::ActivationFunction<TYPE>(aft, &value);
	return value;
}

const char* NeuralNetwork::to_cstr(ActivationFunctionType aft) {
	return NeuralNetwork::ActivationFunctionTypeDescription[(uint8_t)aft];
}

const char* NeuralNetwork::to_cstr(ActivationFunctionType& aft) {
	return NeuralNetwork::ActivationFunctionTypeDescription[(uint8_t)aft];
}

std::string NeuralNetwork::to_string(ActivationFunctionType aft) {
	return std::string(NeuralNetwork::ActivationFunctionTypeDescription[(uint8_t)aft]);
}

std::string NeuralNetwork::to_string(ActivationFunctionType& aft) {
	return std::string(NeuralNetwork::ActivationFunctionTypeDescription[(uint8_t)aft]);
}

template void NeuralNetwork::ActivationFunction<float>(NeuralNetwork::ActivationFunctionType aft, float* value);
template void NeuralNetwork::ActivationFunction<double>(NeuralNetwork::ActivationFunctionType aft, double* value);
template void NeuralNetwork::ActivationFunction<long double>(NeuralNetwork::ActivationFunctionType aft, long double* value);

template float NeuralNetwork::ActivationFunction<float>(NeuralNetwork::ActivationFunctionType aft, float value);
template double NeuralNetwork::ActivationFunction<double>(NeuralNetwork::ActivationFunctionType aft, double value);
template long double NeuralNetwork::ActivationFunction<long double>(NeuralNetwork::ActivationFunctionType aft, long double value);
