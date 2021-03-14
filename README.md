# Piskworky

Piskoworky is a console version of game **Gomoku** (sometimes called *Five In Row*) on infinite field. User can choose if he will play against his friend (human rival)
or computer (AI).

## INSTALL

For this game is required UNIX-like systems with cmake. You can build (and istall) it with commands above:
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

At first user can select in which combination of players (Human players x Computer player) the game will be played. After this phase it will appear a grid (field) on console and players can select where they place their next move after each other.
If one of players will be have five his signs in row (horizontal, verical, both diagonal) the game ends and this player is winner.

If the game ends users can choose if their can played next game with the same configuration or exit back.


## INTERNALS