#include<time.h>
#include<conio.h>
#include<iostream>
#include<windows.h>
#define DIM 8
#define WIDTH  5
#define HEIGHT 1
#define MAXROWS 25
#define MAXCOLS 80

char LT=218;
char RT=191;
char LB=192;
char RB=217;
char TT=194;
char BT=193;
char HL=196;
char VL=179;
char LST=195;
char RST=180;
char CROSS=197;
char SPACE =32;
char BS=8;
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27
#define ENTER 13
#define FLAG 70
#define BOX_OPENED 1
#define BOX_CLOSED 0
#define FLAG_MARKED 2
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
class Mines
{
    int mines[DIM][DIM];
    int visited[DIM][DIM];
    int tot_mines,ind,row,col;
    int minePositions[][2];
public:
    Mines()
    {
        for(int i=0;i<DIM;i++)
            for(int j=0;j<DIM;mines[i][j]=0,visited[i][j]=0,j++);
        tot_mines=6;
        minePositions[tot_mines][2];
    }
    void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);
}

    void drawbox()
{
 int row, col, ctr1, ctr2, ctr3, ctr4;
 col = ( (MAXCOLS) - ( (DIM) * (WIDTH) + (DIM+1) ) )  / 2;
 row = ( (MAXROWS) - ( (DIM) * (HEIGHT)+ (DIM+1) ) )  / 2;
 gotoxy(col, row);
cout<<LT;
 for(ctr2 = 0; ctr2 < DIM; ctr2 ++)
 {
   for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
     cout<<HL;
 cout<<TT;
 }
 cout<<BS<<RT;
  for(ctr3 = 0; ctr3 < DIM; ctr3++)
 {
 gotoxy(col, ++row);
 for(ctr2 = 0; ctr2 <= DIM; ctr2++)
 {
 cout<<VL;
   for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
     cout<<SPACE;
 }
 gotoxy(col, ++row);
 cout<<LST;
 for(ctr2 = 0; ctr2 < DIM; ctr2++ )
 {
   for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
     cout<<HL;
cout<<CROSS;
 }
  cout<<BS<<RST;
}

 gotoxy(col, row);
cout<<LB;
 for(ctr2 = 0; ctr2 < DIM; ctr2 ++)
 {
   for(ctr1 = 0; ctr1 < WIDTH; ctr1++)
     {
         cout<<HL;
     }
cout<<BT;
 }
cout<<BS<<RB;
}

    void placeMines()
    {
     time_t t;
     int mineCtr=0,row,col;
    srand((unsigned)time(&t));
   while(mineCtr<tot_mines)
   {
       row = rand()% DIM;
       col= rand() %DIM;
       if(mines[row][col]==0)
       {
	   mines[row][col]=9;
	   minePositions[mineCtr][0]=row;
	   minePositions[mineCtr][1]=col;
	   cout<<minePositions[mineCtr][0]<< " "<<minePositions[mineCtr][1];
	   mineCtr++;
       }
   }
    }
    void fillMinesCount()
    {
        int ind,c_row,c_col;
  for(ind= 0 ;ind<tot_mines;ind++)
  {
      c_row=minePositions[ind][0];
      c_col=minePositions[ind][1];
      //top
      if(c_row-1 >=0 &&mines[c_row-1][c_col]!=9)
            mines[c_row-1][c_col]++;
      //right top
      if(c_row-1>=0 && c_col+1<DIM &&mines[c_row-1][c_col+1]!=9)
            mines[c_row-1][c_col+1]++;
      //right
      if( c_col+1<DIM &&mines[c_row][c_col+1]!=9)
            mines[c_row][c_col+1]++;
      //right bottom
      if( c_col+1<DIM &&c_row+1<DIM &&mines[c_row+1][c_col+1]!=9)
            mines[c_row+1][c_col+1]++;
      //bottom
      if( c_row+1<DIM &&mines[c_row+1][c_col]!=9)
            mines[c_row+1][c_col]++;
      //left bottom
       if( c_col-1>=0 &&c_row+1<DIM &&mines[c_row+1][c_col-1]!=9)
            mines[c_row+1][c_col-1]++;
          //left
       if( c_col-1>=0  &&mines[c_row][c_col-1]!=9)
            mines[c_row][c_col-1]++;
      //left top
      if( c_col-1>=0 &&c_row-1>=0 &&mines[c_row-1][c_col-1]!=9)
            mines[c_row-1][c_col-1]++;

  }
    }
    void gamePlay()
    {
        int key,scol,srow,box_row,box_col,flagCtr,properFlagCtr;
   //set a cursor
   scol= (MAXCOLS - ((DIM*WIDTH) + DIM +1 )) /2 ;
    srow = (MAXROWS - ((DIM*HEIGHT)+DIM+1)) /2;
    gotoxy(scol+19,srow-1);
    cout<<"MINESWEEPER";
    scol+=3;
    srow+=1;
     flagCtr=properFlagCtr=0;
    gotoxy(scol+50,srow);
    cout<<"FLAG REM :"<<tot_mines-flagCtr;
   box_row=0;
    box_col=0;
    gotoxy(scol+(box_col*(WIDTH+1)),srow+(box_row*(HEIGHT+1)));
    while(key!=ESC)
    {
         if (kbhit())
      {
            key = getch();
	switch(key)
	{
	  case UP:
		   if(box_row-1>=0)
		   {
		    box_row--;
		    gotoxy(scol+(box_col*(WIDTH+1)),srow+(box_row*(HEIGHT+1)));
		   }
		   break;
	  case DOWN:
		   if(box_row+1<DIM)
		   {
		    box_row++;
		    gotoxy(scol+(box_col*(WIDTH+1)),srow+(box_row*(HEIGHT+1)));
		   }
		   break;
	  case RIGHT:
		   if(box_col+1<DIM)
		   {
		    box_col++;
		    gotoxy(scol+(box_col*(WIDTH+1)),srow+(box_row*(HEIGHT+1)));
		   }
		   break;
	  case LEFT:
		   if(box_col-1>=0)
		   {
		    box_col--;
		    gotoxy(scol+(box_col*(WIDTH+1)),srow+(box_row*(HEIGHT+1)));
		   }
		   break;
	  case ENTER:
		     if(mines[box_row][box_col]==9)//mine
		     {
		       cout<<"Game over";
		       key=ESC;
		       break;
		     }
		     if(mines[box_row][box_col]>0 && visited[box_row][box_col]==BOX_CLOSED) //non zeros
		     {
		       cout<<mines[box_row][box_col];
		       visited[box_row][box_col]=BOX_OPENED;
		       break;
		     }
		     if(mines[box_row][box_col]==0&& visited[box_row][box_col]==BOX_CLOSED)
		     {
			cout<<mines[box_row][box_col];
			visited[box_row][box_col]=BOX_OPENED;
			openSurroundingBoxes(box_row,box_col);
		     }
		   break;
	  case FLAG:
		    if(visited[box_row][box_col]==BOX_CLOSED&&flagCtr<tot_mines)
		    {
		     cout<<"F";
		      flagCtr++;
		      if(mines[box_row][box_col] == 9) //there is a mine
		      {
			properFlagCtr++;//marking on a mine
			if(properFlagCtr==tot_mines) //game won
			{
			 cout<<"YOU WON";
			 key = ESC;
			 break;
			}
		      }
		      visited[box_row][box_col]=FLAG_MARKED;
		    }
		    else if(visited[box_row][box_col]==FLAG_MARKED)
		    {
		     cout<<" ";//flag removed
		     flagCtr--;
		      if(mines[box_row][box_col] == 9) //there is a mine
		      {
			properFlagCtr--;//removing a flag where mine is availabel
		      }
		     visited[box_row][box_col] = BOX_CLOSED;
		    }
		   break;
	}
	gotoxy(scol+50,srow);
	cout<<"FLAG REM :"<<tot_mines-flagCtr;
   gotoxy(scol+(box_col*(WIDTH+1)),srow+(box_row*(HEIGHT+1)));

   }
    }
    }

    void openSurroundingBoxes(int zero_row,int zero_col)
    {

   int srow,scol;
    scol= (MAXCOLS - ((DIM*WIDTH) + DIM +1 )) /2 ; //(given-used)/2
    srow = (MAXROWS - ((DIM*HEIGHT)+DIM+1)) /2;
    scol+=3;
    srow+=1;
 //top
 if(zero_row-1>=0&&visited[zero_row-1][zero_col]==BOX_CLOSED)
 {
	gotoxy(scol+((zero_col)*(WIDTH+1)),srow+((zero_row-1)*(HEIGHT+1)));
	cout<<mines[zero_row-1][zero_col];
	visited[zero_row-1][zero_col]=BOX_OPENED;
	if(mines[zero_row-1][zero_col]==0) //doing recursive for the zero
	   openSurroundingBoxes(zero_row-1,zero_col);
 }
 //right top
 if(zero_row-1>=0&&zero_col+1<DIM&&visited[zero_row-1][zero_col+1]==BOX_CLOSED)
 {
   gotoxy(scol+((zero_col+1)*(WIDTH+1)),srow+((zero_row-1)*(HEIGHT+1)));
   cout<<mines[zero_row-1][zero_col+1];
   visited[zero_row-1][zero_col+1]=BOX_OPENED;
   if(mines[zero_row-1][zero_col+1]==0) //doing recursive for the zero
      openSurroundingBoxes(zero_row-1,zero_col+1);
 }
 //right
 if(zero_col+1<DIM&&visited[zero_row][zero_col+1]==BOX_CLOSED)
 {
   gotoxy(scol+((zero_col+1)*(WIDTH+1)),srow+((zero_row)*(HEIGHT+1)));
   cout<<mines[zero_row][zero_col+1];
   visited[zero_row][zero_col+1]=BOX_OPENED;
   if(mines[zero_row][zero_col+1]==0) //doing recursive for the zero
      openSurroundingBoxes(zero_row,zero_col+1);
 }
 //right bottom
 if(zero_row+1<DIM&&zero_col+1<DIM&&visited[zero_row+1][zero_col+1]==BOX_CLOSED)
 {
   gotoxy(scol+((zero_col+1)*(WIDTH+1)),srow+((zero_row+1)*(HEIGHT+1)));
   cout<<mines[zero_row+1][zero_col+1];
   visited[zero_row+1][zero_col+1]=BOX_OPENED;
   if(mines[zero_row+1][zero_col+1]==0) //doing recursive for the zero
      openSurroundingBoxes(zero_row+1,zero_col+1);
 }
 //bottom
 if(zero_row+1<DIM&&visited[zero_row+1][zero_col]==BOX_CLOSED)
 {
   gotoxy(scol+((zero_col)*(WIDTH+1)),srow+((zero_row+1)*(HEIGHT+1)));
   cout<<mines[zero_row+1][zero_col];
   visited[zero_row+1][zero_col]=BOX_OPENED;
   if(mines[zero_row+1][zero_col]==0) //doing recursive for the zero
      openSurroundingBoxes(zero_row+1,zero_col);
 }
 //left bottom
 if(zero_row+1<DIM&&zero_col-1>=0&&visited[zero_row+1][zero_col-1]==BOX_CLOSED)
 {
   gotoxy(scol+((zero_col-1)*(WIDTH+1)),srow+((zero_row+1)*(HEIGHT+1)));
   cout<<mines[zero_row+1][zero_col-1];
   visited[zero_row+1][zero_col-1]=BOX_OPENED;
   if(mines[zero_row+1][zero_col-1]==0) //doing recursive for the zero
      openSurroundingBoxes(zero_row+1,zero_col-1);

 }
 //left
 if(zero_col-1>=0&&visited[zero_row][zero_col-1]==BOX_CLOSED)
 {
   gotoxy(scol+((zero_col-1)*(WIDTH+1)),srow+((zero_row)*(HEIGHT+1)));
   cout<<mines[zero_row][zero_col-1];
   visited[zero_row][zero_col-1]=BOX_OPENED;
   if(mines[zero_row][zero_col-1]==0) //doing recursive for the zero
      openSurroundingBoxes(zero_row,zero_col-1);
 }
 //left top
 if(zero_row-1>=0&&zero_col-1>=0&&visited[zero_row-1][zero_col-1]==BOX_CLOSED)
 {
   gotoxy(scol+((zero_col-1)*(WIDTH+1)),srow+((zero_row-1)*(HEIGHT+1)));
  cout<<mines[zero_row-1][zero_col-1];
   visited[zero_row-1][zero_col-1]=BOX_OPENED;
   if(mines[zero_row-1][zero_col-1]==0) //doing recursive for the zero
      openSurroundingBoxes(zero_row-1,zero_col-1);
 }
    }

};


int main()
{
    cout<<"Press Enter key to open surrounding,arrow keys to move among boxes and 'F' to set flag";
Mines m;
m.drawbox();
m.placeMines();
m.fillMinesCount();
m.gamePlay();
}

