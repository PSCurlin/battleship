# Battleship

A single-player game of Battleship written in C and played in the UNIX terminal.

# How to Play

1. First clone this repository

```
git clone https://github.com/dafnamargalit/battleship.git
```
2. Compile `battleship.c` using the makefile

```
make -k
```

3. Run the game with the following arguments, where `size of board` is a single number between 5 and 20, and `maxshots` is a number between 12 and n^2 - 1, where n is the size of the board:

```
./mainbattleship [size of board] [maxshots]
```
After running this command, a board of the size specified will be outputted. 

4. To guess the location of a ship, input the guess in the following order, no space in between:

```
[row (an integer)][col(a letter)]
```

The game ends when you either run out of shots, have not enough shots left to sink all the ships, or sink all the ships.

For a more comprehensive report on the code, you can read the following:
https://drive.google.com/file/d/1Ff4nJortrApcKVTTl8gqXmzaw8mI-8k4/view?usp=sharing

# Sources used:

How to do a static input:
http://home.hccnet.nl/r.helderman/adventures/htpataic02.html 

Generic makefile:
https://gist.github.com/ork/11248510 

Colors:
https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
https://askubuntu.com/questions/558280/changing-colour-of-text-and-background-of-terminal

Time Delay:
https://www.geeksforgeeks.org/time-delay-c/

