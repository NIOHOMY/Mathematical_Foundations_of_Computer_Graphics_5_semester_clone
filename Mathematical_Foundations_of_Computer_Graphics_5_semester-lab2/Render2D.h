#pragma once
#include "Model2D.h"
#include <wtypes.h>

class Render2D
{
public:
	Render2D() = default;
	~Render2D();

	void draw(const HDC& hdc);
	void addObject(Model2D* model);

private:
	std::vector<Model2D*> m_objects;
};
