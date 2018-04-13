#pragma once

class Matrix {
public:
	Matrix();

	void MakeIdentity();

	void Transpose();


public:
	float arr[4][4] = { 0, 1, 2, 3,4,5,6,7,8,9,10,11,12,13,14,15};

};
