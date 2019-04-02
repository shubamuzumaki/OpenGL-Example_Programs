#pragma once
#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#define _USE_MATH_DEFINES
#include<math.h>
using namespace std;
int width = 500;
int height = 500;

void Delay(int x)
{
	while(--x)
	{
		cout << ".";
	}
}

void DDALine(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	int step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);//max of abs(dx),abs(dy)
	double xinc = dx / step;
	double yinc = dy / step;

	double x = x1;
	double y = y1;

	while (step--)
	{
	glBegin(GL_POINTS);
		glVertex2d(x, y);
	glEnd();
	glFlush();
	Delay(200);
		x += xinc;
		y += yinc;
	}
}



void _khelper(double x1, double y1, double x2, double y2, int itr)
{

	//calculate point p1 2:1		;section formula
	float p1y = (2 * y1 + y2) / 3;
	float p1x = (2 * x1 + x2) / 3;

	//calculate point p2 1:2		;section formula
	float p2x = (x1 + 2 * x2) / 3;
	float p2y = (y1 + 2 * y2) / 3;

	//find the top point _/\_	//explanation is at the end for this equation
	double rad = (M_PI / (double)180) * -60;
	double x =  p2x * cos(rad) + p2y * sin(rad) - p1x * cos(rad) - p1y * sin(rad) + p1x;
	double y = -p2x * sin(rad) + p2y * cos(rad) + p1x * sin(rad) - p1y * cos(rad) + p1y;

	if (itr - 1 == 0)//draw pattern
	{
		glVertex2f(x1, y1);		 //  
		glVertex2f(p1x, p1y);	 //  _ 
		glVertex2f(x, y);        //  _/                                   ;
		glVertex2f(p2x, p2y);	 //  _/\ 
		glVertex2f(x2, y2);      // _/\_ 

		//for visual purposes
		//DDALine(x1, y1, p1x, p1y);	// _
		//DDALine(p1x, p1y, x, y);	//  /
		//DDALine(x, y, p2x, p2y);	//   \ 
		//DDALine(p2x, p2y, x2, y2);  //    _

	}
	else//go deeper
	{
		_khelper(x1, y1, p1x, p1y, itr - 1);	// _
		_khelper(p1x, p1y, x, y, itr - 1);	//  /
		_khelper(x, y, p2x, p2y, itr - 1);	//   \ 
		_khelper(p2x, p2y, x2, y2, itr - 1);  //    _
	}
}

void KochCurve(double x1, double y1, double x2, double y2, int itr)
{
	glBegin(GL_LINE_STRIP);
	_khelper(x1, y1, x2, y2, itr);
	glEnd();
}

void Disp() {}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	//create Window
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("KOCH CURVES");

	//create viewport
	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	gluOrtho2D(0, width, 0, height);

	//clear screen
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	//set gl color
	glColor3f(1, 1, 1);

	glutDisplayFunc(Disp);

	//starting point and end point of line & no. of itr
	KochCurve(10, 250, 480, 250, 13);
	glFlush();	//don't miss it


	glutMainLoop();
	return 0;
}



//EXPLANATION:
//we need to rotate p2 w.r.t p1 at an angle 60(counterclockwise)
//we first translate p1 to origin
//perform rotation
//perform inverse translation on point p1
//multiply matrices to get that equation