//Michael Ivanitskiy

using namespace std;

extern pair<int,int> * trind;

int to_index(int r, int p);

// currently two different index formats are used,
// along with one coordinate system
// no good names for them yet, but
// the code gathered in src/calc.cpp uses a system optimized for calculation by placement of card
// the invertible matricies code uses a system optimized for modular arithmetic

// there is also a coordinate system that uses two values (row, place) to determine a card

//take row (r), place (p)
int to_index(int r, int p)
{
	//use n(n+1)/2 with n=r-1, add place in row
	int x = p + r * (r - 1) / 2;
	return x;
}
