#include <vector>
#include <string>
#include <queue>

using namespace std;

struct HuffmanNode {
	int value, occur;
	HuffmanNode *left, *right;
	HuffmanNode(
		int v = 0, int o = 0, HuffmanNode *l = NULL, HuffmanNode *r = NULL) :
		value(v), occur(o), left(l), right(r)
	{ }
};

struct NodePtrComparator {
	bool operator()(const HuffmanNode *a, const HuffmanNode *b) const {
		return a->occur > b->occur;
	}
};

void huffman_dfs(HuffmanNode *ptr, const string &s, vector<string> &result){
	if(ptr->value >= 0){
		result[ptr->value] = s;
	}else{
		huffman_dfs(ptr->left, s + "0", result);
		huffman_dfs(ptr->right, s + "1", result);
	}
	delete ptr;
}

vector<string> huffman_coding(const vector<int> &occurence){
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, NodePtrComparator> pq;
	for(int i = 0; i < occurence.size(); ++i){
		pq.push(new HuffmanNode(i, occurence[i]));
	}
	while(pq.size() > 1){
		HuffmanNode *n1 = pq.top(); pq.pop();
		HuffmanNode *n2 = pq.top(); pq.pop();
		pq.push(new HuffmanNode(-1, n1->occur + n2->occur, n1, n2));
	}
	vector<string> result(occurence.size());
	huffman_dfs(pq.top(), "", result);
	return result;
}

#include <iostream>

int main(){
	int m, x;
	cin >> m;
	vector<int> occur(m);
	while(cin >> x){ ++occur[x]; }
	vector<string> code = huffman_coding(occur);
	for(int i = 0; i < m; ++i){
		cout << i << " : " << code[i] << endl;
	}
	return 0;
}

