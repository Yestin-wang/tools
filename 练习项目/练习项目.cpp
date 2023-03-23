#include <algorithm>
#include <utility>
#include "tools.h"
using namespace std; 
enum alpha {
	alpha_a=0, alpha_b, alpha_c, alpha_d, alpha_e, alpha_f, alpha_g, alpha_h
};
enum alpha aa = alpha_a;
enum alpha bb = alpha_b;
enum alpha cc = alpha_c;
enum alpha dd = alpha_d;
enum alpha ee = alpha_e;
enum alpha ff = alpha_f;
enum alpha gg = alpha_g;
enum alpha hh = alpha_h;

int main()
{
	/*vector<vector<int>> edge{ {bb,cc},{dd,ee},{ff,gg},{},{hh},{},{},{} };
	vector<char>node{ 'a','b','c','d','e','f','g','h'};
	Graphic G(8, 7, edge, node);
	G.BFSTraversal(bb);*/
	vector<double> v{ 32,3,6,10,7,19,2,21 };
	Huffman<double> tree(v);
	tree.showHFT();
	tree.HuffmanCode('0', '1');
	tree.ShowCode();



}