/*
 * An example program for our 2D geometry API that build a
 * 2D figure and export as SVG which could be open in Edge
 * for visualization.
 *
 * Author: Lightech (lightech@outlook.com)
 *
 * Public Domain.
 */

#include "include/Figure.h"

int main(int argc, const char **argv)
{
	PrintString("Generate figure 1\n");

	typedef Figure<double> Fig;

	Fig fig;

	// Triangle ABC
	Fig::Point A(0, 1, "A"), B(-1, -1, "B"), C(3, -1.25, "C");
	fig.Add(A, B, C);
	Fig::Triangle TABC(A, B, C);
	fig.Add(TABC);

	// Write out the figure to SVG file
	char output_file_name[1024];
	sprintf(output_file_name, "%s.svg", __FILE__);
	fig.RenderAsSVG(600, 400, -2, 4, -2, 2, output_file_name);
	PrintString("Done\n");

	return 0;
}