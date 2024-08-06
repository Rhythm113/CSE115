#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define O 79
#define X 88
#define BLANK 46

int board[3][3];

/*

O X O   O = 79
O X O   X = 88
O X O


*/

void print_board()
{
     printf("\n\n\n");
     for (int i = 0; i < 3; i++)
     {
          for (int j = 0; j < 3; j++)
          {
               printf("%c", board[i][j]);
               printf(" ");
          }

          printf("\n");
     }
}

void clear_board()
{
     for (int i = 0; i < 3; i++)
     {
          for (int j = 0; j < 3; j++)
          {
               board[i][j] = BLANK;
          }
     }
}

bool win(int val)
{
     for (int i = 0; i < 3; i++)
     {
          if (board[i][0] == val && board[i][1] == val && board[i][2] == val)
               return true;
     }

     for (int i = 0; i < 3; i++)
     {
          if (board[0][i] == val && board[1][i] == val && board[2][i] == val)
               return true;
     }
     // diagonal
     if ((board[0][0] == val && board[1][1] == val && board[2][2] == val) ||
         (board[0][2] == val && board[1][1] == val && board[2][0] == val))
     {
          return true;
     }

     return false;
}

bool draw()
{
     for (int i = 0; i < 3; i++)
     {
          for (int j = 0; j < 3; j++)
          {
               if (board[i][j] == BLANK)
               {
                    return false;
               }
          }
     }
     return true;
}

void update(int m, int *ptr)
{
     if (m == 0 || m == 10)
     {
          return;
     }
     int go = m - 1;
     int p = go - 3;
     if (p < 0)
     { // 0,1,2
          if (board[0][go] != BLANK)
          {
               // printf("\n\n\nAlready filed, Try again !\n");
               return;
          }
          board[0][go] = *ptr;
     }
     int q = p - 3;
     if (q <= 0 && p >= 0)
     { // 3,4,5
          if (board[1][p] != BLANK)
          {
               // printf("\n\n\nAlready filed, Try again !\n");
               return;
          }
          board[1][p] = *ptr;
     }
     if (q > 0)
     { // 6,7,8
          if (board[2][q] != BLANK)
          {
               // printf("\n\n\nAlready filed, Try again !\n");
               return;
          }
          board[2][q] = *ptr;
     }

     // swap

     if (*ptr == O)
     {
          *ptr = X;
          return;
     }
     if (*ptr == X)
     {
          *ptr = O;
          return;
     }
}

void play()
{
     system("cls");
     clear_board(board);
     int tt = O;
     int move;

     while (1)
     {
          
          if (move == 10)
          {
               system("cls");
               printf("\t\t\tThe Game was cancelled!!\n\n\n");
               break;
          }
          
          if (win(X))
          {
               system("cls");
               printf("\t\t\t%c WON !!\n\n\n", X);
               break;
          }
          if (win(O))
          {
               system("cls");
               printf("\t\t\t%c WON !!\n\n\n", O);
               break;
          }
          if (draw())
          {
               system("cls");
               printf("\t\t\tIt's a DRAW !!\n\n\n");
               break;
          }
          system("cls");
          print_board();
          printf("\n\n\n%c's Turn (1-9) [10 to exit] : ", tt);
          scanf("%d", &move);

          if (move > 10 || move < 1)
          {
               printf("\n\n\nInvalid Move !\n");
               move = 0;
          }
          update(move, &tt);
     }
}







void print_menu()
{
     // system("cls");
     // printf("%d",'.');
     printf("\t\t\t==========================\n");
     printf("\t\t\tSimple useless game -_- \n");
     printf("\t\t\tAuthor : Rhythm113\n");
     printf("\t\t\t==========================\n");
     printf("\n\t\t\tChoose an option : \n");
     printf("\t\t\t1.Play Multi Player\n");
     printf("\t\t\t2.Exit\n");
     printf("\n\n\t\t\tChoose between (1-2) : ");
}

int main()
{
     while (1)
     {
          int n;
          print_menu();
          scanf("%d", &n);
          switch (n)
          {
          case 1:
               play();
               break;
          case 2:
               exit(0);

          default:
               printf("Invalid choice!\n");
               system("cls");
          }
     }
}