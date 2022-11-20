/*
*
*       Author: Ahmet KARACALI
*   Student ID: 160101015
*      Subject: CEN110 Project 4 - Mancala Game on OpenGL
*
*
*/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <windows.h>

int window;
int mainStack=0;
int levelStack=0,islevel=0;
int mainmenu=1;
int helpmenu=0;
const int font = (int)GLUT_BITMAP_HELVETICA_18;

void whenGameOver(void);
void cupsShow(void);
void compMove(void);

int winner=0;
int singleplayer=0;

int cups[2][14];
char showcups[2][14];

int selection=13;
int selection2=1;
int turn=1;

int isPlaying=0;
int ynStack=0,yesOrNo=0;
int isPause=0,pauseStack=0;;
int gameOver=0;
int gameOverStack=0;


void sel_polygon(int xx1, int xx2, int yy1, int yy2)
{
	glColor3f(1.0,0.689,0.0);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(xx1,yy1);
		glVertex2f(xx2,yy1);
		glVertex2f(xx2,yy2);
		glVertex2f(xx1,yy2);
	}
	glEnd();
	glFlush();
}
void renderBitmapString(float x, float y, void *font, const char *string)
{
       const char *c;
       glRasterPos2f(x, y);
       for (c = string; *c != '\0'; c++) {
              glutBitmapCharacter(font, *c);
       }
}

int checkGameOver()
{
    int isOver=1,isOver2=1;
    int i;

    for(i=1;i<7;i++)
    {
        if(cups[0][i]!=0) isOver=0;
    }

    for(i=8;i<14;i++)
    {
        if(cups[0][i]!=0) isOver2=0;
    }

    if(cups[0][0]+cups[0][7]==48) {
            isOver=1;
    }

    if(isOver==1 || isOver2==1) { gameOver=1; isPlaying=0; whenGameOver(); }
}

void whenGameOver()
{
    int scoreP1=0,scoreP2=0;

    for(int i=13;i>7;i--)
    {
        cups[0][7]+=cups[0][i];
        cups[0][i]=0;
    }

    for(int i=1;i<7;i++)
    {
        cups[0][0]+=cups[0][i];
        cups[0][i]=0;
    }
    cupsShow();

    scoreP1= cups[0][7];
    scoreP2= cups[0][0];

    if(scoreP1==scoreP2) winner=0;
    else if(scoreP1>scoreP2) winner=1;
    else if(scoreP1<scoreP2) winner=2;
}

void initGame()
{
    gameOver=0;
    winner=0;

    selection=13;
    selection2=1;
    turn=1;

        for(int j=1;j<14;j++)
        {
            cups[0][j]=4;
        }
        for(int i=1;i<8;i++)
        {
            cups[0][0]=0;
            cups[0][7]=0;
        }
        cupsShow();
}

