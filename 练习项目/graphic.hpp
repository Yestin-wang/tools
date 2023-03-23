#ifndef	GRAPHIC_HPP
#define GRAPHIC_HPP
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//邻接表的实现
using VexType = char;//顶点结点数据类型
using EageType = int;//边结点权值的数据类型
typedef struct ENode {
	int adjVex;//边尾指向的顶点下标(从0开始)
	EageType weight;//边的权值
	struct ENode* next;
}ENode;
typedef struct VNode {
	VexType data;//顶点存储的数据
	ENode* firstedge;//第一个邻接边
}VNode;
//typedef struct AdjList {
//	vector<VNode> adjList;
//	int vexNum, edgeNum;
//}Adjlist;
class Graphic {
private:
	int vexNum, edgeNum;//节点数 边数
	vector<VNode> adjList;//邻接表
	vector<int> visited;
public:
	//通过已有的图构建图
	//G_index 存储邻接表
	//G_node 存储结点数据
	Graphic(int Vnum, int Enum, vector<vector<int> > G_index, vector<VexType> G_node);
	Graphic(const Graphic& G);//拷贝构造函数
	void createGraphic(vector<vector<int> > G_index, vector<VexType> G_node);//创建图
	void putWeight(vector<vector<EageType> >G_weight);//为图中的边赋予权重
	int firstNeighbor(int v);//访问下标为v的顶点的第一个邻接点下标，若没有返回-1
	int nextNeighbor(ENode *e);//访问邻接边v的下一邻接边的邻接点下标，若没有返回-1
	void visit(int v);//打印结点值;//访问结点
	//深度优先遍历
	void DFS(int v);
	void DFSTraversal(int v=0); //从指定下标值的结点处开始遍历
	//广度优先遍历
	void BFS(int v);
	void BFSTraversal(int v=0);//从指定下标值的结点处开始遍历
};
Graphic::Graphic(int Vnum, int Enum, vector<vector<int> > G_index, vector<VexType> G_node) {
	if (Vnum != G_node.size()&&Vnum != G_index.size())
		cerr << "请检查图的结点个数是否正确!" << endl;
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
		int len = G_index[i].size();//获取当前结点的邻接边个数
		ENode* node = nullptr;
		//创建邻接表
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
	//深度优先算法类似回溯的套路
	for (int i = firstNeighbor(v);i >= 0;i = nextNeighbor(e),e=e->next) {
		if (!visited[i])
			DFS(i);
	}
}
void Graphic::DFSTraversal(int v) {
	if (v >= vexNum) {
		cerr << "超出范围!" << endl;
		return;
	}
	visited.resize(vexNum, false);
	//依次访问结点
	for (int i = 1;i <= vexNum;v=(v+i)%vexNum,i++) {
		if(!visited[v])//若已访问过不再继续
		DFS(v);
	}
}
void Graphic::BFS(int v) {
	//存放邻接点的队列
	queue<int>buff;
	//v结点访问，入队列
	visit(v);
	visited[v] = true;
	buff.push(v);
	while (buff.size()) {
		int index = buff.front();
		buff.pop();
		for (ENode* eage = adjList[index].firstedge;eage;eage = eage->next) {
			//如果邻接点未访问，访问并将该点入队
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
		cerr << "超出范围!" << endl;
		return;
	}
	visited.resize(vexNum, false);
	for (int i = 0;i < vexNum;v = (v + i) % vexNum, i++) {
		if (!visited[v])
			BFS(v);
	}
}
#endif