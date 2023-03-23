#ifndef	GRAPHIC_HPP
#define GRAPHIC_HPP
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//�ڽӱ��ʵ��
using VexType = char;//��������������
using EageType = int;//�߽��Ȩֵ����������
typedef struct ENode {
	int adjVex;//��βָ��Ķ����±�(��0��ʼ)
	EageType weight;//�ߵ�Ȩֵ
	struct ENode* next;
}ENode;
typedef struct VNode {
	VexType data;//����洢������
	ENode* firstedge;//��һ���ڽӱ�
}VNode;
//typedef struct AdjList {
//	vector<VNode> adjList;
//	int vexNum, edgeNum;
//}Adjlist;
class Graphic {
private:
	int vexNum, edgeNum;//�ڵ��� ����
	vector<VNode> adjList;//�ڽӱ�
	vector<int> visited;
public:
	//ͨ�����е�ͼ����ͼ
	//G_index �洢�ڽӱ�
	//G_node �洢�������
	Graphic(int Vnum, int Enum, vector<vector<int> > G_index, vector<VexType> G_node);
	Graphic(const Graphic& G);//�������캯��
	void createGraphic(vector<vector<int> > G_index, vector<VexType> G_node);//����ͼ
	void putWeight(vector<vector<EageType> >G_weight);//Ϊͼ�еı߸���Ȩ��
	int firstNeighbor(int v);//�����±�Ϊv�Ķ���ĵ�һ���ڽӵ��±꣬��û�з���-1
	int nextNeighbor(ENode *e);//�����ڽӱ�v����һ�ڽӱߵ��ڽӵ��±꣬��û�з���-1
	void visit(int v);//��ӡ���ֵ;//���ʽ��
	//������ȱ���
	void DFS(int v);
	void DFSTraversal(int v=0); //��ָ���±�ֵ�Ľ�㴦��ʼ����
	//������ȱ���
	void BFS(int v);
	void BFSTraversal(int v=0);//��ָ���±�ֵ�Ľ�㴦��ʼ����
};
Graphic::Graphic(int Vnum, int Enum, vector<vector<int> > G_index, vector<VexType> G_node) {
	if (Vnum != G_node.size()&&Vnum != G_index.size())
		cerr << "����ͼ�Ľ������Ƿ���ȷ!" << endl;
	else {
		vexNum = Vnum;
		edgeNum = Enum;
		adjList.resize(vexNum);
		createGraphic(G_index, G_node);
	}
}
Graphic::Graphic(const Graphic& G) {
	vexNum = G.vexNum;
	edgeNum = G.edgeNum;
	adjList = G.adjList;
}
void Graphic::createGraphic(vector<vector<int> > G_index,vector<VexType> G_node) {
	for (int i = 0;i < vexNum;i++) {
		adjList[i].data = G_node[i];
		int j = 0;
		int len = G_index[i].size();//��ȡ��ǰ�����ڽӱ߸���
		ENode* node = nullptr;
		//�����ڽӱ�
		if (len) {
			adjList[i].firstedge = new ENode({ G_index[i][j],0,nullptr });
			j++;
			node = adjList[i].firstedge;
		}
		while (j<len) {
			node->next = new ENode({ G_index[i][j],0,nullptr });
			j++;
		}	
	}
}
void Graphic::putWeight(vector<vector<EageType> >G_weight) {

}
void Graphic::visit(int v) { 
	cout << adjList[v].data << " "; 
}
int Graphic::firstNeighbor(int v) {
	if (adjList[v].firstedge)
		return adjList[v].firstedge->adjVex;
	else
		return -1;
}
int Graphic::nextNeighbor(ENode *e) {
	if (e->next)
		return e->next->adjVex;
	else
		return -1;
}

void Graphic::DFS(int v) {
	visited[v] = true;
	visit(v);
	ENode *e=adjList[v].firstedge;
	//��������㷨���ƻ��ݵ���·
	for (int i = firstNeighbor(v);i >= 0;i = nextNeighbor(e),e=e->next) {
		if (!visited[i])
			DFS(i);
	}
}
void Graphic::DFSTraversal(int v) {
	if (v >= vexNum) {
		cerr << "������Χ!" << endl;
		return;
	}
	visited.resize(vexNum, false);
	//���η��ʽ��
	for (int i = 1;i <= vexNum;v=(v+i)%vexNum,i++) {
		if(!visited[v])//���ѷ��ʹ����ټ���
		DFS(v);
	}
}
void Graphic::BFS(int v) {
	//����ڽӵ�Ķ���
	queue<int>buff;
	//v�����ʣ������
	visit(v);
	visited[v] = true;
	buff.push(v);
	while (buff.size()) {
		int index = buff.front();
		buff.pop();
		for (ENode* eage = adjList[index].firstedge;eage;eage = eage->next) {
			//����ڽӵ�δ���ʣ����ʲ����õ����
			if(!visited[eage->adjVex]){
				visit(eage->adjVex);
				visited[eage->adjVex] = true;
				buff.push(eage->adjVex);
			}
		}
	}
}
void Graphic::BFSTraversal(int v) {
	if (v >= vexNum) {
		cerr << "������Χ!" << endl;
		return;
	}
	visited.resize(vexNum, false);
	for (int i = 0;i < vexNum;v = (v + i) % vexNum, i++) {
		if (!visited[v])
			BFS(v);
	}
}
#endif