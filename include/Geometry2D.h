/*
 * Geometry API
 *
 * Author: Lightech (lightech@outlook.com)
 *
 * Public Domain.
 */

#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "Array.h"
#include "LinearAlgebra.h"

namespace G2D
{
	template<typename R>
	class Point : public LA::Vector<R, 2>
	{
	public:
		Point()
		{
		}

		Point(R x, R y)
		{
			this->v[0] = x;
			this->v[1] = y;
		}

		Vector<R, 2> VectorTo(Point<R> &point)
		{
			Vector<R, 2> result;
			for(int i = 0; i < 2; i++)
				result.v[i] = point.Get(i) - this->Get(i);

			return result;
		}
	};

	template<typename R>
	class Line
	{
	public:
		// A point on a line can be identified by a single scalar
		// parameter $t$ whose coordinate is given by the formula
		// P_0 + t (P_1 - P_0) = (1 - t) P_0 + t P_1
		// where P_0, P_1 are the two endpoints defining this line.
		// This works for more general parametric curves as well.
		class PointOn : public Point<R>
		{
		public:
			PointOn(Line<R> *L, R t)
			{
				for(int i = 0; i < 2; i++)
					this->v[i] = (1 - t) * L->endpoints[0]->Get(i)
									+ t  * L->endpoints[1]->Get(i);
			}
		};

		Line<R>()
		{
		}

		// Construct a line passing through specified points
		Line<R>(Point<R> *first, Point<R> *second)
		{
			endpoints[0] = first;
			endpoints[1] = second;
		}

		// Compute intersection of this line with another line
		PointOn Intersect(Line<R> &line)
		{
			// We need to identify the parameter $t$ (on this
			// line) and $t'$ on the given $line$ such that
			// P + t V = P' + t' V' where P, P' are initial
			// points and V, V' are direction vectors of the
			// 2 lines. This reduces to a linear system
			// t V - t' V' = P' - P <=> (V  V') (t -t')^T = P' - P
			// which solve to
			// $t = \det(P' - P, -V') / \det(V, -V')$
			// by Cramer's rule. Here (V V') is the 2x2 matrix
			// form by the column vectors V and V'.
			auto V = endpoints[0]->VectorTo(*endpoints[1]);
			auto Vp = line.endpoints[0]->VectorTo(*(line.endpoints[1]));
			auto D = endpoints[0]->VectorTo(*(line.endpoints[0]));
			auto det = V.Get(0) * Vp.Get(1) - V.Get(1) * Vp.Get(0);
			auto t = D.Get(0) * Vp.Get(1) - D.Get(1) * Vp.Get(0);

			return PointOn(this, t / det);
		}

		// Get projection of from given point to this line
		PointOn ProjectFrom(Point<R> &point)
		{
			// Recall that <v_1, v_2> = |v_1| . |v_2| . cos(v_1, v_2)
			// so <v_1, v_2> / |v_2| is the projection of v_1 onto v_2
			auto v1 = endpoints[0]->VectorTo(point);
			auto v2 = endpoints[0]->VectorTo(*endpoints[1]);
			R t = v1.InnerProduct(v2) / v2.ModulusSquare();

			return PointOn(this, t);
		}

		Point<R> *endpoints[2];
	};

	template<typename R>
	class LineSegment : public Line<R>
	{
	public:
		LineSegment<R>()
		{
		}

		// Construct a line segment with specified endpoints
		LineSegment<R>(Point<R> *first, Point<R> *second) : Line<R>(first, second)
		{
		}

		typename Line<R>::PointOn MidPoint()
		{
			return typename Line<R>::PointOn(this, 0.5);
		}
	};

	template<typename R>
	class Polygon
	{
	public:
		Polygon<R>()
		{
		}

		Array<Point<R>*> vertices;
		bool is_closed; // If closed, we have a polygon; else we have a polyline
	};

	template<typename R>
	class Circle
	{
	public:
		Circle<R>(Point<R> &center, R radius)
		{
			this->center = &center;
			this->radius = radius;
		}

		Point<R> *center;
		R radius;
	};
}

#endif /* _GEOMETRY_H_ */