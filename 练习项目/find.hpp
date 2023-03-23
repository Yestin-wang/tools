#ifndef	FIND_HPP
#define FIND_HPP
#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
//�������ṹ
//����������





//KMP
//getNext��next����
int* getNext(string str) {
	int str_len = str.size();
	int* next = new int[str_len];//Ϊ����next���������ڴ�ռ�
	next[0] = 0;
	next[1] = 0;
	int prefix = 0;
	int index = 2;
	//�Ƚ�ǰ׺���׺
	while (index < str_len) {
		if (str[index - 1] == str[prefix]) {
			prefix++;
			next[index] = prefix;
			index++;
		}
		else {
			if (prefix == 0) {
				next[index] = prefix;
				index++;
			}
			else
				prefix = next[prefix - 1];
		}
	}
	return next;
}
int KMP(string pattern, string str) {
	//�õ�next����
	int* next = getNext(pattern);
	int i = 0, j = 0;//���������ֱ����������ģʽ�����±�
	//������ģʽ���бȽ�
	while (i < str.size()) {
		//�ַ�ƥ��������ģʽ������������
		if (str[i] == pattern[j] || j == 0) {
			i++;j++;
			if (j >= pattern.size()) {
				break;
			}
		}
		//��ƥ�䣬�����������䣬ģʽ����������next��������Ӧ�ĸı�
		else {

			j = next[j];
		}
	}
	delete[] next;
	if (j == pattern.size())
		return i - pattern.size();
	else return -1;
}
#endif