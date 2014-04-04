#pragma once
#include "../core.h"

NS_MPF
NS_VSL

//æÿ’Û
template<typename T>
struct Matrix
{
	Matrix()
	{
		std::memset(m, 0, sizeof(m));
	}

	Matrix(const Matrix<T>& matrix)
	{
		memcpy_s(m, sizeof(m), matrix.m, sizeof(matrix.m));
	}

	const Matrix<T>& operator=(const Matrix<T>& matrix)
	{
		memcpy_s(m, sizeof(m), matrix.m, sizeof(matrix.m));
		return *this;
	}

	static Matrix<T> MakeRotation(float x, float y)
	{
		Matrix<T> matrix;

		return matrix;
	}

	enum
	{

	};

	T m[2][2];
};

typedef Matrix<float> matrix_t;

NS_ED
NS_ED