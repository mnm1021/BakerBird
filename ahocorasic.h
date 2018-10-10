/**
 * Implementation of Aho-Corasic algorithm.
 * Author: Yongseok Jin
 * Date: 2018. 10. 4.
 */

#ifndef __AHOCORASIC_H__
#define __AHOCORASIC_H__

#include <vector>
#include <utility>
#include <queue>
#include <cstring>

#define NUM_CHILD 26

static int output_num = 1; /* output number of node */

/* 'tree' of aho-corasic FSM */
class AhoTreeNode
{
public:
	AhoTreeNode* child[NUM_CHILD]; /* 'next' node */
	AhoTreeNode* failure; /* failure node */
	int output; /* output number */

	/**
	 * Constructor of AhoTreeNode.
	 */
	AhoTreeNode ()
	{
		for (int i = 0; i < NUM_CHILD; ++i)
		{
			child[i] = NULL;
		}
		failure = NULL;
		output = 0;
	}

	/**
	 * Destructor of AhoTreeNode.
	 */
	~AhoTreeNode ()
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
	 * @return:			output number
	 */
	int insert (const char* string)
	{
		/* if it points the end of string, set output. */
		if (*string == 0)
		{
			if (output == 0)
			{
				output = output_num;
				output_num += 1;
			}
	
			return output;
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
	 * @return:		output number. 0 if none.
	 */
	int is_output ()
	{
		if (output != 0)
		{
			return output;
		}
	
		AhoTreeNode* current = failure;
	
		/* track through failure */
		while (current != current->failure)
		{
			if (current->output != 0)
			{
				return current->output;
			}
	
			current = current->failure;
		}
	
		return 0;
	}
};

/**
 * Finding failure node on Aho-Corasic FSM.
 *
 * @param root: 	root node of Aho-Corasic FSM.
 */
void set_failure (AhoTreeNode* root)
{
	std::queue<AhoTreeNode*> bfs_queue;

	root->failure = root;
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

			if (node == root)
			{
				/* root's child goes back to root. */
				current->failure = root;
			}
			else
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
 * @return:			vector of pair of (key number, index).
 */
std::vector< std::pair<int, int> > ahocorasic_search_keywords (
		AhoTreeNode* root, const char* input)
{
	AhoTreeNode* current = root;
	int length = strlen (input);
	std::vector< std::pair<int, int> > result;

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
		int output_num = current->is_output ();
		if (output_num != 0)
		{
			result.push_back (std::make_pair (output_num, i));
		}
	}
	
	return result;
}

#endif /* __AHOCORASIC_H__ */
