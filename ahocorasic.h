/**
 * Declaration of Aho-Corasic tree.
 * Author: Yongseok Jin
 * Date: 2018. 10. 4.
 */

#ifndef __AHOCORASIC_H__
#define __AHOCORASIC_H__

#define NUM_CHILD 26

/* 'tree' of aho-corasic FSM */
class AhoTreeNode
{
public:
	AhoTreeNode* child[NUM_CHILD];
	AhoTreeNode* failure;
	bool output;
	int depth;

	AhoTreeNode (void);
	~AhoTreeNode (void);
	void insert (const char*);
	int is_output (void);
};

void set_failure (AhoTreeNode* root);
void ahocorasic_search_keywords (AhoTreeNode* root, const char* input);

#endif /* __AHOCORASIC_H__ */
