//Michael Ivanitskiy
//started july 10 2017

#include "card.cpp"

using namespace std;

extern pair<int,int> * trind;

class Triangle
{
public:


	/*

	 ██████ ████████  ██████  ██████
	██         ██    ██    ██ ██   ██
	██         ██    ██    ██ ██████
	██         ██    ██    ██ ██   ██
	 ██████    ██     ██████  ██   ██

	 */


	//default constructor
	Triangle(int size, bool in_draw = false)
	{
		//size of tri
		n = size;
		//number of indecies
		k = n * (n+1) / 2;
		//initialize array of empty cards
		cards = new Card[k+1];
		//fill
		for (int i = 0; i <= k; i++)
		{
			cards[i] = Card(i,n);
		}
		//drawing
		draw = in_draw;
	}

	//copy constructor
	Triangle(Triangle * x)
	{
		//copy triangle size
		n = x->n;
		//TODO: assert k = x.k
		//calculate number of indecies
		k = n * (n+1) / 2;
		//initialie array of empty cards
		cards = new Card[k+1];
		//copy whether to draw
		draw = x->draw;

		//loop to copy card data
		for (int i = 0; i <= k; i++)
		{
			cards[i] = Card((x->cards)[i]);
		}
	}



	/*

	 ██████ ██   ██ ██   ██
	██      ██   ██ ██  ██
	██      ███████ █████
	██      ██   ██ ██  ██
	 ██████ ██   ██ ██   ██

	*/



	//check_permutations main call
	int arrange_main()
	{
		//no cards have been checked and none have been placed,
		//so tell it to place card 1 and check all cards
		return check_arrange(1, 0);
	}

	//recursive function for checking # of arrangements possible in this triangle
	//with x cards
	//makes copies of the current triangle with 1 card added, then calls itself
	//takes card layer being placed as input
	//to account for the fact that placed cards should not be distinct
	//store the largest card index that has been tested
	int check_arrange(int x, int in_chk_index)
	{
		//fill this triangle, just in case
		this->fill_tri_loop();

		//subtotal for this instance
		int sub_total = 0;
		//largest card index checked for this instance
		int chk_idx = in_chk_index;

		//loop through all remaining empty, unchecked cards
		for (int i = chk_idx + 1; i <= k; i++)
		{
			//fill this triangle, just in case
			this->fill_tri_loop();

			//if card is not determined, and this index has not yet been checked:
			if ( !(cards[i].get_det()) && (i > chk_idx) )
			{
				//copy tri, fill card, recurse if needed, display (if draw==true)
				//if on last layer, check that it fills the triangle and return 1

				//fill this triangle, just in case
				this->fill_tri_loop();

				//create copy of the triangle in its current state
				//this isnt necessary for calculations,
				//but makes the code make more sense and enables correct drawing of filled tris
				Triangle subtri = Triangle(this);

				//fill the triangle's cards
				subtri.fill_tri_loop();
				this->fill_tri_loop();

				//set card at index to "determined"
				//use place() to store that this card was manually placed
				(subtri.cards[i]).place(x);

				//mark this card index as checked for this iteration
				chk_idx = i;

				//fill the triangle's cards
				subtri.fill_tri_loop();
				this->fill_tri_loop();

				//if not last card, recurse
				if (x < n)
				{
					//fill the triangle's cards
					subtri.fill_tri_loop();
					this->fill_tri_loop();

					//recurse
					//pass next card layer, max checked index
					//add to subtotal
					//TODO: subtotal should be 0 apart from this
					sub_total = sub_total + subtri.check_arrange(x + 1, chk_idx);
				}

				//fill the triangle's cards
				subtri.fill_tri_loop();
				this->fill_tri_loop();

				//if last layer, add 1 for this card placement
				//if tri if fully det
				if (x == n)
				{
					//fill the triangle's cards
					subtri.fill_tri_loop();
					this->fill_tri_loop();


					//TODO: impl chk for triangle filled
					//its bugged right now and always returns false
					//if (chk_all_filled())
					sub_total++;

					if (draw)
					{
						subtri.draw_tri();
						cout << endl;
					}
				}
			}
		}

		//return subtotal
		return sub_total;
	}

	//function for checking all cards are filled
	bool chk_all_filled()
	{
		int i = 1;
		while (i <= k)
		{
			if ((cards[i]).place_order == 0)
			{
				return false;
			}
			i++;
		}
		return true;
	}

