#include <iostream>
#include <algorithm>

#include "DelaunayMachine.h"
#include "Utils.h"

#include <Windows.h>

DelaunayMachine::DelaunayMachine(std::shared_ptr<std::vector<Vector2>> pointset) : pointset{pointset} {}

void DelaunayMachine::delaunay_incremental_AFL()
{
    std::sort(pointset->begin(), pointset->end(),
	    [](const Vector2& a, const Vector2& b) -> bool { return a.x < b.x; });

	makeFirstSimplex();
}

int findClosest(std::shared_ptr<std::vector<Vector2>> arr, const Vector2& target)
{
	double min = DBL_MAX;	
	int index = 0;
	int midpoint = arr->size() / 2;

	for (int i = 0; i < arr->size(); ++i)	
	{
		if (i == midpoint) continue;

		double current = target.squareDistanceTo((*arr)[i]);
		if (current < min)
		{
			min = current;
			index = i;
		}			
	}
	return index;
}

void DelaunayMachine::makeFirstSimplex()
{
	//Utils::printPointset(pointset);

	//double alphaX = (*pointset)[pointset->size() / 2].x;
	//std::shared_ptr<Vector2> p1 = findFirstPoint(alphaX);

	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	const Vector2& midVector = (*pointset)[pointset->size() / 2];
	int indexOfClosest = findClosest(pointset, midVector);

	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	std::cout << "Elapsed us: " << ElapsedMicroseconds.QuadPart << std::endl;
	std::cout << "Elapsed ms: " << ElapsedMicroseconds.QuadPart / 1000 << std::endl;

	std::cout << "indexOfClosest: " << indexOfClosest << std::endl;
}

std::shared_ptr<Vector2> DelaunayMachine::findFirstPoint(double alfa)
{
	
}

// funkcja sprawdza czy punkty p oraz cp leza po tej samej stronie linii wyznaczanej przez wektor f
int DelaunayMachine::sameHalfspaceTest(const Edge& f, const Vector2& p, const Vector2& cp)
{
	Vector2 w(f.v2.y - f.v1.y, -(f.v2.x - f.v1.x));
	double result = w.dotProduct((p - f.v1)) * w.dotProduct((cp - f.v1));

	if (result < 0) // rozne strony
	{
		return -1;
	}
	else if (result > 0) // ta sama strona
	{
		return 1;
	}
	else // na linii
	{
		return 0;
	}
}

Vector2 DelaunayMachine::centerOfMass(const Vector2& a, const Vector2& b, const Vector2& c)
{
	return Vector2((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3);
}

// funkcja delaunay distance (dd) zdefiniowana w publikacji algorytmu DeWall
double DelaunayMachine::delaunayDistance(const Edge& f, const Vector2& p)
{
	Vector2 circumcenter = DelaunayMachine::circumCenter(f.v1, f.v2, p);
	double radius = circumcenter.distanceTo(p);
	if (sameHalfspaceTest(f, p, circumcenter) >= 0)
	{
		return radius;
	}
	else
	{
		return -radius;
	}
}

// srodek kola opisanego na trojkacie abc
Vector2 DelaunayMachine::circumCenter(const Vector2& a, const Vector2& b, const Vector2& c)
{
	double A, B, C, D, E, F, G;

	A = b.x - a.x;
	B = b.y - a.y;
	C = c.x - a.x;
	D = c.y - a.y;
	E = A * (a.x + b.x) + B * (a.y + b.y);
	F = C * (a.x + c.x) + D * (a.y + c.y);
	G = 2.0 * (A * (c.y - b.y) - B * (c.x - b.x));
	if (G == 0)
	{
		throw std::exception("No collinear triangle faces are allowed.");
	}
	else
	{
		double Px = (D * E - B * F) / G;
		double Py = (A * F - C * E) / G;

		return Vector2(Px, Py);
	}
}
