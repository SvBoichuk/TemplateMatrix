#include "template_matrix.h"

void main()
{
	Matrix<int> m1(4, 2);
	Matrix<int> m2(2, 3);

	std::cin >> m1;
	std::cin >> m2;
	
	std::cout << (m1 * m2) << std::endl;
}