	/*

	███████ ██ ██      ██
	██      ██ ██      ██
	█████   ██ ██      ██
	██      ██ ██      ██
	██      ██ ███████ ███████

	*/



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
			if ( cards[i].get_det() == false )
			{
				//cout << "chk card @ " << i << endl;
				//check it
				if (fill_card(i))
				{
					//cout << "card filled @ " << i << endl;

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
		//keep track of whether anything was changed
		bool changed = false;
		//keep going until all valid tri sizes checked
		bool loop_continue = true;
		//counter var
		int i = 0;
		//triangle chk size
		int size = ((3 ^ i) + 1);

		//TODO: add error checking for if more than one set tries to define this card
		//this shouldnt be possible but I haven't proved it yet so idk

		//keep going until all valid tri sizes checked
		//TODO: figure out why the code breaks for n < 4 if we make the
		//		looping requirement just size <= n
		while ( size <= n + 3 )
		{
			//calculate tri size
			size = ((3 ^ i) + 1);

			//if the triangle corners fit inside the tri
			//call corner checking function on the index we have been given
			//if this card turns out to be the corner of a triangle, fill it
			if ( chk_corner_tri( index, size ) )
			{
				//change the actual card
				//use fill() to indicate it was filled, not placed
				(cards[index]).fill();
				//store that the card is changed
				changed = true;
			}

			//iterate counter
			i++;
		}

		//return whether anything has changed
		return changed;
	}

	//checks for the x-th (3^x)+1 tri at an index
	bool chk_corner_tri(int index, int x)
	{
		// r/p = row/place
		//get r/p of index
		int r = cards[index].get_row();
		int p = cards[index].get_place();

		//triangle of size x implies corners are x-1 away
		int k = x - 1;

		//check 2 corners above
		bool test_U = chk_adj(r,p,k,0,k,k);

		//check bottom left
		bool test_L = chk_adj(r,p,0,-k,-k,-k);

		//check bottom right
		bool test_R = chk_adj(r,p,0,k,-k,0);

		//if any are true, return true
		return (test_U || test_L || test_R);
	}


	//for checking 2 cards by relative positioning
	//returns true if both determined
	//USAGE:
	// takes original p/r, then modifiers
	// original r, p, 1st r mod, p mod, 2nd r mod, p mod
	bool chk_adj(int r, int p, int r_1, int p_1, int r_2, int p_2)
	{
		//TODO: throw error if base r/p outside

		//first check everything is inside
		if (chk_in(r,p) && chk_in(r + r_1, p + p_1) && chk_in(r + r_1, p + p_1))
		{
			//if not at the edge, check those two cards
			bool test1 = cards[crd.to_index(r + r_1, p + p_1)].get_det();
			bool test2 = cards[crd.to_index(r + r_2, p + p_2)].get_det();

			//if BOTH were determined, return true
			return (test1 && test2);
		}
		else
		{
			//still here? that means it was on an edge
			//just return false
			return false;
		}
	}

	//function for checking that a p/r are inside the triangle
	bool chk_in(int r, int p)
	{
		return ( (p > 0) && (p <= r) && (r <= n) && (r > 0) );
	}


		/*

		██████  ██████   █████  ██     ██
		██   ██ ██   ██ ██   ██ ██     ██
		██   ██ ██████  ███████ ██  █  ██
		██   ██ ██   ██ ██   ██ ██ ███ ██
		██████  ██   ██ ██   ██  ███ ███

		*/



	//draw whole triangle
	void draw_tri()
	{
		//upside down pyramid drawing
		//TODO: row/place labels?

		for (int r = n; r > 0; r--)
		{
			draw_tri_row(r);
		}
	}

	//draw the row r
	void draw_tri_row(int r)
	{
		//buffer before text starts on every line
		cout << "     ";

		//buffer of (n-r) * 2 spaces before the start
		for (int i = 0; i < (n-r); i++)
		{
			cout << " ";
		}

		for (int p = 1; p <= r; p++)
		{
			int index = crd.to_index(r, p);
			draw_tri_card(index);
		}

		//endline
		cout << endl;
	}

	//draw the card at index into cout
	void draw_tri_card(int index)
	{
		//characters are effectively 2 spaces, one for the char and one for a space
		//  x for det by placement card
		// '#' for det by fill card
		// 'O' for undet card

		if (cards[index].get_det())
		{
			if (cards[index].place_order > 0)
			{
				cout << cards[index].place_order << " ";
			}
			else
			{
				cout << "# ";
			}
		}
		else
		{
			cout << "O ";
		}
	}



	/*

	██    ██  █████  ██████  ███████
	██    ██ ██   ██ ██   ██ ██
	██    ██ ███████ ██████  ███████
	 ██  ██  ██   ██ ██   ██      ██
	  ████   ██   ██ ██   ██ ███████

	*/



	//side length of triangle
	int n;
	//total number of indecies
	// k = n*(n+1)/2
	int k;

	//starts at 1, pyramid upwards
	//index starts from left side
	Card * cards;

	//card for using to_index
	Card crd;

	//boolean for whether to draw triangles
	bool draw = false;

};//end of triangle class
