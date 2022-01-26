# **Connect 4 Game**
I made this project for my GamePlay Programming Examn!
School: HOWEST - DEA - second year

## **Game Overview**
Connect 4 is a 2 player based game. The official board is with 6 rows and 7 columns, but this can be different if you'd like.
The goal is to connect 4 disk/coins either horizontally, vertically or diagonally. 

<img src="https://github.com/Gautjekski/Connect4Examn/blob/master/Connect4Game.PNG" alt="drawing" width="400"/>

## **Approach Making Game**
First I had to make a connect 4 game, without an AI just the basic two player game. Each turn you switch from player1 to player2.
I made this in the framework of Programming 1. I used this framework because it's easy to implement simple graphical shapes(squares and ellipses).

But first I made it without graphics, I used the command prompt to print an 6x7 array. And used the 1-7 keys on the keyboard to insert the disk.
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

So now I have a scoring system. Then I decided to make an AI that makes choices in this boardstate. So he does not look in the future (I don't use the minimax algorithm ***yet***).
I check this function for every column that isn't full. When I loop over every column I know wich one is the best to place the disk ***in this boardstate***.

When this worked I had a semi smart bot/AI. The only problem is that you can easily trick him, becasue he cannot look in the future. It just finds the best column for that moment.

Now I wanted to use the minimax algorithm. I found a pseudocode on the wikipedia so it was not that hard to implement. With this algorithm the AI is way smarter. It can look in the future, you only have to change the depth. The depth desides how ***far in the future it can look*** this algorithm is (O^n). This means its a slow algorithm but smart.
Because this is an slow algorithm I searched for ways to reduce the time it needs to find the best column. I found the ***alpha-beta pruning*** method. This elminates branches that won't change the score, so this help a lot in time!

## **Minimax Algorithm**

<img src="https://user-images.githubusercontent.com/95616199/151162358-5196b563-0338-465e-867c-5118705a4f26.png" alt="drawing" width="650"/>

So this is minimax algorithm I used, basically every time it goes down a level in depth it switches between min and max. When it is a at a **min** level it takes the minimum of its children. Max takes the max of its children. This algorithm is designed to get the best score, not the best column. So I had to modify the code a bit so tha algorithm remembers the best column.

This is the pseudo code:
```
function  minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value
```
## **Alpha-Beta pruning**

![image](https://user-images.githubusercontent.com/95616199/151164263-7409fe98-a13b-4692-8252-540039ab75f2.png)

This is an algorithm that prunes some branches of the minimax algorithm. By looking at the score it already has and based on that knows whether or not it'll affect the score, if not it won't Look in to that branch of the minimac algorithm.

This is pseudo code:
```
function alphabeta(node, depth, α, β, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            if value ≥ β then
                break (* β cutoff *)
            α := max(α, value)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            if value ≤ α then
                break (* α cutoff *)
            β := min(β, value)
        return value
```

## **Finnished Game/AI**
After I implemented these algorithms I had a finnished game/AI. I could only win once, since my AI is way to smart for me.
