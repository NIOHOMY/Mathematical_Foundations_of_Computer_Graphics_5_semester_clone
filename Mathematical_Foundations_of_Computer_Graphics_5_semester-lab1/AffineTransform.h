#ifndef AFFINE_TRANSFORM_H
#define AFFINE_TRANSFORM_H
#include "Matrix.h"
#include <math.h>

Matrix<> Translation(double x, double y)
{
	double T[9] = {
		1, 0, x,
		0, 1, y,
		0, 0, 1 };
	return Matrix<>(3, 3, T);
}

Matrix<> Identity()
{
	double I[9] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 };
	return Matrix<>(3, 3, I);
}

Matrix<> Rotation(double angle)
{
    angle = angle * (3.14159265359 / 180.0);
    double cosA = std::cos(angle);
    double sinA = std::sin(angle);
    double R[9] = {
        cosA, -sinA, 0,
        sinA, cosA, 0,
        0, 0, 1,
    };
    return Matrix<>(3, 3, R);
}

Matrix<> Scaling(double scaleX, double scaleY)
{
    double S[9] = {
        scaleX, 0, 0,
        0, scaleY, 0,
        0, 0, 1
    };
    return Matrix<>(3, 3, S);
}

Matrix<> ReflectionX()
{
    double RX[9] = {
        1, 0, 0,
        0, -1, 0,
        0, 0, 1
    };
    return Matrix<>(3, 3, RX);
}

Matrix<> ReflectionY()
{
    double RY[9] = {
        -1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };
    return Matrix<>(3, 3, RY);
}


#endif AFFINE_TRANSFORM_H
