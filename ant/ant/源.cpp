/*
	��Ⱥ�㷨��ؼ�·������

	�Ŵ��㷨��ؼ�·������

*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 20	//��������
#define CITY_NUM 9	//��������
#define TOTAL_TURN 160 //����������
#define QIFA 0.5	//�£�����ʽ��Ϣ����
#define EVER_FAVOR 0.6	//������Ϣ������
#define FAVOR 0.7	//��ʼ��Ϣ��Ũ�ȱ���
#define ZHENGFA 0.5	//������

typedef struct graph {
	int edge[CITY_NUM][CITY_NUM];	//�����·������
	//int numV;	//��ǰ������
	//int numE;	//��ǰ����
	float qifa[CITY_NUM][CITY_NUM] = { 0 };
	float xinxisu[CITY_NUM][CITY_NUM] = { 0 };	//��Ϣ��Ũ��
}graph;

graph *createGraph(graph *G, int city[][CITY_NUM]) {
	int i, j;
	//int v, e;
	//printf("���붥�����ͱ���\n");
	//scanf_s("%d %d", &v, &e);
	//G->numE = e; G->numV = v;
	for(i=0;i<CITY_NUM;i++)
		for (j = 0; j < CITY_NUM; j++) {
			if (i >= j) {
				G->edge[i][j] = 0;
				continue;
			}
			//printf("���루%d,%d����ֵ��", i, j);
			//scanf_s("%d", &G->edge[i][j]);
			G->edge[i][j] = city[i][j];
		}
	return G;
}

void print_graph(graph G) {
	int i, j;
	//printf("��������%d��������%d", G.numV, G.numE);
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
int wheelSelection(float city[]) {
	float number = 0.0, order;
	int i;
	do {
		number = rand() / (RAND_MAX + 1.0);
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
	for (i = 0; i != CITY_NUM - 1;) {
		temp_max = 0;
		for (j = 0; j < CITY_NUM; j++) {
			if (i >= j)continue;
			if (G.edge[i][j] > temp_max) {
				temp_max = G.edge[i][j];
				temp_index = j;
			}
		}
		i = temp_index;
		count += temp_max;
	}
	return count;
}

//�о���һ�����ܵ���ĳ���
int selectNextCity(graph G, int now) {
	int j, selected, i;
	float next_city_gailv[CITY_NUM] = { 0 };
	for (j = 0; j < CITY_NUM; j++) {
		next_city_gailv[j] = G.xinxisu[now][j] * EVER_FAVOR + (float)G.edge[now][j] * QIFA;	//��һ���ʳ��и���
	}
	float all = 0;	//���ʺ�
	for (j = 0; j < CITY_NUM; j++) {
		all += next_city_gailv[j];
	}
	//����ӵ�ǰ���е�ÿһ�����ܵ���ĳ��и���
	for (j = 0; j < CITY_NUM; j++) {
		next_city_gailv[j] = next_city_gailv[j] / all;
	}
	//���̶�ѡ��
	//do {
		selected = wheelSelection(next_city_gailv);
	//} while (selected >= CITY_NUM);
	

	return selected;	//������һ�������±��
}

//������Ϣ��
void renew(graph *G, float length[], int route[][CITY_NUM]) {
	int i, j, k, l;	//�����㡢����㡢���Ϻš����·��
	float weight;	//
	for (i = 0; i < CITY_NUM; i++) {
		for (j = 0; j < CITY_NUM; j++) {
			if (G->edge[i][j] == 0)continue;	//�����㲻ͨ��·��
			weight = 0.0;
			for (k = 0; k < NUM; k++) {
				for (l = 0; l < CITY_NUM; l++) {
					//�жϵ�ǰ���ϵ�·�����Ƿ񾭹�Ŀǰ���ı�
					if (route[k][l + 1] == -1)break;
					if (route[k][l] == i && route[k][l + 1] == j)
						//1/weigh
						weight += length[k];
				}
			}
			G->xinxisu[i][j] = G->xinxisu[i][j] * (1 - ZHENGFA) + weight;
		}
	}
}

void ant_system(){ 
	float C;
	int i, j;
	//��Ϣ��Ũ��(ȫ�ֳ�ʼ��)
	float t0;

	int city[CITY_NUM][CITY_NUM] = {
	{0,6,4,5,0,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,0,0,2,0,0,0},
	{0,0,0,0,0,0,9,7,0},
	{0,0,0,0,0,0,0,4,0},
	{0,0,0,0,0,0,0,0,2},
	{0,0,0,0,0,0,0,0,4},
	{0,0,0,0,0,0,0,0,0}
	};

	//int qifa[CITY_NUM][CITY_NUM] = { 0 };

	//�����ڽӾ���(·������)
	graph G;
	createGraph(&G, city);
	//print_graph(G);
	C = tanlan(G);	//·������
	printf("̰��·�����ȣ�%f\n", C);
	//��ʼ����Ϣ��Ũ��
	t0 = FAVOR * NUM * (float)C;
	for (i = 0; i < CITY_NUM; i++) {
		for (j = 0; j < CITY_NUM; j++) {
			if (i >= j)continue;
			if (G.edge[i][j] > 0)G.xinxisu[i][j] = t0;	//ֻ�����ڵ�·������Ϣ��
		}
	}

	int now, next;	//��ǰ�����±ꡢ��һ�����±�
	int route[NUM][CITY_NUM];	//��¼ÿֻ���Ͽ��ܵ������һ����
	int turn=0;
	float length[NUM] = { 0.0 };	//һֻ��������·���ĳ���

	//������
	while (turn < TOTAL_TURN) {
		//printf("turn:%d\n", turn);
		for (i = 0; i < NUM; i++)
			length[i] = 0;
		for (i = 0; i < NUM; i++) {
			
			now = 0; next = 0; 
			for (j = 0; j < CITY_NUM; j++) 				
				route[i][j] = -1;	//ÿ��ֻ������������·������ͷ��ʼ
			
			j = 0;
			route[i][0] = 0;	//�������ϴ�0�ų��г���
			while (now != CITY_NUM - 1) {	//����ǰ�ڵ��±�Ϊ�����±�ʱ������ѭ�����õ�����·��
				next = selectNextCity(G, now);
				route[i][++j] = next;
				length[i] += G.edge[now][next];	//����ÿֻ���Ϲ�������·������,��iֻ���ϵ�·��
				now = next;
			}
		}
		//����ÿ�����ϵ���Ϣ��Ũ��
		renew(&G, length, route);
		turn++;
	}

	//��������ȶ���·��
	for (i = 0; i < NUM; i++) {
		printf("\n=====length[%d]:%f=====\n", i, length[i]);
		printf("һ����ÿһֻ���Ϲ��������·����");//�������ɹ������
		for (j = 0; j < CITY_NUM; j++) {
			if (route[i][j] == -1)
				break;
			else
				printf("->");
			printf("%d", route[i][j]);	
		}
	}
}

//��Ⱥ��ʼ��
void init() {

}

//��Ӧ����������
void evaluate() {

}

//�������̶Ķ���Ⱥ�����滻������������Ⱥ������
void select() {

}

//���䣬�趨������ʣ����̶ľ����Ƿ���
void jiaopei() {

}

//���죬�趨������ʣ�ֻ�Էֲ������
//Ҫ�жϵ��Ƿ��Ƿֲ�㣬��Ҫ��¼�õ�ֱ�Ӻ������
void bianyi() {

}

void genetic_algorithm() {

	//��ʼ��

	//��Ӧ������

	//ѭ����
	//ѡ��

	//����

	//����

	//������

}

int main() {
	int i;

	//��ʼ��ʱ������
	srand((unsigned)time(NULL));
	
	//�������̶�
	//test_of_WheelSelection();

	/*for (i = 0; i < 10; i++) {
		printf("\n\n��%d����\n", i + 1);
		ant_system();
	}*/


	//�����ڽ�����
	//head headlist;//headʵ�����ǽṹ��������׵�ַ
	//createHeadNode(headlist);
	//print_linklist(headlist);

	genetic_algorithm();

	return 0;
}