/******************************************************
 * ** Program: limits.cpp
 * ** Date: 01/13/2019
 * ** Description:Part 1 and 2 of Assignment 1 (finds max and min of shorts, ints and longs)
 * ** Input:None
 * ** Output: Max and mins for shorts, ints and longs (unsigned and signed)
 * ******************************************************/ 
#include <iostream>
#include <climits>
#include <cmath>

int main(){

	//Part 1 using climits
	std::cout << "Part 1 Preprocessor Macros: " << std::endl;
	std::cout << "Unsigned Long Max: " << ULONG_MAX << std::endl;
	std::cout << "Long Max: " << LONG_MAX << std::endl;
	std::cout << "Long Min:  " << LONG_MIN << std::endl;
	std::cout << "Unsigned Int Max:  " << UINT_MAX << std::endl;
	std::cout << "Int Max: " << INT_MAX << std::endl;
	std::cout << "Int Min: " << INT_MIN << std::endl;
	std::cout << "Unsigned Short Max: " << USHRT_MAX << std::endl;
	std::cout << "Short Max: " << SHRT_MAX << std::endl;
	std::cout << "Short Min " << SHRT_MIN << std::endl;
	std::cout << ""  << std::endl;

	//Part 2 without macros, equations learned in class
	std::cout << "Part 2 No Macros: " << std::endl;
	std::cout <<  "Unsigned Long Max: " << (unsigned long) pow(2,(sizeof(long)*8))-1 << std::endl;
	std::cout << "Long Max: " << (long) pow(2,sizeof(long)*8)-1 << std::endl;
	std::cout << "Long Min:  " << (long) pow(2, sizeof(long)*-8) << std::endl;
	std::cout << "Unsigned Int Max:  " << (unsigned int) pow(2,sizeof(int)*8)-1 << std::endl;
	std::cout << "Int Max: " << (int) pow(2,sizeof(int)*8)-1 << std::endl;
	std::cout << "Int Min: " << (int) pow(2,sizeof(int)*-8) << std::endl;
	std::cout << "Unsigned Short Max: " << pow(2,sizeof(short)*8)-1 << std::endl;
	std::cout << "Short Max: " << pow(2,sizeof(signed short)*8)/2-1 << std::endl;
	std::cout << "Short Min " << pow(2,sizeof(short)*8)/-2 << std::endl;

	return 0;
}
