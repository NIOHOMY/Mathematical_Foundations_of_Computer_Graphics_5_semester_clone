#pragma once
#include <vector>
#include <Windows.h>
#include <windowsx.h>
#include "Vector2D.h"
#include "Matrix.h"

class Model2D
{
public:
	Model2D() = default;
	Model2D(const std::vector<Vector2D> &vertices, const std::vector<int> indices);

	void draw(const HDC& hdc);

private:
	std::vector<Vector2D> m_vertices;
	std::vector<int> m_indices;

	Matrix<> m_modelMatrix;
};
