# **Connect 4 Game**
## ** some text **
I made this project for my GamePlay Programming Examn!
School: HOWEST - DEA - second year

## **Game Overview**
Connect 4 is a 2 player based game. The official board is with 6 rows and 7 columns, but this can be different if you'd like.
The goal is to connect 4 disk/coins either horizontally, vertically or diagonally. 

## **Approach Making Game**
First I had to make a connect 4 game, without an AI just the basic two player game. Each turn you switch from player1 to player2.
I made this in the framework of Programming 1. I used this framework because it's easy to implement simple graphical shapes(squares and ellipses).

But first I made it without graphics, I used the command prompt to print an 6x7 array. And used the 1-7 keys on tthe keyboard to insert the disk.
When this worked propperly I wanted to make a connect 4 board. And some animation, the disk hovers over the board when its your turn.
Here I had a problem that the rows of the array are inverted with the rows of the board. So I had to find a way to invert these Cells on my board.

When this worked I finally had a working connect 4 game!
Now I only have to make a bot for it...

## **Aproach Making AI**
The first bot/AI I made was really dumb. Basically every time it was his turn the bot took a random column that isn't full. As I made this 'AI' I knew this wasn't the optimal solution for making an AI but I wanted to implement this. ***I also wanted to make sure this idea of just giving it a column and placing it there worked.***
After doing this I had to find a way to find the absolute best column to place the disk. 
I found an algorithm ***minimax*** that is used a lot for simple disicion games. like Chess, Tic Tac Toe and e.g. Connect 4.
This algorithm requires a score for every terminal node. This means I have to make a scoring system based on what the best column is for the AI to place the disk.

So I made this function -> if the AI would place the disk in this column calculate how much the score would be.
I calculate the score if the board has a 3 in a row then I add 5 to the score. if I have 2 in a row I add 2 to the score.
If the board has a 4 in a row this means the AI can win if he'd place the disk in this column, I add 9999 to the score. If the enemy/Player1 has 3 in a row I substract 4.
I return the score.

So nw I have ascoring system. Then I decided to make an AI that makes choices in this boardstate. So he does not look in the future (I don't use the minimax function ***yet***).
I check this function for every column that isn't full. When I loop over every column I know wich one is the best to place the disk ***in this boardstate***.

When this worked I had a semi smart bot/AI. The only problem is that you can easily trick him, becasue he cannot look in the future. But it just looks at the best column for that moment.

Now I wanted to use the minimax algorithm. I found a pseudocode on the wikipedia so it was not that hard to implement. With this algorithm the AI is way smarter. It can look in the future, you only have to change the depth. The depth desides how ***far in the future it can look*** this algorithm is (O^n). This is a slow algorithm but smart.
Because this is an slow algorithm i searched for ways to reduce the time it needs. I found the ***alpha-beta pruning*** method. This elminates branches that won't change the sore, so this help a lot in time!
