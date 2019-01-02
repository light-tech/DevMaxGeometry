/*
 * An more complicated example.
 *
 * Author: Lightech (lightech@outlook.com)
 *
 * Public Domain.
 */

#include "include/Figure.h"

int main(int argc, const char **argv)
{
	PrintString("Generate figure 2\n");

	typedef Figure<double> Fig;

	Fig fig;

	// Triangle ABC
	Fig::Point A(0, 1, "A"), B(-1, -1, "B"), C(3, -1.25, "C");
	fig.Add(A, B, C);
	Fig::Triangle TABC(A, B, C);
	fig.Add(TABC);

	Fig::LineSegment BC(B, C), AB(A, B), CA(C, A);

	// Add the 3 altitudes
	Fig::Point H(BC.ProjectFrom(A), "H");
	Fig::Point I(AB.ProjectFrom(C), "I");
	Fig::Point J(AB.ProjectFrom(B), "J");
	Fig::LineSegment AH(A, H), CI(C, I), BJ(B, J);
	fig.Add(H, I, J);
	fig.Add(AH, CI, BJ);

	// Add the 3 midpoints and medians
	Fig::Point M(BC.MidPoint(), "M");
	Fig::Point N(CA.MidPoint(), "N");
	Fig::Point P(AB.MidPoint(), "P");
	fig.Add(M, N, P);
	Fig::LineSegment AM(A, M), BN(B, N), CP(C, P);
	fig.Add(AM, BN, CP);

	// Center of gravity = intersection of 3 medians
	Fig::Point G(AM.Intersect(BN), "G");
	fig.Add(G);

	// Write out the figure to SVG file
	char output_file_name[1024];
	sprintf(output_file_name, "%s.svg", __FILE__);
	fig.RenderAsSVG(600, 400, -2, 4, -2, 2, output_file_name);
	PrintString("Done\n");

	return 0;
}