# triangle_configurations
x
by Michael Ivanitskiy
Sumer 2017
for Dr. Michael Jones

explanation of problem:
(roughly copied from a message so it might not make much sense, need to clarify this later)

tokens with 3 states (originally cards either red, black, or face down)
start with a line of n cards
Each row below that is generated using the following rules:
If the 2 cards above it are the same, it is the same state
If they are different, it is the "missing" state

The question we're trying to answer is how many ways can you arrange n cards in a triangle of size n
such that no conflicts are possible and the triangle is defined entirely
also hopefully prove that any valid, non-conflicting arrangements of n cards always define a triangle

some of the calculated configurations so far may be found in the /data directory
calc.exe in the main directory will often be outdated, and does not have a real user interface yet, code must be edited directly

the ".imdone" folder is for an atom plugin that tracks commented issues
