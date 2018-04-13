#include "Matrix.h"

Matrix::Matrix()
{
	//MakeIdentity();
	Transpose();
}

void Matrix::MakeIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] = (i == j) ? 1 : 0;
		}
	}
}

void Matrix::Transpose()
{
	float ans[4][4];


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ans[i][j] = arr[j][i];
		}
	}


	//arr = ans;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] = ans[i][j];
		}
	}

}

