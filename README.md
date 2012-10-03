==============================
Tic-Tac-Toe: Human Vs Computer
==============================

This is a Tic-Tac-Toe Game to be played against a Computer.

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

==================
Basic Information:
==================

Based upon the Dimensions of the Matrix you choose (eg: 3x3, 4x4 etc), you will be presented with a Printed Matrix
initialized with all 'O's.

In general: 'O' means -> vacant position
            'X' means -> User's Entry
            'Y' means -> Computer's Entry

For Example:

-----------------------
   |   0   1   2   3  |
-----------------------
 0 |   X   O   O   O  |
 1 |   O   Y   O   O  |
 2 |   O   O   O   O  |
 3 |   O   O   O   O  |
-----------------------

Here: Position (0,0) is occupied by the User's Entry
      Position (1,1) is occupied by the Computer's Entry


=====================
How To Play the Game?
=====================

For each Chance, the User has to provide 2 Inputs: ROWNO COLNO

For Example:

Consider this fresh Matrix:

-----------------------
   |   0   1   2   3  |
-----------------------
 0 |   O   O   O   O  |
 1 |   O   O   O   O  |
 2 |   O   O   O   O  |
 3 |   O   O   O   O  |
-----------------------

Suppose the User wants to make an entry at: Row No. 2, Column No. 3

Then, the User must provide the folloing Input: 2 3 (Enter)

-----------------------
   |   0   1   2   3  |
-----------------------
 0 |   O   O   O   O  |
 1 |   O   O   O   O  |
 2 |   O   O   O   X  |
 3 |   O   O   O   O  |
-----------------------






