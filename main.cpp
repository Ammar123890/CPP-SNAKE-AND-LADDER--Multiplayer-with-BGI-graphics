

#include <iostream>
#include <conio.h>
#include "winbgi.h"
#include "graphics.h"
#include "stdio.h"
#include <Windows.h>
#include <stdlib.h>
#include <windows.h>
#include "winbgim.h"
#include <ctime>
#include <string.h>

using namespace std;

//User Defined Functions
int StartGame(int x[], int y[]);
void PrintBoard(int x[],int y[],int a,int,int);
void cp1(int,int);
void cp2(int,int);
void Snakes(int& currentPosition);
void Ladders(int& currenPosition);
void PlayerPositions(int x[], int y[],int one, int two);
void InitCordinates(int x[],int y[]);
void DrawingBoard(int xCord[], int yCord[]);
void PrintBoxNumber(int boxNum);
void DiceSetting(int diceValue);
void SnakesAndLadders();

//Constants 
const int TotalBox=30;
const int columnCount=6;
const int w=100;
const int h=63;

void main()
{	
	int x[TotalBox+1],y[TotalBox+1];
	InitCordinates(x,y);
	initwindow(1180,600,"19L-1110, 19L-1095");
	ShowWindow( GetConsoleWindow(), SW_HIDE );
	while (true)
	{
		if (StartGame(x,y)==true)
		{
			cin.clear();
			getch();
		}
	}
	system("pause");
}

int StartGame(int x[], int y[])
{
	int px=0,py=0;
		int currentPosition1=0,currentPosition2=0,diceValue,temp=0,count=2,playerTurn=1;
		PrintBoard(x,y,1,0,0);
		while (currentPosition1<30 && currentPosition2<30)
		{
			ShowWindow( GetConsoleWindow(), SW_HIDE );
			cin.clear();
			temp=0;
			diceValue=0;
			count=1;
			srand(time(NULL));
			if(playerTurn%2!=0)
			{
				if(playerTurn!=1)
					delay(200);
				setcolor(WHITE);
				settextstyle(6,HORIZ_DIR,3);
				moveto(330,370);
				outtext("Player 1 Turn");
				moveto(330,370);
			}  
			else 
			{
				delay(200);
				setcolor(WHITE);
				settextstyle(6,HORIZ_DIR,3);
				moveto(330,370);
				moveto(330,370);
				outtext("Player 2 Turn");
			}

			while(!ismouseclick(WM_LBUTTONDOWN))
			{
				//delay(100);
			}
			getmouseclick(WM_LBUTTONDOWN,px ,py);
			while ((px<280 || px>320 || py<370 || py>410) && (px<680 && px>1050 && py<360&& py>375))
			{
				clearmouseclick(WM_LBUTTONDOWN);
				getmouseclick(WM_LBUTTONDOWN,px ,py);
			}
			if (px>680 && px<1050 && py>360&& py<375)
			{
				return 0;
			}
			if(px>280 && px<320 && py>370 && py<410)
			{
				diceValue=rand()%6+1;
				DiceSetting(diceValue);
				temp=diceValue;
				while (diceValue==6 || diceValue==0)
				{
					delay(250);
					diceValue=rand()%6+1;
					DiceSetting(diceValue);
					temp=temp+diceValue;
				
					if (count==3)
					{
						temp=0;
						setcolor(WHITE);
						moveto(40,430);
						settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
						outtext("You have lost your move");
						delay(500);
						outtext("                             ");

					}
					count++;
				}
				setcolor(WHITE);
				if (playerTurn%2!=0)
				{
					currentPosition1=currentPosition1+temp;
					Snakes(currentPosition1);
					Ladders(currentPosition1);
					if (currentPosition1>30)
						currentPosition1-=temp;
					outtextxy(275,480,"    ");
					moveto(275,480);
					PrintBoxNumber(currentPosition1);
					PlayerPositions(x,y,currentPosition1,currentPosition2);
				}
				else if (playerTurn%2==0)
				{
					currentPosition2=currentPosition2+temp;
					Snakes(currentPosition2);
					Ladders(currentPosition2);
					if (currentPosition2>30)
						currentPosition2-=temp;
					outtextxy(275,505,"    ");
					moveto(275,505);
					PrintBoxNumber(currentPosition2);
					PlayerPositions(x,y,currentPosition1,currentPosition2);
				}
				playerTurn++;
				cin.clear();
			}
			clearmouseclick(WM_LBUTTONDOWN);
		}

		if (currentPosition1==30)
		{
			delay(800);
			readimagefile("P1Wins.jpg",0,0,1180,600);
			//getch();
			return 1;
		}
		else if (currentPosition2==30)
		{
			delay(800);
			readimagefile("P2Wins.jpg",0,0,1180,600);
			//getch();
			return 1;
		}
		
}

