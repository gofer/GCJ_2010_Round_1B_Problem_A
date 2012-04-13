#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dir_tree.h"

void init_tree(tree_node* root) {
	root->name = (char*)calloc(2, sizeof(char));
	memmove(root->name, "/", 2);
	root->num_children = 0;
}

unsigned int insert_node(tree_node* parent, const char* name) {
	int name_len;
	tree_node *child;
	
	// もし親がNULLなら終了する
	if(parent == NULL) return;
	
	// データ長の計算
	name_len = strlen(name) + 1;
	
	// 子供を作る
	do child = (tree_node*)calloc(1, sizeof(tree_node));
	while(child == NULL);
	
	do child->name = (char*)calloc(name_len, sizeof(char));
	while(child->name == NULL);
	
	memmove(child->name, name, name_len);
	child->num_children = 0;

	// 親に子供をセット
	parent->children[parent->num_children] = child;
	
	// 親の子供の数を増やす
	parent->num_children++;

	return parent->num_children-1;
}

int children_number(tree_node* parent, const char *name)  {
	unsigned int i, name_len = strlen(name) + 1, num_children = parent->num_children;
	for(i=0; ( (i<num_children) && (parent->children[i] != NULL) ); ++i) {
		if(!strncmp(parent->children[i]->name, name, name_len)) {
			return i;
		}
	}
	return -1;
}

int insert_node_2str(tree_node* parent, char *name, int count) {
	char* buf = (char*)calloc(BUFFER_MAXLEN, sizeof(char));
	unsigned int i;
	int child_num;
	
	if(name[0] == '/') {
		for(i=0; name[i+1] != '/'; ++i) {
			if(name[i+1] == '\0') {
				buf[i] = '\0';
				
				child_num = children_number(parent, buf);
				if(child_num == -1) {
					// 存在しないなら追加
					child_num = insert_node(parent, buf);
					// つまりmkdirした
					++count;
				}
				free(buf);
				return count;
			}
			buf[i] = name[i+1];
		}
		buf[i] = '\0';
		
		child_num = children_number(parent, buf);
		if(child_num == -1) {
			// 存在しないなら追加
			child_num = insert_node(parent, buf);
			// つまりmkdirした
			++count;
		}
		count = insert_node_2str(parent->children[child_num], name+i+1, count);
	}
	
	free(buf);
	return count;
}

void free_tree(tree_node* parent) {
	unsigned int num_children = parent->num_children, i;
	
	if(parent->name != NULL)
		free(parent->name);
	
	for(i=0; ( (i<num_children) && (parent->children[i] != NULL) ); ++i)
		free_tree(parent->children[i]);
	
	if(parent != NULL)
		free(parent);
}

void display_tree_aux(tree_node* parent, int tabs) {
	unsigned int num_children = parent->num_children, i;
	
	// もし親がNULLなら終了する
	if(parent == NULL) return;
	
	// タブの出力
	for(i=0; i<tabs; ++i) printf("    ");
	
	// ファイル名表示
	printf("%s\n", parent->name);
	
	// 子供が存在する限り再帰処理
	for(i=0; ( (i<num_children) && (parent->children[i] != NULL) ); ++i) {
		display_tree_aux(parent->children[i], tabs+1);
	}
}

void display_tree(tree_node* root) {
	display_tree_aux(root, 0);
}
