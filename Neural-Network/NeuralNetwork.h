#pragma once

//#ifdef DEBUG
#define NN_COMPILE_ALL_TYPES
#define NN_COMPILE_ALL_SIZES
#undef EXCLUDE_TRAINING
//#endif // DEBUG

#ifdef NN_COMPILE_FLOAT
#undef NN_COMPILE_ALL_TYPES
#endif // NN_COMPILE_FLOAT

#ifdef NN_COMPILE_DOUBLE
#undef NN_COMPILE_ALL_TYPES
#endif // NN_COMPILE_DOUBLE

#ifdef NN_COMPILE_FLOAT
#undef NN_COMPILE_ALL_TYPES
#endif // NN_COMPILE_FLOAT

#ifdef NN_COMPILE_ALL_TYPES
#define NN_COMPILE_FLOAT
#define NN_COMPILE_DOUBLE
#define NN_COMPILE_LONG_DOUBLE
#undef NN_COMPILE_ALL_TYPES
#endif // NN_COMPILE_ALL_TYPES

#ifdef NN_COMPILE_UINT8_T
#undef NN_COMPILE_ALL_SIZES
#endif // NN_COMPILE_UINT8_T

#ifdef NN_COMPILE_UINT16_T
#undef NN_COMPILE_ALL_SIZES
#endif // NN_COMPILE_UINT16_T

#ifdef NN_COMPILE_UINT32_T
#undef NN_COMPILE_ALL_SIZES
#endif // NN_COMPILE_UINT32_T

#ifdef NN_COMPILE_UINT64_T
#undef NN_COMPILE_ALL_SIZES
#endif // NN_COMPILE_UINT64_T

#ifdef NN_COMPILE_ALL_SIZES
#define NN_COMPILE_UINT8_T
#define NN_COMPILE_UINT16_T
#define NN_COMPILE_UINT32_T
#define NN_COMPILE_UINT64_T
#undef NN_COMPILE_ALL_SIZES
#endif // NN_COMPILE_ALL_SIZES

#include "ActivationFunctions.h"
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <fstream>

#ifndef EXCLUDE_TRAINING
#include <random>
#endif // !EXCLUDE_TRAINING

namespace NeuralNetwork {

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE">float/double/long double</typeparam>
	/// <typeparam name="SIZE">uint8_t/uint16_t/uint32_t/uint64_t</typeparam>
	template <typename TYPE=float, typename SIZE=uint16_t> class NeuralNetwork
	{
			  /* layer *//* last neurons *//* next neuron */
	private: std::vector<std::vector<std::vector<TYPE>>> Weigths;

	private: std::vector<SIZE> numNeurons;

	private: std::vector<ActivationFunctionType> aft;

	public: std::vector<std::vector<TYPE>> operator[](SIZE pos) { return this->getWeigthAt(pos); }

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	/// <param name="numNeurons"> = {input_layer, hidden_layer, ... , output_layer} </param>
	public: NeuralNetwork(std::initializer_list<SIZE> numNeurons);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	/// <param name="numNeurons"> = {input_layer, hidden_layer, ... , output_layer} </param>
	public: NeuralNetwork(std::vector<SIZE> numNeurons);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: NeuralNetwork(std::vector<std::vector<std::vector<TYPE>>> weigths, std::vector<ActivationFunctionType> afts /* for every layer on element */);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: ~NeuralNetwork();

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: void setActivationFunctions(std::vector<ActivationFunctionType> afts);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: std::vector<ActivationFunctionType> getActivationFunctions();
		   
	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: std::vector<TYPE>* calc(std::vector<TYPE> inputs);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: std::vector<SIZE> getNumOfNeurons();

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: void setWeigths(std::vector</*layer*/ std::vector</*neurons*/ std::vector</*weigths*/ TYPE>>>* weigths);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: void setWeigthAt(SIZE layer, SIZE neuron_0, SIZE neuron_1, TYPE weigth);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: void setWeigthAt(SIZE layer, SIZE neuron, std::vector<TYPE>* weigths);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: void setWeigthAt(SIZE layer, std::vector<std::vector<TYPE>>* weigths);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: std::vector</*layer*/ std::vector</*neurons*/ std::vector</*weigths*/ TYPE>>> getWeigths();


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: TYPE getWeigthAt(SIZE layer, SIZE neuron_0, SIZE neuron_1);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: std::vector<TYPE> getWeigthAt(SIZE layer, SIZE neuron);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	public: std::vector<std::vector<TYPE>> getWeigthAt(SIZE layer);

	};

#ifndef EXCLUDE_TRAINING

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	/// <param name="nn"></param>
	/// <returns></returns>
	template <typename TYPE, typename SIZE> std::string print(NeuralNetwork<TYPE, SIZE>& nn);

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	/// <param name="nn"></param>
	template <typename TYPE, typename SIZE> void normal_init(NeuralNetwork<TYPE, SIZE>* nn);

#endif // !EXCLUDE_TRAINING

}
