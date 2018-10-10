/**
 * Implementation of KMP algorithm.
 * Author: Yongseok Jin
 * Date: 2018. 10. 8.
 */

#ifndef __KMP_H__
#define __KMP_H__

#include <vector>
#include <cstring>

#define MAX_INPUT_LENGTH 100

int pi[MAX_INPUT_LENGTH];

/**
 * setting prefix array.
 *
 * @param key: 		key string to find.
 */
void set_pi (const char* key)
{
	int length = strlen (key);
	int i, j = 0;

	pi[0] = 0;
	for (i = 1; i < length; ++i)
	{
		while (j > 0 && key[i] != key[j])
		{
			j = pi[j - 1];
		}
		if (j > 0 || key[i] == key[j])
		{
			++j;
		}
		pi[i] = j;
	}
}

/**
 * find the occurance of 'key' in given input.
 * 
 * @param input: 	input string.
 * @param key: 		key string to find.
 * @return:			vector of index of the key.
 */
std::vector<int> kmp (const char* input, const char* key)
{
	std::vector<int> output;
	int status = 0;
	int length = strlen (input);
	int key_length = strlen (key);

	for (int i = 0; i < length; ++i)
	{
		while (status > 0 && input[i] != key[status])
		{
			status = pi[status - 1];
		}
		if (status > 0 || input[i] == key[status])
		{
			++status;
		}
		if (status == key_length)
		{
			output.push_back (i);
			status = pi[status - 1];
		}
	}

	return output;
}

/**
 * perform kmp operation 1 step.
 * 
 * @param input: 	input character.
 * @param key: 		key string to find.
 * @param status:	current status.
 * @return:			result status.
 */
int kmp_step (char input, const char* key, int status)
{
	std::vector<int> output;

	while (status > 0 && input != key[status])
	{
		status = pi[status - 1];
	}
	if (status > 0 || input == key[status])
	{
		++status;
	}

	return status;
}

#endif // __KMP_H__
