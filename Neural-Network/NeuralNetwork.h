/**********************************************************************************************************************************\
 * file: NeuralNetwork.h
 *
 *  author: Karl Jahn tollpatsch3141@web.de
 *  date: 2021/08/20
 *
\**********************************************************************************************************************************/

#pragma once

#include "ActivationFunctions.h"
#include <stdexcept>
#include <vector>
#include <cstdint>
#include <fstream>

namespace NeuralNetwork {

	template <typename TYPE=float, typename SIZE=uint16_t> class NeuralNetwork
	{
			  /* layer *//* neurons *//* weigths */
	private: std::vector<std::vector<TYPE>> Neurons;

	private: std::vector<std::vector<std::vector<TYPE>>> Weigths;

	private: std::vector<SIZE> numNeurons;

	private: std::vector<ActivationFunctionType> aft;


	public: NeuralNetwork(std::initializer_list<SIZE> numNeurons);

	public: NeuralNetwork(std::vector<SIZE> numNeurons);

	public: NeuralNetwork(std::vector<std::vector<std::vector<TYPE>>> weigths, std::vector<ActivationFunctionType> afts /* for every layer on element */);


	public: ~NeuralNetwork();


	public: void setActivationFunctions(std::vector<ActivationFunctionType> afts);

	public: std::vector<ActivationFunctionType> getActivationFunctions();

		   
	public: std::vector<TYPE>* calc(std::vector<TYPE> inputs);


	public: std::vector<SIZE> getNumOfNeurons();


	public: void setWeigths(std::vector</*layer*/ std::vector</*neurons*/ std::vector</*weigths*/ TYPE>>>* weigths);

	public: std::vector</*layer*/ std::vector</*neurons*/ std::vector</*weigths*/ TYPE>>> getWeigths();


	public: TYPE getWeigthAt(SIZE layer, SIZE neuron, SIZE index);

	public: std::vector<TYPE> getWeigthAt(SIZE layer, SIZE neuron);

	public: std::vector<std::vector<TYPE>> getWeigthAt(SIZE layer);

	public: void setWeigthAt(SIZE layer, SIZE neuron, SIZE index, TYPE weigth);

	public: void setWeigthAt(SIZE layer, SIZE neuron, std::vector<TYPE>* weigths);

	public: void setWeigthAt(SIZE layer, std::vector<std::vector<TYPE>>* weigths);

	};

	template <typename TYPE, typename SIZE> std::string print(NeuralNetwork<TYPE, SIZE>& nn) {

	}

}