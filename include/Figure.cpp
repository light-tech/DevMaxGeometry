/*
 * Figure class implementation
 *
 * Author: Lightech (lightech@outlook.com)
 *
 * Public Domain.
 */

#include "Figure.h"

template<typename R>
void Figure<R>::Add(Component &C)
{
	components.Append(&C);
}

/*
 * Transform the coordinate system to SVG file's coordinate system.
 * It's easy to work out the matrix since our goal is to transform the rectangle
 * (x_min, y_max) .. (x_max, y_min) to the rectangle (0, 0) .. (width, height)
 * and so the transformation is the projective linear transformation
 * X = (x - x_min) * xc where xc = width / (x_max - x_min)
 * Y = (y_max - y) * yc where yc = height / (y_max - y_min)
 */
template<typename R>
class WorldToViewTransform
{
public:
	WorldToViewTransform(int width, int height,
		R x_min, R x_max, R y_min, R y_max)
	{
		R xc = static_cast<R>(width) / (x_max - x_min);
		R yc = static_cast<R>(height) / (y_max - y_min);
		a = xc;
		b = - x_min * xc;
		c = - yc;
		d = y_max * yc;
	}

	// Transform point with coordinates (x, y) to (X, Y)
	void Transform(R x, R y, R &X, R &Y)
	{
		X = a * x + b;
		Y = c * y + d;
	}

	// Transform a specified point
	void Transform(G2D::Point<R> *P, R &X, R &Y)
	{
		Transform(P->Get(0), P->Get(1), X, Y);
	}

private:
	R a, b, c, d;
};

template<typename R>
void Figure<R>::RenderAsSVG(int width, int height, R x_min, R x_max, R y_min, R y_max, const char *svg_file_path)
{
	auto file = fopen(svg_file_path, "wb");
	if (file == nullptr)
	{
		PrintString("Can't open ");
		PrintString(svg_file_path);
		return;
	}

	WorldToViewTransform<R> T(width, height, x_min, x_max, y_min, y_max);

	fputs("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>", file);
	fprintf(file, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"%d\" height=\"%d\">", width, height);
	components.ForEach([&T, file](Component *C)
	{
		switch (C->type)
		{
		case POINT:
		{
			if (C->label != nullptr)
			{
				Point *P = (Point*) C;
				R X, Y;
				T.Transform(P, X, Y);
				fprintf(file, "<text x=\"%lf\" y=\"%lf\">%s</text>", X, Y, C->label);
			}
		}
			break;

		case LINE_SEGMENT:
		{
			LineSegment *L = (LineSegment*) C;
			R X, Y;
			T.Transform(L->endpoints[0], X, Y);
			fprintf(file, "<line stroke=\"black\" stroke-width=\"2\" x1=\"%f\" y1=\"%f\" ", X, Y);
			T.Transform(L->endpoints[1], X, Y);
			fprintf(file, "x2=\"%f\" y2=\"%f\" />", X, Y);
		}
			break;

		case LINE:
		{
			// This is a bit more complicated as we need to find out the intersection
			// of the line with the clipping viewport.
		}
			break;

		case CIRCLE:
			break;

		case POLYGON:
		{
			Polygon *P = (Polygon*) C;
			if (P->is_closed)
				fputs("<polygon fill=\"none\" stroke=\"black\" stroke-width=\"2\" points=\"", file);
			else
				fputs("<polyline fill=\"none\" stroke=\"black\" stroke-width=\"2\" points=\"", file);
			P->vertices.ForEach([&T, file](G2D::Point<R> *V)
			{
				R X, Y;
				T.Transform(V, X, Y);
				fprintf(file, "%f,%f ", X, Y);
			});
			fputs("\" />", file);
		}
			break;

		default:
			break;
		}
	});
	fputs("</svg>", file);
	fclose(file);
}