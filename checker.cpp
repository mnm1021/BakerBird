/**
 * checker for Baker-Bird algorithm.
 * Author: Yongseok Jin
 * Date: 2018. 10. 10.
 */

#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char** argv)
{
	char input[100][101];
	char pattern[100][101];
	int pattern_length, input_length;
	int row_input, col_input;
	
	ifstream input_file (argv[1]);
	ifstream output_bb (argv[2]);
	ofstream output_checker (argv[3]);

	/* get input of pattern and input string length. */
	input_file >> pattern_length >> input_length;

	/* get input from file */
	for (int i = 0; i < pattern_length; ++i)
	{
		input_file >> pattern[i];
	}
	for (int i = 0; i < input_length; ++i)
	{
		input_file >> input[i];
	}

	/* brute-force to get answer. */
	for (int row = pattern_length - 1; row < input_length; ++row)
	{
		for (int col = pattern_length - 1; col < input_length; ++col)
		{
			/* match input[row,col] */
			for (int i = 0; i > 0 - pattern_length; --i)
			{
				for (int j = 0; j > 0 - pattern_length; --j)
				{
					if (input[row + i][col + j] != pattern[pattern_length + i - 1][pattern_length + j - 1])
					{
						goto PATTERN_MISMATCH;
					}
				}
			}

			/* if matched, check row and col. */
			output_bb >> row_input >> col_input;
			if (output_bb.fail())
			{
				output_checker << "no";
				return -1;
			}
			if (row_input != row || col_input != col)
			{
				output_checker << "no";
				return -1;
			}
PATTERN_MISMATCH:;
		}
	}

	output_bb >> row_input;
	if (!output_bb.fail())
	{
		output_checker << "no";
	}
	else
	{
		output_checker << "yes";
	}
	return 0;
}
