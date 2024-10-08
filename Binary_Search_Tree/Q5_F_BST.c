//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	BSTNode * newRoot;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("3: del;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("del node num: ");
			scanf("%d", &i);
			printf("prev: ");
			postOrderIterativeS2(root);
			printf("\n");
			printf("res: ");
			newRoot = removeNodeFromTree(root, i);
			postOrderIterativeS2(newRoot);
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	if (root == NULL) {
		return;
	}
	
	Stack stack1;
	Stack stack2;
	BSTNode *cur;

	stack1.top = NULL;
	stack2.top = NULL;
	push(&stack1, root);

	while (1) {
		if (isEmpty(&stack1)) {
			break;
		}
		cur = pop(&stack1);
		push(&stack2, cur);
		if (cur->left != NULL) {
			push(&stack1, cur->left);
		}
		if (cur->right != NULL) {
			push(&stack1, cur->right);
		}
	}
	
	while (1) {
		if (isEmpty(&stack1)) {
			break;
		}
		pop(&stack1);
	}

	while (1) {
		if (isEmpty(&stack2)) {
			break;
		}
		printf("%d ", pop(&stack2)->item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */

BSTNode* removeNodeFromTree(BSTNode *root, int value)
{
	if (root == NULL) {
		return NULL;
	}

	if (value < root->item) {
		root->left = removeNodeFromTree(root->left, value);
		return root;
	}

	if (root->item < value) {
		root->right = removeNodeFromTree(root->right, value);
		return root;
	}
	
	BSTNode *tmp;

	if (root->left == NULL) {
		tmp = root->right;
		free(root);
		return tmp;
	}

	if (root->left == NULL) {
		tmp = root->left;
		free(root);
		return tmp;
	}
	
	tmp = root->right;
	
	while(1) {
		if (tmp == NULL || tmp->left == NULL) {
			break;
		}
		tmp = tmp->left;
	}

	root->item = tmp->item;
	root->right = removeNodeFromTree(root->right, tmp->item);
	return root;
}
///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}


	// if (root == NULL) {
	// 	return NULL;
	// }
	// BSTNode *node = malloc(sizeof(BSTNode));
	// printf("%d ", root->item);
	// node->item = root->item;
	// node->left = removeNodeFromTree(root->left, value);
	// node->right = removeNodeFromTree(root->right, value);
	// return node;