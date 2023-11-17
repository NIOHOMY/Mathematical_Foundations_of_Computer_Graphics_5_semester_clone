#pragma once
#include "Render2D.h"
#include <Windows.h>
#include <windowsx.h>

Render2D::~Render2D()
{
	for (const auto& object : m_objects)
		if (object)
			delete object;
}

void Render2D::draw(const HDC& hdc)
{
	for (const auto& object : m_objects)
		if (object)
			object->draw(hdc);
}

void Render2D::addObject(Model2D* model)
{
	m_objects.push_back(model);
}
