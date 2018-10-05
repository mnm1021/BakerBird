/**
 * Implementation of Aho-Corasic tree.
 * Author: Yongseok Jin
 * Date: 2018. 10. 4.
 */

#include "ahocorasic.h"
#include <queue>
#include <iostream>
#include <cstring>

/* TODO implement DP for finding failure node. */
/* TODO depth may be removed on submission: depth is just for printing the result on current status. */

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
 * figures out whether this node is matched or not
 *
 * @return:		depth of 'output' node. -1 if none.
 */
int AhoTreeNode::is_output ()
{
	if (output)
	{
		return depth;
	}

	AhoTreeNode* current = failure;

	/* track through failure */
	while (current != current->failure)
	{
		if (current->output)
		{
			return current->depth;
		}

		current = current->failure;
	}

	return -1;
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
	while (!bfs_queue.empty ())
	{
		AhoTreeNode* node = bfs_queue.front ();
		bfs_queue.pop ();

		/* handle each input. */
		for (int i = 0; i < NUM_CHILD; ++i)
		{
			AhoTreeNode* current = node->child[i];

			if (current == NULL)
			{
				continue;
			}

			/* set depth of current node */
			current->depth = node->depth + 1;

			if (node == root)
			{
				/* root's child goes back to root. */
				current->failure = root;
			}
			else /* TODO implement DP on finding failure node */
			{
				/* track back failure nodes. */
				AhoTreeNode* dest = node->failure;
		
				while (dest != root && dest->child[i] == NULL)
				{
					dest = dest->failure;
				}
	
				/* advance a node if it has branch on it. */
				if (dest->child[i] != NULL)
				{
					dest = dest->child[i];
				}

				current->failure = dest;
			}

			/* put to queue */
			bfs_queue.push (current);
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

	for (int i = 0; i < length; ++i)
	{
		int idx = input[i] - 'a';
		AhoTreeNode* next = current->child[idx];

		if (next != NULL)
		{
			/* switch to next node if there exists. */
			current = next;
		}
		else
		{
			/* track back failure node. */
			do
			{
				current = current->failure;
			} while (current != root && current->child[idx] == NULL);

			if (current->child[idx] != NULL)
			{
				current = current->child[idx];
			}
		}

		/* figure out if current status is on output or not. */
		int depth = current->is_output ();
		if (depth != -1)
		{
			/* print keyword if current node is accepted output. */
			for (int idx = i - depth + 1; idx <= i; ++idx)
			{
				std::cout << input[idx];
			}
			std::cout << std::endl;
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
	std::cout << "keywords are: aabba, aaabb, ababa, aabba, aaabb" << std::endl;
	root->insert ("aabba");
	root->insert ("aaabb");
	root->insert ("ababa");
	root->insert ("aabba");
	root->insert ("aaabb");
	set_failure (root);
	std::cout << "testing 'aabbaaabba'" << std::endl;
	ahocorasic_search_keywords (root, "aabbaaabba");
	std::cout << "testing 'aaabbaaabb'" << std::endl;
	ahocorasic_search_keywords (root, "aaabbaaabb");
	std::cout << "testing 'ababababa'" << std::endl;
	ahocorasic_search_keywords (root, "ababababa");
	delete root;
	return 0;
}




