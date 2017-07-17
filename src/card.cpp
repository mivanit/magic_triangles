//Michael Ivanitskiy
//started july 10 2017

using namespace std;

extern pair<int,int> * trind;

class Card
{
public:


	/*

	 ██████ ████████  ██████  ██████
	██         ██    ██    ██ ██   ██
	██         ██    ██    ██ ██████
	██         ██    ██    ██ ██   ██
	 ██████    ██     ██████  ██   ██

	*/



	//blank constructor for array creation
	Card() {}

	//real constructor
	Card(int in_index, int in_n)
	{
		index = in_index;
		n = in_n;
	}

	//copy constructor
	Card(Card * x)
	{
		index = x->index;
		n = x->n;
		det = x->det;
		//value = x->value;
		place_order = x->place_order;
	}



	/*

	██   ██ ███████ ██      ██████  ██████
	██   ██ ██      ██      ██   ██ ██   ██
	███████ █████   ██      ██████  ██████
	██   ██ ██      ██      ██      ██   ██
	██   ██ ███████ ███████ ██      ██   ██

	*/



	bool place(int x)
	{
		det = true;
		place_order = x;
	}

	bool fill()
	{
		det = true;
		place_order = -1;
	}

	bool get_det()
	{
		return det;
	}


	int get_row()
	{
		return trind[index].first;
	}

	int get_place()
	{
		return trind[index].second;
	}


	//take row (r), place (p)
	int to_index(int r, int p)
	{
		//use n(n+1)/2 with n=r-1, add place in row
		int x = p + r * (r - 1) / 2;
		return x;
	}



	/*

	██    ██  █████  ██████  ███████
	██    ██ ██   ██ ██   ██ ██
	██    ██ ███████ ██████  ███████
	 ██  ██  ██   ██ ██   ██      ██
	  ████   ██   ██ ██   ██ ███████

	*/

	//assignment operator
	//Card operator=(Card * rhs)
	//{	return Card(rhs);	}

	// 0 if undet,
	// -1 if by fill,
	// x otherwise
	int place_order = 0;

	//int value = 0;
	//index (location in triangle, just in case)
	int index;
	//size of triangle
	int n;

private:
	//whether card is determined
	bool det = false;

};//end of card class