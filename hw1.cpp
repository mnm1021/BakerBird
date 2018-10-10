/**
 * Implementation of assignment 1: baker-bird algorithm.
 * Author: Yongseok Jin
 * Date: 2018. 10. 10.
 */

#include "ahocorasic.h"
#include "kmp.h"
#include <iostream>
#include <fstream>

using namespace std;

/**
 * baker-bird algorithm implementation for hw1.
 */
int main(int argc, char** argv)
{
	char input[100][101];
	char pattern[101];
	char column_pattern[101];
	int kmp_status[100];
	AhoTreeNode* root;
	int pattern_length, input_length;
	
	ifstream input_file (argv[1]);
	ofstream output_file (argv[2]);

	memset (kmp_status, 0, sizeof(int) * 100);

	/* get input of pattern and input string length. */
	input_file >> pattern_length >> input_length;

	/* create Aho-Corasic tree. */
	root = new AhoTreeNode ();

	/* get pattern from user, and create Aho-Corasic tree. */
	for (int i = 0; i < pattern_length; ++i)
	{
		input_file >> pattern;
		column_pattern[i] = root->insert (pattern) + '0';
	}
	column_pattern[pattern_length] = 0;

	/* set failures for ahocorasic and kmp. */
	set_failure (root);
	set_pi (column_pattern);

	/* get input string from user, get R, and perform KMP 1 step each. */
	for (int i = 0; i < input_length; ++i)
	{
		input_file >> input[i];
		vector<char> R = ahocorasic_search_keywords (root, input[i]);

		for (int j = 0; j < input_length; ++j)
		{
			kmp_status[j] = kmp_step (R[j], column_pattern, kmp_status[j]);
			if (kmp_status[j] == strlen (column_pattern))
			{
				output_file << i << " " << j << endl;
				kmp_status[j] = pi[kmp_status[j] - 1];
			}
		}
	}

	delete root;
	return 0;
}
