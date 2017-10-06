// Michael Ivanitskiy

#include <iostream>
#include <cstring>
#include <fstream>

using std::ofstream;
using std::string;

// function prototyping
void wipe_all();
void write_to_file(string filename, char d);
void fill_steps_max(int n);
void fill_steps_to(int n);
int ipow(int base, int exp);

// stores number of steps to get to that index
int * steps_to;
// stores number of steps to fill a tri of that size
int * steps_max;
// stores number that everything is calculated out to
int num_calc = 0;


int main()
{
	std::cout << "begin program\n";
	fill_steps_max(10000);
	std::cout << "steps_to filled to " << num_calc << "\n";
	std::cout << "steps_max filled to " << num_calc << "\n";
	write_to_file("test_10000.csv", '\t');
	std::cout << "output printed!\n";
}

// function because im getting weird errors and its 4am
void wipe_all()
{
	delete steps_to;
	delete steps_max;
}

// function to write arrays to tsv/csv file
void write_to_file(string filename, char d)
{
	// get file ready
	ofstream fout;
	fout.open(filename);

	// write header
	fout << "index" << d << "steps" << d << "max" << '\n';

	// write each line
	for (int i = 1; i <= num_calc; i++)
	{
		fout << i << d << steps_to[i] << d << steps_max[i] << '\n';
	}
}


// fill each index with the maximum from steps_to up to that point
void fill_steps_max(int n)
{
	// set num_calc
	num_calc = n;

	// resize array
	steps_max = new int[n+1];

	// call fill_steps_to if needed
	fill_steps_to(n);

	// var to store maximum
	int max_so_far = 0;

	// using while loops because for loops are acting weird and its 4am
	int i = 1;

	// loop through each index
	while( i < (n+2) )
	{
		// test for new max
		if (steps_to[i] > max_so_far)
		{
			max_so_far = steps_to[i];
		}

		// store max in arr
		steps_max[i] = max_so_far;

		// iterate
		i++;
	}
}


// main function to fill
void fill_steps_to(int n)
{
	// the index 1 is defined as taking 0 steps to fill

	// resize array
	steps_to = new int[n+1];

	// fill with n, because every element will take at most n-1 steps to reach
	for(int i = 2; i < n+2; i++)
	{
		steps_to[i] = n;
	}

	// make the first element 0
	steps_to[1] = 0;

	// loop through each index needed
	for (int i = 1; i <= n+1; i++)
	{
		// get the current step value, add 1 to it to get next step value
		int k = steps_to[i] + 1;

		// loop variables for 3^j
		int j = 0;
		int h = 1;
		// loop through each j until index i+h exceeds n
		while (i+h <= n)
		{
			// if the current value in the array is larger, replace it
			if (steps_to[i+h] > k)
			{
				steps_to[i+h] = k;
			}

			// iterate counter
			j++;
			// calculate new index modifier
			h = ipow(3,j);
		}
	}
}


// fast integer exponentiation function
int ipow(int base, int exp)
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
