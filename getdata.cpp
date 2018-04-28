#include <bits/stdc++.h>

using namespace std;

int tot = 0;
struct silicon {
	void input() {
		id = tot++;
		scanf("%s", factory);
		scanf("%s", number);
		scanf("%s", type);
		scanf("%s", quality_s);
		//quality = strcmp(quality_s, "杂质") ? 1 : 0;
		scanf("%d", &length);
		scanf("%d", &matrix);
		group = 0;
	}
	void output() {
		printf("%4s\t\t", factory);
		printf("%4s\t\t", number);
		printf("%2s\t\t", type);
		printf("%4s\t\t", quality_s);
		printf("%4d\t\t", length);
		printf("%4d\t\t", matrix);
		printf("\n");
	}
	int id;//硅棒序号
	char factory[11];
	char number[11];
	char type[11];
	char quality_s[11];
	//int quality;
	int length;
	int matrix;
	int group;//拼接方案组号
	int cut;
	// bool  operator < (const silicon &a)const {
	// 	return length < a.length;
	// }
};
vector<silicon> a;

int main(int argc, char const *argv[])
{
	freopen("51.in", "r", stdin);
	freopen("51.out", "w", stdout);
	a.clear();
	silicon in;
	tot = 0;
	while (tot < 300) {
		// data-mod2-1.dat
		// in.input();
		// if (!strcmp(in.factory,"包头")
		// 	&& (!strcmp(in.type,"B")||!strcmp(in.type,"C"))
		// 	&&!strcmp(in.quality_s,"正常")
		// 	){
		// 	in.output();
		// }
		// data-mod2-2.dat
		// in.input();
		// if ((!strcmp(in.factory,"包头")||!strcmp(in.factory,"银和"))
		// 	&& (!strcmp(in.type,"B")||!strcmp(in.type,"C"))
		// 	&& (!strcmp(in.quality_s,"正常")||!strcmp(in.quality_s,"杂质"))
		// 	){
		// 	in.output();
		// }
		// a.push_back(in);
		// data-mod2-3.dat
		in.input();
		if ((!strcmp(in.factory,"银和"))
			&& (!strcmp(in.type,"A")||!strcmp(in.type,"B")||!strcmp(in.type,"C"))
			&& (!strcmp(in.quality_s,"正常"))
			){
			in.output();
		}
		a.push_back(in);
	}

	return 0;
}