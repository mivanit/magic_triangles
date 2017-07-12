//Michael Ivanitskiy
//started july 10 2017

#include "card.cpp"

using namespace std;

extern pair<int,int> * trind;

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
	Card crd;

	bool fill_tri()
	{
		bool result = true;

		for (int i = 1; i < n; i++)
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

		//3 cases for fill:
		//2 cards above, or 2 cards to either side & below

		bool changed = false;


		//TODO: add error checking for if more than one set tries to define this card
		//this shouldnt be possible but I haven't proved it yet so idk
		if (chk_adj(r,p,1,0,1,1))
		{
			//check above
			changed = true;
		}
		else if (chk_adj(r,p,0,-1,-1,-1))
		{
			//check left
			changed = true;
		}
		else if	(chk_adj(r,p,0,1,-1,0))
		{
			//check right
			changed = true;
		}

		//change actual value of card
		if (changed)
		{
			cards[index].det = true;
		}

		return changed;
	}

	//for checking 2 adjacent cards
	//returns true if both determined
	//USAGE:
	// takes original p/r, then modifiers
	// original r, p, 1st r mod, p mod, 2nd r mod, p mod
	bool chk_adj(int r, int p, int r1, int p1, int r2, int p2)
	{
		bool test1 = cards[crd.to_index(r+r1,p+p1)].det;
		bool test2 = cards[crd.to_index(r+r2,p+p2)].det;

		return (test1 && test2);
	}

	void draw_tri()
	{
		//TODO
	}


private:
	int n;




};//end of triangle class
