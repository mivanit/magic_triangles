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
		for (int i = 0; i <= k; i++)
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
		//to account for the fact that placed cards should not be distinct
		//store the largest card index that has been tested
		//
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
		int sub_total = 0;

		//loop through all remaining empty cards
		for (int i = 1; i <= k; i++)
		{
			//if card is not determined, and has not yet been checked:
			if ( !(cards[i].det) && (i > chk_idx))
			{
				//add 1 for placement of this card
				sub_total++;

				//mark this card as checked in the index
				//but only if we are on the first layer of cards
				if (x == 1)
				{
					chk_idx = i;
				}

				//if not last card
				//copy tri, fill card, and recurse
				if (x < n)
				{
					//create copy
					Triangle subtri = Triangle(this);

					//set card at index to determined
					(subtri.cards[i]).det = true;

					//fill
					subtri.fill_tri_loop();

					cout << sub_total << endl;
					cout << "about to recurse for card #" << x+1 << " for tri of size " << n << endl;
					//recurse with next card, add to subtotal
					sub_total = sub_total + subtri.check_permutations(x + 1);
					cout << sub_total << endl;
				}
			}


			//return subtotal
			return sub_total;
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

	//checking for triangle corners of (3^x)+1 tris inside

	//main function for filling a card
	bool fill_card(int index)
	{
		bool changed = false;
		bool loop_continue;
		int i = 0;

		//TODO: add error checking for if more than one set tries to define this card
		//this shouldnt be possible but I haven't proved it yet so idk

		while (loop_continue)
		{
			//continue until there are no 3^x + 1 tris remain inside
			if ( ((3^i) + 1) < n )
			{
				//call corner checking function
				if ( chk_corner_tri( index, ((3^i) + 1) ) )
				{
					//change the actual card
					(cards[index]).det = true;

					//mark that it is changed
					changed = true;
				}

				//iterate counter
				i++;
			}
			else
			{
				loop_continue = false;
			}
		}

		return changed;
	}

	//checks for the x-th (3^x)+1 tri at an index
	bool chk_corner_tri(int index, int x)
	{
		//get r/p of index
		int r = trind[index].first;
		int p = trind[index].second;

		//triangle of size x => corners are x-1 away
		int k = x - 1;

		//check above
		bool test_U = chk_adj(r,p,k,0,k,k);

		//check left
		bool test_L = chk_adj(r,p,0,-k,-k,-k);

		//check right
		bool test_R = chk_adj(r,p,0,k,-k,0);

		return (test_U || test_L || test_R);
	}


	//for checking 2 cards by relative positioning
	//returns true if both determined
	//USAGE:
	// takes original p/r, then modifiers
	// original r, p, 1st r mod, p mod, 2nd r mod, p mod
	bool chk_adj(int r, int p, int r1, int p1, int r2, int p2)
	{
		//TODO: throw error if base r/p outside

		//first check everything is inside
		if (chk_in(r+r1, p+p1) && chk_in(r+r1, p+p1))
		{
			//if not at the edge, check those two cards
			bool test1 = cards[crd.to_index(r+r1,p+p1)].det;
			bool test2 = cards[crd.to_index(r+r2,p+p2)].det;

			//if BOTH were determined, return true
			return (test1 && test2);
		}

		//still here? that means it was on an edge
		//just return false
		return false;
	}

	//function for checking that a p/r are inside the triangle
	bool chk_in(int r, int p)
	{
		return ((p > 0) && (p <= r) && (r <= n) && (r > 0));
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
	//largest card index checked
	int chk_idx = 0;

};//end of triangle class
