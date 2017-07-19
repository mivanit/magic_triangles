//Michael Ivanitskiy
//started july 10 2017

#include <iostream>
#include <limits>

int factorial(int n);
void pause();







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

void pause()
{
	std::cout << "Press ENTER to continue...";
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}
