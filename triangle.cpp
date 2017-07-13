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
		k = n * (n+1) / 2;
		cards = new Card[k+1];

	}

	//copy constructor
	Triangle(Triangle * x)
	{
		n = x->n;
		k = x->k;
		cards = new Card[k+1];

		//loop to copy card data
		for (int i = 1; i < k+1; i++)
		{
			cards[i] = (x->cards)[i];
		}
	}

	//starts at 1, pyramid upwards
	//index starts from left side
	Card * cards;

	//card for using to_index
	Card crd;

	//check_permutations main call
	int perm_main()
	{
		return check_permutations(1);
	}

	//recursive(?) function for checking # of permutations possible in this triangle
	//with x cards
	//makes copies of the current triangle with 1 card added, then calls itself
	//takes card being placed # as input
	int check_permutations(int x)
	{
		cout << "checking card #" << x << " for tri of size " << n << endl;

		//subtotal for this instance
		int subtotal = 0;

		//loop through all remaining empty cards
		for (int i = 1; i <= k; i++)
		{
			//if card is not determined:
			if ( !(cards[i].det) )
			{
				//add 1 for placement of this card
				subtotal++;

				//if not last card
				//copy tri, fill card, and recurse
				if (x <= n)
				{
					//create copy
					Triangle subtri = Triangle(this);

					//set card at index to determined
					(subtri.cards[i]).det = true;

					//fill
					subtri.fill_tri_loop();

					cout << "about to recurse for card #" << x << " for tri of size " << n << endl;

					//recurse with next card, add to subtotal
					subtotal = subtotal + subtri.check_permutations(x + 1);
					cout << subtotal << endl;
				}
			}

			//return subtotal
			return subtotal++;
		}
	}

	//recursive function for placing a card

	//loop until all determined cards are marked as such
	void fill_tri_loop()
	{
		while ( fill_tri() ) {}
	}


	//test all undet cards, fill them
	bool fill_tri()
	{
		//default is no change
		bool changed = false;

		//loop through all cards in tri
		for (int i = 1; i <= k; i++)
		{
			//if card is not yet determined
			if (!(cards[i].det))
			{
				//check it
				if (fill_card(i))
				{
					//if it changes, then save that information
					changed = true;
				}
			}
		}

		//return whether any cards were changed
		return changed;
	}

	//test a card, make it determined if need be
	bool fill_card(int index)
	{
		bool changed = false;

		//r/p ==> row/place

		//get r/p of our card
		int r = trind[index].first;
		int p = trind[index].second;

		//3 cases for fill:
		//2 cards above, or 2 cards to either side & below

		//TODO: add error checking for if more than one set tries to define this card
		//this shouldnt be possible but I haven't proved it yet so idk

		//check above
		bool test_U = chk_adj(r,p,1,0,1,1);

		//check left
		bool test_L = chk_adj(r,p,0,-1,-1,-1);

		//check right
		bool test_R = chk_adj(r,p,0,1,-1,0);

		if (test_U && test_L && test_R)
		{
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
		//first check for not at an edge
		if ((0 < p+p1 <= r) && (0 < p+p2 <= r) && (r <= n) && (r > 1))
		{
			//if not at the edge, check those two cards
			bool test1 = cards[crd.to_index(r+r1,p+p1)].det;
			bool test2 = cards[crd.to_index(r+r2,p+p2)].det;

			//if BOTH were determined, return true
			return (test1 && test2);
		}

		//youre still here? that means it was on an edge
		//just return false
		return false;
	}

	void draw_tri()
	{
		//TODO
	}


private:
	//side length of triangle
	int n;
	//total number of indecies
	int k;

};//end of triangle class
