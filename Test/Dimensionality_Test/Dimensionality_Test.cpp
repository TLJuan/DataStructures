#include "pch.h"
#include <iostream>
#include <vector>
#include <math.h>
#include <utility>
#include <chrono>
#include <random>
#include <sstream>
#include <fstream>

using namespace std;

//output files paths
const string savePath = "Tests/";

//Euclidean distance for a n-dimensional vector
//dim = vector something.size() in calls
double euclDist(int dim, vector<double> A, vector<double> B)
{
	long double sum = 0;
	double val = 0;
	for (int i = 0; i < dim; i++)
	{
		val = (A[i] - B[i]);
		sum += (val*val);
	}
	return double(sqrt(sum));
}

//random generator 
//based on code from https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
vector<double> genRandom(double init, double limit, int times)
{
	std::random_device rd; //seed
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(init, limit);
	vector<double> v;
	for (int n = 0; n < times; ++n) {
		v.push_back(dis(gen));
	}
	return v;
}

template<short int dimension>
struct DataHolder
{
	vector<double> v;
	DataHolder()
	{
		v = genRandom(1.0, 10.0, dimension);
	}
};

template<int size, int dim>
class DistanceMatrix
{
	vector<vector<double>> Data;
public:
	DistanceMatrix()
	{
		//Create k vector of n dimensions - k(size), n(dim)
		for (int i = 0; i < size;i++)
		{
			DataHolder<dim> data;
			Data.push_back(data.v);
		}
		CalculateDistances();
	}
	~DistanceMatrix()
	{
		Data.empty();
	}
	void CalculateDistances()
	{
		//save file woth number of vectors + dim of vectors
		string detail = to_string(size) + "_" + to_string(dim)+".txt";
		//string matrix_details;
		double answer = 0;
		//distance processing
		std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0;i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				answer = euclDist(dim, Data[i], Data[j]);
				//matrix_details += to_string(answer) + " ";
				answer = 0;
			}
			//matrix_details += "\n";
		}
		end = std::chrono::high_resolution_clock::now();
		int64_t period = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		//saving values
		string to_save = to_string(size) + " vectors of dimension "+ to_string(dim)+"\n";
		to_save += "Used time:" + to_string(period) + " milliseconds. \n";
		//to_save+= matrix_details;
		ofstream output(detail);
		output << to_save;
		output.close();
	}
};

//sizes = { 10000, 20000,25000 };
//dim   = { 10,15,20 };

int main()
{
	DistanceMatrix<10000, 15> test_01;
	//
	cout << "Finish\n";
	DistanceMatrix<10000, 20> test_02;
	//
	cout << "Finish\n";
	DistanceMatrix<20000, 10> test_03;
	//
	cout << "Finish\n";
	DistanceMatrix<20000, 15> test_04;
	//
	cout << "Finish\n";
	DistanceMatrix<20000, 20> test_05;
	//
	DistanceMatrix<25000, 10> test_06;
	//
	cout << "Finish\n";
	DistanceMatrix<25000, 15> test_07;
	//
	cout << "Finish\n";
	DistanceMatrix<25000, 20> test_08;
	cout << "Finish\n";

	system("pause");
}