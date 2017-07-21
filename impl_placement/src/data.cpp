// Michael Ivanitskiy
// started july 10 2017

#include <iostream>
#include <fstream>

// global variable for storing data
// for lookup of row, pair from index
// function in card.cpp handles other direction
// cause its much easier
// trind stands for triangle_index, im too lazy to type
// TODO:50 fix the mess that is all the rotation code
pair<int,int> * trind;

// global variable for storing data on the full triangle
int ** tbl;



void gen_tri_index(int n);
void print_trind_test();

int * test_tri_fulltbl(int n, string filename = "");
void print_tri_fulltbl(int n, int * tbl);




/*

	████████ ██████  ██ ███    ██ ██████
	   ██    ██   ██ ██ ████   ██ ██   ██
	   ██    ██████  ██ ██ ██  ██ ██   ██
	   ██    ██   ██ ██ ██  ██ ██ ██   ██
	   ██    ██   ██ ██ ██   ████ ██████

*/


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


// TODO: put in error checking for p > r?
void print_trind_test()
{
	gen_tri_index(10);

	for (int i = 1; i < 50; i++)
	{
		cout << trind[i].first << "\t" << trind[i].second << endl;
	}
}




/*

	████████ ██████  ██
	   ██    ██   ██ ██
	   ██    ██████  ██
	   ██    ██   ██ ██
	   ██    ██████  ███████

*/





int * gen_tri_fulltbl(int n)
{
	// initialize array tbl
	tbl = new int*[n+1];
	for(int i = 0; i <= n; i++)
	{
		tbl[i] = new int[n+1];
		for(int j = 0; j <= n; j++)
		{
			tbl[i][j] = 0;
		}
	}

	// tbl[i] holds array with n elements
	// containing # of arrangements for tri of size n
	// where tbl[i][j] holds the number of arrangements for tri size x,
	// with y cards on the top row
	// tbl[i][0] hold total for that n
}

// print the data up to n
void print_tri_fulltbl(int n, string filename = "")
{
	// if filename left blank, use cout
	// otherwise, use the file name
	// TODO: is there a way to declare ostream and switch between it being cout and an ofstream?
	if (filename.length() != 0)
	{
		ofstream fout;
		fout.open (filename);

		// print key
		fout << "n\ttotal\tnum top row" << endl;

		for(int i = 1; i <= n; i++)
		{
			// print current n for readability
			fout << i << "\t";

			// loop through each value
			for(int j = 0; j <= n; j++)
			{
				// print it
				fout << tbl[i][j] << "\t";
			}
			fout << endl;
		}

		fout.close();
	}
	else
	{
		// print key
		cout << "n\ttotal\tnum top row" << endl;

		for(int i = 1; i <= n; i++)
		{
			// print current n for readability
			cout << i << "\t";

			// loop through each value
			for(int j = 0; j <= n; j++)
			{
				// print it
				cout << tbl[i][j] << "\t";
			}
			cout << endl;
		}
	}
}
