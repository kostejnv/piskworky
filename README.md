# Piskworky

Piskoworky is a console version of game **Gomoku** (sometimes called *Five In Row*) on infinite field. User can choose if he will play against his friend (human rival) or computer (AI).

## INSTALL

For this game is required UNIX-like systems with cmake (version 3.16.3.). You can build (and istall) it with commands bellow:
```
cd <game-directory path>
mkdir exe
cd exe
cmake ../
make
```
Then you can run game with command:
``` 
<game-directory path>/piskworky 
```

## TUTORIALS

You can control the game with the key **'w'**, **'a'**, **'s'**, **'d'** (as arrows) and **'Enter'** (for confirmation of choice) in every point of game (selecting choice, selecting played cell).

At first, user can select in which combination of players (Human players x Computer player) the game will be played. After this phase it will appear a grid (field) on console and players can select where they place their next move after each other. If they want to place move outside the grid, the player can shift cursor in a given direction and the grid will shift, too. If one of the players will have five his signs in row (horizontal, verical, both diagonal) the game ends and this player is winner.

If the game ends users can choose if their can played next game with the same configuration or exit back.


## INTERNALS

### Files

The source code of the game consists of following files:

+ *main* (.cpp)
  + contains main configuration and main loop of game

+ *point* (.h)
  + basic class with x, y coordinates

+ *playground* (.cpp, .h)
  + class with field. It contains function for adding new moves, getting sign on a given coordinate, checking winning status (*is_solve()*) etc.
  
+ *user_interface* (.cpp, .h)
  + class for controlling console through library *ncurses.h*. It consists of functions printing field, header, footer or getting moves from user

+ *player* (.h)
  + interface for human and computer player. It requires functions *play()* and data field *sign* (visulized players move - for example "X")

+ *human_player* (.cpp, .h)
  + implementation of interface *player* for through keyboard controlled player (user)

+ *computer_player* (.cpp, .h)
  + implemantation of interface *player* for AI. Minimax algorithm with alpha-beta prunning is used as AI.

### Main issues

**Infinite field**

One of the biggest issues during implemanting the game was infinite field. Because static size of field with changing size after each move has high time complexity (because of copying, inizializating etc.) and it is not nice, I chose a data structure *map<int,map<int,char>>* for field where *int, int* gives coordinates of players moves and *char* his sign. Adding and getting is *O(log n)* and field is almost infinite (according to limits of *int* size).

The second issue with infinite field was its displaying for user. At first, I display minimal size of squared field (with some borders) and after every moves check if there is a need to expand the displayed field. This representation has several problems. The grid was changing after some moves which led to confusing of user about complex situation of previous moves. The second issue is that the user cannot also give his move to arbitary place but only to squared field that display all previous moves (with some borders). On the other hand it is sufficient in praxis because every other moves is not good in any strategy.

Finally, I changed the representation and now it display only static size of field (20x20) but when user can display another part of field, he can shift in this direction and the field also shifts. This representation fix both issues with previous representation.

**AI algorithm**

For finding the best move for computer player I chose minimax algorithm with alpha-beta prunning. More information about this algorithm you can find [here](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning).

This algorithm is recursive. But the depth is constant so there should be no problem with stack-overflow. I set the depth as 2 because it seems like best in ratio fast-correctness.

There are two important parts in the algorithm that are in every game different:

+ finding next possible moves
+ compute evaluation function for given field

As next possible moves I select only the cells around previous moves that are empty. It is a little bit simplification but almost always it is suffient for finding best move.

The second part was more complex. The following procedure I repeated for current player and then for rival and then add up both value (for rival as negative value) which gives final value.

The procedure is below:

1. search every five in row (horizontal, vertical, both diagonal) that consists of at least one previous move.
2. If given five-row contains only 2, 3, 4, or 5 moves of given player and no from opossite player, remember it.
3. if there is at least one five-row with 5 moves of given player return maximum possible value else return

   $$ fr[2] + fr[3] \cdot 2^2 + fr[4] \cdot 2^4 $$

   where *fr[i]* is number of five-row with *i* moves of given player

If the field is solved (one of player wins) then it is right that it leads for maximal value because it is finally state. Otherwise the mathematical function suffiently favours higher number of moves in five-row.

There is a place for improvement in this proccess because I have to create new playground for every evaluation field with one next possible move, which is not efficient. It would be changed with new interface for playground and for some easy class with pointer on playground and one point. However, my implementation works fine that's the reason why I do not improve it. 