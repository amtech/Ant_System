#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define NUM 5

typedef struct graph {
	int edge[NUM][NUM];
	int numV;//��ǰ������
	int numE;//��ǰ����
}graph;

graph *createGraph(graph *G) {
	int v, e, i, j;
	printf("���붥�����ͱ���\n");
	scanf_s("%d %d", &v, &e);
	G->numE = e; G->numV = v;
	for(i=0;i<NUM;i++)
		for (j = 0; j < NUM; j++) {
			if (i >= j) {
				G->edge[i][j] = 0;
				continue;
			}
			printf("���루%d,%d����ֵ��", i, j);
			scanf_s("%d", &G->edge[i][j]);
		}
	return G;
}

void print_graph(graph G) {
	int i, j;
	printf("��������%d��������%d", G.numV, G.numE);
	for (i = 0; i < NUM; i++) {
		printf("\n");
		for (j = 0; j < NUM; j++) {
			printf("%d ", G.edge[i][j]);
		}
	}
}

typedef struct node{
	int nodenum;
	node *next;
}node;

typedef struct headnode {
	int headnum;
	node *next;
}head[NUM];

node *createNode() {
	int n;
	node *node_now = NULL;
	node_now = (node *)malloc(sizeof(node));
	if (!node_now)return NULL;
	printf("������ڵ��");
	scanf("%d", &n);
	node_now->nodenum = n;
	node_now->next = NULL;
	//���赱�ڵ�ֵΪ-1���ͷŽڵ�
	if (node_now->nodenum == -1)
		node_now = NULL;
	return node_now;
}

headnode *createHeadNode(head headlist) {
	int i, j, n;
	printf("����ͷ�ڵ�ṹ������\n");
	for (i = 0; i < NUM; i++) {
		printf("������ͷ�ڵ��:");
		scanf("%d", &n);
		headlist[i].headnum = n;
		//temp��ʾ��һ���ڵ�ĵ�ַ
		node **temp = &headlist[i].next;
		for (j = 0;; j++) {
			node *nextnode = createNode();
			//�����һ���ڵ�������nextnode������ȥ
			//�����next��ΪNULL
			if (nextnode){
				*temp = nextnode;
				temp = &nextnode->next;
			}
			else {
				*temp = NULL;
				break;
			}
		}
	}

	return headlist;
}

void print_linklist(struct headnode *headlist) {
	int i;
	node *temp = NULL;
	for (i = 0; i < NUM; i++) {
		printf("v%d", (headlist+i)->headnum);
		temp = (headlist+i)->next;
		while (1) {
			if (temp) {
				printf("->%d", temp->nodenum);
				temp = temp->next;
			}
			else {
				printf("\n");
				break;
			}
		}
	}
}

int main() {
	//�����ڽӾ���
	//graph G;
	//createGraph(&G);
	//print_graph(G);

	//�����ڽ�����
	head headlist;//headʵ�����ǽṹ��������׵�ַ
	createHeadNode(headlist);
	print_linklist(headlist);
	//printf("headlist[1].next.headnum=%d", headlist[1].next->nodenum);


	getchar();
	getchar();
	return 0;
}