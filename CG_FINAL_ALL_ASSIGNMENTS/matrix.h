#include<iomanip>
#define _USE_MATH_DEFINES
#include<math.h>
#ifndef __MATRIX__
#define __MATRIX__
class Matrix
{
	int row;
	int col;
	void memAlloc();
public:
	double **mat;
	//ctor
	Matrix()
	{
		row = col = -1;
	}
	Matrix(int r,int c)
	{
		if (r < 1 || c < 1)//defence
		{
			std::cout << "INVALID MARIX";
			throw 3;
		}

		row = r;
		col = c;
		memAlloc();
	}

	//methods
	void Show();
	int GetRow() { return row; }
	int GetCol() { return col; }
	Matrix operator*(const Matrix&);

	//static methods
	static Matrix Translation2D(int,int);
	static Matrix Rotation2D(double);
	static Matrix Shear2D(double,double);
	static Matrix Scale2D(double,double);
};

//----------------------------------------------
void Matrix::memAlloc()							//_____memAlloc_____
{
	mat = new double*[row];
	for (int i = 0; i < row; i++)
		mat[i] = new double[col];

	//clear allocation
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			mat[i][j] = 0;
}

Matrix Matrix::operator*(const Matrix &b)		//------MULTIPLY-----
{
	if (col != b.row)
	{
		std::cout << "MATRICES CANNOT BE MULTIPLIED";
		throw 2;
	}
	Matrix temp(row,b.col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < b.col; j++)
			for (int k = 0; k < col; k++)
				temp.mat[i][j] += mat[i][k] * b.mat[k][j];

	return temp;
}

Matrix Matrix::Translation2D(int tx,int ty)					//-----TRANSLATION_2D------
{
	Matrix temp(3, 3);
	for (int i = 0; i < 3; i++)
		temp.mat[i][i] = 1;

	temp.mat[2][0] = tx;
	temp.mat[2][1] = ty;
	return temp;
}

Matrix Matrix::Rotation2D(double angle)					//-----ROTATION_2D-----
{
	double rad = ((double)M_PI / 180)*angle;
	Matrix temp(3,3);

	temp.mat[0][0] = temp.mat[1][1] = cos(rad);
	temp.mat[0][1] = -sin(rad);
	temp.mat[1][0] = sin(rad);
	temp.mat[2][2] = 1;

	return temp;
}

Matrix Matrix::Shear2D(double x_shear, double y_shear)		//-----SHEAR_2D-----
{
	Matrix temp(3,3);
	
	for (int i = 0; i < 3; i++)
		temp.mat[i][i] = 1;

	temp.mat[1][0] = x_shear;
	temp.mat[0][1] = y_shear;

	return temp;
}

Matrix Matrix::Scale2D(double s_x,double s_y)										//-----SCALE_2D-----
{
	Matrix temp(3,3);
	
	temp.mat[0][0] = s_x;
	temp.mat[1][1] = s_y;
	temp.mat[2][2] = 1;

	return temp;
}

//for debugging purposes
void Matrix::Show()								//-----SHOW-----
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			std::cout << std::left << std::setw(3) << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

#endif // !__MATRIX__

