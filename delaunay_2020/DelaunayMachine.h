#pragma once

#include <vector>
#include <memory>

#include "Vector2.h"
#include "Structures.h"

using namespace d20;

constexpr int pointCount = 1000000;

class DelaunayMachine
{
public:
	DelaunayMachine(std::shared_ptr<std::vector<Vector2>> pointset);

	void delaunay_incremental_AFL();
	
private:
	void makeFirstSimplex();
	std::shared_ptr<Vector2> findFirstPoint(double alfa);
    int sameHalfspaceTest(const Edge& f, const Vector2& p, const Vector2& cp);
	Vector2 centerOfMass(const Vector2& a, const Vector2& b, const Vector2& c);
	double delaunayDistance(const Edge& f, const Vector2& p);
	Vector2 circumCenter(const Vector2& a, const Vector2& b, const Vector2& c);

	std::shared_ptr<std::vector<Vector2>> pointset;
};
