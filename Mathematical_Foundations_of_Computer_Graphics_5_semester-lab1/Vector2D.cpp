#pragma once
#include "Vector2D.h"

Vector2D::Vector2D(const double& x, const double& y) :
    m_x(x),
    m_y(y)
{
}

void Vector2D::setX(const double& x)
{
    m_x = x;
}

void Vector2D::setY(const double& y)
{
    m_y = y;
}

double Vector2D::x() const
{
    return m_x;
}

double Vector2D::y() const
{
    return m_y;
}
