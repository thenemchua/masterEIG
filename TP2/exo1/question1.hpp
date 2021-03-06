#ifndef _QUESTION1_HPP_
#define _QUESTION1_HPP_

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using boost::numeric::ublas::matrix;

namespace question1 {

	/**
	 * Effectue un produit de matrices d'entiers.
	 */
	matrix<int> operator*(matrix<int> const& A, matrix<int> const& B);

}

#endif
