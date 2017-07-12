//Michael Ivanitskiy
//started july 10 2017

using namespace std;

class Card
{
public:
	//blank constructor for array creation
	Card() {}

	//real constructor
	Card(int in_index, int in_n)
	{
		index = in_index;
		n = in_n;
	}

	int get_row()
	{



	}

	int get_place()
	{



	}


	//take row (r), place (p)
	int to_index(int r, int p)
	{
		//use n(n+1)/2, add place in row
		int x = place + row * (r + 1) / 2;
		return x;
	}


	bool det = false;
	//value 0 for no det card, 1-3 for states
	int value = 0;
	//index (location in triangle, just in case)
	int index;
	//size of triangle
	int n;

};//end of card class
