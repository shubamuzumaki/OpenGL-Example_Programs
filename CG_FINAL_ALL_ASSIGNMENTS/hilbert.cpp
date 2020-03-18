#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#include<time.h>
#include<random>
#include<math.h>
#include<stdlib.h>

using namespace std;
int width = 700;
int height = 700;
bool complete = false;
bool isDrawn = true;
//hil var
float X, Y, _size;
int ITR = 1;

int modr = 250;
int modg = 250;
int modb = 250;



void Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

}

void ColorChanger()
{
	unsigned char r = rand() % modr;
	unsigned char g = rand() % modg;
	unsigned char b = rand() % modb;
	glColor3ub(r, g, b);
}


void _hilHelper(float x, float y, float xi, float xj, float yi, float yj, int itr)
{
	if (itr == 0)
	{
		float x1 = x + (xi + yi) / 2;
		float y1 = y + (xj + yj) / 2;
		ColorChanger();
		glVertex2d(x1, y1);
	}
	else
	{
		_hilHelper(x                   , y                   ,  yi / 2 ,  yj / 2 ,  xi / 2 ,  xj / 2 , itr - 1);
		_hilHelper(x + xi / 2          , y + xj / 2          ,  xi / 2 ,  xj / 2 ,  yi / 2 ,  yj / 2 , itr - 1);
		_hilHelper(x + xi / 2 + yi / 2 , y + xj / 2 + yj / 2 ,  xi / 2 ,  xj / 2 ,  yi / 2 ,  yj / 2 , itr - 1);
		_hilHelper(x + xi / 2 + yi     , y + xj / 2 + yj     , -yi / 2 , -yj / 2 , -xi / 2 , -xj / 2 , itr - 1);
	}

}

void Hilbert(float x, float y, float size, int itr)
{
	glBegin(GL_LINE_STRIP);
	_hilHelper(x, y,size,0, 0 ,size, itr);
	glEnd();
	glutSwapBuffers();
}

void disp() {}
void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP) return;
	y = -y + height;


	if (button == 0)//LEFT CLICK	
	{
		if (!complete)
		{
			X = x;
			Y = y;
			complete = true;
		}
		else if (isDrawn)
		{
			//draw hilbert
			float dy = abs(y - Y);
			float dx = abs(x - X);
			_size = dx > dy ? dx : dy;

			Hilbert(X, Y, _size, ITR);
			isDrawn = false;
		}
	}
	else if (button == 1)//middle button
	{
		Clear();
		complete = false;
		isDrawn = true;

	}
	else if (!isDrawn && button == 3 && ITR < 10)
	{
		Clear();
		Hilbert(X, Y, _size, ++ITR);
	}
	else if (!isDrawn && button == 4 && ITR > 1)
	{
		Clear();
		Hilbert(X, Y, _size, --ITR);
	}
}

void Keyboard(unsigned char key, int, int)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'd':
		Clear();
		complete = false;
		isDrawn = true;
		break;
	case 'r':
		Clear();
		Hilbert(X, Y, _size, ITR);
		break;
	}
}

void initCallBacks()
{
	glutDisplayFunc(disp);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	
}


void menu(int ch)
{
	switch (ch)
	{
	case 1://reddish
		modr = 250;
		modg = 100;
		modb = 100;
		Clear();
		Hilbert(X, Y, _size, ITR);
		break;
	case 2://blusih
		modr = 100;
		modg = 100;
		modb = 255;
		Clear();
		Hilbert(X, Y, _size, ITR);
		break;
	case 3://greenish
		modr = 100;
		modg = 255;
		modb = 100;
		Clear();
		Hilbert(X, Y, _size, ITR);
		break;
	case 4://neutral
		modr = 255;
		modg = 255;
		modb = 255;
		Clear();
		Hilbert(X, Y, _size, ITR);
		break;
	case 5://clear
		Clear();
		complete = false;
		isDrawn = true;
		break;
	case 6://exit
		exit(0);
		break;
	}
}

void tst(int ch)
{
	if (ch == 1)
		cout << "red sangu" << endl;
	if (ch == 2)
		cout << "ge sharma" << endl;
}

void MyMenu()
{
	int subId=glutCreateMenu(tst);
	glutAddMenuEntry("RED",1);
	glutAddMenuEntry("GREEN",2);


	glutCreateMenu(menu);
	glutAddSubMenu("MOTU",subId);
	glutAddMenuEntry("REDDISH", 1);
	glutAddMenuEntry("BLUSIH", 2);
	glutAddMenuEntry("GREENISH", 3);
	glutAddMenuEntry("NEUTRAL", 4);
	glutAddMenuEntry("CLEAR", 5);
	glutAddMenuEntry("EXIT", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void Help()
{
	system("clear");
	cout << "\tFirst Click  = Base Point of Curve" << endl;
	cout << "\tSecond Click = Size of curve" << endl;
	cout << "\tScroll Up    = Increase Iterations(max=10)" << endl;
	cout << "\tScrool Down  = Decrease Iterations(min=1)" << endl;
	cout << "\tRight Click  = Menu" << endl;
	cout << "\t!!!  ENJOY !!!" << endl;

}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	//create window
	glutInitWindowPosition(200, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("HILBERT");

	//init
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, width, 0, height);

	//clear screen
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	srand(time(NULL));

	initCallBacks();

	MyMenu();

	Help();
	glutMainLoop();

}



//MADE BY : SHARMA
//THANKS FOR WATCHING