#pragma once
#include<iostream>
#include<string>
#include <iomanip>
#include <vector>

using namespace std;
#include "BigInt.h"
using namespace BignumArithmetic;

void FillWithData(BigDigit *numbers, int const amount)
{
	srand(time(NULL) + rand());
	for (int i = 0; i < amount; i++)
	{
		numbers[i].length = capacity - 1; // без последнего числа (так захотел)
		for (int p = 0; p < numbers[i].length; p++)
			numbers[i].store[p] = (rand() * rand()) % 0xffffffff;
	}
}
void TestSum()
{
	BigDigit *numbers; 
	int amount = 10000;
	numbers = new BigDigit[amount];
	FillWithData(numbers, amount);
	clock_t t11 = clock();
	clock_t t22 = clock();
	{
		cout << "------sum ------" << endl;
	
		t11 = clock();
		for (int i = 0; i < amount; i += 2)
		{
			bool f;
			BigDigit d = Add(numbers[i], numbers[i + 1], f);
		//	cout<<d.length<<" ";
		}
		t22 = clock();
		cout << "1: Time  : " << (double)(t22 - t11) / (double)CLOCKS_PER_SEC << '\n';		
	}
	delete[] numbers;
}