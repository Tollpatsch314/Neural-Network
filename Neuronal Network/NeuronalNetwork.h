#pragma once
#include <string>
#include <cmath>
#include <random>

class NeuronalNetwork
{

private: int inputnodes, hiddennodes, outputnodes;
private: float learningrate;
private: double** wih;
private: double** who;


/// <summary>
/// 
/// </summary>
/// <param name="inputnodes"></param>
/// <param name="hiddennodes"></param>
/// <param name="outputnodes"></param>
/// <param name="learningrate"></param>
public: NeuronalNetwork(int inputnodes, int hiddennodes, int outputnodes, float learningrate);

public: ~NeuronalNetwork();

public: std::string info();

public: void train();

public: void query();

public: double sigmoid(double x); // activation function

};

