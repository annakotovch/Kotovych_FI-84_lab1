#pragma once
#include<string>
using namespace std;

namespace BignumArithmetic
{
	int const capacity =  165;//2048/32 = 165
	short const bitsInBase = 32;
	unsigned long base = (1 << bitsInBase) - 1;
	//https://ru.stackoverflow.com/questions/633860/%D0%9F%D1%80%D0%BE%D0%B2%D0%B5%D1%80%D0%B8%D1%82%D1%8C-%D1%8F%D0%B2%D0%BB%D1%8F%D0%B5%D1%82%D1%81%D1%8F-%D0%BB%D0%B8-%D1%87%D0%B8%D1%81%D0%BB%D0%BE-%D1%81%D1%82%D0%B5%D0%BF%D0%B5%D0%BD%D1%8C%D1%8E-%D0%B4%D0%B2%D0%BE%D0%B9%D0%BA%D0%B8
	struct BigDigit
	{
		unsigned long int store[capacity];
		int length;
		BigDigit()
		{
			length = 0;
			for (int i = 0; i < capacity; i++)
				store[i] = 0;
		}
	};
	int Max(int const &a, int const &b)
	{
		if (a >= b)
			return a;
		return b;
	}
	BigDigit Add(BigDigit const &number1, BigDigit const &number2, bool &IsOverflow)
	{
		BigDigit result;
		unsigned long carry = 0;
		IsOverflow = false;
		unsigned long long  temp;
		int l = Max(number1.length, number2.length);
		for (int i = 0; i < l; i++)
		{
			temp = (unsigned long long)number1.store[i] + number2.store[i] + carry;
			result.store[i] = temp &(base);
			carry = temp >> bitsInBase;
			result.length++;
		}
		if (carry>0 && result.length == capacity)
		{
			IsOverflow = true;
		}// todo
		if (carry>0 && result.length < capacity)
		{
			result.store[result.length] = carry;
			result.length++;
		}
	
		return result;
	}
	BigDigit Substract(BigDigit const &number1, BigDigit const &number2, bool &IsNegative)
	{
		BigDigit result;
		int borrow = 0;
		IsNegative = false;
		 long long  temp;
		int l = Max(number1.length, number2.length);

		for (int i = 0; i < l; i++)
		{
			temp = ( long long)number1.store[i] - number2.store[i] - borrow;
			if (temp >= 0)
			{
				result.store[i] = temp;
				borrow = 0;
			}
			else
			{
				result.store[i] = base + 1 + temp;
				borrow = 1;
			}
		//	result.length++;
		}
	
		if (borrow == 1)
		{
			IsNegative = true;
		}
		for (int i = l - 1; i >= 0; i--)
		{
			if (result.store[i] > 0)
			{
				result.length = i + 1;
				break;
			}
		}
		if (result.length == 0)
			result.length = 1; // we get zero;
		return result;
	}

	BigDigit MultiplyByOneNumber(BigDigit const &number1, unsigned long const &number2, bool &IsOverflow)
	{
		IsOverflow = false;
		unsigned long carry  = 0;
		unsigned long long  temp;
		BigDigit result;
		for (int i = 0; i < number1.length; i++)
		{
			temp = (unsigned long long)number1.store[i] * number2 + carry;
			result.store[i] = temp & base;
			carry = temp >> bitsInBase; 
		}
		result.store[number1.length] = carry;
		if (carry>0)
			result.length = number1.length + 1;	
		else
			result.length = number1.length ;
		if ( result.length == capacity)
		{
			IsOverflow = true;
		}
		return result;
	}
	void LongShiftDigitsToHigh(BigDigit &number, int shift)
	{
		for (int i = number.length; i >= 0; i--)
			number.store[shift + i] = number.store[i];
		for (int i = 0; i < shift; i++)
			number.store[i] = 0;
		number.length += shift;
	}
	BigDigit Multiply(BigDigit const &number1, BigDigit const &number2, bool &IsOverflow)
	{
		IsOverflow = false;
		unsigned long carry = 0;
		BigDigit  temp;
		BigDigit result;
		for (int i = 0; i < number2.length; i++)
		{
			bool islocalOverflow = false;
			temp = MultiplyByOneNumber(number1, number2.store[i], islocalOverflow);
			if (islocalOverflow)
			{
				IsOverflow = true;
				break;
			}
			if (temp.length+i<capacity)
				LongShiftDigitsToHigh(temp, i);
			else
			{
				IsOverflow = true;
				break;
			}
			islocalOverflow = false;
			result = Add(result, temp, islocalOverflow);
			if (islocalOverflow)
			{
				IsOverflow = true;
				break;
			}
		}
		bool isZero = true;
		for (int i = result.length - 1; i >= 0; i--)
		{
			if (result.store[i] != 0)
				isZero = false;
		}
		if (isZero)
			result.length = 1;
		return result;
	}
	BigDigit Square(BigDigit const &number, bool &IsOverflow)
	{
		BigDigit result;
		IsOverflow = false;
		result = Multiply(number, number, IsOverflow);
		return result;
	}
	int GetBitInUsualNumber(unsigned long x)
	{
		int pos = 31;
		unsigned long t = 1 << 31;
		while (x < t)
		{
			pos--;
			t >>= 1;
		}
		return pos;
	}