void PrintBoard(int x[],int y[],int a,int one,int two)
{
   readimagefile("bk.jpg",0,0,1180,600);
   DrawingBoard(x, y);
   SnakesAndLadders();
   setcolor(WHITE);
   setcolor(GREEN);
   moveto(340,4);
   settextstyle(GOTHIC_FONT,HORIZ_DIR,4);
   outtext("SNAKE AND LADDER");
   setcolor(WHITE);
   moveto(230,460);
   settextstyle(0,HORIZ_DIR,2);
   outtext("Positions");
   settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
   moveto(65,475);
   outtext(" Player 1 ");
   moveto(65,502);
   outtext(" Player 2 ");
   cp1(-35,470);
   cp2(-35,470);
   setcolor(WHITE);
   moveto (40,370);
   settextstyle(6,HORIZ_DIR,5);
   outtext("Roll Dice");
   moveto(55,412);
   setcolor(WHITE);
   settextstyle(0,0,1);
   outtext("(Click the dice button)");
   rectangle(280,370,320,410);
   setcolor(RED);
   rectangle(635,365,35,450);

   setcolor(RED);
   moveto(685,70);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
   outtext("Snakes Positions:");
   moveto(685,226);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
   outtext("Ladders Positions:");
   settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
   rectangle (680,70,1120,350);
   setcolor(WHITE);
   settextstyle(6,HORIZ_DIR,2);
   outtextxy(275,480,"    ");
   moveto(275,480);
   PrintBoxNumber(0);
   outtextxy(275,505,"    ");
   moveto(275,505);
   PrintBoxNumber(0);
   //rectangle(680,360,1050,375);
   outtextxy(680,360,"Click me to Reset the Game");
   moveto(690,96);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
   outtext("> Top: 27 / Bottom: 1");
   moveto(690,122);
   outtext("> Top: 21 / Bottom: 9");
   moveto(690,148);
   outtext("> Top: 17 / Bottom: 4");
   moveto(690,174);
   outtext("> Top: 19 / Bottom: 7");

   moveto(690,252);
   settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
   outtext("> Bottom: 3 / Top: 22");
   moveto(690,278);
   outtext("> Bottom: 5 / Top: 8");
   moveto(690,304);
   outtext("> Bottom: 11 / Top: 26");
   moveto(690,330);
   outtext("> Bottom: 20 / Top: 29");

   
   readimagefile("dicec.jpg",280,370,320,410);
}

void Snakes(int& currentPosition)
{	
	settextstyle(GOTHIC_FONT,HORIZ_DIR,1);
	if (currentPosition==27)
	{
		currentPosition=1;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Oops! You hit the snake");
		delay(1200);
	}
	else if (currentPosition==21)
	{
		currentPosition=9;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Oops! You hits the snake");
		delay(1200);
	}
	else if (currentPosition==17)
	{
		currentPosition=4;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Oops! hits the snake");
		delay(1200);
	}
	else if (currentPosition==19)
	{
		currentPosition=7;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Oops! hits the snake");
		delay(1200);
	}
	moveto(40,430);
	outtext("                                         ");
}

void Ladders(int& currenPosition)
{
	if (currenPosition==5)
	{
		currenPosition=8;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Hurry! You hit the Ladder");
		delay(1200);
	}
	else if (currenPosition==3)
	{
		currenPosition=22;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Hurry! You hit the Ladder");
		delay(1200);
	}
	else if (currenPosition==11)
	{
		currenPosition=26;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Hurry! You hit the Ladder");
		delay(1200);
	}
	else if (currenPosition==20)
	{
		currenPosition=29;
		setcolor(WHITE);
		moveto(40,430);
		outtext("Hurry! You hit the Ladder");
		delay(1200);
	}
	moveto(40,430);
	outtext("                                         ");
}

void cp2(int xx,int yy)
{
	int a,b;
	a=xx+85;
	b=yy+42;
	setcolor(LIGHTGREEN);
	circle(a,b,12);
	setfillstyle(1,9);
	floodfill(a,b,LIGHTGREEN);
}
void cp1(int xx,int yy)
{
	int a,b;
	a=xx+85;
	b=yy+16;
	setcolor(LIGHTGREEN);
   circle(a,b,12);
   setfillstyle(1,14);
   floodfill(a,b,LIGHTGREEN);
}

