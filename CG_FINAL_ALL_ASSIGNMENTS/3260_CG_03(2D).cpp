#include "pch.h"
#include<gl/freeglut.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include "matrix.h"
#include "shape.h"

using namespace std;

//global variables
int width = 600;
int height = 600;
PolyGon *poly = NULL;

//glut
void init2D();
void Clear();

//APPLICATION
void Help();
void Menu();
void EnterPoly();
void TransLate();
void Rotate();
void Scale();
void Shear();

//-------------------------------------
//			__GLUT__
//-------------------------------------

void init2D()								//-----init2D-----
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, width, 0, height);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 1);
}

void Clear()								//-----CLEAR-----
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 1);
}

//-------------------------------------
//			__MAIN__
//-------------------------------------

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutCreateWindow("ASSIGNMENT_1");
	
	init2D();

	
	Menu();
	return 0;
}

//-------------------------------------
//			__APPLICATION__
//-------------------------------------

void Menu()										//-----MENU-----
{
	int ch;
	do
	{
		Help();
		cin >> ch;
		switch (ch)
		{
		case 1:
			EnterPoly();
			break;
		case 2:
			TransLate();
			break;
		case 3:
			Rotate();
			break;
		case 4:
			Shear();
			break;
		case 5:
			Scale();
			break;
		}
		glFlush();
	} while (ch!=6);
}

void TransLate()								//------TRANSLATE-----
{
	glColor3ub(240,120,30);
	if (poly == NULL)  return;

	int t_x, t_y;
	cout << "Enter T_x: "; cin >> t_x;
	cout << "Enter T_y: "; cin >> t_y;
	
	Matrix Original = poly->GetMatrix();//Get (sides x 3) polygon matrix
	Matrix trans = Original * Matrix::Translation2D(t_x,t_y);//make a translated marix

	PolyGon translatedFigure(trans);//passing sides x 3 matrix to initialize polygon
	
	translatedFigure.Draw();
}

void Rotate()										//-----ROTATE-----
{
	glColor3ub(197,65,125);
	if (poly == NULL) return;

	int angle;
	int x, y;
	cout << "Enter Angle: "; cin >> angle;
	cout << "Enter Point(x,y): "; cin >> x >> y;

	Matrix Original = poly->GetMatrix();//return the coordinate of polygon in matrix form
	Matrix Rotated = Original * Matrix::Translation2D(-x, -y) * Matrix::Rotation2D(angle) * Matrix::Translation2D(x, y);

	PolyGon rotatedFigure(Rotated);
	
	rotatedFigure.Draw();
}

void Shear()						//-----SHEAR-----
{
	glColor3ub(255, 255, 0);
	if (poly == NULL) return;

	double shear_x, shear_y;
	cout << "Enter Shear x: "; cin >> shear_x;
	cout << "Enter Shear y: "; cin >> shear_y;

	Matrix Original = poly->GetMatrix();//return the coordinate of polygon in matrix form
	Matrix Sheared = Original * Matrix::Shear2D(shear_x,shear_y);


	PolyGon shearedFigure(Sheared);

	shearedFigure.Draw();
}

void Scale()						//-----SCALE-----
{
	glColor3ub(255, 255, 0);
	if (poly == NULL) return;

	double s_x, s_y;
	int x, y;
	cin.get();
	cout << "Enter Scale x: "; cin >> s_x;
	cout << "Enter Scale y: "; cin >> s_y;
	cout << "Enter Point(x,y): "; cin >> x >> y;

	Matrix Original = poly->GetMatrix();//return the coordinate of polygon in matrix form
	Matrix Scaled = Original * Matrix::Translation2D(-x, -y)*Matrix::Scale2D(s_x, s_y)*Matrix::Translation2D(x,y);

	PolyGon scaledFigure(Scaled);
	
	scaledFigure.Draw();
}
void Help()										//-----HELP-----
{
	system("cls");
	//system("clear");
	cout << "*******************[ HELP ]******************* "<< endl;
	cout << "1. Enter Polygon"<<endl;
	cout << "2.TRANSLATE" << endl;
	cout << "3.ROTATE" << endl;
	cout << "4.SHEAR" << endl;
	cout << "5.SCALE" << endl;
	cout << "*********************************************** " << endl;
}

void EnterPoly()								//-----ENTER_POLY-----
{
	Clear();
	cout << "Enter Sides of PolyGon: " << endl;
	int s;
	cin >> s;

	while (s < 3)//defence
	{
		cout << "INVALID SIDES: " << endl;
		cout << "RE_ENTER :"; cin >> s;
	}

	poly = new PolyGon(s);
	for (int i = 0; i < s; i++)
	{
		int x, y;
		cout << "Enter CoOrdinates(x,y): ";
		cin >> x >> y;
		poly->Pushback(x, y);
	}

	poly->Draw();
}





//for (int i = 0; i < row; i++)
	//{
	//	translatedFigure.Pushback(trans.mat[i][0],trans.mat[i][1]);
	//}
