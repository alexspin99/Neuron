#include<iostream>
#include<cmath>
#include <cstdlib>
#include<time.h>
using namespace std;

//Create the hebb function to return Weights, learning set will be passed as parameters
const int ROWS = 4; //Number of learning sets
const int COLS = 8; //Number of samples in each set

//prototypes
void hebb(double[COLS], double[ROWS][COLS]); 
void outputZ(bool); 
void outputY(bool, bool); //first bool controls printing y values, second is recalculating
void ErCor(double[ROWS][COLS], double[COLS], bool);
void displayWeights();

//Learning set with binary inputs
double x[ROWS][COLS] = {
	{ 1,1,1,1,1,1,1,1 }, //x0
	{ 1, 1, 1, 1, -1, -1, -1, -1 }, //x1
	{ 1, 1, -1, -1, 1, 1, -1, -1}, //x2
	{ 1, -1, 1, -1, 1, -1, 1, -1} //x3
};										 

//desired outputs
//double f[COLS] = { 1, 1, 1, -1, 1, 1, -1, -1 }; //p.14
//double f[COLS] = { 1, -1, -1, -1, 1, -1, 1, -1 }; //p.15
//double f[COLS] = { 1, 1, -1, 1, -1, 1, 1, 1 }; //p.15
double f[COLS] = {1, 1, 1, -1, 1, 1, 1, -1};  //midterm



//Weights
double W[ROWS];
//experimental z and y
double z[COLS];
double y[COLS];

int main() {
	
	//error correct
	ErCor(x, f, false);  //parameters input, output, bool if you want to use hebb or not (rand)
	displayWeights();
	outputY(true, false); //prints out Y which was calculated in ErCor function
	
	cin.get(); //stops window from closing
	return 0;
}

void hebb(double f[COLS], double x[ROWS][COLS]) {
	double prod; //used to store product
	for (int z = 0; z < ROWS; z++) {
		double norm = 0; //stores number of cols as double for normalization
		for (int i = 0; i < COLS; i++)
		{
			//dot product
			prod = f[i] * (1 / x[z][i]);
			W[z] = W[z] + prod;

			norm++;
		}
		//normalize for each W[z]
		W[z] = 1 / norm * W[z];
	}
}

//parameters are error and current learning set
void correctWeights(double error, int j) {
	for (int i = 0; i < ROWS; i++) {
		W[i] = W[i] + error * (1/x[i][j]); //Need to use reciprocal of x or it may not work for nonbinary inputs
	}
}

void ErCor(double x[ROWS][COLS], double f[COLS], bool hebbian) {
	
	if (hebbian == true) {   //calculates hebbian weight vector
		cout << "Hebbian Learning: " << endl;
		hebb(f, x);
		displayWeights();
		outputZ(false);       //calculate z and actual output y
		outputY(true, true);
	}
	else {    //calculates random weights
		srand(time(NULL));
		for (int i = 0; i < ROWS; i++) {
			double random = (double)rand() / RAND_MAX - 0.5;
			W[i] = random;
		}
		cout << "Generated Random Weights: ";
		displayWeights();
		outputZ(false);
		outputY(true, true);
	}



	int iterations = 0;
	//if learning is true, it is learning, if false it is done
	bool learning = true; 
	
	while (learning == true)
	{
		double error; //variable used to store error at each sample
		learning = false; //set to false at beginning of each iteration
		iterations++;
		for (int j = 0; j < COLS; j++)
		{
			outputZ(false);
			outputY(false, true);
			if (y[j] != f[j]) {  //If actual and desired outputs !=, learn
				learning = true; 
				error = f[j] - y[j]; //desired - actual = error
				correctWeights(error, j);
			}
		}
	}

	cout << endl << endl << "Error Correction: " << "iterations = " << iterations << endl;
	
}

//calculates z and outputs it if bool parameter is true
void outputZ(bool print) {

	if (print == true) { cout << endl << "The weighted sums (z) for this neuron are: " << endl; }

	for (int j = 0; j < COLS; j++)
	{
		double outputs;
		outputs = W[0];
		for (int i = 1; i < ROWS; i++) //starts at 1 since W0 is already added to the output
		{
			outputs = outputs + W[i] * x[i][j];
		}
		z[j] = outputs;
		//print on screen if bool is true
		if (print == true){ cout << z[j] << ", "; }
		
	}
}

//calculates Y and outputs it if bool parameter is true
void outputY(bool print, bool calculate) {

	if (print == true) { cout << endl << "The actual output values for this neuron are: " << endl; }

	for (int j = 0; j < COLS; j++)
	{
		if (calculate == true) {
			if (z[j] > 0) { y[j] = 1; }
			if (z[j] < 0) { y[j] = -1; }
			if (z[j] = 0) { y[j] = z[j]; }
		}
		//print on screen if bool is true
		if (print == true){ cout << y[j] << ", "; }
	}
}

void displayWeights() {
	cout << "W[] = ";
	for (int i = 0; i < ROWS; i++) {
		cout << W[i] << ",";
	}
}