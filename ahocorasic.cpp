/**
 * Implementation of Aho-Corasic tree.
 * Author: Yongseok Jin
 * Date: 2018. 10. 4.
 */

#include "ahocorasic.h"
#include <queue>
#include <iostream>
#include <cstring>

/**
 * Constructor of AhoTreeNode.
 */
AhoTreeNode::AhoTreeNode ()
{
	for (int i = 0; i < NUM_CHILD; ++i)
	{
		child[i] = NULL;
	}
	failure = NULL;
	output = false;
}

/**
 * Destructor of AhoTreeNode.
 */
AhoTreeNode::~AhoTreeNode ()
{
	for (int i = 0; i < NUM_CHILD; ++i)
	{
		if (child[i])
		{
			delete child[i];
		}
	}
}

/**
 * Inserting a key string to given ahocorasic FSM.
 *
 * @param string:	key string to find
 */
void AhoTreeNode::insert (const char* string)
{
	/* if it points the end of string, set output. */
	if (*string == 0)
	{
		output = true;
	}
	else
	{
		/* set new child for current node. */
		int index = *string - 'a';

		if (child[index] == NULL)
		{
			child[index] = new AhoTreeNode ();
		}
		child[index]->insert (string + 1);
	}
}

/**
 * Finding failure node on Aho-Corasic FSM.
 *
 * @param root: 	root node of Aho-Corasic FSM.
 */
void set_failure (AhoTreeNode* root)
{
	std::queue<AhoTreeNode*> bfs_queue;

	root->failure = root;
	root->depth = 0;
	bfs_queue.push (root);

	/* set every node's failure node by BFS. */
	while (!bfs_queue.empty())
	{
		AhoTreeNode* node = bfs_queue.front();
		bfs_queue.pop();

		/* handle each input. */
		for (int i = 0; i < NUM_CHILD; ++i)
		{
			AhoTreeNode* next = node->child[i];
			if (next == NULL)
			{
				continue;
			}
			next->depth = node->depth + 1;

			/* track through the nearest parent. */
			AhoTreeNode* dest = node->failure;
			
			while (dest != root && dest->child[i] == NULL)
			{
				dest = dest->failure;
			}

			if (dest != root && dest->child[i] != NULL)
			{
				dest = dest->child[i];
			}

			next->failure = dest;

			/* put to queue */
			bfs_queue.push (next);
		}
	}
}

/**
 * Finding keywords by Aho-Corasic algorithm in 'input'.
 *
 * @param root:		root node of Aho-Corasic FSM.
 * @param input:	input string.
 */
void ahocorasic_search_keywords (AhoTreeNode* root, const char* input)
{
	AhoTreeNode* current = root;
	int length = strlen (input);
	int keyword_start = 0;

	for (int i = 0; i < length; ++i)
	{
		int idx = input[i] - 'a';
		AhoTreeNode* next = current->child[idx];

		if (next != NULL)
		{
			/* switch to next node if there exists. */
			current = next;

			if (current->output)
			{
				/* print keyword if current node is accepted output. */
				for (int idx = keyword_start; idx <= i; ++idx)
				{
					std::cout << input[idx];
				}
				std::cout << std::endl;
			}

			/* TODO track back down to failure nodes to check prior pattern match */
		}
		else
		{
			/* track back failure node. */
			do
			{
				current = current->failure;
			} while (current != root && current->child[idx] != NULL);

			if (current->child[idx] != NULL)
			{
				current = current->child[idx];
			}

			keyword_start = i - current->depth + 1; /* root has no first key, so +1 */
		}
	}
}

/**
 * main function for testing
 */
int main()
{
	AhoTreeNode* root;
	root = new AhoTreeNode ();
	std::cout << "keywords are: a, ab, ac, adab, adada" << std::endl;
	root->insert ("a");
	root->insert ("ab");
	root->insert ("ac");
	root->insert ("adab");
	root->insert ("adada");
	set_failure (root);
	std::cout << "testing 'a'" << std::endl;
	ahocorasic_search_keywords (root, "a");
	std::cout << "testing 'adadada'" << std::endl;
	ahocorasic_search_keywords (root, "adadada");
	std::cout << "testing 'adababbba'" << std::endl;
	ahocorasic_search_keywords (root, "adababbba");
	delete root;
	return 0;
}




