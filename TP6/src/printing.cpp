#include "printing.hpp"

#include <iostream>
#include <iomanip>

#include <stdio.h>
#include <unistd.h>

using boost::numeric::ublas::matrix;

bool isInteractive() {
	return isatty(fileno(stdout));
}

std::ostream& operator<<(std::ostream& os, Map m) {
	int line = m.getSize() - 1;
	os << "   ┌";
	for(int i = 1 ; i < m.getSize() ; ++i) {
		os << "───┬";
	}
	os << "───┐\n";

	for(int i = 1 ; i < m.getSize() ; ++i) {
		os << std::right << std::setw(2) << line--
		   << " │";
		for(int j = 1 ; j < m.getSize() ; ++j) {
			os << "   │";
		}
		os <<  "   │\n   ├";
		for(int j = 1 ; j < m.getSize() ; ++j) {
			os << "───┼";
		}
		os << "───┤\n";
	}

	os << std::right << std::setw(4) << " 0 │";
	for(int j = 1 ; j < m.getSize() ; ++j) {
		os << "   │";
	}
	os << "   │\n   └";
	for(int i = 1 ; i < m.getSize() ; ++i) {
		os << "───┴";
	}
	os << "───┘\n  ";
	for(int i = 0 ; i < m.getSize() ; ++i) {
		os << std::setw(4) << i;
	}
	os << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, Robot r) {
	if(isInteractive()) {
		// Go right
		os << "\x1b[" << (4*r.getCoordX() + 5) << "C"
		   // Go up
		   << "\x1b[" << (2*r.getCoordY() + 3) << "A"
		   << "⬤"
		   // Re go left (+1)
		   << "\x1b[" << (4*r.getCoordX() + 6) << "D"
		   // Re go down
		   << "\x1b[" << (2*r.getCoordY() + 3) << "B";
	} else {
		os << "(" << r.getCoordX() << ", " << r.getCoordY() << ")";
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, matrix<float> mat) {
	int rows = mat.size1(),
		cols = mat.size2();

	for(int row = rows - 1 ; row >= 0 ; --row) {
		for(int col = 0 ; col < cols ; ++col) {
			if(col == 0) {
				if(row == rows - 1) {
					os << "⎡ ";
				} else if(row == 0) {
					os << "⎣ ";
				} else {
					os << "⎢ ";
				}
			}

			os << std::setprecision(2) << std::fixed << std::setw(5) << mat(row, col) << " ";

			if(col == cols - 1) {
				if(row == rows - 1) {
					os << "⎤\n";
				} else if(row == 0) {
					os << "⎦" << std::endl;
				} else {
					os << "⎥\n";
				}
			}
		}
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, WallE_Matrix mat) {
	int rows = mat.size1(),
		cols = mat.size2();

	// Matrice's origins are top left
	for(int row = rows - 1 ; row >= 0 ; --row) {
		for(int col = 0 ; col < cols ; ++col) {
			if(col == 0) {
				if(row == rows - 1) {
					os << "⎡ ";
				} else if(row == 0) {
					os << "⎣ ";
				} else {
					os << "⎢ ";
				}
			}

			int value = mat(row, col);
			switch(value) {
				case EAST:
					os << "←" << " ";
					break;
				case NORTH:
					os << "↓" << " ";
					break;
				case NORTH_EAST:
					os << "↙" << " ";
					break;
				default:
					std::cerr << "Wrong value in WallE_Matrix" << std::endl;
					std::abort();
			}

			if(col == cols - 1) {
				if(row == rows - 1) {
					os << "⎤\n";
				} else if(row == 0) {
					os << "⎦" << std::endl;
				} else {
					os << "⎥\n";
				}
			}
		}
	}

	return os;
}
