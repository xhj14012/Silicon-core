#include <bits/stdc++.h>
#define _ ios_a::sync_with_stdio(0);cin.tie(0);
#define QH freopen("qh.in", "r", stdin);
#define SS ios::sync_with_stdio(false);
#define LL long long
#define INF (LL)1e16
#define eps 1e-6
#define pi acos(-1)
#define debug(x) cout<<#x<<"="<<x<<" "
#define MP(x,y) make_pair(x,y)
#define MAX(a,b) a=max(a,b)
#define MIN(a,b) a=min(a,b)
//#define mp make_pair
#define pb push_back
#define gi(a) scanf("%d",&a);
#define gi2(a,b) scanf("%d%d",&a,&b);
#define gi3(a,b,c) scanf("%d%d%d",&a,&b,&c);
#define gl(a) scanf("%I64d",&a);
#define gs(s) scanf("%s",s);
#define wi(a) printf("%d\n",a);
#define wi2(a,b) printf("%d %d\n",a,b);
#define wl(a) printf("%I64d\n",a);
#define CM(a,b) memcpy(a,b,sizeof(b))
#define CL(a) memset(a,0,sizeof(a))
#define CLINF(a) memset(a, 0x3f3f3f3f, sizeof(a))
#define PII pair <int, int>
#define PIII pair <int, PII>
#define PIIII pair <int,PIII>
using namespace std;
char title[100];
const int minlen = 685;
const int maxlen = 695;
#define fi first
#define se second.first
//#define th second.second

#define third second.second.first
#define forth second.second.second
// PIII mpiii(int a, int b, int c) {
// 	return mp(a, mp(b, c));
// }
PIIII mp(int a, int b, int c, int d = 0) {
	return make_pair(a, make_pair(b, make_pair(c, d)));
}
int cnt = 0;
int tot;
vector<string> factory_cant_mix;
struct Part {
	void input() {
		id = tot++;
		cin >> factory;
		cin >> number;
		cin >> type;
		string quality_s; cin >> quality_s;
		quality = (quality_s == "normal") ? 0 : 1;
		cin >> length;
		cin >> matrix;
		group = 0;
		//output();
	}
	void output() {
		cout << id << "\t";
		cout << factory << "\t";
		cout << number << "\t";
		cout << type << "\t";
		cout << ((quality == 0) ? "normal  " : "impurity") << "\t";
		cout << length << "\t";
		cout << matrix << "\t";
		cout << group << endl;
	}
	int id;//硅棒序号
	string factory;
	string number;
	char type;
	int quality;
	int length;
	int matrix;
	int group;//拼接方案组号
	// bool  operator < (const Part &a)const {
	// 	return length < a.length;
	// }
};

bool cmp_length(const Part a, const Part b) {
	return a.length < b.length;
}
bool cmp_group(const Part a, const Part b) {
	return a.group < b.group;
}
bool cmp_id(const Part a, const Part b) {
	return a.id < b.id;
}


int check(int val) {
	if (val < minlen) return -1;
	else if (val >= minlen && val <= maxlen) return 1;
	//else if (val > maxlen)
	return 0;
}


