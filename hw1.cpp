/**
 * Implementation of assignment 1: baker-bird algorithm.
 * Author: Yongseok Jin
 * Date: 2018. 10. 10.
 */

#include "ahocorasic.h"
#include "kmp.h"
#include <iostream>

using namespace std;

/**
 * baker-bird algorithm implementation for hw1.
 */
int main()
{
	char pattern[101][101];
	char input[101][101];
	char column_pattern[101];
	char column[101];
	vector<char> R[100];
	AhoTreeNode* root;
	int pattern_length, input_length;

	/* get input of pattern and input string length. */
	cin >> pattern_length >> input_length;

	/* create Aho-Corasic tree. */
	root = new AhoTreeNode ();

	/* get pattern from user, and create Aho-Corasic tree. */
	for (int i = 0; i < pattern_length; ++i)
	{
		cin >> pattern[i];
		column_pattern[i] = root->insert (pattern[i]) + '0';
	}
	column_pattern[pattern_length] = 0;

	/* set failure node. */
	set_failure (root);

	/* get input string from user, and get Rs. */
	for (int i = 0; i < input_length; ++i)
	{
		cin >> input[i];
		R[i] = ahocorasic_search_keywords (root, input[i]);
	}

	/* search column_pattern from the columns of R by KMP algorithm. */
	for (int i = 0; i < input_length; ++i)
	{
		for (int j = 0; j < input_length; ++j)
		{
			column[j] = R[j][i]; /* TODO remove redundant operations by 2D array */
		}
		column[input_length] = 0;

		vector<int> result = kmp (column, column_pattern);
		for (int j = 0; j < result.size (); ++j)
		{
			cout << result[j] << " " << i << endl;
		}
	}

	delete root;
	return 0;
}
