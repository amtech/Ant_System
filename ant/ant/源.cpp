/*
	��Ⱥ�㷨��ؼ�·������

	�Ŵ��㷨��ؼ�·������

*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//��Ⱥ��س���
#define NUM 20	//��������
#define CITY_NUM 9	//��������
#define TOTAL_TURN 160	//����������
#define QIFA 0.5	//�£�����ʽ��Ϣ����
#define EVER_FAVOR 0.6	//������Ϣ������
#define FAVOR 0.7	//��ʼ��Ϣ��Ũ�ȱ���
#define ZHENGFA 0.5	//������

//�Ŵ���س���
#define BREED 20	//��Ⱥ����
#define CITY2 9	//��������
#define JIAOPEI	0.88	//�������
#define BIANYI 0.1	//�������
#define TOTAL_TURN2 100	//����������

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
	int length;	//�����·������
	node *next;
}node;

typedef struct headnode {
	int headnum;
	int tail_length = 0;
	node *next;
}head[CITY2];

node *createNode() {
	int n, length = 0;
	node *node_now = NULL;
	node_now = (node *)malloc(sizeof(node));
	if (!node_now)return NULL;
	printf("������ڵ�š������·������");
	scanf("%d %d", &n, &length);
	node_now->nodenum = n;
	node_now->length = length;
	node_now->next = NULL;
	//���赱�ڵ�ֵΪ-1���ͷŽڵ�
	if (node_now->nodenum == -1)
		node_now = NULL;
	return node_now;
}

headnode *createHeadNode(head headlist) {
	int i, j, n, count = 0;
	printf("����ͷ�ڵ�ṹ������\n");
	for (i = 0; i < CITY2; i++) {
		printf("������ͷ�ڵ��:");
		scanf("%d", &n);
		headlist[i].headnum = n;
		//temp��ʾ��һ���ڵ�ĵ�ַ
		node **temp = &headlist[i].next;
		count = 0;	//���㣬���¼���
		for (j = 0;; j++) {
			node *nextnode = createNode();
			//�����һ���ڵ�������nextnode������ȥ
			//�����next��ΪNULL
			if (nextnode){
				*temp = nextnode;
				temp = &nextnode->next;
				count += 1;	//���Ӻ�̽ڵ�ɹ����������+1
			}
			else {
				*temp = NULL;
				break;
			}	
		}
		//��¼�õ���м����ɵ���ĵ�
		headlist[i].tail_length = count;	
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

//����һ����Ⱥ�㷨�����ڴ˴��޸�Ҫ���Ե�ͼ
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

//����һ��0~(range-1)������
int randx(int range) {
	int number;
	number = rand() % range;
	return number;
}

float rand0_1() {
	float number;
	number = rand() / (RAND_MAX + 1.0);
	return number;
}

//����һ�������˷������е�����
void selectNextCity2(struct headnode *city_list,int order[]) {
	int i, j, next = 0, round, tail = 0;
	node *temp = NULL;
	for (i = 0; i < CITY2; i++) {
		order[i] = city_list[next].headnum;	//��һ���0�㿪ʼ
		printf("order:%d\n", order[i]);
		if (order[i] == CITY2 - 1)break;	//·���ѵ���ͼ��ĩβ�ڵ����˳�
		//���ѡ����ʿɴ����һ���ڵ�
		//round��һ���±꣬�ڽӱ��ÿ���ڵ�����±��0��ʼ
		round = randx(city_list[next].tail_length);
		//tail = city_list[next].tail_length;
		temp = city_list[next].next;
		for (j = 0; j < round + 1; j++) {
			next = temp->nodenum;
			temp = temp->next;
			if (temp == NULL)break;
		}
	}
}

//��Ⱥ��ʼ��
void init(int c[BREED][CITY2], struct headnode *city_list) {
	int i, j;
	int order[CITY2];
	
	for (i = 0; i < CITY2; i++) {
		order[i] = -1;
	}
	
	for (i = 0; i < BREED; i++) {
		printf("=====��%d����Ⱥ·����=====\n", i);
		selectNextCity2(city_list, order);
		//���ݷ������н���0/1ת��
		for (j = 0; j < CITY2; j++) {
			if (order[j] == -1)
				break;
			else
				c[i][order[j]] = 1;
		}
	}
}

//��һ�㵽��һ���·�����Ȳ�ѯ
int pathLength(int now, int next, struct headnode *city_list) {
	int length, i, tail_length;
	node *temp = city_list[now].next;
	
	while (temp)
	{
		length = temp->length;
		if (temp->nodenum == next)break;
		temp = temp->next;
	}

	return length;
}

//��Ӧ����������
void evaluate(int c[BREED][CITY2], float value[BREED], struct headnode *city_list) {
	int i, j, now, next;
	for (i = 0; i < BREED; i++) {
		now = 0;
		for (j = 0; j < CITY2; j++) {
			if (c[i][j] == 1) {
				next = j;
				value[i] += pathLength(now, next, city_list);
				now = next;
			}
		}
	}
}

//���̶��㷨2��ֻ��CITY_NUM�ĳ�BREED�ˣ����ܲ�����취�ϲ��������̶�
int wheelSelection2(float city[]) {
	float number = 0.0, order;
	int i;
	do {
		number = rand() / (RAND_MAX + 1.0);
	} while (number == 0.0);

	order = 0.0;
	for (i = 0; i < BREED; i++) {
		if (number > order && number <= order + city[i])
			return i;	//����ѡ����Ⱥ�±��
		order += city[i];
	}
}

//�������̶Ķ���Ⱥ�����滻���и�������������Ⱥ������
void select(int c[BREED][CITY2], float value[BREED]) {
	int selected[BREED];	//��˳��ѡ���滻����
	int c_copy[BREED][CITY2];
	int i, j;
	float all = 0.0;

	for (i = 0; i < BREED; i++) {
		all += value[i];
	}

	for (i = 0; i < BREED; i++) {
		value[i] = value[i] / all;
	}

	for (i = 0; i < BREED; i++) {
		selected[i] = wheelSelection2(value);
	}

	for(i=0;i<BREED;i++)
		for (j = 0; j < CITY2; j++) {
			c_copy[i][j] = c[i][j];
		}

	for (i = 0; i < BREED; i++) {
		for (j = 0; j < CITY2; j++) {
			c[i][j] = c_copy[selected[i]][j];
		}
	}
}

//����·��
void swap(int x[], int y[], int site) {
	int temp, i;
	for (i = site + 1; i < CITY2; i++) {
		temp = x[i];
		x[i] = y[i];
		y[i] = temp;
	}
}

//���䣬�趨������ʣ����̶ľ����Ƿ���
//������ԣ�������λ�ĳ��нڵ���ͬ�Һ�̴���1����������������·��
void jiaopei(int c[BREED][CITY2], struct headnode *city_list) {
	float jiaopeigailv[BREED];
	int i, j, count = 0;	//count��¼�������
	int site = CITY2 - 5;	//����λ
	
	for (i = 0; i < BREED; i++) {
		jiaopeigailv[i] = rand0_1();
		if (jiaopeigailv[i] < JIAOPEI) {
			jiaopeigailv[i] = 1;
			count++;
		}else
			jiaopeigailv[i] = 0;
	}
	i = 0;
	while ((count % 2) != 0) {
		jiaopeigailv[i++] = 0;
		count--;
	}
	
	//���ܴ���û��һ��·�ܽ�������Σ����ǲ�Ҫ��
	for (i = 0; i < BREED; i++) {
		if (jiaopeigailv[i] == 1) {
			for (j = i+1; j < BREED; j++) {
				//ûд��̴���һ������
				if (c[i][site] == c[j][site] && city_list[site].tail_length > 1) {
					//��������λ������·��
					swap(c[i], c[j], site);
					jiaopeigailv[i] = 0;
					count--;
					jiaopeigailv[j] = 0;
					count--;
				}
			}
		}	
	}
}

//���죬�趨������ʣ�ֻ�Էֲ������
//Ҫ�жϵ��Ƿ��Ƿֲ�㣬��Ҫ��¼�õ�ֱ�Ӻ������
//�ٶ�ÿ����Ⱥֻ����һ��
void bianyi(int c[BREED][CITY2], struct headnode *city_list) {
	float bianyigailv[BREED][CITY2];
	int i, j, k, l;
	node *temp = NULL;
	for (i = 0; i < BREED; i++) {
		for (j = 0; j < CITY2; j++)
			bianyigailv[i][j] = rand0_1();
	}

	for (i = 0; i < BREED; i++) {
		//j����0��ʼ����Ϊ�����0��ʼ
		for (j = 1; j < CITY2; j++) {
			//���ﵽ������ʣ������õ㣬�õ��̴���һ��
			if (bianyigailv[i][j] < BIANYI && c[i][j] == 1 && city_list[j].tail_length > 1) {
				do {
					k = randx(CITY2);	//k��Ҫ����Ľ��
				} while (city_list[k].tail_length > 1);
				do {
					l = randx(CITY2);	//�����Ľ��
				} while (city_list[k].tail_length > 1);

				

				break;	//ֻ����һ��
			}
		}
	}
}

void geneticAlgorithm() {
	int c[BREED][CITY2] = { 0 };	//��Ⱥ
	float value[BREED] = { 0.0 };	//����ÿ����Ⱥ��Ӧ��
	srand((unsigned)time(NULL));

	//�ڽӱ�
	/*
0
1 6
2 4
3 5
-1 0
1 
4 1
-1 0
2
4 1
-1 0
3
5 2
-1 0
4
6 9
7 7
-1 0
5
7 4
-1 0
6
8 2
-1 0
7
8 4
-1 0
8
-1 0
	*/

	//��ʼ����Ⱥ��ͼ
	head city_list;
	createHeadNode(city_list);
	//print_linklist(city_list);
	init(c, city_list);

	//��Ӧ������
	evaluate(c, value, city_list);

	//ѭ��
	int i, j;
	for (i = 0; i < TOTAL_TURN2; i++) {
		//ѡ��
		select(c, value);

		//����
		jiaopei(c, city_list);

		//����
		bianyi(c, city_list);

		//����
		evaluate(c, value, city_list);
	}

	for (i = 0; i < BREED; i++) {
		printf("\n��%d��Ⱥ��", i);
		for (j = 0; j < CITY2; j++) {
			if (c[i][j] == 1)
				printf("%d ", j);
		}
	}	
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

	geneticAlgorithm();

	return 0;
}