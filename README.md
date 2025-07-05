# INTRODUCTION:
Here are the main informations I wanted to add in complement to all the explanation inside the code.
It will focuse on some data of the solving processes that have been made using the computer of the CI (PCB61-04-12),
some explanation of the optimization that have been made and the information to explain how to launch some functions
that need special argument in the command line (even if it's already explained in the functions).

---

# DATA:
FIRST VERSION OF THE SOLVER (using optimization 1):
|MAP                |EXPLORED NODES             |TIME CLASSICAL/BST (without OPT=1)           |TIME CLASSICAL/BST (with OPT=1) |
| :--------------- |:---------------|:-----|:-----|
|soko_dumb          |74                          |0.000126 / 0.000129                           |- / -|
|soko81             |29123                       |5.012064 / 0.108436                           |- / -|
|soko99             |138033                      |155.593639 / 0.658075                         |- / -|
|soko1               |193778                      |259.758196 / 1.341496                         |- / -|


SECOND VERSION OF THE SOLVER (using optimization 2):
|MAP                 |EXPLORED NODES              |TIME CLASSICAL/BST (without OPT=1)            |TIME CLASSICAL/BST (with OPT=1)|
| :--------------- |:---------------|:-----|:-----|
|soko_dumb           |74                          |0.000131 / 0.000136                           |0.000058 / 0.000071|
|soko81              |8734                        |0.408341 / 0.026501                           |0.310618 / 0.012198|
|soko99              |24977                       |3.584679 / 0.084943                           |2.902468 / 0.045079|
|soko1               |55448                       |10.884184 / 0.267875                          |8.456591 / 0.151626|

Times are in seconds.

---

# OPTIMIZATION:
The first optimization (optimization 1) was used in the solver when you compare the current map to the map in the explored list. 
Initialy I was comparing all the characters of the map. The first optimization consists of firstly testing if the player was in the same position
on both maps.

The second optimization (optimization 2) was add in the while loop of the solver. It consists of checking if a box was on an empty place
in a corner. In this case all the map explored from this one were useless. This second optimization let explored less nodes and works well.

---

# EXECUTING EXPLANATION:
Reminder : everything is already detailled in the head of the concerned functions.
I give some example of uses.

Play function: ./play data/soko1.in

Replay function: ./replay data/soko1.in 7 "NNNEEESSS"

Solve function: ./solve data/soko1.in
You will have to interact in the console (choosing the solver type and if you want to show the solving process using SDL). 
