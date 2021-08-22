/**********************************************************************************************************************************\
 * file: NeuralNetwork.h
 *
 * author: Karl Jahn tollpatsch3141@web.de
 * date: 2021/08/20
 * final processing: 2021/08/20
 * 
 * WARNING: If you change some #define of this Header you must recompile it for changing.
 *
\**********************************************************************************************************************************/

#pragma once

#ifdef DEBUG
#define COMPILE_ALL_TYPES
#define COMPILE_ALL_SIZES
#endif // DEBUG

#pragma region TYPES
#ifdef COMPILE_FLOAT
#undef COMPILE_ALL_TYPES
#endif // COMPILE_FLOAT

#ifdef COMPILE_FLOAT
#undef COMPILE_ALL_TYPES
#endif // COMPILE_FLOAT

#ifdef COMPILE_FLOAT
#undef COMPILE_ALL_TYPES
#endif // COMPILE_FLOAT

#if defined(COMPILE_ALL_TYPES)
#define COMPILE_FLOAT
#define COMPILE_DOUBLE
#define COMPILE_LONG_DOUBLE
#endif // COMPILE_ALL_TYPES
#pragma endregion

#pragma region SIZES
#ifdef COMPILE_UINT8_T
#undef COMPILE_ALL_SIZES
#endif // COMPILE_UINT8_T

#ifdef COMPILE_UINT16_T
#undef COMPILE_ALL_SIZES
#endif // COMPILE_UINT16_T

#ifdef COMPILE_UINT32_T
#undef COMPILE_ALL_SIZES
#endif // COMPILE_UINT32_T

#ifdef COMPILE_UINT64_T
#undef COMPILE_ALL_SIZES
#endif // COMPILE_UINT64_T

#if defined(COMPILE_ALL_SIZES)
#define COMPILE_UINT8_T
#define COMPILE_UINT16_T
#define COMPILE_UINT32_T
#define COMPILE_UINT64_T
#endif // COMPILE_ALL_SIZES
#pragma endregion

#include "ActivationFunctions.h"
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <fstream>

namespace NeuralNetwork {

	template <typename TYPE=float, typename SIZE=uint16_t> class NeuralNetwork
	{
			  /* layer *//* neurons *//* weigths */
	private: std::vector<std::vector<TYPE>> NeuronsValue;

	private: std::vector<std::vector<std::vector<TYPE>>> Weigths;

	private: std::vector<SIZE> numNeurons;

	private: std::vector<ActivationFunctionType> aft;

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

	};

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TYPE"></typeparam>
	/// <typeparam name="SIZE"></typeparam>
	/// <param name="nn"></param>
	/// <returns></returns>
	template <typename TYPE, typename SIZE> std::string print(NeuralNetwork<TYPE, SIZE>& nn) {

	}

}