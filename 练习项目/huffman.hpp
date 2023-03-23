#ifndef	HUFFMAN_HPP
#define HUFFMAN_HPP
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include <iomanip>
using namespace std;
//������������
template<class T>
struct HFN {
	T weight;//��Ž��Ȩֵ
	int left=-1;//��¼�����±�
	int right=-1;//��¼�Һ����±�
	int parent=-1;//��¼���ڵ��±�
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
	Huffman(const vector<T>& data);//�����������
	void getMin(int& min1, int& min2, int end);//��ȡȨֵ��С���������,endΪ������ֹ�±�(������)
	void showHFT();//��ӡ��������
	void HuffmanCode(char _left,char _right);//����������,_left,_right������������
	void backTrack(char _left,char _right,int start);
	void ShowCode();//��ӡ����������
private:
	vector<HFN<T>> HFT;//����
	int node_size;//��¼ԭʼ������
	T MAX;//��¼���������������ֵ
	string path;//��¼���ݹ����еĹ���������
	map<int, string> code;//��¼���Ĺ���������
};
template<class T>
void Huffman<T>::getMin(int& min1, int& min2, int end) {
	T minD1 = MAX;
	T minD2 = MAX;
	for (int i = 0;i <end;i++) {
		//��������������û�и����Ľ��
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
	//��֧��int,float,double;�������ʹ����
	//ģ������Ϊint
	if (typeid(T) == typeid(int)) {
		MAX = INT_MAX;
	}
	//ģ������Ϊfloat
	else if (typeid(T) == typeid(float)) {
		MAX = FLT_MAX;
	}
	//ģ������Ϊdouble
	else if (typeid(T) == typeid(double)) {
		MAX = DBL_MAX;
	}
	else {
		cerr << "��֧�ָ���������!" << endl;
		return;
	}
	//dataΪ���ݶԣ�firstΪ��ֵ��secondΪȨ��
	vector<T>nodes = data;
	//������������洢����Ŀռ��С
	int size = 2 * nodes.size() - 1;
	HFT.resize(size);
	//�����ݽ�������������
	int i = 0;
	for (;i < nodes.size();i++) {
		HFT[i].weight = nodes[i];
	}
	//��������
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
	int root = 2*(node_size-1);//���ڵ��±�
	backTrack(_left, _right, root);
}
template<class T>
void Huffman<T>::showHFT()
{
	cout << "index  weight  parent  LTree  RTree" << endl;
	cout << left;     //��������
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