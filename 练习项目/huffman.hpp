#ifndef	HUFFMAN_HPP
#define HUFFMAN_HPP
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include <iomanip>
using namespace std;
//定义哈夫曼结点
template<class T>
struct HFN {
	T weight;//存放结点权值
	int left=-1;//记录左孩子下标
	int right=-1;//记录右孩子下标
	int parent=-1;//记录父节点下标
};
template<class T>
class HuffCmp {
public:
	bool operator()(HFN<T> val1, HFN<T> val2) {
		return val2.weight > val1.weight;
	}
};
template<class T>
class Huffman {
public:
	Huffman(const vector<T>& data);//构造哈夫曼树
	void getMin(int& min1, int& min2, int end);//求取权值最小的两个结点,end为结束截止下标(开区间)
	void showHFT();//打印哈夫曼树
	void HuffmanCode(char _left,char _right);//哈夫曼编码,_left,_right左右子树编码
	void backTrack(char _left,char _right,int start);
	void ShowCode();//打印哈夫曼编码
private:
	vector<HFN<T>> HFT;//结点表
	int node_size;//记录原始结点个数
	T MAX;//记录该数据类型最大数值
	string path;//记录回溯过程中的哈夫曼编码
	map<int, string> code;//记录结点的哈夫曼编码
};
template<class T>
void Huffman<T>::getMin(int& min1, int& min2, int end) {
	T minD1 = MAX;
	T minD2 = MAX;
	for (int i = 0;i <end;i++) {
		//检索区间内所有没有父结点的结点
		if (HFT[i].parent == -1) {
			if (minD1 > HFT[i].weight) {
				minD2 = minD1;
				min2 = min1;
				minD1 = HFT[i].weight;
				min1 = i;
			}
			else {
				if (minD2 > HFT[i].weight) {
					minD2 = HFT[i].weight;
					min2 = i;
				}
			}
		}
	}
}
template<class T>
Huffman<T>::Huffman(const vector<T>& data) {
	node_size = data.size();
	//仅支持int,float,double;更多类型待添加
	//模板类型为int
	if (typeid(T) == typeid(int)) {
		MAX = INT_MAX;
	}
	//模板类型为float
	else if (typeid(T) == typeid(float)) {
		MAX = FLT_MAX;
	}
	//模板类型为double
	else if (typeid(T) == typeid(double)) {
		MAX = DBL_MAX;
	}
	else {
		cerr << "不支持该数据类型!" << endl;
		return;
	}
	//data为数据对，first为键值，second为权重
	vector<T>nodes = data;
	//计算哈夫曼树存储所需的空间大小
	int size = 2 * nodes.size() - 1;
	HFT.resize(size);
	//将数据结点填入哈夫曼树
	int i = 0;
	for (;i < nodes.size();i++) {
		HFT[i].weight = nodes[i];
	}
	//哈夫曼树
	for (;i < size;i++) {
		int index1 = -1, index2 = -1;
		getMin(index1, index2, i);
		HFT[i].weight = HFT[index1].weight + HFT[index2].weight;
		HFT[i].left = index1;
		HFT[i].right = index2;
		HFT[index1].parent = i;
		HFT[index2].parent = i;
	}
}
template<class T>
void Huffman<T>::backTrack(char _left, char _right, int start) {
	if (start == -1)return;
	if (start < node_size) {
		code[start] = path;
		return;
	}
	path+= _left;
	backTrack(_left, _right, HFT[start].left);
	path.pop_back();
	path+= _right;
	backTrack(_left, _right, HFT[start].right);
	path.pop_back();

}
template<class T>
void Huffman<T>::HuffmanCode(char _left, char _right) {
	int root = 2*(node_size-1);//根节点下标
	backTrack(_left, _right, root);
}
template<class T>
void Huffman<T>::showHFT()
{
	cout << "index  weight  parent  LTree  RTree" << endl;
	cout << left;     //左对齐输出
	int m = HFT.size();
	for (int i = 0; i < m; i++) {
		cout << setw(5) << i << "  ";                       
		cout << setw(6) << HFT[i].weight << "  ";     
		cout << setw(6) << HFT[i].parent << "  ";
		cout << setw(6) << HFT[i].left << "  ";
		cout << setw(6) << HFT[i].right << "  " << endl;
	}
}
template<class T>
void Huffman<T>::ShowCode() {
	for (auto it : code) {
		cout << it.first << " : " << it.second << endl;
	}
}
#endif