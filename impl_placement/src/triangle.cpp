//Michael Ivanitskiy
//started july 10 2017

#include "card.cpp"

using namespace std;

extern pair<int,int> * trind;
extern int ** tbl;

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


	// default constructor
	Triangle(int size, bool in_draw = false, bool in_fill_tbl = true)
	{
		// size of tri
		n = size;
		// number of indecies
		k = n * (n+1) / 2;
		// initialize array of empty cards
		cards = new Card[k+1];
		// fill
		for (int i = 0; i <= k; i++)
		{
			cards[i] = Card(i,n);
		}

		// declare array with locations of placed cards
		cards_placed_locations = new int[n+1];
		// fill with -1 to indicate this card not yet placed
		for (int i = 1; i <= n; i++)
		{
			cards_placed_locations[i] = -1;
		}

		// drawing
		draw = in_draw;
		// filling tbl
		fill_tbl = in_fill_tbl;
	}

	// copy constructor
	Triangle(Triangle * x)
	{
		// copy triangle size
		n = x->n;
		// TODO:10 assert k = x.k
		// calculate number of indecies
		k = n * (n+1) / 2;
		// initialie array of empty cards
		cards = new Card[k+1];
		// copy whether to draw
		draw = x->draw;
		// copy whether to fill tbl
		fill_tbl = x->fill_tbl;

		// number of cards placed
		cards_placed = x->cards_placed;

		// declare array with locations of placed cards
		cards_placed_locations = new int[n+1];

		// fill array with locations of placed cards
		// fill with -1 to indicate this card not yet placed
		for (int i = 1; i <= n; i++)
		{
			cards_placed_locations[i] = x->cards_placed_locations[i];
		}

		//loop to copy card data
		for (int i = 0; i <= k; i++)
		{
			cards[i] = Card((x->cards)[i]);
		}
	}

	// destructor
	~Triangle()
	{
		delete cards_placed_locations;
		delete cards;
	}



