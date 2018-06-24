/*
	��Ⱥ�㷨��ؼ�·������

	�Ŵ��㷨��ؼ�·������

*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 5	//��������
#define CITY_NUM 5	//��������

typedef struct graph {
	int edge[CITY_NUM][CITY_NUM];
	int numV;//��ǰ������
	int numE;//��ǰ����
}graph;

graph *createGraph(graph *G) {
	int v, e, i, j;
	printf("���붥�����ͱ���\n");
	scanf_s("%d %d", &v, &e);
	G->numE = e; G->numV = v;
	for(i=0;i<CITY_NUM;i++)
		for (j = 0; j < CITY_NUM; j++) {
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
	for (i = 0; i < CITY_NUM; i++) {
		printf("\n");
		for (j = 0; j < CITY_NUM; j++) {
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
}head[CITY_NUM];

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
	for (i = 0; i < CITY_NUM; i++) {
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

//��Ϊʵ���ǽṹ�����飬���Ҫ���������׵�ַ��������ƫ���������в���
void print_linklist(struct headnode *headlist) {
	int i;
	node *temp = NULL;
	for (i = 0; i < CITY_NUM; i++) {
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

//���̶��㷨
int wheelSelection(float city[CITY_NUM]) {
	float number, order;
	int i;
	do {
		number = rand() / (float)(RAND_MAX);
	} while (number == 0.0);

	order = 0.0;
	for (i = 0; i < CITY_NUM; i++) {
		if (number > order && number <= order + city[i])
			return i;	//���س����б�����±��
		order += city[i];
	}
}

//�������̶�
void test_of_WheelSelection() {
	int count_a = 0, count_b = 0, count_c = 0, count_d = 0, count_e = 0;
	int temp = 0, i;
	char city_name[CITY_NUM] = { 'a','b','c','d','e' };
	float city_gailv[CITY_NUM] = { 0.14,0.23,0.06,0.4,0.17 };
	for (i = 0; i < 100000; i++) {
		temp = wheelSelection(city_gailv);
		//printf("ѡ��ĳ���:%d\n", temp);
		switch (temp) {
		case 0:count_a++; break;
		case 1:count_b++; break;
		case 2:count_c++; break;
		case 3:count_d++; break;
		case 4:count_e++; break;
		}
	}
	printf("a����:%f\n", count_a / float(count_a + count_b + count_c + count_d + count_e));
	printf("b����:%f\n", count_b / float(count_a + count_b + count_c + count_d + count_e));
	printf("c����:%f\n", count_c / float(count_a + count_b + count_c + count_d + count_e));
	printf("d����:%f\n", count_d / float(count_a + count_b + count_c + count_d + count_e));
	printf("e����:%f\n", count_e / float(count_a + count_b + count_c + count_d + count_e));
}

//̰���㷨��һ����·
float tanlan(graph G) {
	int i = 0, j, temp_index;
	float count = 0, temp_max;
	printf("CITY_NUM:%d\n", CITY_NUM);
	for (i = 0; i != (CITY_NUM) - 1;) {
		printf("CITY_NUM:%d\n", CITY_NUM - 1);
		temp_max = 0;
		for (j = 0; j < CITY_NUM; j++) {
			if (i >= j)continue;
			if (G.edge[i][j] > temp_max) {
				temp_max = G.edge[i][j];
				temp_index = j;
			}
		}
		count += temp_max;
	}
	return count;
}

int main() {
	//float 
	float C;

	//��ʼ��ʱ������
	srand((unsigned)time(NULL));
	
	test_of_WheelSelection();

	//�����ڽӾ���
	graph G;
	createGraph(&G);
	//print_graph(G);
	C = tanlan(G);
	printf("̰����%f", C);

	//�����ڽ�����
	//head headlist;//headʵ�����ǽṹ��������׵�ַ
	//createHeadNode(headlist);
	//print_linklist(headlist);




	return 0;
}