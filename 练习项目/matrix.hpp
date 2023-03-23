#ifndef MATRIX_HPP
#define MATRIX_HPP
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
template<class T>
class Matrix {
public:
	//���캯��
	Matrix(int row, int line);
	Matrix(const Matrix& m);
	Matrix(int row, int line, const vector<T> nums);
	//��������Ļ�ȡ
	int getRow() const{ return m_row; }
	int getLine()const { return m_line; }
	T getValue(int i, int j) const{ return mat[i][j]; }
	//��������
	void MatPrint();//��ӡ
	void MatWrite(string file_name);//д���ı�
	//����Ķ���
	//void MatRead(string file_name);
	//��������
	Matrix operator +(const Matrix& p);
	Matrix operator -(const Matrix& p);
	Matrix operator *(const Matrix& p);
	Matrix &operator =(const Matrix& p);
private:
	vector< vector<T> > mat;
	int m_row;
	int m_line;
};

template<class T>
Matrix<T>::Matrix(int row, int line) {
	mat.resize(row, vector<T>(line, 0));
	m_row = row;
	m_line = line;
}
template<class T>
Matrix<T>::Matrix(const Matrix& m) {
	mat = m.mat;
	m_line = m.m_line;
	m_row = m.m_row;
}
template<class T>
Matrix<T>::Matrix(int row, int line, const vector<T> nums) {
	mat.resize(row, vector<T>(line, 0));
	if (nums.size() != (row * line))
		cerr << endl << "���ݸ�ʽ�����Ԫ�ظ�����ƥ��!" << endl;
	else {
		int cur = 0;
		for (int i = 0;i < row;i++)
			for (int j = 0;j < line;j++)
				mat[i][j] = nums[cur++];
		m_row = row;
		m_line = line;
	}
}
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix) {
	if (this->m_line != matrix.getLine() || this->m_row != matrix.getRow()) {
		cerr << endl << "�޷����!" << endl;
		return Matrix(0,0);
	}	
	Matrix tmp(this->m_row, this->m_line);
	for (int i = 0;i < this->m_row;i++)
		for (int j = 0;j < this->m_line;j++)
			tmp.mat[i][j] = this->mat[i][j] + matrix.mat[i][j];
	return tmp;
};
template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix) {
	if (this->m_line != matrix.getLine() || this->m_row != matrix.getRow()) {
		cerr << endl << "�޷����!" << endl;
		return Matrix(0, 0);
	}
	Matrix tmp(this->m_row, this->m_line);
	for (int i = 0;i < this->m_row;i++)
		for (int j = 0;j < this->m_line;j++)
			tmp.mat[i][j] = this->mat[i][j] - matrix.mat[i][j];
	return tmp;
};
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
	mat = m.mat;
	m_line = m.m_line;
	m_row = m.m_row;
	return *this;
};
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix) {
	int row = this->m_row;
	int line = matrix.m_line;
	if (this->m_line != matrix.m_row){
		cerr << endl << "�޷����!" << endl;
		return Matrix(0, 0);
	}
	Matrix tmp(row,line);
	for (int i = 0;i < this->m_row;i++)
		for (int j = 0;j < line;j++)
			for (int k = 0;k < line;k++)
				tmp.mat[i][j] += this->mat[i][k] * matrix.mat[k][j];
	return tmp;
};
template<class T>
void Matrix<T>::MatPrint() {
	cout << "{" << endl;
	for (int i = 0;i<m_row;i++) {
		cout << "[";
		for (int j = 0;j < m_line-1;j++)
			cout << mat[i][j] << ",";
		cout << mat[i][m_line - 1];
		cout << "]" << endl;
	}
	cout << "}" << endl;
}
template<class T>
void Matrix<T>::MatWrite(string file_name) {
	ofstream fout;
	fout.open(file_name,ios::app);
	if (!fout.is_open())
		cerr << endl<< "�ļ���ʧ��!" << endl;
	for (int i = 0;i < m_row;i++) {
		fout << "[ ";
		for (int j = 0;j < m_line - 1;j++)
			fout << mat[i][j] << ",";
		fout << mat[i][m_line - 1];
		fout << " ]" << endl;
	}
	fout.close();
}
#endif
