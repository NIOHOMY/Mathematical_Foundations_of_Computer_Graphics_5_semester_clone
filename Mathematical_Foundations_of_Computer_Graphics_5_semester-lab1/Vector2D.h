#pragma once

class Vector2D
{
public:
	Vector2D() = default;
	Vector2D(const double &x, const double &y);

	void setX(const double& x);
	void setY(const double& y);

	double x() const;
	double y() const;

private:
	double m_x = 0.0;
	double m_y = 0.0;
};

