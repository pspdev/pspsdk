/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.cpp - A basic C++ example for checking the GProf profiler.
 *
 * Copyright (c) 2024 Francisco Javier Trujillo Mata - fjtrujy@gmail.com
 *
 */
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>

#include <pspmoduleinfo.h>
#include <pspthreadman.h>

PSP_MODULE_INFO("GProf Basic C++ Example", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// Class to handle prime number operations
class PrimeCalculator
{
public:
	// Method to check if a number is prime
	bool isPrime(int num) const
	{
		if (num <= 1)
			return false;
		if (num <= 3)
			return true;
		if (num % 2 == 0 || num % 3 == 0)
			return false;
		for (int i = 5; i * i <= num; i += 6)
		{
			if (num % i == 0 || num % (i + 2) == 0)
				return false;
		}
		return true;
	}

	// Method to compute the sum of square roots of the first N prime numbers
	double sumOfSquareRoots(int N) const
	{
		int count = 0;
		int num = 2;
		double sum = 0.0;

		while (count < N)
		{
			if (isPrime(num))
			{
				sum += std::sqrt(num);
				count++;
			}
			num++;
		}
		return sum;
	}

	// Method to get the first N prime numbers
	std::vector<int> getFirstNPrimes(int N) const
	{
		std::vector<int> primes;
		int num = 2;

		while (primes.size() < static_cast<size_t>(N))
		{
			if (isPrime(num))
			{
				primes.push_back(num);
			}
			num++;
		}
		return primes;
	}
};

void dummyFunction()
{
	for (int i = 0; i < 10000; i++)
	{
		std::cout << ".";
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[])
{
	std::cout << "Hello from C++!" << std::endl;
	
	dummyFunction();
	
	PrimeCalculator calculator;
	int N = 10000; // Large number of primes to compute
	
	double sum = calculator.sumOfSquareRoots(N);
	std::cout << "Sum of square roots of the first " << N 
	          << " prime numbers is " << sum << std::endl;
	
	std::cout << "Goodbye from C++!" << std::endl;

	return 0;
}
