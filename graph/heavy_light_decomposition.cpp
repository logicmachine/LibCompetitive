#include <vector>
#include <stack>
#include <utility>
#include <cmath>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct DecomposedTree {
	int parent;				// in raw graph
	vector<int> children;	// in decomposed graph
	vector<int> nodes;
	int depth;
};

vector<DecomposedTree> heavy_light_decomposition(
	const vector< vector<int> > &conn)
{
	int n = conn.size();
	// Subtree size calculation
	vector<int> subtree_size(n);
	vector<bool> passed(n);
	vector<bool> gathered(n);
	stack<pii> count_stack;
	count_stack.push(pii(0, 0));
	while(!count_stack.empty()){
		pii p = count_stack.top();
		count_stack.pop();
		if(p.second == 0){
			passed[p.first] = true;
			count_stack.push(pii(p.first, 1));
			for(int i = 0; i < conn[p.first].size(); ++i){
				if(passed[conn[p.first][i]]){ continue; }
				count_stack.push(pii(conn[p.first][i], 0));
			}
		}else{
			int sum = 1;
			gathered[p.first] = true;
			for(int i = 0; i < conn[p.first].size(); ++i){
				if(!gathered[conn[p.first][i]]){ continue; }
				sum += subtree_size[conn[p.first][i]];
			}
			subtree_size[p.first] = sum;
		}
	}
	// Decomposition
	vector<DecomposedTree> result;
	vector<int> mapping(n, -1);
	stack<pii> decompose_stack;
	decompose_stack.push(pii(0, -1));
	while(!decompose_stack.empty()){
		pii p = decompose_stack.top();
		decompose_stack.pop();
		int index = result.size();
		result.push_back(DecomposedTree());
		DecomposedTree &dt = result.back();
		if(p.second >= 0){
			result[mapping[p.second]].children.push_back(index);
		}
		dt.parent = p.second;
		dt.depth = (p.second < 0 ? 0 : (result[mapping[p.second]].depth + 1));
		int cur = p.first;
		while(cur >= 0){
			dt.nodes.push_back(cur);
			int st_size = subtree_size[cur], threshold = st_size / 2;
			int heavy_edge = -1;
			for(int i = 0; i < conn[cur].size(); ++i){
				if(subtree_size[conn[cur][i]] > st_size){ continue; }
				mapping[cur] = index;
				if(heavy_edge < 0 && subtree_size[conn[cur][i]] >= threshold){
					heavy_edge = conn[cur][i];
				}else{
					decompose_stack.push(pii(conn[cur][i], cur));
				}
			}
			cur = heavy_edge;
		}
	}
	return result;
}

#include <iostream>

using namespace std;

void dump(const vector<DecomposedTree> &tree, int n, int depth){
	const DecomposedTree &dt = tree[n];
	for(int i = 0; i < depth; ++i){ cout << "  "; }
	cout << dt.parent << ", (";
	for(int i = 0; i < dt.nodes.size(); ++i){ cout << " " << dt.nodes[i]; }
	cout << " )" << endl;
	for(int i = 0; i < dt.children.size(); ++i){
		dump(tree, dt.children[i], depth + 1);
	}
};

int main(){
	vector< vector<int> > conn(10);

#define ADD_EDGE(a, b) \
	conn[a].push_back(b); \
	conn[b].push_back(a);

	ADD_EDGE(0, 1);
	ADD_EDGE(0, 4);
	ADD_EDGE(0, 5);
	ADD_EDGE(1, 2);
	ADD_EDGE(1, 3);
	ADD_EDGE(5, 6);
	ADD_EDGE(6, 7);
	ADD_EDGE(6, 8);
	ADD_EDGE(8, 9);

#undef ADD_EDGE

	vector<DecomposedTree> result = heavy_light_decomposition(conn);
	dump(result, 0, 0);

	return 0;
}

