//Michael Ivanitskiy
//started july 10 2017

using namespace std;

extern pair<int,int> * trind;

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

	//copy constructor
	Card(Card * x)
	{
		index = x->index;
		n = x->n;
		det = x->det;
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


	bool det = false;
	//value 0 for no det card, 1-3 for states
	//int value = 0;
	//index (location in triangle, just in case)
	int index;
	//size of triangle
	int n;

	//assignment operator
	void operator=(Card * rhs)
	{
		index = rhs->index;
		n = rhs->n;
		det = rhs->det;
	}

};//end of card class