void DisplayScreen()
{
   glClearColor(0.0, 0.663, 0.663, 0.663);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.545, 0.000, 0.000);
   glRectf (5,50,15,30); // Player 2's mancala.
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(9.0f, 40.0f,0.0f);
   for(int i=0;i<2;i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][0]);
   }
   glColor3f(0.545, 0.000, 0.000);

   glRectf (65,50,75,30); // Plater 1's mancala.
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(69.0f, 40.0f,0.0f);
   for(int i=0;i<2;i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][7]);
   }
   glColor3f(0.545, 0.000, 0.000);
   glRectf (17,50,22,41); // Cups Num1 From left
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(18.0f, 45.0f,0.0f);
   for(int i=0;i<2;i++)
   {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][1]);
   }

   glColor3f(0.545, 0.000, 0.000);
   glRectf (17,39,22,30);
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(18.0f, 34.0f,0.0f);
      for(int i=0;i<2;i++)
   {
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][13]);
   }
   glColor3f(0.545, 0.000, 0.000);

   glRectf (25,50,30,41); // Cups Num2 From left
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(26.0f, 45.0f,0.0f);
   for(int i=0;i<2;i++)
   {
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][2]);
   }
   glColor3f(0.545, 0.000, 0.000);
   glRectf (25,39,30,30);
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(26.0f, 34.0f,0.0f);
   for(int i=0;i<2;i++)
   {
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][12]);
   }
   glColor3f(0.545, 0.000, 0.000);

   glRectf (33,50,38,41); // Cups Num3 From left
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(34.0f, 45.0f,0.0f);
   for(int i=0;i<2;i++)
   {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][3]);
   }
   glColor3f(0.545, 0.000, 0.000);
   glRectf (33,39,38,30);
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(34.0f, 34.0f,0.0f);
   for(int i=0;i<2;i++)
   {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][11]);
   }
   glColor3f(0.545, 0.000, 0.000);

   glRectf (41,50,46,41); // Cups Num4 From left
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(42.0f, 45.0f,0.0f);
   for(int i=0;i<2;i++)
   {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][4]);
   }
   glColor3f(0.545, 0.000, 0.000);
   glRectf (41,39,46,30);
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(42.0f, 34.0f,0.0f);
   for(int i=0;i<2;i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][10]);
   }
   glColor3f(0.545, 0.000, 0.000);

   glRectf (49,50,54,41); // Cups Num5 From left
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(50.0f, 45.0f,0.0f);
   for(int i=0;i<2;i++)
   {
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][5]);
   }
   glColor3f(0.545, 0.000, 0.000);
   glRectf (49,39,54,30);
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(50.0f, 34.0f,0.0f);
   for(int i=0;i<2;i++)
   {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][9]);
   }
   glColor3f(0.545, 0.000, 0.000);

   glRectf (57,50,62,41); // Cups Num6 From left
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(58.0f, 45.0f,0.0f);
   for(int i=0;i<2;i++)
   {
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][6]);
   }
   glColor3f(0.545, 0.000, 0.000);
   glRectf (57,39,62,30);
   glColor3f(1.0, 1.000, 1.000);
   glRasterPos3f(58.0f, 34.0f,0.0f);
   for(int i=0;i<2;i++)
   {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,showcups[i][8]);
   }
   glColor3f(0.545, 0.000, 0.000);


   if(turn==1)
   {
       if(selection==13) sel_polygon(17,22,39,30);
       if(selection==12) sel_polygon(25,30,39,30);
       if(selection==11) sel_polygon(33,38,39,30);
       if(selection==10) sel_polygon(41,46,39,30);
       if(selection==9) sel_polygon(49,54,39,30);
       if(selection==8) sel_polygon(57,62,39,30);
   }
      if(turn==2)
   {
       if(selection2==1) sel_polygon(17,22,50,41);
       if(selection2==2) sel_polygon(25,30,50,41);
       if(selection2==3) sel_polygon(33,38,50,41);
       if(selection2==4) sel_polygon(41,46,50,41);
       if(selection2==5) sel_polygon(49,54,50,41);
       if(selection2==6) sel_polygon(57,62,50,41);
   }


   renderBitmapString(30.0f, 66.0f, (void *)font, "Mancala Game");
   glColor3f(0.045, 0.400, 0.050);
   renderBitmapString(64.0f, 27.0f, (void *)font, "Player 1");
   if(singleplayer==0) renderBitmapString(3.0f, 52.0f, (void *)font, "Player 2");
   else if(singleplayer==1) renderBitmapString(3.0f, 52.0f, (void *)font, "Computer");

   if(turn==1)
   {
   glColor3f(1.045, 1.400, 1.050);
   renderBitmapString(61.0f, 27.0f, (void *)font, "->          ");
   }
   else if(turn==2)
   {

       glColor3f(1.045, 1.400, 1.050);
       renderBitmapString(3.0f, 52.0f, (void *)font, "              <-");
   }

   glFlush();
   glutSwapBuffers();

}


