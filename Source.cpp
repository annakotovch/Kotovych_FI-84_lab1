#pragma once
#include<iostream>
#include<string>
#include <iomanip>
#include <vector>


using namespace std;
#include "BigInt.h"
using namespace BignumArithmetic;
#include "Tests.h"
using namespace BignumTests;
#include "SpeedTests.h"
void show(BigDigit &number)
{
	// следующие числа нам нужно печатать группами по 8 символов
	// поэтому сохраним текущий символ-заполнитель, а потом восстановим его
	cout << hex;
	char old_fill = cout.fill('0');
	for (long long i = number.length-1; i >= 0; --i)
		cout << setw(8) << number.store[i] << " ";
	cout.fill(old_fill);
	cout << endl;
	cout << dec;
}

int main()
{
	cout << "----tests----" << endl;
	CheckAllOperations();
	cout << "-------------" << endl;


	BigDigit zerro;
	zerro.length = 1;
	zerro.store[0] = 0;

	BigDigit one;
	one.length = 1;
	one.store[0] = 1;


	BigDigit a1,b1,c1;
	//cout << "4 294 967 295"  << endl;
	//cout << hex << 4294967295 << endl;
	//unsigned long l = (1 << 32) -1;
	//cout << dec<<(l) << endl;
	// w=16 65 536
	// чи w = 32   4 294 967 296
	//cin >> str;
	string str;

	str = "fffffffe";

	CreateNumber(a1, str);
	str = "2";
	CreateNumber(b1, str);
	
	cout << "----Continue ----" << endl;
	show(a1);
	show(b1);
	
	cout << "--------" << endl;
	{
		bool IsNegative;
		c1 = Substract(b1, a1, IsNegative);
		if (IsNegative)
			cout << "we get negative number" << endl;
	}

	TestSum();
	system("pause");
}