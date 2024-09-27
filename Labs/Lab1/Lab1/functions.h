#pragma once
#include <iostream>

bool isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}

int Reversed(int testNumber)
{
	int reversedNumber = 0;

	while (testNumber > 0)
	{
		int lastDigit = testNumber % 10;
		reversedNumber = reversedNumber * 10 + lastDigit;
		testNumber /= 10;
	}
	return reversedNumber;
}
bool isAPalindrome(int testNumber)
{
	int originalNum = testNumber;
	int reversedNum = 0;
	
	while (testNumber > 0)
	{
		int lastDigit = testNumber % 10;
		reversedNum = reversedNum * 10 + lastDigit;
		testNumber /= 10;
	}
	return originalNum == reversedNum;
}
bool isAPrimeNumber(int numbertoTest)
{
	if (numbertoTest < 2)
	{
		return false;
	}
	for (int i = 2; i * i <= numbertoTest; i++)
	{
		if (numbertoTest % i == 0)
		{
			return false;
		}
	}
	return true;
}
int input5CharsConvertToInt()
{
	int returnInt = 0;
	char inputChar;
	for (int i = 0; i < 5; i++)
	{
		std::cin >> inputChar;
		if (inputChar < '0' || inputChar > '9')
		{
			return 0;
		}
		//check if its a digit.
		//do something
		returnInt = returnInt * 10 + (inputChar - '0');
	}
	return returnInt;
}
int convertBinarytoDecimal(int binaryNumber)
{
	return 0;
}
void drawRightAngledTriangle()
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			std::cout << "A";
		}
		std::cout << std::endl;
	
	}
}
void drawIsocelesTriangle()
{
	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= i; ++j) {
			std::cout << "A";
		}
		std::cout << std::endl;
	}
	for (int i = 3; i >= 1; --i) {
		for (int j = 1; j <= i; ++j) {
			std::cout << "A";
		}
		std::cout << std::endl;
	}
}
void drawIsocelesTriangle2()
{

}

int find(int size, int arr[], int toFind)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == toFind)
		{
			return i;
		}
	}
	return -1;
}
int find2ndLargest(int size, int arr[])
{
	if (size < 2)
	{
		return -1;
	}
	int largest = 0;
	int secondLargest = 0;

	for (int i = 0; i < size; i++) 
	{
		if (arr[i] > largest) 
		{
			secondLargest = largest;
			largest = arr[i];
		}
		else if (arr[i] > secondLargest && arr[i] != largest) 
		{
			secondLargest = arr[i];
		}
	}

	return secondLargest;
}
void copyArraytoArray(int size, int arr1[], int arr2[])
{
	return;
}
bool insertElement(int& size, int& count, int arr[], int elementToInsert, int insertIndex)
{

	return false;
}
bool deleteElement(int& size, int& count, int arr[], int deleteIndex)
{

	return true;
}
int frequencyCount(int size, int arr[], int value)
{

	return 0;
}
int countDuplicates(int size, int arr[])
{

	return 0;
}
void reverse(int size, int arr[])
{
	return;
}
int rotateLeft(int size, int arr[])
{
	return -1;
}
bool twoMovies(int flightLength, int movieLengths[], int size)
{
	return false;
}
int wordCounter(int size, char characters[])
{
	return 0;
}