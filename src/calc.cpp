//Michael Ivanitskiy
//started july 10 2017
//v 0.1 (july 14 2017)

#include <tuple>
#include <iostream>
#include <cassert>
#include "mylib.cpp"
#include "triangle.cpp"

using namespace std;

int test_tri(int n, bool draw);
void gen_tri_index(int n);
void print_trind_test();

//global variable for storing data
//for lookup of row, pair from index
//function in card.cpp handles other direction
//cause its much easier
//trind stands for triangle_index, im too lazy to type
pair<int,int> * trind;

int main()
{
	//DONT REMOVE THIS
	//GENERATES THE INDEX OF INDEX TO ROW/PLACE CONVERSIONS
	const int max_tri_size = 15;
	gen_tri_index(max_tri_size);


	//test triangles
	for (int i = 1; i <= 5; i++)
	{
		test_tri(i,false);
	}
}

int test_tri(int n, bool draw = false)
{
	//cout << "testing tri of size " << n << endl;

	//create triangle
	Triangle tester = Triangle(n, draw);

	//calculate
	int comb = tester.arrange_main();
	cout << "triangle size:\t" << n << "\tarrangements:\t" << comb << endl;

	//cout << "tri of size " << n << " complete!" << "\n\n";


	return comb;
}

//generate the index out to a size
//first term is row, second is place
//index starts at 0

void gen_tri_index(int n)
{
	//calculate what index we need to go out to
	int max = n * (n+1) / 2;

	trind = new pair<int,int>[max + 1];

	//row, place
	int r = 1;
	int p = 1;

	//lo
	for (int i = 1; i < max; i++)
	{
		//store values
		trind[i] = make_pair(r, p);

		//iterate row, pair:
		//if place is last item in row,
		//set place to 1 and iterate row
		if (p == r)
		{
			p = 1;
			r++;
		}
		else
		{
			//else, iterate place
			p++;
		}
	}
}


		//put in error checking for p > r?
void print_trind_test()
{
	gen_tri_index(10);

	for (int i = 1; i < 50; i++)
	{
		cout << trind[i].first << "\t" << trind[i].second << endl;
	}
}
