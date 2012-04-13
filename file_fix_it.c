#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dir_tree.h"

void make_init_tree(tree_node *root, FILE* fp, unsigned int N) {
	unsigned int i;
	char *buf = (char*)malloc(BUFFER_MAXLEN * sizeof(char));
	
	// �؂̏�����
	init_tree(root);
	
	// 1���O�����������
	for(i=0; i<N; ++i) {
		fscanf(fp, "%s", buf);
		insert_node_2str(root, buf, 0);
	}
	
	free(buf);
}

int solve(tree_node *root, FILE* fp, unsigned int M) {
	unsigned int i, count = 0;
	char *buf = (char*)malloc(BUFFER_MAXLEN * sizeof(char));
	
	for(i=0; i<M; ++i) {
		fscanf(fp, "%s", buf);
		count += insert_node_2str(root, buf, 0);
	}
	
	free(buf);
	
	return count;
}

int main(int argc, char** argv) {
	unsigned int T = 0, N = 0, M = 0, i, j;
	
	//FILE *fp = fopen("input.txt", "r");
	//FILE *fp = fopen("A-small-practice.in", "r");
	FILE *fp = fopen("A-large-practice.in", "r");
	
	fscanf(fp, "%d", &T);
	
	for(i=0; i<T; ++i) {
		fscanf(fp, "%d %d", &N, &M);
		
		// �؂̏�����
		tree_node *root = (tree_node*)malloc(sizeof(tree_node));
		
		// ���߂̖؂����
		make_init_tree(root, fp, N);
		
		// ��������
		printf("Case #%d: %d\n", i+1, solve(root, fp, M));
		
		// �؂̉��
		free_tree(root);
	}
	
	fclose(fp);
	
	return EXIT_SUCCESS;
}