int dropPebbles()
{
    int pebble=0;
    int allcups=13;
    int current=selection-1;
    int lose=0;

    if(turn==1)
    {
    pebble=cups[0][selection];

        cups[0][selection]=0;

    for(;pebble!=0;pebble--)
    {
      cups[0][current]+=1;

     current=current-1;

     if(current==-1) current=13;
     }


    if(pebble==0)
    {
        if(cups[0][current+1]==1)
        {
            if(current+1!=7)
            {
            cups[0][current+1]=0;
            switch(current+1)
            {
        case 8: { lose=cups[0][6]+1;
                      cups[0][6]=0;
                      }
                break;
        case 9: { lose=cups[0][5]+1;
                      cups[0][5]=0;
                      }
                break;
        case 10: { lose=cups[0][4]+1;
                      cups[0][4]=0;
                      }
                break;
       case 11: { lose=cups[0][3]+1;
                      cups[0][3]=0;
                      }
                break;
        case 12: { lose=cups[0][2]+1;
                      cups[0][2]=0;
                      }
                break;
       case 13: { lose=cups[0][1]+1;
                      cups[0][1]=0;
                      }
                break;
            }

        for(int i=0;i<lose;i++)
        {
          cups[0][7]+=1;
        }
    }
        }
    if(current!=6) turn=2;
    }
        }


    else if(turn==2)
    {
        current=selection2-1;
        pebble=cups[0][selection2];
        cups[0][selection2]=0;
    for(;pebble!=0;pebble--)
    {
        cups[0][current]+=1;
        current=current-1;

        if(current==-1) current=13;
    }

    if(pebble==0)
    {
        if(cups[0][current+1]==1)
        {
            if(current+1!=7)
            {
            cups[0][current+1]=0;
            switch(current+1)
            {

        case 1: { lose=cups[0][13]+1;
                      cups[0][13]=0;
                      }
                break;
            case 2: { lose=cups[0][12]+1;
                      cups[0][12]=0;
                      }
                break;
            case 3: { lose=cups[0][11]+1;
                      cups[0][11]=0;
                      }
                break;
            case 4: { lose=cups[0][10]+1;
                      cups[0][10]=0;
                      }
                break;
            case 5: { lose=cups[0][9]+1;
                      cups[0][9]=0;
                      }
                break;
            case 6: { lose=cups[0][8]+1;
                      cups[0][8]=0;
                      }
                break;
            }

        for(int i=0;i<lose;i++)
        {
          cups[0][0]+=1;
        }
        }
    }
    if(current!=13) turn=1;
    }
    }
    cupsShow();
}

void compMove()
{
    int valid=0;
    srand(time(NULL));
    validation: selection2=rand()%6+1;

    if(cups[0][selection2]==0) goto validation;

}

void cupsShow()
{
        for(int j=0;j<14;j++)
        {
            if(cups[0][j]<10)
            {
              showcups[0][j]='0';
              showcups[1][j]=cups[0][j]+48;
            }
            else
            {
                showcups[0][j]=((cups[0][j]/10)+48);
                showcups[1][j]=((cups[0][j]%10)+48);
            }

        }
}

void inGameKeyboard(unsigned char Key, int x, int y)
{
switch (Key) {
       case 'a': {
             if(turn==1) if (selection<13) selection++;
             if(turn==2) if (selection2>1) selection2--;
          break;
       }
       case 'd': {
             if(turn==1) if(selection>8) selection--;
             if(turn==2)  if (selection2<6) selection2++;

          break;
       }
       case 13: {
           if(turn==1 && cups[0][selection]!=0)
           {
             dropPebbles();
             cupsShow();
           }
           else if(turn==2 && cups[0][selection2]!=0)
           {
             dropPebbles();
             cupsShow();
           }
           break;
          }

       case 27: {
           if(isPlaying==1)
           {
               isPlaying=0;
               isPause=1;
           }
          else yesOrNo=1;
          break;
    };
}
}

/////////////////////////////////////////////////////////////////////////////////////////////////



