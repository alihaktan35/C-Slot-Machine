#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_LINES 3
#define MAX_BET 100
#define MIN_BET 1

#define SYMBOL_COUNT 4
#define ROWS 3
#define COLUMNS 3

int map[ROWS][COLUMNS];

void printMap(int map[][COLUMNS])
{
    /**
    printf("*********");
    printf("* A B C *");
    **/

    printf("*********\n");
    for (int r = 0; r < ROWS; ++r)
    {
        printf("* ");
        for (int c = 0; c < COLUMNS; ++c)
        {
            switch (map[r][c])
            {
                case 0:
                    printf("A ");
                    break;
                case 1:
                    printf("B ");
                    break;
                case 2:
                    printf("C ");
                    break;
                case 3:
                    printf("D ");
                    break;
            }
        }
        printf("*\n");
    }
    printf("*********\n");
}

void spin() {
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLUMNS; ++c)
        {
            map[r][c] = rand() % SYMBOL_COUNT;
        }
    }
    printMap(map);
}

int checkWinnings(int map[][COLUMNS], int bet)
{
    int winningRows = 0;
    for (int r = 0; r < ROWS; ++r)
    {
            if (map[r][0] == map[r][1] && map[r][0] == map[r][2] && map[r][2] == map[r][1])
                winningRows++;
    }
    if (winningRows > 0)
    {
        printf("You won on %d lines.\n",winningRows);
        printf("You won $%d.\n",(int)pow(2,winningRows)*bet);
        return ((int)pow(2,winningRows)*bet);
    }
    else
    {
        printf("You won $0.\n");
        return 0;
    }
}

int deposit()
{
    int amount;
    while(true)
    {
        printf("What would you like to deposit?\n$");
        scanf("%d",&amount);
        if (amount > 0)
        {
            printf("\n");
            break;
        }
        else
            printf("Amount must be greater than 0.\n\n");
    }
    return amount;
}

int getNumberOfLines()
{
    int lines;
    while(true)
    {
        printf("Enter the number of lines to bet on (1-%d)?\n",MAX_LINES);
        scanf("%d",&lines);
        if (lines > 0 && lines <= MAX_LINES)
        {
            printf("\n");
            break;
        }
        else
            printf("\nPlease enter a number between 1 to %d.\n\n", MAX_LINES);
    }
    return lines;
}

int getBet()
{
    int amount;
    while(true)
    {
        printf("What would you like to bet on each line?\n$");
        scanf("%d",&amount);
        if (amount >= MIN_BET && amount <= MAX_BET)
        {
            printf("\n");
            break;
        }
        else
            printf("Please enter a number between $%d to $%d.\n\n",MIN_BET,MAX_BET);
    }
    return amount;
}

int main()
{
    srand(time(0)); //Prepares the program for randomizing
    int roundCount = 0;
    int balance = deposit();
    while(balance>0)
    {
        int lines = getNumberOfLines();
        int bet;
        int totalBet;
        while (true) //(Balance > Bet) checker
        {
            bet = getBet();
            totalBet = bet * lines;

            if (totalBet > balance) {
                printf("You do not have enough balance to bet that amount.\n"
                       "You are trying to bet $%d in total.\n"
                       "Your balance is $%d.\n\n", totalBet, balance);
            } else
                break;
        }
        printf("You are betting $%d on %d lines.\nTotal bet is $%d.\n\n", bet, lines, bet * lines);
        balance = balance - (bet*lines);
        spin();
        balance = balance + checkWinnings(map, bet);
        printf("\nYour new balance is $%d.\n\n",balance);
        roundCount++;
    }
    printf("Game Over!\nYou lost your all money.\n");
    printf("You have played %d rounds.\n",roundCount);
    return 0;

}
