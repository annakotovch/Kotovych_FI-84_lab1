
#pragma once
#include<iostream>
#include<string>
#include <iomanip>
#include <vector>

using namespace std;
#include "BigInt.h"
using namespace BignumArithmetic;

namespace Local
{
	void show(BigDigit &number)
	{
		cout << hex;
		char old_fill = cout.fill('0');
		for (long long i = number.length - 1; i >= 0; --i)
			cout << setw(8) << number.store[i] << " ";
		cout.fill(old_fill);
		cout << endl;
		cout << dec;
	}
}
namespace BignumTests
{

	void Add()
	{
		
		{
			BigDigit a1, b1, result;
			string str;
			str = "fffffffffffffffe";
			CreateNumber(a1, str);
			str = "3";
			CreateNumber(b1, str);
		
			bool IsOverflow = false;
			result = Add(a1, b1, IsOverflow);
			BigDigit expected;
			str = "10000000000000001";
			CreateNumber(expected, str);
			if (!(Compare(expected, result) ==0))
				cout << "Error in Addition " << endl;
			if (IsOverflow)
				cout << "Error in Addition " << endl;
		}
		
		{
			BigDigit a1, b1, result;
			unsigned long int e = 0xffffffffffffffff;
			a1.length = capacity;
			for (int i = 0; i < capacity; i++)
				a1.store[i] = e;
			string str;
			str = "1";
			CreateNumber(b1, str);
			bool IsOverflow = false;
			result = Add(a1, b1, IsOverflow);
			if (!IsOverflow)
				cout << "Error with overflow in Addition " << endl;
		}	

	}
	void Compare()
	{
		BigDigit a1, b1, c1;
		string str;
		str = "fffffffffffffffe";
		CreateNumber(a1, str);
		CreateNumber(b1, str);
		
		if (Compare(a1, b1) != 0)
		{
			Local::show(a1);
			Local::show(b1);
			cout << "Compare does not work properly. Equal numbers are not equal" << endl;
		}


		str = "fffffffffffffffe";
		CreateNumber(a1, str);
		str = "fffffff1fffffffe";
		CreateNumber(b1, str);

		if (Compare(a1, b1) == 0)
		{
			Local::show(a1);
			Local::show(b1);
			cout << "Compare does not work properly. Not Equal numbers are equal" << endl;
		}

		str = "fffffffffffffffe";
		CreateNumber(a1, str);
		str = "ffffffffeffffffe";
		CreateNumber(b1, str);
		if (Compare(a1, b1) <=0)
		{
			Local::show(a1);
			Local::show(b1);
			cout << "Compare does not work properly. Biger number is not biger" << endl;
		}
		str = "fffffffffffffffe";
		CreateNumber(a1, str);
		str = "e";
		CreateNumber(b1, str);
		if (!(Compare(a1, b1) > 0))
		{
			Local::show(a1);
			Local::show(b1);
			cout << "Compare does not work properly. Bigger number is not bigger" << endl;
		}
		str = "ff";
		CreateNumber(a1, str);
		str = "fffffffffffffffe";
		CreateNumber(b1, str);
		if (!(Compare(a1, b1) < 0))
		{
			Local::show(a1);
			Local::show(b1);
			cout << "Compare does not work properly. Smaller number is not Smaller" << endl;
		}
	}
	void Substract()
	{
		{
			BigDigit a1, b1, result;
			string str = "fffffffe";
			CreateNumber(a1, str);
			str = "2";
			CreateNumber(b1, str);
			bool IsNegative=false;
			result = Substract(a1, b1, IsNegative);

			if (IsNegative)
				cout << "Error with negative flag in substract, must be false " << endl;
			BigDigit expected;
			str = "fffffffc";
			CreateNumber(expected, str);
			if (!(Compare(expected, result) == 0))
				cout << "Error in substract " << endl;
		}

		{
			BigDigit a1, b1, result;
			string str = "fffffffe";
			CreateNumber(a1, str);
			str = "2";
			CreateNumber(b1, str);
			bool IsNegative = false;
			result = Substract(b1, a1, IsNegative);
			if (!IsNegative)
				cout << "Error with negative flag in substract, must be true " << endl;
		}
		{
			BigDigit a2, b2, result;
			string str = "10000000e";
			CreateNumber(a2, str);
			str = "fffffffe";
			CreateNumber(b2, str);			
			bool IsNegative = false;
			result = Substract(a2, b2, IsNegative);

			if (IsNegative)
					cout << "Error with negative flag in substract, must be false " << endl;
			BigDigit expected;
			str = "10";
			CreateNumber(expected, str);
			if (!(Compare(expected, result) == 0))
				cout << "Error in substract " << endl;
		}
	}
	void  MultiplyByOneNumber()
	{
		{
			BigDigit a1, result;
			string str;
			str = "10ffffff0fffff0ffe";
			CreateNumber(a1, str);
			unsigned long b1 = 4;
			bool IsOverflow=false;
			result = MultiplyByOneNumber(a1, b1, IsOverflow);

			BigDigit expected,temp;
			temp = Add(a1, a1, IsOverflow);
			expected = Add(temp, temp, IsOverflow);
			if (!(Compare(expected, result) == 0))
				cout << "Error in MultiplyByOneNumber" << endl;
			if (IsOverflow)
				cout << "Error in MultiplyByOneNumber" << endl;
		}
		{
		BigDigit a1, result;
		string str;
		str = "f000000000000000";
		CreateNumber(a1, str);
		unsigned long b1 = 5;
		bool IsOverflow = false;
		result = MultiplyByOneNumber(a1, b1, IsOverflow);

		BigDigit expected;
		str = "4b000000000000000";
		CreateNumber(expected, str);
		if (!(Compare(expected, result) == 0))
			cout << "Error in MultiplyByOneNumber" << endl;
		if (IsOverflow)
			cout << "Error in MultiplyByOneNumber" << endl;
		}
		{// check a*n = a+a+...+n; 
			BigDigit a1, result;
			string str;
			str = "f0000000ab000001";
			CreateNumber(a1, str);
			unsigned long b1 = 105;
			bool IsOverflow=false;
			result = MultiplyByOneNumber(a1, b1, IsOverflow);
			if (IsOverflow)
				cout << "Error in MultiplyByOneNumber" << endl;

			BigDigit expected;
			CreateNumber(expected, str);
			IsOverflow = false;
			for (int i = 0; i < b1-1; i++)
			{
				expected = Add(expected, a1, IsOverflow);
				if (IsOverflow)
				{
					cout << "Error in MultiplyByOneNumber" << endl;
					break;
				}
			}
			if (!(Compare(expected, result) == 0))
				cout << "Error in MultiplyByOneNumber" << endl;
			if (IsOverflow)
				cout << "Error in MultiplyByOneNumber" << endl;
		}
	}

