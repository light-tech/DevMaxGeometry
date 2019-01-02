/*
 * Figure making API
 *
 * Author: Lightech (lightech@outlook.com)
 *
 * Public Domain.
 */

#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "DevMax.h"
#include "Array.h"
#include "Geometry2D.h"

/*
 * Class to contain a 2D geometric figure.
 */
template<typename R>
class Figure
{
public:
	enum ComponentType : char
	{
		POINT,
		LINE,
		LINE_SEGMENT,
		CIRCLE,
		POLYGON,
		COORD_SYSTEM
	};

	class Style
	{
	public:
		int strokeWidth;
		int strokeColor;
	};

	/*
	 * Base class for all 2D figure objects to provide styling
	 * and label.
	 */
	class Component
	{
	public:
		Component(ComponentType t, const char *name)
		{
			type = t;
			label = name;
			style = nullptr;
		}

		ComponentType type;
		const char *label;
		Style *style;
	};

	/*
	 * Labelled point
	 */
	class Point : public G2D::Point<R>, public Component
	{
	public:
		Point(R x, R y, const char *name = nullptr) : 
			G2D::Point<R>(x, y),
			Component(POINT, name)
		{
		}

		Point(G2D::Point<R> point, const char *name = nullptr) : 
			G2D::Point<R>(point.v[0], point.v[1]),
			Component(POINT, name)
		{
		}
	};

	class Line : public G2D::Line<R>, public Component
	{
	public:
		Line(G2D::Point<R> &first, G2D::Point<R> &second, const char *name = nullptr) :
			G2D::Line<R>(&first, &second),
			Component(LINE, name)
		{
		}
	};

	class LineSegment : public G2D::LineSegment<R>, public Component
	{
	public:
		LineSegment(G2D::Point<R> &first, G2D::Point<R> &second, const char *name = nullptr) :
			G2D::LineSegment<R>(&first, &second),
			Component(LINE_SEGMENT, name)
		{
		}
	};

	class Polygon : public G2D::Polygon<R>, public Component
	{
	public:
		Polygon(const char *name = nullptr) : Component(POLYGON, name)
		{
		}
	};

	class Triangle : public Polygon
	{
	public:
		Triangle(G2D::Point<R> &P1, G2D::Point<R> &P2, G2D::Point<R> &P3, const char *name = nullptr) :
			Polygon(name)
		{
			this->vertices.Reserve(3);
			this->vertices.Append(&P1);
			this->vertices.Append(&P2);
			this->vertices.Append(&P3);
			this->is_closed = true;
		}
	};

	Figure()
	{
	}

	// Add a geometric object to this figure
	void Add(Component &);

	// Convenient template method to add multiple objects in one call
	template<typename... Ts>
	void Add(Component &obj, Ts & ... rest)
	{
		Add(obj);
		Add(rest...);
	}

	// Render to SVG file
	// TODO Remove the SVG height: Should be computed automatically
	// Or maybe if height = 0 then we compute automatically to match aspect ratio
	void RenderAsSVG(
		int width, int height, // of the SVG document
		R x_min, R x_max, R y_min, R y_max, // clipping region
		const char *svg_file_path
	);

private:
	Array<Component*> components;
};

#include "Figure.cpp"

#endif /* _FIGURE_H_ */