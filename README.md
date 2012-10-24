**Tic-Tac-Toe: Human Vs Computer**


This is a Tic-Tac-Toe Game to be played against the Computer.

The User is free to choose any size (NxN) Matrix

This Game is based on Artifitial Intelligence. The Computer evaluates every move made by you and decides the 
optimal step, based on a Set of Rules.

This Game is Slighly Different in terms of the Rules:


You Win:: If you are able to complete any of the below conditions -
(A) Complete any Row
(B) Complete any Column
(C) Complete Left Body Diagonal
(D) Complete Right Body Diagonal

You Lose:: If none of the above mentioned conditions (to win) are fulfilled, you are Defeated.

*Basic Information:*


Based upon the Dimensions of the Matrix you choose (eg: 3x3, 4x4 etc), you will be presented with a Printed Matrix
initialized with all 'O's.

In general: 'O' means -> vacant position
            'X' means -> User's Entry
            'Y' means -> Computer's Entry

*How to Compile:*

If you do not want to print Stats after every Human move, compile as follows:

$ gcc tic_tac_toe.c -ansi -Wall -pedantic -o tictactoe

If you want to print Stats after every Human move, compile as follows:

$ gcc tic_tac_toe.c -ansi -Wall -pedantic -o tictactoe -DDEBUG_FLAG


*How To Play this Game:*

For each Chance, the User has to provide 2 Inputs: ROWNO COLNO

For Example:

Suppose the User wants to make an entry at: Row No. 2, Column No. 3

Then, the User must provide the following Input: 2 3 (Enter)

*Screenshot:*

![Tic-Tac-Toe: Human Vs Computer](https://raw.github.com/sandeepsinghmails/tictactoe_HumanVsComputer/master/images/screenshot.jpeg)
