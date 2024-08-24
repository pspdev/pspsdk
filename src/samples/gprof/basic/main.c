/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - A basic example for checking the GProf profiler.
 *
 * Copyright (c) 2024 Francisco Javier Trujillo Mata - fjtrujy@gmail.com
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <pspmoduleinfo.h>
#include <pspthreadman.h>

PSP_MODULE_INFO("GProf Basic Example", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// Function to check if a number is prime
int is_prime(int num)
{
	if (num <= 1)
		return 0;
	if (num <= 3)
		return 1;
	if (num % 2 == 0 || num % 3 == 0)
		return 0;
	for (int i = 5; i * i <= num; i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
			return 0;
	}
	return 1;
}

// Function to compute the sum of square roots of the first N prime numbers
double sum_of_square_roots(int N)
{
	int count = 0;
	int num = 2;
	double sum = 0.0;

	while (count < N)
	{
		if (is_prime(num))
		{
			sum += sqrt(num);
			count++;
		}
		num++;
	}
	return sum;
}

int dummy_function()
{
	int i;
	for (i = 0; i < 10000; i++)
	{
		printf(".");
	}
	printf("\n");
	return 0;
}

int main(int argc, char *argv[])
{
	printf("Hello, world!\n");
	dummy_function();
	int N = 10000; // Large number of primes to compute
	printf("Sum of square roots of the first %d prime numbers is %lf\n", N, sum_of_square_roots(N));
	printf("Goodbye, world!\n");

	return 0;
}