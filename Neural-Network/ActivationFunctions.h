/**********************************************************************************************************************************\
 * file: ActivationFunctions.h 
 * 
 *  author: Karl Jahn tollpatsch3141@web.de
 *  date: 2021/08/20
 * 
\**********************************************************************************************************************************/ 

#pragma once

#include <cmath>
#include <string>

namespace NeuralNetwork {

	enum class ActivationFunctionType {
		Identity = 0,
		BinaryStep = 1,
		Logistic = 2, Sigmoid = 2, SoftStep = 2,
		HyperbolicTangent = 3, tanh = 3,
		RectifiedLinearUnit = 4, ReLU = 4,
		GaussianErrorLinearUnit = 5, GELU = 5,
		Softplus = 6,
		ScaledExponentialLinearUnit = 7, SELU = 7,
		LeakyRectifiedLinearUnit = 8, LeakyReLU = 8,
		SigmoidLinearUnit = 9, SiLU = 9, SigmoidShrinkage = 9, SiL = 9, Swish_1 = 9,
		Mish = 10,
		Gaussian = 11
	};

	extern const char* ActivationFunctionTypeDescription[];

	template<typename TYPE> TYPE ActivationFunction(ActivationFunctionType aft, TYPE value);
	template<typename TYPE> void ActivationFunction(ActivationFunctionType aft, TYPE* value);

	const char* to_cstr(ActivationFunctionType aft);
	const char* to_cstr(ActivationFunctionType& aft);
	std::string to_string(ActivationFunctionType aft);
	std::string to_string(ActivationFunctionType& aft);

}