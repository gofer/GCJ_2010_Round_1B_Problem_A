#define BUFFER_MAXLEN	128
#define MAX_CHILDREN_NUM	128

typedef struct _tree_node {
	char* name;
	unsigned int num_children;
	struct _tree_node *children[MAX_CHILDREN_NUM];
}tree_node;

void init_tree(tree_node*);
unsigned int insert_node(tree_node*, const char*);
int insert_node_2str(tree_node*, char*, int);
void display_tree(tree_node*);
