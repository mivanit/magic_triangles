//Michael Ivanitskiy
//started july 10 2017

#include <iostream>
#include <limits>

int factorial(int n);
void pause();


// new faster function, does not use recursion
int factorial(int n)
{
	for(int i = (n-1); i > 0; i--)
	{
		n *= i;
	}
	return n;
}

/*
int factorial(int n)
{
	if (n == 1)
	{
		return 1;
	}
	else
	{
		return ( n * factorial(n-1) );
	}
}
*/


// new integer exponentiation function copied from stack exchange, old one was slow due to recursion
int pow_int(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

/*
int pow_int(int base, int exponent)
{
	if (exponent == 0)
	{
		return 1;
	}
	else
	{
		return (base * pow_int(base, (exponent - 1)));
	}
}
*/


void pause()
{
	std::cout << "Press ENTER to continue...";
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}
