#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>

int row;
int column;
char **board;
char **my_data;
clock_t my_time;

int my_isdigit(char c)
{
        //printf(" c is %c\n\n",c);
        if(c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9')
        return 0;
    else
        return -1;
}
void open_adjacent_empty(int r,int c)
{
    int i,j;
    int x;
    int ac1,ar1,ac2,ar2;
    ac1=c;
    ar1=r;
    ac2=c;
    ar2=r;
    i=r-1;
    j=c-1;
    if(i<0)
        ar1=1;
    if(j<0)
        ac1=1;
    if(r+1>row)
        ar2=row-1;
    if(c+1>column)
        ac2=column-1;
//printf(" %d and %d and %d and %d\n",r,ar1,ar2,row-1);
//printf(" %d and %d and %d and %d\n",c,ac1,ac2,column-1);
    for(i=ar1-1;i<ar2+2;i++)
        {
                    //printf("%d and %d\n",i,row);

            if(i>row-1){
                break;}
                        //printf("broke here3\n");

        for(j=ac1-1;j<ac2+2;j++)
        {
                    //printf("broke here4\n");

            if(j>column)
                break;
                //printf("broke here 5\n");
         //printf("%d and %d",i,j);
         //printf("%d\n\n",(board[i][j]!='*' && board[i][j]!='F' && board[i][j]!=' '));
         //printf("Row %d and Column %d is %c\n",i+1,j+1,board[i][j]);
               //    printf("%d and %d\n",i,j);   printf("are %c\n\n",board[i][j]);
            //printf("x is %d\n",x);
            if(my_data[i][j]!='*' && my_data[i][j]!='F' && board[i][j]!=my_data[i][j])
            {
           //     printf("check 1\n");
           //printf("was %c\t",board[i][j]);
                board[i][j]=my_data[i][j];
             //   printf("became %c\n",board[i][j]);
             //printf("check 2\n");
             //printf("%d and %d\n",i,j);
            //
             //printf("are %c\n\n",board[i][j]);
             x=my_isdigit(board[i][j]);
             //printf("%d",x);
             if(x!=0){
                open_adjacent_empty(i,j);
             }
                //printf("chech hete\n");
            }

        }
        //printf("done row %d\n",i+1);
        //printf("broke here1\n");

}
//printf("check alpha\n");
}

void game_over()
{
    display_board();
    printf("Game Over !!");
    exit(0);
}
void get_size(){
    printf("Please enter the number of rows:\n ");
    scanf("%d",&row);
    printf("Please enter the number of columns: \n");
    scanf("%d",&column);
}

void create_board(){
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++){
            board[i][j]='X';
            my_data[i][j]='0';
         //   printf("is %c\n",my_data[i][j]);
        }
    }
}

void display_board(int way){
    int i,j;
    printf("  |");
    for(j=0;j<column;j++)
    {
        printf(" %d |",j+1);
    }
    printf("\n");
    for(i=0;i<row;i++)
    {
        printf("%02d|",i+1);
        for(j=0;j<column;j++)
        {

            if(board[i][j]=='0')
                printf("   |");
                else
                    printf(" %c |",board[i][j]);
            }
            printf("%d\n",i+1);
            }
            printf("\n");
            if(way==2)
                open_cell(2);
}

void mines_func(int r,int c){
    srand(time(0));
    int x,y,i,j;
    int mines;
    mines= 1+ (row*column)/5;
    //printf("check 5");
    for(i=0;i<mines;i++)
    {
        //printf("check 5.5");
        do{
        x=rand()%row;
        y=rand()%column;
        }while(x==r || y==c);
        //printf("%d and %d",x,y);
        my_data[x][y]='*';
    //printf("check 6\n");
    }
//printf("check 7");
}

void init_board()
{
    int i,j,k,l;
    for(i=0;i<row;i++)
    {

        for(j=0;j<column;j++)
        {
            for(k=i-1;k<i+2&& k<row;k++)
            {

                if(k<0)
                k=0;
            for(l=j-1;l<j+2 && l<column;l++)
        {

            if(l<0)
                l=0;
            if(my_data[k][l]=='*'&& !(l==j && k==i) && my_data[i][j]!='*')
                //my_data[i][j]='0';
                my_data[i][j]++;
        }

            }
    }
    }
}
void start_game(){
    display_board(1);
    open_cell(1);

}

void open_cell(int way){
    int r,c;
    printf("Enter the coordinates of the cell: \n");
    printf("Row:");
    scanf("%d",&r);
    printf("Column:");
    scanf("%d",&c);
    if(way==1)
    {
    //display_board(1);
    mines_func(r-1,c-1);
    init_board();
    }
    if(my_data[r-1][c-1]=='*' && way==2)
    {
        board[r-1][c-1]=my_data[r-1][c-1];
        game_over();
    }
    else
        {
            board[r-1][c-1]=my_data[r-1][c-1];
            //printf("is %c\n\n",my_data[r-1][c-1]);
            //printf("and is %c\n\n",board[r-1][c-1]);
            open_adjacent_empty(r-1,c-1);
            //printf("check hi\n");
        }
        //printf("check w\n");
    display_board(2);
}


int main()
{
    int i;
    get_size();
//printf("check 1");
    board=(char**)malloc(row*sizeof(char*));
    my_data=(char**)malloc(row*sizeof(char*));
    for(i=0;i<row;i++)
    {
        board[i]=(char*)malloc(column*sizeof(char));
        my_data[i]=(char*)malloc(column*sizeof(char));
    }
    //printf("check 2");
    create_board();
    //printf("check 3");
    start_game();

    return 0;
}
