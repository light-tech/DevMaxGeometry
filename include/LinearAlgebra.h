/*
 * Basic objects in linear algebra
 *
 * Author: Lightech (lightech@outlook.com)
 *
 * Public Domain.
 */

#ifndef _LINEAR_ALGEBRA_H_
#define _LINEAR_ALGEBRA_H_

namespace LA
{

	/*
	* Template for n x m matrix (n rows, m columns) to describe linear
	* transformation from R^m -> R^n
	*/
	template<typename R, int n, int m>
	class Matrix
	{
	public:
		R GetEntry(int i, int j)
		{
			return entries[i][j];
		}

		template<int p>
		Matrix<R, n, p> PostMultiply(Matrix<R, m, p> &M)
		{
			Matrix<R, n, p> result;
			// TODO Implement
			return result;
		}

		static inline constexpr int NumRows() { return n; }
		static inline constexpr int NumCols() { return m; }

		R entries[n][m];
	};

	/*
	* Basic column vector
	*/
	template<typename R, int dim>
	class Vector
	{
	public:
		Vector()
		{
		}

		R Get(int n)
		{
			return v[n];
		}

		R ModulusSquare()
		{
			R s = 0;
			for(int i = 0; i < dim; i++)
			{
				auto ci = Get(i);
				s += ci * ci;
			}
			return s;
		}

		R InnerProduct(Vector<R, dim> &V)
		{
			R s = 0;
			for(int i = 0; i < dim; i++)
			{
				s += Get(i) * V.Get(i);
			}
			return s;
		}

		R v[dim];
	};

} /* namespace LA */

#endif /* _LINEAR_ALGEBRA_H_ */