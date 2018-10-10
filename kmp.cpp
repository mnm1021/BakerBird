/**
 * Test case for implemented KMP algorithm.
 * Author: Yongseok Jin
 * Date: 2018. 10. 8.
 */

#include "kmp.h"
#include <iostream>

/**
 * main function for testing
 */
int main()
{
	set_pi ("aba");
	std::vector<int> result = kmp ("ababacacababa", "aba");
	std::cout << "finding 'aba' in 'ababacacababa'" << std::endl;
	for (int i = 0; i < result.size (); ++i)
	{
		std::cout << result[i] << std::endl;
	}
	return 0;
}