void PlayerPositions(int x[], int y[],int one ,int two)
{
	DrawingBoard(x, y);
	SnakesAndLadders();
	if (one!=0)
	{
		cp1(x[one],y[one]);
	}
	if (two!=0)
	{
		cp2(x[two],y[two]);
	}
}

 void InitCordinates(int x[],int y[])
{
	bool LtoR=true;
	int box=1;
	int x_position=35,y_position=295;
	x[0]=35;
	while(box<=TotalBox)
	{
		x_position=x[box-1];
		if (LtoR==true)
		{
			for (int i=0;i<columnCount;i++)
			{				
				x[box]=x_position+(i*w);
				y[box]=y_position;
				box++;
			}
			LtoR=false;
		}
		else 
		{		

			for (int i=0;i<columnCount;i++)
			{
				y[box]=y_position;
				x[box]=x_position-(i*w);
				box++;
			}
			LtoR=true;
		}
		y_position=y_position-h;
	}
}
void DrawingBoard(int xCord[], int yCord[])
	{
		int x,y,x1,y1;
		setcolor(WHITE);
		for (int i=1;i<=TotalBox;i++)
		{
			x=xCord[i];
			y=yCord[i];
			x1=x+w;
			y1=y+h;
			rectangle(x,y,x1,y1);
			
			if (i%2!=0)
			{
				setfillstyle(1,2);
				floodfill(x+50,y+50,WHITE);
				setcolor(WHITE);				
			}
			if (i%2==0)
			{
				setfillstyle(1,4);
				floodfill(x+50,y+50,WHITE);
			}
			moveto(x+w/2-10,y+h/2);
			settextstyle(6,HORIZ_DIR,2);
			PrintBoxNumber(i);	
		}
	}
