﻿// MakkiNeurons.cpp : Defines the entry point for the application.
//

#include <ctime>
#include "MakkiNeurons.h"

using namespace std;

void testMultiply()
{
	cout << "Multiply test." << endl;
	RandomSupplier random;

	float farray1[6] = {1.0, 2.0, 0.0, 7.0, 0.0, 7.0};
	ArraySupplier array1 = ArraySupplier(farray1, 6);
	float farray2[12] = {4.0, 6.0, 6.0, 7.0, 0.0, 7.0, 4.0, 6.0, 6.0, 7.0, 0.0, 7.0};
	ArraySupplier array2 = ArraySupplier(farray2, 12);

	auto layer1 = new BrainLayer(6, 1, &array1);
	auto layer2 = new BrainLayer(2, 6, &array2);
	auto layer3 = new BrainLayer(2, 1);
	layer1->Print();
	cout << endl;
	layer2->Print();
	cout << endl;
	layer3->SetToZeros();
	layer1->Multiply(layer2, layer3);
	layer3->Print();

	delete (layer1);
	delete (layer2);
	delete (layer3);
}

void testBrain(Brain *brain, float *input, size_t input_len, float *output, size_t output_len)
{

	brain->SetInput(input, input_len);
	brain->Calculate(output, output_len);
}

void testBrain()
{
	LeakyReLuFunction func;
	RandomRangeSupplier random;
	auto brain = Brain(&func, &random);
	// brain.SetDebug(true);
	brain.Append(4, &random);
	brain.Append(8000, &random);
	brain.Append(8000, &random);
	brain.Append(2);

	float input1[4] = {0, 0, 0, 0};
	float input2[4] = {1, 1, 1, 1};
	float input3[4] = {1, 0, 0, 1};
	float input4[4] = {1, 1, 0, 0};
	float input5[4] = {0, 0, 0, 1};
	float input6[4] = {0, 0, 1, 1};

	float output[2] = {0, 0};

	clock_t begin = clock();
	for (int i = 0; i < 1; i++)
	{
		testBrain(&brain, input1, 4, output, 2);
		testBrain(&brain, input2, 4, output, 2);
		testBrain(&brain, input3, 4, output, 2);
		testBrain(&brain, input4, 4, output, 2);
		testBrain(&brain, input5, 4, output, 2);
		testBrain(&brain, input6, 4, output, 2);
	}
	clock_t end = clock();
	double elapsed_secs = double(end - begin);
	cout << "Elapsed time: " << elapsed_secs << "ms." << endl;

	BrainStructure* brain_sturcture = brain.GetStructure();
	for (int i; i < brain_sturcture->len; i++) {
		cout << " " << brain_sturcture->array[i] << endl;
	}
	delete brain_sturcture;
}

int main()
{
	cout << "Hello compiler." << endl;
	// testMultiply();
	testBrain();
	return 0;
}
