#ifndef	FIND_HPP
#define FIND_HPP
#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
//定义树结构
//二叉搜索树





//KMP
//getNext求next数组
int* getNext(string str) {
	int str_len = str.size();
	int* next = new int[str_len];//为申请next数组申请内存空间
	next[0] = 0;
	next[1] = 0;
	int prefix = 0;
	int index = 2;
	//比较前缀与后缀
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
	//得到next数组
	int* next = getNext(pattern);
	int i = 0, j = 0;//两个索引分别代表主串和模式串的下标
	//主串与模式进行比较
	while (i < str.size()) {
		//字符匹配则主串模式串索引均后移
		if (str[i] == pattern[j] || j == 0) {
			i++;j++;
			if (j >= pattern.size()) {
				break;
			}
		}
		//不匹配，主串索引不变，模式串索引根据next数组作相应的改变
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