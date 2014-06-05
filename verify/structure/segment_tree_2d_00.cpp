// AOJ 1068 - School of Killifish (MLE)
#include <iostream>
#include <vector>
#include "structure/segment_tree_2d.h"
#include "structure/segment_tree/min.h"

using libcomp::structure::SegmentTree2D;
using libcomp::structure::MinSegmentTreeTraits;
typedef SegmentTree2D< MinSegmentTreeTraits<int> > MinSegmentTree2D;

int main(){
	ios_base::sync_with_stdio(false);
	while(true){
		size_t r, c, q;
		cin >> r >> c >> q;
		if(r == 0 && c == 0 && q == 0){ break; }
/*
		vector< vector<int> > grid(r, vector<int>(c));
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){ cin >> grid[i][j]; }
		}
		MinSegmentTree2D st(grid.begin(), grid.end());
*/
		MinSegmentTree2D st(r, c);
		for(int i = 0; i < r; ++i){
			for(int j = 0; j < c; ++j){
				int aij;
				cin >> aij;
				st.update(i, j, aij);
			}
		}
		while(q--){
			int y0, x0, y1, x1;
			cin >> y0 >> x0 >> y1 >> x1;
			cout << st.query(x0, y0, x1 + 1, y1 + 1) << endl;
		}
	}
	return 0;
}

