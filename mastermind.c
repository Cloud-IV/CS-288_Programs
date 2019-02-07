/*--------------------------------------------------------------------------------------------------------------------*/
/* Author: Abrar Rouf                                                                                                 */
/* mastermind.c                                                                                                       */
/*--------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc == 2)  /*checks if correct # of arguments were passed*/
    {
        int turnCounter = 12;
        char playerGuess[4];
        int i;  /*primary loop iterator*/
        int j;  /*secondary loop iterator*/

        printf("Available Colors: (B)lue (G)reen (O)range (P)urple (R)ed (Y)ellow\n");
        while (playerGuess != argv[1])
        {
            int correctPos = 0;     /*counts number of colors in the correct position*/
            int correctColor = 0;   /*counts number of correct colors in incorrect positions*/

            int bFlag = 0;          /*flags keep track of color encounters*/
            int gFlag = 0;
            int oFlag = 0;
            int pFlag = 0;
            int rFlag = 0;
            int yFlag = 0;

            printf("\n");
            printf("No. guesses left: %d\n", turnCounter);
            printf("Enter your guess: ");
            scanf("%s", playerGuess);

            for (i = 0; i < 4; i++) /*iterates through each letter of playerGuess*/
            {
                if (playerGuess[i] == argv[1][i]) correctPos++; /*checks if color is in correct position*/

                if (playerGuess[i] == 'B' && bFlag == 1) continue;  /*skips color if already encountered*/
                if (playerGuess[i] == 'G' && gFlag == 1) continue;
                if (playerGuess[i] == 'O' && oFlag == 1) continue;
                if (playerGuess[i] == 'P' && pFlag == 1) continue;
                if (playerGuess[i] == 'R' && rFlag == 1) continue;
                if (playerGuess[i] == 'Y' && yFlag == 1) continue;

                for (j = 0; j < 4; j++) if (playerGuess[i] == argv[1][j]) correctColor++; /*checks if there is a correct color*/

                if (playerGuess[i] == 'B') bFlag = 1;           /*raises flag if color is encountered*/
                if (playerGuess[i] == 'G') gFlag = 1;
                if (playerGuess[i] == 'O') oFlag = 1;
                if (playerGuess[i] == 'P') pFlag = 1;
                if (playerGuess[i] == 'R') rFlag = 1;
                if (playerGuess[i] == 'Y') yFlag = 1;
            }
            correctColor -= correctPos; /*adjusts correctColor for double-counted colors*/

            printf("        Feedback: %d, %d\n", correctPos, correctColor);
            if (correctPos == 4)        /*checks if win condition has been met and exits the game*/
            {
                printf("YOU WIN!\n");
                break;
            }
            else
            {
                turnCounter--;          /*decrements turn counter with every guess*/
                if (turnCounter == 0)   /*checks if no more turns are available and exits game*/
                {
                    printf("YOU LOSE! The code is %s\n", argv[1]);
                    break;
                }
                else continue;
            }
        }
    }
    else printf("ERROR: Wrong number of arguments.");
    return 0;
}