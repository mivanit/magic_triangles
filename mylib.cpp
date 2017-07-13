//Michael Ivanitskiy
//started july 10 2017

int factorial(int n);

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
