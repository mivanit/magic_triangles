//Michael Ivanitskiy
//started july 10 2017

#include <tuple>
#include <iostream>
#include <cassert>
#include "lib_math.cpp"
#include "triangle.cpp"
#include "data.cpp"

using namespace std;

int test_tris(int n, bool draw);

int main()
{
	cout << "magic_triangles started\n";
	const int max_tri_size = 20;
	// DONT REMOVE THIS
	// GENERATES THE INDEX OF (INDEX) TO (ROW/PLACE) CONVERSIONS
	gen_tri_index(max_tri_size);
	cout << "trind generated up to " << max_tri_size << endl;
	// DONT REMOVE THIS EITHER
	// GENERATES GLOBAL ARRAY OF FULL TRI DATA
	gen_tri_fulltbl(max_tri_size);
	cout << "tbl prepared up to " << max_tri_size << endl;
	cout << "===========================\n\n";

	// test triangles
	for (int i = 1; i <= 6; i++)
	{
		test_tris(i, false, true);
	}

	// print output
	print_tri_fulltbl(6);

	//pause();

}

int test_tris(int n, bool draw = false)
{
	//cout << "testing tri of size " << n << endl;

	//create triangle
	Triangle tester = Triangle(n, draw);

	//calculate
	int comb = tester.arrange_main();
	cout << "triangle size:\t" << n << "\tarrangements:\t" << comb << endl << endl;

	//cout << "tri of size " << n << " complete!" << "\n\n";


	return comb;
}