void printText()
{
   glClearColor(0.0, 0.000, 0.00, 0.196078);
   glClear(GL_COLOR_BUFFER_BIT);

   if(gameOver!=1 && helpmenu!=1)
   {

   glColor3f(1.000, 0.500, 0.000);
    renderBitmapString(22.0f, 70.0f, (void *)font, "--- Mancala Game ---");

    glColor3f(0.85, 0.85, 0.100);
    renderBitmapString(28.0f, 10.0f, (void *)font, "Ahmet Karacali");

   }
   if(mainmenu==1)
   {
       if(mainStack==0)
{
    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 50.0f, (void *)font, "New Game");
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 45.0f, (void *)font, "Help");
    renderBitmapString(30.0f, 40.0f, (void *)font, "Quit");
}
if(mainStack==1)
{
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, (void *)font, "New Game");

    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 45.0f, (void *)font, "Help");
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 40.0f, (void *)font, "Quit");
}
if(mainStack==2)
{
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, (void *)font, "New Game");
    renderBitmapString(30.0f, 45.0f, (void *)font, "Help");
    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 40.0f, (void *)font, "Quit");
}

}

 else if(helpmenu==1)
   {
           glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, (void *)font, "HELP MENU");

    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(7.0f, 40.0f, (void *)font, "You can use W,A,S,D for select the lane and menu.");
    renderBitmapString(8.0f, 35.0f, (void *)font, "Press ENTER for execute and press ESC to exit...");
    glColor3f(1.545, 1.000, 0.000);
    renderBitmapString(10.0f, 10.0f, (void *)font, "Please wait 3 seconds,i will return main menu...");

    glFlush();
   glutSwapBuffers();
    helpmenu=0;
    usleep(999999);
    usleep(999999);
    mainmenu=1;
   }
   else if(islevel==1)
    {

        if(levelStack==0)
{
    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 50.0f, (void *)font, "Singleplayer");
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 45.0f, (void *)font, "Multiplayer");

}
    if(levelStack==1)
{
    glColor3f(1.0, 1.00, 1.000);
    renderBitmapString(30.0f, 50.0f, (void *)font, "Singleplayer");

    glColor3f(0.545, 1.000, 0.000);
    renderBitmapString(30.0f, 45.0f, (void *)font, "Multiplayer");



}
    }
    else if (isPause==1)
    {
        if(pauseStack==0)
        {
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 45.0f, (void *)font, "Resume Game");
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 40.0f, (void *)font, "Quit Game");
        }
        if(pauseStack==1)
        {
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 45.0f, (void *)font, "Resume Game");
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 40.0f, (void *)font, "Quit Game");
        }
    }
    if(yesOrNo==1)
    {
        if(ynStack==0)
        {
            glColor3f(1.0, 0.000, 0.000);
            renderBitmapString(50.0f, 45.0f, (void *)font, "Yes");
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(50.0f, 40.0f, (void *)font, "No");
        }
        if(ynStack==1)
        {
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(50.0f, 45.0f, (void *)font, "Yes");
            glColor3f(1.0, 0.000, 0.000);
            renderBitmapString(50.0f, 40.0f, (void *)font, "No");
        }
    }
    else if(gameOver==1)
    {
    //
    glColor3f(1.000, 0.000, 0.000);
            if(winner==1)
        {
            renderBitmapString(30.0f, 65.0f, (void *)font, "Player 1 WINS!");
        }
    else if(winner==2)
        {
            if(singleplayer==1)renderBitmapString(30.0f, 65.0f, (void *)font, "Computer WINS!");
            else if(singleplayer==0)renderBitmapString(30.0f, 65.0f, (void *)font, "Player 2 WINS!");

        }
    else if(winner==0)
        {
            renderBitmapString(30.0f, 60.0f, (void *)font, "GAME DRAW!");
        }
        glColor3f(0.000, 0.000, 1.000);

    //


        if(gameOverStack==0)
        {
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 45.0f, (void *)font, "Restart Game");
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 40.0f, (void *)font, "Quit Game");
        }
        if(gameOverStack==1)
        {
            glColor3f(1.0, 1.00, 1.000);
            renderBitmapString(30.0f, 45.0f, (void *)font, "Restart Game");
            glColor3f(0.545, 1.000, 0.000);
            renderBitmapString(30.0f, 40.0f, (void *)font, "Quit Game");
        }
    }
   glFlush();
   glutSwapBuffers();

}
void ScreenResizer(GLsizei w, GLsizei h)
{
   if (h == 0) h = 1;
   glViewport(0, 0, w, h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0f, 80.f, 0.0f, 80.f, -1.0, 1.0);
   glFlush();
}