/*

	 ██████ ██   ██ ██   ██
	██      ██   ██ ██  ██
	██      ███████ █████
	██      ██   ██ ██  ██
	 ██████ ██   ██ ██   ██

*/



	// check_permutations main call
	int arrange_main()
	{
		// no cards have been checked and none have been placed,
		// so tell it to place card 1 and check all cards
		return check_arrange(1, 0);
	}

	// recursive function for checking # of arrangements possible in this triangle
	// with x cards
	// makes copies of the current triangle with 1 card added, then calls itself
	// takes card layer being placed as input
	// to account for the fact that placed cards should not be distinct
	// store the largest card index that has been tested
	int check_arrange(int x, int in_chk_index)
	{
		// fill this triangle, just in case
		this->fill_tri_loop();

		// subtotal for this instance
		int sub_total = 0;
		// largest card index checked for this instance
		int chk_idx = in_chk_index;

		// loop through all remaining empty, unchecked cards
		for (int i = (chk_idx + 1); i <= k; i++)
		{
			// fill this triangle, just in case
			this->fill_tri_loop();

			// if card is NOT determined, and this index has not yet been checked:
			if ( cards[i].empty() ) // && (i >= chk_idx) )
			{
				// copy tri, fill card, recurse if needed, display (if draw==true)
				// if on last layer, check that it fills the triangle and return 1

				// fill this triangle, just in case
				this->fill_tri_loop();

				// create copy of the triangle in its current state
				// this isnt necessary for calculations,
				// but makes the code make more sense and enables correct drawing of filled tris
				Triangle subtri = Triangle(this);

				// fill the triangle's cards
				subtri.fill_tri_loop();
				this->fill_tri_loop();

				// set card at index to "determined"
				// use place() to store that this card was manually placed
				(subtri.cards[i]).place(x);

				// store that this cards was placed on the top row if needed
				if (x == n)
				{
					subtri.num_placed_top++;
				}

				// mark in the array and var that this card was placed and where
				subtri.cards_placed = x;
				subtri.cards_placed_locations[x] = i;

				// mark this card index as checked for this iteration
				chk_idx = i;

				// fill the triangle's cards
				subtri.fill_tri_loop();
				this->fill_tri_loop();

				// if not last card, recurse
				if (x < n)
				{
					// fill the triangle's cards
					subtri.fill_tri_loop();
					this->fill_tri_loop();

					// recurse
					// pass next card layer, max checked index
					// add to subtotal
					// TODO:120 subtotal should be 0 apart from this
					sub_total = sub_total + subtri.check_arrange(x + 1, chk_idx);
				}

				// fill the triangle's cards
				subtri.fill_tri_loop();
				this->fill_tri_loop();

				// if last card played and tri is fully det,
				// add 1 for this card placement
				if (x == n)
				{
					// fill the triangle's cards
					// just in case
					subtri.fill_tri_loop();
					this->fill_tri_loop();


					// DONE: impl chk for triangle filled
					// its bugged right now and always returns false
					// if (subtri.chk_all_filled())

						sub_total++;

						// if fill_tbl is enabled,
						// store data to global array
						if (fill_tbl)
						{
							// to make sure proper num_placed_top
							// use get_num_top() fctn

							// iterate total
							tbl[n][0]++;

							// iterate top row subtotal
							tbl[n][get_num_top()+1]++;
						}


					// draw the triangle
					// this can be moved as needed, and often is for debugging
					if (draw)
					{
						subtri.draw_tri();
						cout << endl;
					}
				}
			}
		}

		// return subtotal
		return sub_total;
	}

	// function for checking all cards are filled
	bool chk_all_filled()
	{
		int i = 1;
		while (i <= k)
		{
			if ( (cards[i]).empty() )
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
			if ( cards[i].empty() )
			{
				// cout << changed << endl;
				//check if it should be filled
				if (fill_card(i))
				{
					//if it changes, then save that information
					changed = true;
					// cout << i << "\tcard filled\n";
				}
				// cout << i << "\tcard\t\tNOT filled\n";
			}
			else
			{
				// if the card is determined,
				// check for the special 3tri case

				// could make check if the triangle is n > 3
				// but this only optimizes for small cases that take no time already

				if (fill_3tri_corners(i))
				{
					// if changed, save that information
					changed = true;
					// cout << i << "\tcard filled\n";
				}
				// cout << i << "\tcard\t\tNOT filled\n";
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
		int size = (pow_int(3, i) + 1);

		// TODO:0 add error checking for if more than one set tries to define this card
		//this shouldnt be possible but I haven't proved it yet so idk

		// keep going until all valid tri sizes checked
		// DONE: figure out why the code breaks for n < 4
		// if we make the looping requirement just size <= n
		// A: its because i used ^ for exponentiation because im an idiot
		while ( size <= n )
		{
			// calculate tri size
			size = (pow_int(3, i) + 1);

			// if the triangle corners could fit inside the tri
			// call corner checking function on the index we have been given
			// if this card turns out to be the corner of a triangle, fill it
			if ( chk_all_corner_tri( index, size ) )
			{
				// change the actual card
				// use fill() to indicate it was filled, not placed
				if ((cards[index]).fill())
				{
					// store that the card is changed
					changed = true;
				}
			}

			// iterate counter
			i++;
		}

		// return whether anything has changed
		return changed;
	}


	// special case check for the 3 triangle corners case
	// checks if this card is ONLY THE BOTTOM the corner of a 3tri
	// TODO:100 re-impliment all directions checking
	// takes index of a card
	// if the triangle is filled (including the card at r/p),
	// then fill the 3 missing cards because the triangle should be defined
	bool fill_3tri_corners(int index)
	{
		// check to see the given card is determined
		// this should be deprecated because it is checked for before the fctn call
		// but leaving it in just in case
		if (cards[index].get_det())
		{
			// if it is, check the other 2 in the given direction
			// 3 is hardcoded for this because unique for 3 tris
			// TODO:90 might not be unique to 3 tris
			if (chk_corner_tri_dir(index, 3, 0))
			{
				// if both these conditions pass, try to fill the triangle
				if (fill_3tri_dir(index, 0))
				{
					// return that a change has occured
					return true;
				}
			}
		}
		// if you get to here, no change has occured
		return false;
	}





/*

	██████   █████  ███████ ███████      ██████ ██   ██ ██   ██
	██   ██ ██   ██ ██      ██          ██      ██   ██ ██  ██
	██████  ███████ ███████ █████       ██      ███████ █████
	██   ██ ██   ██      ██ ██          ██      ██   ██ ██  ██
	██████  ██   ██ ███████ ███████      ██████ ██   ██ ██   ██

*/



	// fills the missing bits of a corner-only 3tri
	// starting at the given index, and going in the given location
	// TODO:30 fctn for rotating? (-partially complete)
	bool fill_3tri_dir(int index, int dir)
	{
		bool changed = false;

		// get r/p of index
		int r = cards[index].get_row();
		int p = cards[index].get_place();

		// modifiers
		int r_m = 0;
		int p_m = 0;


		// hard coding only up case for now
		// TODO:130 this breaks because out of bounds of tri,
		// look back into the call for this fctn
		if (r <= (n - 2) )
		{
			// left
			r_m = 1;
			p_m = 0;
			if ( (cards[crd.to_index(r + r_m, p + p_m)]).fill() )
			{
				changed = true;
			}

			// right
			r_m = 1;
			p_m = 1;
			if ( (cards[crd.to_index(r + r_m, p + p_m)]).fill() )
			{
				changed = true;
			}

			// furthest
			r_m = 2;
			p_m = 1;
			if ( (cards[crd.to_index(r + r_m, p + p_m)]).fill() )
			{
				changed = true;
			}
		}
		return changed;
	}


	// checks for the x-th (3^x)+1 tri at an index
	bool chk_all_corner_tri(int index, int x)
	{
		// check 2 corners above
		bool test_U = chk_corner_tri_dir(index, x,  0);

		// check bottom left
		bool test_L = chk_corner_tri_dir(index, x, -1);

		// check bottom right
		bool test_R = chk_corner_tri_dir(index, x,  1);

		// if any are true, return true
		return (test_U || test_L || test_R);
	}

	// checks for the given coord being a corner of a given tri
	// ONLY in the given direction
	// takes: index, size of tri, d=direction
	// 0 is up, -1 is left, 1 is right
	bool chk_corner_tri_dir(int index, int size, int d)
	{
		// r/p = row/place
		//get r/p of index
		int r = cards[index].get_row();
		int p = cards[index].get_place();

		//triangle of size x implies corners are size - 1 away
		int x = size - 1;

		//determine values
		int r_1 = x * (1 - abs(d));
		int p_1 = x * d;
		int r_2 = x * (1 - 2 * abs(d));
		// TODO:80 improve p_2 calculation?
		int p_2;
		if (d == 0)
		{
			p_2 = x;
		}
		else if (d == (-1))
		{
			p_2 = (-x);
		}
		else
		{
			p_2 = 0;
		}

		return chk_adj(r, p, r_1, p_1, r_2, p_2);
	}



	// for checking 2 cards by relative positioning
	// returns true if both determined
	// USAGE:
	// takes original p/r, then modifiers
	// original r, p, 1st r mod, p mod, 2nd r mod, p mod
	bool chk_adj(int r, int p, int r_1, int p_1, int r_2, int p_2)
	{
		//TODO:140 throw error if base r/p outside

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

	██████   ██████  ████████
	██   ██ ██    ██    ██
	██████  ██    ██    ██
	██   ██ ██    ██    ██
	██   ██  ██████     ██

*/



	// rotate a relative coordinate modifier 60 degrees clockwise
	// ONLY WORKS FOR ADJACENT COORDS
	// passes by reference
	// TODO: rotation code is shit, fix this
	void rot(int * r, int * p)
	{
		if (*r == *p)
		{
			// when equal, only iterate row

			if (*r > 0)
			{
				// if greater than 0, subtract
				(*r)--;
			}
			else
			{
				// if negative, add
				(*r)++;
			}
		}
		else
		{
			// otherwise, iterate both coordinates

			// iterate r
			if (*r > 0)
			{
				// if greater than 0, subtract
				(*r)--;
			}
			else if (*r < 0)
			{
				// if negative, add
				(*r)++;
			}
			else
			{
				// if 0, then need p
				if (*p > 0)
				{
					// if p greater than 0, decrement
					(*r)--;
				}
				else
				{
					// otherwise, increment
					(*r)--;
				}
			}




			// iterate p
			if (*p > 0)
			{
				// if greater than 0, subtract
				(*p)--;
			}
			else if (*p < 0)
			{
				// if negative, add
				(*p)++;
			}
			else
			{
				// if 0, then need r
				if (*r > 0)
				{
					// if r greater than 0, increment
					(*p)++;
				}
				else
				{
					// otherwise, decrement
					(*p)--;
				}
			}
		}
	}



	// TODO:20 extend to other rotations?



/*

	███    ███ ██ ███████  ██████
	████  ████ ██ ██      ██
	██ ████ ██ ██ ███████ ██
	██  ██  ██ ██      ██ ██
	██      ██ ██ ███████  ██████

*/

// returns the number of PLACED cards on the top row for any particular triangle
int get_num_top()
{
	// declare counter var
	int num_placed = 0;

	// loop through cards at the top
	for (int i = 1; i <= n; i++)
	{
		// top row, so all have the same r value
		// i is place value
		int index = crd.to_index(n, i);
		if ( cards[index].place_order > 0 )
		{
			num_placed++;
		}
	}

	num_placed_top = num_placed;
	return num_placed;
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
		//TODO:110 row/place labels?

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



	// side length of triangle
	int n;
	// total number of indecies
	// k = n*(n+1)/2
	int k;

	// number of cards placed
	int cards_placed = 0;

	// number of cards on the top row
	int num_placed_top = 0;

	// array with locations of placed cards
	int * cards_placed_locations;

	// starts at 1, pyramid upwards
	// index starts from left side
	Card * cards;

	// card for using to_index
	Card crd;

	// boolean for whether to draw triangles
	bool draw = false;

	// boolean for whether to fill table with data
	bool fill_tbl = true;

};//end of triangle class
