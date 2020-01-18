#pragma once

#include <vector>

#include "Vector2.h"
#include "Structures.h"

constexpr int pointCount = 10000;

class DelaunayMachine
{
public:
	DelaunayMachine(std::vector<Vector2>& pointset);

	void delaunay_incremental_AFL();
	int sameHalfspaceTest(const Edge& f, const Vector2& p, const Vector2& cp);
	Vector2 centerOfMass(const Vector2& a, const Vector2& b, const Vector2& c);
	double delaunayDistance(const Edge& f, const Vector2& p);
	Vector2 circumCenter(const Vector2& a, const Vector2& b, const Vector2& c);
	void makeFirstSimplex();
private:

	const std::vector<Vector2>& pointset;
};