	void Multiply()
	{
		{
			BigDigit a1,b1, result;
			string str;
			str = "10ffffff0fffff0ffe";
			CreateNumber(a1, str);
			"D C040 FF4C";
				str = "dc040ff4c";// =  0xeaaefff4 * f
			CreateNumber(b1, str);

			unsigned long d = 0xeaaefff4;
			unsigned long d1 = 0xf;
			bool IsOverflow = false;
			BigDigit expected,  temp;
		
				expected = MultiplyByOneNumber(a1, d, IsOverflow);
				expected = MultiplyByOneNumber(expected, d1, IsOverflow);

			result = Multiply(a1, b1, IsOverflow);
			if (!(Compare(expected, result) == 0))
				cout << "Error in Multiply" << endl;
			if (IsOverflow)
				cout << "Error in Multiply" << endl;
		}
		{
		BigDigit a1, b1, c1;
		string str;
		str = "10ffffff0fffff0ffe";
		CreateNumber(a1, str);

		str = "12dc040ff4c";
		CreateNumber(b1, str);

		str = "74dc040ff4c0101";
		CreateNumber(c1, str);

		bool IsOverflow = false;
		BigDigit expected1, temp;

		temp = Add(a1, b1, IsOverflow);
		expected1 = Multiply(temp, c1, IsOverflow);


		BigDigit expected2, mult1, mult2;

		mult1 = Multiply(a1, c1, IsOverflow);
		mult2 = Multiply(b1, c1, IsOverflow);
		expected2 = Add(mult1, mult2, IsOverflow);
		if (!(Compare(expected1, expected2) == 0))
			cout << "Error in Multiply" << endl;

	}
		{
			BigDigit zero;
			zero.length = 1;

			BigDigit a1, b1, c1;
			string str;
			str = "10ffffff0fffff0ffe";
			CreateNumber(a1, str);
			bool IsOverflow;
			b1 = Multiply(a1, zero, IsOverflow);
			if (b1.length!=1)
				cout << "Error in Multiply, wrong length in zero" << endl;
			if (!(Compare(b1, zero) == 0))
				cout << "Error in Multiply. missed zero" << endl;
		}
		{
			BigDigit zero;
			zero.length = 1;

			BigDigit a1, b1, c1;
			string str;
			str = "10ffffff0fffff0ffe";
			CreateNumber(a1, str);
			bool IsOverflow;
			b1 = Multiply( zero, a1,IsOverflow);
			if (b1.length != 1)
				cout << "Error in Multiply, wrong length in zero" << endl;
			if (!(Compare(b1, zero) == 0))
				cout << "Error in Multiply. missed zero" << endl;
		}
		{
			BigDigit one;
			one.length = 1;
			one.store[0] = 1;
			BigDigit a1, b1, c1;
			string str;
			str = "10ffffff0fffff0ffe";
			CreateNumber(a1, str);
			bool IsOverflow;
			b1 = Multiply(one, a1, IsOverflow);
			
			if (!(Compare(b1, a1) == 0))
				cout << "Error in Multiply. missed one" << endl;
		}

	}
	void ShowExamples()
	{
		BigDigit a1, b1, c1;
		string str;

		str = "fffffffffffffffe";
		CreateNumber(a1, str);
		str = "2";
		CreateNumber(b1, str);
		cout << "Numbers : " << endl;
		Local::show(a1);
		Local::show(b1);
		{
			bool IsOverflow;
			c1 = Add(a1, b1, IsOverflow);
		}
		cout << "Result of add : "  << endl;
		Local::show(c1);
		{
			bool IsNegative;
			c1 = Substract(a1, b1, IsNegative);
		}
		cout << "Result of substract : " << endl;
		Local::show(c1);

		{
			string str;
			str = "f000000000000000";
			CreateNumber(a1, str);
			unsigned long b1 = 5;
			bool IsOverflow;
			c1 = MultiplyByOneNumber(a1, b1, IsOverflow);
		}
		cout << endl;
	
		cout << "Result of multiply" << endl;
		Local::show(a1);
		cout << "by number 5 : " << endl;
		Local::show(c1);
	}
	void Bits()
	{
		unsigned long n = 0x80000000;
		int pos = GetBitInUsualNumber(n);
		if (pos !=31)
			cout << "Error in Bits" << endl;
		n = 0x40000000;
		pos = GetBitInUsualNumber(n);
		if (pos != 30)
			cout << "Error in Bits" << endl;
		n = 0x2;
		pos = GetBitInUsualNumber(n);
		if (pos != 1)
			cout << "Error in Bits" << endl;
		n = 0x0;
		pos = GetBitInUsualNumber(n);
		if (pos != -1)
			cout << "Error in Bits" << endl;


		n = 0x20000000;
			pos = GetBitInUsualNumber(n);
		if (pos != 29)
			cout << "Error in Bits" << endl;

		BigDigit a1;
		string str;
		str = "4000000040000000";
		CreateNumber(a1, str);
		pos = BitLength(a1);
		if (pos != (30+32))
			cout << "Error in bits in BigDigit" << endl;
		

		str = "40000000";
		CreateNumber(a1, str);
		setbit(a1, 29);
		str = "4000000040000000";
		CreateNumber(a1, str);
		setbit(a1, 61);
		BigDigit expected;
		str = "6000000040000000";;
		CreateNumber(expected, str);
		if (!(Compare(a1, expected) == 0))
			cout << "Error in setbit for BigDigit" << endl;


		str = "f00000f0";
		CreateNumber(a1, str);
		BigDigit result = shiftBitsUpper(a1, 1);
		str = "1e00001e0";
		CreateNumber(expected, str);
		if (!(Compare(result, expected) == 0))
			cout << "Error in shiftBitsLeft" << endl;

		result = shiftBitsUpper(a1, 33);
		str = "1e00001e000000000";
		CreateNumber(expected, str);
		if (!(Compare(result, expected) == 0))
			cout << "Error in shiftBitsLeft" << endl;

		result = shiftBitsUpper(a1, 32);
		str = "f00000f000000000";
		CreateNumber(expected, str);
		if (!(Compare(result, expected) == 0))
			cout << "Error in shiftBitsLeft" << endl;
		//		r = ShiftBitsToHigh(n, 3);
		//		cout << r;
		{
			string str;
				
			BigDigit result, expected,a1;
			str = "a210000000";
			CreateNumber(a1, str);
			str = "a2100000000";
			CreateNumber(expected, str);
			result = shiftBitsUpper(a1, 4);
			if (!(Compare(result, expected) == 0))
				cout << "Error in shiftBitsLeft" << endl;
		}
	}
	void Division()
	{
		{
		BigDigit a1, b1, result, mod, expected;
		string str;
		str = "502878";
		CreateNumber(a1, str);
		str = "78";
		CreateNumber(b1, str);

		Division(a1, b1, result, mod);

		str = "ab01";
		CreateNumber(expected, str);
		if (!(Compare(result, expected) == 0))
			cout << "Error in Division" << endl;



		str = "9";
		CreateNumber(expected, str);

		str = "20000000";

		CreateNumber(a1, str);

		str = "15";
		CreateNumber(mod, str);
		BigDigit d;
		bool f;
		d = Multiply(a1, expected, f);
		d = Add(d, mod, f);
		BigDigit result1, result2;

		Division(d, a1, result1, result2);
		if (!(Compare(result1, expected) == 0))
			cout << "Error in Division " << endl;
		if (!(Compare(result2, mod) == 0))
			cout << "Error in Division " << endl;
	}
		{
		BigDigit a1, b1, result, mod, expected;
		string str;
		str = "a473fa31f0";
		CreateNumber(expected, str);

		
		str = "1107823a21fa31f380";
		CreateNumber(a1, str);

		str = "ea15";
		CreateNumber(mod, str);
		BigDigit d,d1;
		bool f;
		d = Multiply(a1, expected, f);
		d1 = Multiply( expected, a1,f);
		d = Add(d, mod, f);
		BigDigit result1, result2;


		Division(d, a1, result1, result2);
		if (!(Compare(result1, expected) == 0))
			cout << "Error in Division " << endl;
		if (!(Compare(result2, mod) == 0))
			cout << "Error in Division " << endl;

		}
		{
			BigDigit a1, b1, result, expected;
			BigDigit d, d1;
			string str;
			str = "f0";
			expected.length = 1;
			CreateNumber(d, str);
			str = "f380";
			CreateNumber(a1, str);	
			bool f;
			BigDigit result1, result2;
			Division(d, a1, result1, result2);
			if (!(Compare(result1, expected) == 0))
				cout << "Error in Division " << endl;
			if (!(Compare(result2, d) == 0))
				cout << "Error in Division " << endl;

		}
	}
	void CheckAllOperations()
	{
		Compare();
		Add();
		Substract();
		ShowExamples();
		MultiplyByOneNumber();
		Multiply();
		Bits();
		Division();
	}
}