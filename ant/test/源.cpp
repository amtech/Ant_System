#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define NUM 5


typedef struct node {
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
			if (nextnode) {
				*temp = nextnode;
				*temp = nextnode->next;
			}
			else {
				*temp = NULL;
				break;
			}
		}
	}

	return headlist;
}

int main() {
	//int a;
	//int *b = &a;
	//scanf("%d", &a);
	//printf("a=%d", a);
	//printf("\n&a=%x", &a);
	//printf("\nb=%x", b);
	//int c = 140;
	//b = &c;
	//*b = 10000;
	//printf("\n*b=%d", *b);
	//printf("\nc=%d", c);

	head headlist;//headʵ�����ǽṹ��������׵�ַ
	createHeadNode(headlist);
	printf("v%d", headlist[0]->headnum);

	getchar();
	getchar();
	return 0;
}