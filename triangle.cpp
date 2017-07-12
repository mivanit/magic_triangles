//Michael Ivanitskiy
//started july 10 2017

#include "card.cpp"

using namespace std;

class Triangle
{
public:
	Triangle(int size)
	{
		n = size;
		cards = new Card[n+1];

	}

	//starts at 1, pyramid upwards
	//index starts from left side
	Card * cards;

	//card for using to_index
	Card crd();

	bool fill_tri()
	{
		bool result = true;

		for (int i = 1; i < size; i++)
		{
			if (fill_card(i) == false)
			{
				result = false;
			}
		}
	}

	bool fill_card(int index)
	{
		//r/p ==> row/place

		//get r/p of our card
		int r = trind[index].first;
		int p = trind[index].second;

		//temp r/p for checking
		int r_temp1;
		int p_temp1;

		int r_temp2;
		int p_temp2;

		//3 cases for fill:
		//2 cards above, or 2 cards to either side & below

		//check above
		bool test_up = 

		//check left
		bool test_left =

		//check right
		bool test_right =


	}

	//for checking 2 adjacent cards
	//returns true if both determined
	//USAGE:
	// takes original p/r, then modifiers
	// original r, p, 1st r mod, p mod, 2nd r mod, p mod
	bool check_2_adj(int r, int p, int r1, int p1, int r2, int p2)
	{
		bool test1 = cards[crd.to_idex(r+r1,p+p1)].det;
		bool test2 = cards[crd.to_idex(r+r2,p+p2)].det;

		return (test1 && test2);
	}

	void draw_tri()
	{



	}


private:
	int n;




};//end of triangle class