// vector<PIII> comb;
// void comb_erase(int p) {
// 	for (std::vector<PIII>::iterator it = comb.begin(); it != comb.end();) {
// 		if (it->se == p || it->th == p) {
// 			it = comb.erase(it);
// 		} else {
// 			++it;
// 		}
// 	}
// }
// vector<PIII> comb4;
// void comb4_erase(int p) {
// 	for (std::vector<PIII>::iterator it = comb4.begin(); it != comb4.end();) {
// 		if (it->se == p || it->th == p) {
// 			it = comb4.erase(it);
// 		} else {
// 			++it;
// 		}
// 	}
// }
vector<Part> calc4(vector<Part> v, bool if_cut = 1) {

	vector<Part> result;
	result.clear();
	for (std::vector<Part>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			result.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	sort(v.begin(), v.end(), cmp_length);
	// for (std::vector<Part>::iterator it = v.begin(); it != v.end(); ++it) {
	// 	it->output();
	// }
	//vector<PIII> comb;
	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 2; i < size; ++i) { //组对(i+j+k,i,j,k)
		for (int j = 1; j < i; ++j) {
			for (int k = 0; k < j; ++k) {
				comb.pb(mp(v[i].length + v[j].length + v[k].length, i, j, k));
			}
		}
	}
	sort(comb.begin(), comb.end());
	//reverse(comb.begin(),comb.end());
	for (int p = v.size() - 1; p >= 0; --p) {
		//if (comb.size() == 0) break;
		//comb_erase(p);
		if (v[p].group != 0) {
			continue;
			//result.pb(v[p]);
			//comb_erase(p);
		} else {
			vector<PIIII>::iterator mit, it_low, it_upper;
			it_low = lower_bound(comb.begin(), comb.end(), mp(minlen - v[p].length, 0, 0, 0));
			it_upper = upper_bound(comb.begin(), comb.end(), mp(maxlen - v[p].length + 1, 0, 0, 0));
			--it_upper;
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != it_upper && it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && v[it->forth].group == 0) {
						if (mit == comb.end() || (it->se < mit->se && check(mit->fi + v[p].length) != 1)) { //启发式剪枝，调优点
							mit = it;
						}
					}
				}
			}
			if (check(mit->fi + v[p].length) != 1) {
				mit = comb.end();
			}
			if (mit == comb.end()) {
				v[p].group = -1;
				//result.pb(v[p]);
				//comb_erase(p);
			} else {
				cnt++;
				v[p].group = cnt;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				v[mit->forth].group = cnt;
				// result.pb(v[p]);
				// result.pb(v[mit->se]);
				// result.pb(v[mit->th]);
				//int t1 = mit->se;
				//int t2 = mit->th;
				//comb_erase(p);
				//comb_erase(mit->se);//坑！
				//comb_erase(mit->th);
				//comb_erase(t1);
				//comb_erase(t2);
			}
		}
	}
	//it[1] = lower_bound(comb.begin(), comb.end(), mpiii(1, 0, 0));
	// for (int i = 0; i < comb.size(); ++i) {
	// 	//printf("%d %d %d\n", comb[i].fi,comb[i].se,comb[i].th);
	// }

	for (int p = 0; p < size; ++p) {
		result.pb(v[p]);
	}
	// printf("result:\n");
	// sort(result.begin(), result.end(), cmp_group);
	// for (int i = 0; i < result.size(); ++i) {
	// 	//cout << i << " ";
	// 	result[i].output();
	// }
	return result;
}
vector<Part> calc3(vector<Part> v, bool if_cut = 0) {

	vector<Part> result;
	result.clear();
	for (std::vector<Part>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			result.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	sort(v.begin(), v.end(), cmp_length);
	// for (std::vector<Part>::iterator it = v.begin(); it != v.end(); ++it) {
	// 	it->output();
	// }
	//vector<PIII> comb;
	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 1; i < size; ++i) { //组对(i+j,i,j)
		for (int j = 0; j < i; ++j) {
			comb.pb(mp(v[i].length + v[j].length, i, j));
		}
	}
	sort(comb.begin(), comb.end());
	//reverse(comb.begin(),comb.end());
	for (int p = v.size() - 1; p >= 0; --p) {
		//if (comb.size() == 0) break;
		//comb_erase(p);
		if (v[p].group != 0) {
			continue;
			//result.pb(v[p]);
			//comb_erase(p);
		} else {
			vector<PIIII>::iterator mit, it_low, it_upper;
			it_low = lower_bound(comb.begin(), comb.end(), mp(minlen - v[p].length, 0, 0));
			it_upper = upper_bound(comb.begin(), comb.end(), mp(maxlen - v[p].length + 1, 0, 0));
			--it_upper;
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != it_upper && it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0) {
						if (mit == comb.end() || (it->se < mit->se && check(it->fi + v[p].length) == 1)) { //启发式剪枝，调优点
							mit = it;
						}
					}
				}
			}
			if (check(mit->fi + v[p].length) != 1) {
				mit = comb.end();
			}
			if (mit == comb.end()) {
				v[p].group = -1;
				//result.pb(v[p]);
				//comb_erase(p);
			} else {
				cnt++;
				v[p].group = cnt;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				// result.pb(v[p]);
				// result.pb(v[mit->se]);
				// result.pb(v[mit->th]);
				//int t1 = mit->se;
				//int t2 = mit->th;
				//comb_erase(p);
				//comb_erase(mit->se);//坑！
				//comb_erase(mit->th);
				//comb_erase(t1);
				//comb_erase(t2);
			}
		}
	}
	//it[1] = lower_bound(comb.begin(), comb.end(), mpiii(1, 0, 0));
	// for (int i = 0; i < comb.size(); ++i) {
	// 	//printf("%d %d %d\n", comb[i].fi,comb[i].se,comb[i].th);
	// }

	for (int p = 0; p < size; ++p) {
		result.pb(v[p]);
	}
	// printf("result:\n");
	// sort(result.begin(), result.end(), cmp_group);
	// for (int i = 0; i < result.size(); ++i) {
	// 	//cout << i << " ";
	// 	result[i].output();
	// }
	return result;
}
void report(vector<Part> a) {
	printf("/******report******\n");
	sort(a.begin(), a.end(), cmp_group);
	//a = a;
	reverse(a.begin(), a.end());
	for (int i = 0, g = 0; i <= a.size(); ++i) {
		if (a[i].group <= 0) continue;
		g++;
		printf("group%d:\n", g);
		int sum = a[i].length;
		a[i].output();
		while (a[i].group == a[i + 1].group) {
			sum += a[i + 1].length;
			a[i + 1].output();
			++i;
		}
		printf("sum=%d\n", sum);
	}
	printf("/******report******\n");
}
void gao() {
	//fgets(title,99,stdin);
	cin.getline(title, 99);
	vector <Part> a;
	a.clear();
	while (!cin.eof()) {
		//for (int i = 0; i < 540; ++i) {
		Part t;
		t.input();
		a.push_back(t);
	}
	cnt = 0;
	tot = 0;
	a = calc3(a);
	//report(a);
	a = calc4(a);
	report(a);
}

int main(int argc, char const *argv[]) {
	//freopen("data.dat", "r", stdin);
	freopen("test3.dat", "r", stdin);
	freopen("test.out", "w", stdout);
	//ifstream infile;
	//infile.open("data.dat",ios::in);
	// //variable
//    locale cn("zh_CN.UTF-8");
//    wstring text, str1, str2;
//    wifstream is;
//    wofstream os;
//    is.imbue(cn);
//    os.imbue(cn);
	gao();
	//infile.close();
	return 0;
}