void PrintBoxNumber(int boxNum)
{
	switch(boxNum)
	{
	    case 0:outtext("0");
		break;
		case 1:outtext("1");
		break;
		case 2:outtext("2");
		break;
		case 3:outtext("3");
		break;
		case 4:outtext("4");
		break;
		case 5:outtext("5");
		break;
		case 6:outtext("6");
		break;
		case 7:outtext("7");
		break;
		case 8:outtext("8");
		break;
		case 9:outtext("9");
		break;
		case 10:outtext("10");
		break;
		case 11:outtext("11");
		break;
		case 12:outtext("12");
		break;
		case 13:outtext("13");
		break;
		case 14:outtext("14");
		break;
		case 15:outtext("15");
		break;
		case 16:outtext("16");
		break;
		case 17:outtext("17");
		break;
		case 18:outtext("18");
		break;
		case 19:outtext("19");
		break;
		case 20:outtext("20");
		break;
		case 21:outtext("21");
		break;
		case 22:outtext("22");
		break;
		case 23:outtext("23");
		break;
		case 24:outtext("24");
		break;
		case 25:outtext("25");
		break;
		case 26:outtext("26");
		break;
		case 27:outtext("27");
		break;
		case 28:outtext("28");
		break;
		case 29:outtext("29");
		break;
		case 30:outtext("30");
		break;
	}
}
void DiceSetting(int diceValue)
{
	settextstyle(6,0,5);
	if (diceValue==1)
	{
		outtextxy(285,370,"1");
		readimagefile("dice1.jpg",280,370,320,410);
	}
	else if (diceValue==2)
	{
		outtextxy(285,370,"2");
		readimagefile("dice2.jpg",280,370,320,410);
	}
	else if (diceValue==3)
	{
		outtextxy(285,370,"3");
		readimagefile("dice3.jpg",280,370,320,410);
	}
	else if (diceValue==4)
	{
		outtextxy(285,370,"4");
		readimagefile("dice4.jpg",280,370,320,410);
	}
	else if (diceValue==5)
	{
		outtextxy(285,370,"5");
		readimagefile("dice5.jpg",280,370,320,410);
	}
	else if (diceValue==6)
	{
		outtextxy(285,370,"6");
		readimagefile("dice6.jpg",280,370,320,410);
	}
}
void SnakesAndLadders()
{
	//snakes
	int x = 183, x1 = 177, x2 = 150, x3 = 135, x4 = 120, y = 230, z = 200, d = 400, f = 400, j = 453, k = 470, l = 560, m = 557;
	setcolor(LIGHTGRAY);
	for (int i = 0; i < 15; i++)
	{
		arc(y++, 100, 40, 230, 35);
		arc(x++, 150, 270, 60, 35);
		arc(x1++, 218, 70, 245, 35);
		arc(x2++, 285, 245, 70, 40);
		line(x3++, 320, x4++, 320);
	}
	setcolor(LIGHTGRAY);
	for (int i = 20; i != 0; i--)
	{
		for (int j = 15; j != 0; j--)
		{
			ellipse(270,80, 0, 0, i, j);
		}
	}
	setcolor(BLACK);
	for (int i = 3; i != 0; i--)
	{
		circle(261,73, i);
	}
	for (int i = 3; i != 0; i--)
	{
		circle(275,73, i);
	}
	ellipse(270, 83, 0, 0, 6, 5);
	line(270, 81, 273, 90);
	setcolor(CYAN);
	int p = 400, lo = 400;
	for (int i = 0; i < 15; i++)
	{
		arc(d++, 160, 270, 90, 15);
		arc(f++, 185, 90, 250, 15);
		arc(p++, 213, 250, 90, 15);
		arc(lo++, 240, 90, 250, 15);
	}
	setcolor(CYAN);
	for (int i = 23; i != 0; i--)
	{
		for (int j = 17; j != 0; j--)
		{
			ellipse(391, 140, 0, 0, i, j);
		}
	}
	setcolor(RED);
	for (int i = 3; i != 0; i--)
	{
		circle(385, 133, i);
	}
	for (int i = 3; i != 0; i--)
	{
		circle(400, 133, i);
	}
	ellipse(391, 143, 0, 0, 8, 5);
	line(391, 143, 385, 150);
	setcolor(BLACK);
	int yo = 458, zo = 444;
	for (int i = 0; i < 15; i++)
	{
		arc(j++, 230, 260, 70, 20);
		arc(k++, 195, 60, 250, 20);
		arc(yo++, 267, 90, 250, 20);
		arc(zo++, 302, 230, 60, 20);
		line(436, 315, 415, 315);
	}
	setcolor(BLACK);
	for (int i = 22; i != 0; i--)
	{
		for (int j = 13; j != 0; j--)
		{
			ellipse(503, 190, 0, 0, i, j);
		}
	}
	setcolor(GREEN);
	for (int i = 3; i != 0; i--)
	{
		circle(494, 185, i);
	}
	setcolor(GREEN);
	for (int i = 3; i != 0; i--)
	{
		circle(508, 184, i);
	}
	line(494, 194, 510, 192);
	line(502, 193, 508, 199);
	int wwe = 565;
	for (int i = 0; i < 15; i++)
	{
		setcolor(LIGHTRED);
		arc(l++, 160, 90, 250, 20);
		arc(m++, 197, 260, 90, 20);
		arc(wwe++, 230, 90, 260, 20);
		ellipse(575, 140, 0, 0,20, 16);
		setfillstyle(SOLID_FILL, LIGHTRED);
		floodfill(574, 141, LIGHTRED);
	}
	
	setcolor(BLACK);
	for (int i = 3; i != 0; i--)
	{
		circle(568, 134, i);
	}
	setcolor(BLACK);
	for (int i = 3; i != 0; i--)
	{
		circle(580, 133, i);
	}
	arc(575, 137, 230, 340, 10);
	line(576, 146, 579, 152);

	setlinestyle(0,1,3);
	setcolor(LIGHTRED);
	line(163,220,193,220);
	line(163,200,194,200);
	line(164,180,194,180);
	line(165,160,194,160);
	line(166,140,194,140);
	line(167,120,196,120);
	line(169,100,196,100);
	setlinestyle(3,10,3);
    line(200,80,190,250);
    line(170,80,160,250);
	setlinestyle(0,1,3);
	setcolor(LIGHTRED);
	line(269,180,297,180);
	line(268,200,296,200);
	line(267,220,294,220);
	line(266,240,293,240);
	line(265,260,292,260);
	line(264,280,290,280);
	line(263,300,289,300);
	setlinestyle(3,10,3);
	line(300,150,290,320);
	line(270,150,260,320);
	setlinestyle(0,1,3);
	setcolor(LIGHTRED);
	line(467,265,497,265);
	line(466,280,496,280);
	line(465,295,495,295);
	line(464,310,491,310);
	setlinestyle(3,10,3);
	line(500,250,490,320);
	line(470,250,460,320);
	setlinestyle(0,1,3);
	setcolor(LIGHTRED);
	line(466,100,495,100);
	line(464,120,493,120);
	setlinestyle(3,10,3);
	line(500,80,490,140);
	line(470,80,460,140);	

	setlinestyle(0,10,1);

}
