//Michael Ivanitskiy
//started july 10 2017

#include "card.cpp"

using namespace std;

extern pair<int,int> * trind;

class Triangle
{
public:
	//default constructor
	Triangle(int size)
	{
		n = size;
		num_cards = n * (n+1) / 2;
		maxindex = num_cards + 1;
		cards = new Card[maxindex];

	}

	//copy constructor
	Triangle(Triangle * x)
	{
		n = x->n;
		num_cards = x->num_cards;
		maxindex = num_cards + 1;
		cards = new Card[maxindex];

		//loop to copy card data
		for (int i = 1; i < maxindex; i++)
		{
			cards[i] = (x->cards)[i];
		}
	}

	//starts at 1, pyramid upwards
	//index starts from left side
	Card * cards;

	//card for using to_index
	Card crd;

	//recursive(?) function for checking # of permutations possible in this triangle
	//makes copies of the current triangle with 1 card added, then calls itself
	int check_permutations(Triangle * orig)
	{
		//subtotal for this instance
		int subtotal = 0;

		//loop through all remaining empty cards
		for (int i = 0; i < maxindex; i++)
		{


		}






	}

	//recursive function for placing a card

	//loop until all determined cards are marked as such
	void fill_tri_loop()
	{
		while ( !( fill_tri() ) ) {}
	}


	//test all undet cards, fill them
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

	//test a card, make it determined if need be
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
	int num_cards;




};//end of triangle class