void installGame()
{
    initGame();
    glutDisplayFunc(DisplayScreen);
    glutReshapeFunc(ScreenResizer);
}
void resumeGame()
{
    glutDisplayFunc(DisplayScreen);
    glutReshapeFunc(ScreenResizer);
}
void MyNewKeyboardFunc(unsigned char Key, int x, int y)
{
switch (Key) {
       case 'w': {
          if(mainmenu==1 && yesOrNo!=1){if (mainStack>0) {  mainStack--; } }
          else if (islevel==1) { if (levelStack>0) { levelStack--;} }
          else if(isPause==1 && yesOrNo==0) { if(pauseStack>0) {pauseStack--;} }
          else if(isPause==1 && yesOrNo==1) { if(ynStack>0) {ynStack--;} }
          else if(yesOrNo==1)  { if(ynStack>0) {ynStack--;} }
          else if(gameOver==1 && yesOrNo==0) { if(gameOverStack>0) {gameOverStack--;} }
          break;
       }
       case 's': {
          if(mainmenu==1 && yesOrNo!=1) { if (mainStack<2) { mainStack++;   }   }
          else if(islevel==1) { if (levelStack<1) { levelStack++;} }
          else if(isPause==1 && yesOrNo==0) { if(pauseStack<1) {pauseStack++;} }
          else if(isPause==1 && yesOrNo==1) { if(ynStack<1) {ynStack++;} }
          else if(yesOrNo==1) { if(ynStack<1) {ynStack++;}}
          else if(gameOver==1 && yesOrNo==0) { if(gameOverStack<1) {gameOverStack++;} }
          break;
       }
       case 13: {
           if(mainmenu==1 && yesOrNo!=1)
           {
          if (mainStack==0) { mainmenu=0; islevel=1;}
          if (mainStack==1) { mainmenu=0; helpmenu=1; }
          if (mainStack==2) { ynStack=0; yesOrNo=1; }
           }
           else if(islevel==1)
           {
             if (levelStack==0) { singleplayer=1; islevel=0; isPlaying=1; installGame();}
             if (levelStack==1) { singleplayer=0; islevel=0; isPlaying=1; installGame();}
           }
           else if(isPause==1 && yesOrNo==0)
           {
                if(pauseStack==0) { isPause=0; yesOrNo=0; isPlaying=1; resumeGame();}
                if(pauseStack==1) {yesOrNo=1; }
           }
           else if(isPause==1 && yesOrNo==1)
           {
               if(ynStack==0) { yesOrNo=0; isPause=0; mainmenu=1; }
               else if(ynStack==1) { yesOrNo=0; isPause=1;}
           }
           else if(mainmenu==1 && yesOrNo==1)
           {
               if(ynStack==0) exit(0);
               else if(ynStack==1) { yesOrNo=0; }
           }
           else if(gameOver==1)
           {
               if(gameOverStack==0) { yesOrNo=0; gameOver=0; isPlaying=1; installGame(); }
               else if(gameOverStack==1) { yesOrNo=0; exit(0);}
           }

          break;
       }
       case 27: {
           if(isPlaying==1)
           {
               isPlaying=0;
               isPause=1;
                glutDisplayFunc(printText);
                glutReshapeFunc(ScreenResizer);
                glutKeyboardFunc(MyNewKeyboardFunc);
           }
          else yesOrNo=1;
          break;
       }
    };
}


void loopMain()
{
    int a;

    if(isPlaying!=1)
    {
        glutDisplayFunc(printText);
        glutReshapeFunc(ScreenResizer);
        glutKeyboardFunc(MyNewKeyboardFunc);
    }
    else
    {
        glutDisplayFunc(DisplayScreen);
        glutReshapeFunc(ScreenResizer);
        glutKeyboardFunc(inGameKeyboard);

        if(singleplayer==1)
        {
            if(turn==2) { compMove(); dropPebbles(); usleep(800000); cupsShow();}
        }
        checkGameOver();
    }

    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    window = glutCreateWindow("Mancala Game OpenGL");
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(printText);
    glutReshapeFunc(ScreenResizer);
    glutIdleFunc(loopMain);
    glutMainLoop();
    return EXIT_SUCCESS;
}
