#pragma once
#include "Model2D.h"
#include <windef.h>
#include <wingdi.h>
#include <windowsx.h>

Model2D::Model2D(const std::vector<Vector2D>& vertices, const std::vector<int> indices) :
	m_vertices(vertices),
	m_indices(indices)
{
}

void Model2D::draw(const HDC& hdc)
{

}
