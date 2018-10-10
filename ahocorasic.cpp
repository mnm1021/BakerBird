/**
 * Test case for implementation of Aho-Corasic algorithm.
 * Author: Yongseok Jin
 * Date: 2018. 10. 4.
 */

#include "ahocorasic.h"
#include <iostream>

/**
 * main function for testing
 */
int main()
{
	AhoTreeNode* root;
	root = new AhoTreeNode ();
	std::cout << "'aabba' inserted as key " << root->insert ("aabba") << std::endl;
	std::cout << "'aaabb' inserted as key " << root->insert ("aaabb") << std::endl;
	std::cout << "'ababa' inserted as key " << root->insert ("ababa") << std::endl;
	std::cout << "'aabba' inserted as key " << root->insert ("aabba") << std::endl;
	std::cout << "'aaabb' inserted as key " << root->insert ("aaabb") << std::endl;
	set_failure (root);
	std::cout << "testing 'aabbaaabba'" << std::endl;
	std::vector< std::pair<int, int> > rslt = ahocorasic_search_keywords (root, "aabbaaabba");
	for (int i = 0; i < rslt.size (); ++i)
	{
		std::cout << rslt[i].first << " found at " << rslt[i].second << std::endl;
	}
	std::cout << "testing 'aaabbaaabb'" << std::endl;
	rslt = ahocorasic_search_keywords (root, "aaabbaaabb");
	for (int i = 0; i < rslt.size (); ++i)
	{
		std::cout << rslt[i].first << " found at " << rslt[i].second << std::endl;
	}
	std::cout << "testing 'ababababa'" << std::endl;
	rslt = ahocorasic_search_keywords (root, "ababababa");
	for (int i = 0; i < rslt.size (); ++i)
	{
		std::cout << rslt[i].first << " found at " << rslt[i].second << std::endl;
	}
	delete root;
	return 0;
}




