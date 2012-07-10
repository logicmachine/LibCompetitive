#include <map>

/* development:
 *     /\  /\  /\  /\  /\
 *    / 0\/ 1\/ 2\/ 3\/ 4\
 *    --------------------
 *   /\ 5/\ 6/\ 7/\ 8/\ 9/
 *  /10\/11\/12\/13\/14\/
 *  --------------------
 *  \15/\16/\17/\18/\19/
 *   \/  \/  \/  \/  \/
 *
 * roll / direction (top view)
 *   direction = 0:   direction = 1:
 *     1 /\ 0             0
 *      /xx\             ----
 *      ----             \xx/
 *        2             1 \/ 2
 */

using namespace std;

class Dice20 {

private:
	struct Face3 {
		int index[3];
		Face3(int f = -1, int s = -1, int t = -1){
			index[0] = f; index[1] = s; index[2] = t;
		}
		void rotate(){
			int tmp = index[0];
			index[0] = index[1];
			index[1] = index[2];
			index[2] = tmp;
		}
	};
	static Face3 TABLE[3][20][20];
	static bool s_initialized;
	static void init_table(int t, int f1, int f2, int f3){
		Face3 f(f1, f2, f3);
		for(int i = 0; i < 3; ++i){
			for(int j = 0; j < 3; ++j){
				TABLE[j][t][f.index[j]] = f;
			}
			f.rotate();
		}
	}


public:
	int dir, top, first;

	Dice20(int d, int t, int f) : dir(d), top(t), first(f) {
		if(!s_initialized){
			s_initialized = true;
			for(int i = 0; i < 5; ++i){
				// 0 - 4
				init_table(i, (i + 1) % 5, (i + 4) % 5, i + 5);
				// 5 - 9
				init_table(i + 5, i, i + 10, 10 + (i + 1) % 5);
				// 10 - 14
				init_table(i + 10, i + 5, 5 + (i + 4) % 5, i + 15);
				// 15 - 19
				init_table(i + 15, i + 10, 15 + (i + 4) % 5, 15 + (i + 1) % 5);
			}
		}
	}

	void roll(int f){
		const Face3 &cur = TABLE[0][top][first];
		const Face3 &next = TABLE[(f + 1 + dir) % 3][cur.index[f]][top];
		top = cur.index[f];
		first = next.index[0];
		dir = 1 - dir;
	}
	int neighbor(int f){ return TABLE[0][top][first].index[f]; }

};

Dice20::Face3 Dice20::TABLE[3][20][20];
bool Dice20::s_initialized = false;

#include <cstdio>

int main(){
	Dice20 dice(0, 0, 1);
	while(true){
		if(dice.dir == 0){
			printf("1:%3d     0:%3d\n", dice.neighbor(1), dice.neighbor(0));
			printf("       %3d\n", dice.top);
			printf("     2:%3d\n", dice.neighbor(2));
		}else{
			printf("     0:%3d\n", dice.neighbor(0));
			printf("       %3d\n", dice.top);
			printf("1:%3d     2:%3d\n", dice.neighbor(1), dice.neighbor(2));
		}
		int v;
		if(!~scanf("%d", &v)){ break; }
		if(v < 0){
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			dice = Dice20(a, b, c);
		}else{
			dice.roll(v);
		}
	}
	return 0;
}

