# triangle_configurations
x
by Michael Ivanitskiy & Miriam Weaverdyck
Sumer 2017
for Dr. Michael Jones

explanation of problem:
(roughly copied from a message so it might not make much sense, need to clarify this later)

tokens with 3 states (originally cards either red, black, or face down)
start with a line of n cards
Each row below that is generated using the following rules:
If the 2 cards above it are the same, it is the same state
If they are different, it is the "missing" state

a consequence of this rule is that for x in the natural #s, triangles where n = 1 + 3^x have the property that knowing any 2 corners gives the third
this can be proved by the conversion of this "geometric" rule to the algebraic rule of card values being integers mod 3,
and new value C of a card below the cards A, B being determined by (2A + 2B)mod 3.

The question we're trying to answer is how many ways can you arrange n cards in a triangle of size n
such that no conflicts are possible and the triangle is defined entirely
also hopefully prove that any valid, non-conflicting arrangements of n cards always define a triangle

some of the calculated configurations so far may be found in the /data directory

/card_placement contains an algorithm (in c++) that works by placing cards, and using the geometric rules so see which cards remain "undetermined"
this is flawed because of the emergence of some exceptions (so far found in n=3,5) where the triangle is algebraically determined but is not determined according to the purely geometric rules.

/impl_invertible contains an algorithm (written in matlab) that uses representations of the placed cards in matrix form, and checks for overlap by seeing if they are invertible

/num_moves contains code for a seperate problem that considers how many "steps" are needed to determine an n-tri when the top row is filled






calc.exe in the /card_placement directory will often be outdated, and does not have a real user interface yet, code must be edited directly

the ".imdone" folder is for an atom plugin that tracks commented issues