	int BitLength(BigDigit const &number1)
	{
		int cell = number1.length - 1;
		int pos = GetBitInUsualNumber(number1.store[cell]);
		return cell*32+pos;

	}

	void setbit(BigDigit & number, int shift)
	{
		int offset = (shift / bitsInBase);
		int bitPosition = shift % bitsInBase;
		number.store[offset] |= (1 << bitPosition);		
	}

	int Compare(BigDigit const &number1, BigDigit const &number2)
	{	
		int l = Max(number1.length, number2.length);
		l--;
		int a=number1.store[l];
		while (number1.store[l] == number2.store[l] && l>=0)
			l--;
		if (l == -1 && number1.length== number2.length)  // всі цифри однакові
			return 0;
		else
			if (number1.store[l] > number2.store[l])
				return 1;
			else 
				return -1;
	}

	BigDigit  shiftBitsUpper(BigDigit const & number, int shiftBitCount)
	{
		
		BigDigit result;
		int shiftMod = shiftBitCount % bitsInBase;
		unsigned long  carryMask = (unsigned long)((1 << shiftMod) - 1);
		int offsetBytes = (shiftBitCount / bitsInBase);

		int outIndex;
		for (int i = number.length-1; i >= 0; i--)
		{
			outIndex = i + offsetBytes;
			
			{
				unsigned long src = number.store[i];
				unsigned long dst = (unsigned long)(src << shiftMod);
				
				result.store[outIndex] |= dst;

				unsigned long moved = src >> (bitsInBase - shiftMod);
				if (moved>0 && shiftMod != 0)
					result.store[outIndex + 1] |= moved;
				
			}
		}
		result.length = number.length + offsetBytes;
		unsigned long movedUpper = number.store[number.length - 1] >> (bitsInBase - shiftMod);
		if (movedUpper > 0 && shiftMod != 0)
			result.length++;
		return result;
	}

	void Division(BigDigit const &number1, BigDigit const &number2, BigDigit  &result, BigDigit  &remainder)
	{

		int k = BitLength(number2);//todo ?
		remainder = number1;
		{
			BigDigit zero;
			result = zero;
			result.length = 1;
		}
		while (Compare(remainder, number2) >= 0)
		{
			int t = BitLength(remainder);
		//	cout << t - k << endl;
			BigDigit temp = shiftBitsUpper(number2, t - k);			
			if(Compare(remainder, temp)<0)
			{
				t--;
				temp = shiftBitsUpper(number2, t - k);
			}
			bool isNegative;
			remainder = Substract(remainder, temp, isNegative);

			setbit(result, t - k);
		}
		
		for (int i = number1.length - 1; i >= 0; i--)
		{
			if (result.store[i] > 0)
			{
				result.length = i + 1;
				break;
			}
		}
	}
	void CreateNumber(BigDigit &number, string &str)
	{
		number.length = 0;
		for (int i = 0; i < capacity; i++)
			number.store[i] = 0;

		for (long long i = str.length(); i > 0; i -= 8)
		{
			if (i < 8)
			{
				string s;
				s = str.substr(0, i);
				unsigned long int t = (unsigned long int) strtoul(s.c_str(), NULL, 16);
				number.store[number.length] = t;
			}
			else
			{
				string s;
				s = str.substr(i - 8, 8);
				unsigned long int t = (unsigned long int) strtoul(s.c_str(), NULL, 16);
				number.store[number.length] = t;
			}
			number.length++;
		}
	}
}