#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
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
#define mp make_pair
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
using namespace std;
char title[100];
const int minlen = 685;
const int maxlen = 695;
#define fi first
#define se second.first
#define th second.second
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
		index = 0;
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
		cout << index << endl;
	}
	int id;//硅棒序号
	string factory;
	string number;
	char type;
	int quality;
	int length;
	int matrix;
	int index;//拼接方案组号
	// bool  operator < (const Part &a)const {
	// 	return length < a.length;
	// }
};

bool cmp_length(const Part a, const Part b) {
	return a.length < b.length;
}
bool cmp_index(const Part a, const Part b) {
	return a.index < b.index;
}
bool cmp_id(const Part a, const Part b) {
	return a.id < b.id;
}
vector <Part> base;
vector <Part> a, b, c;

int check(int val) {
	if (val < minlen) return -1;
	else if (val >= minlen && val <= maxlen) return 1;
	//else if (val > maxlen)
	return 0;
}
PIII mpiii(int a, int b, int c) {
	return mp(a, mp(b, c));
}
vector<PIII> comb3;
void comb3_erase(int p) {
	for (std::vector<PIII>::iterator it = comb3.begin(); it != comb3.end();) {
		if (it->se == p || it->th == p) {
			it = comb3.erase(it);
		} else {
			++it;
		}
	}
}
vector<Part> calc3(vector<Part> v, bool if_cut = 0) {
	vector<Part> result;
	result.clear();
	for (std::vector<Part>::iterator it = v.begin(); it != v.end();) {
		if (it->index > 0) {
			result.pb(*it);
			it = v.erase(it);
		} else {
			if (it->index == -1) {
				it->index = 0;
			}
			++it;
		}
	}
	sort(v.begin(), v.end(), cmp_length);
	// for (std::vector<Part>::iterator it = v.begin(); it != v.end(); ++it) {
	// 	it->output();
	// }
	//vector<PIII> comb3;
	comb3.clear();
	int size = v.size();
	for (int i = 1; i < size; ++i) { //组对(i+j,i,j)
		for (int j = 0; j < i; ++j) {
			comb3.pb(mpiii(v[i].length + v[j].length, i, j));
		}
	}
	sort(comb3.begin(), comb3.end());
	//reverse(comb3.begin(),comb3.end());
	for (int p = v.size() - 1; p >= 0; --p) {
		//if (comb3.size() == 0) break;
		//comb3_erase(p);
		if (v[p].index != 0) {
			continue;
			//result.pb(v[p]);
			//comb3_erase(p);
		} else {
			vector<PIII>::iterator mit, it_low, it_upper;
			it_low = lower_bound(comb3.begin(), comb3.end(), mpiii(minlen - v[p].length, 0, 0));
			it_upper = upper_bound(comb3.begin(), comb3.end(), mpiii(maxlen - v[p].length + 1, 0, 0));
			--it_upper;
			mit = comb3.end();
			if (it_low != comb3.end()) {
				for (std::vector<PIII>::iterator it = it_low; it!=it_upper&&it != comb3.end(); ++it) {
					if (v[it->se].index == 0 && v[it->th].index == 0) {
						if (mit == comb3.end() || it->se < mit->se) { //启发式剪枝，调优点
							mit = it;
						}
					}
				}
			}
			if (check(mit->fi + v[p].length) != 1) {
				mit = comb3.end();
			}
			if (mit == comb3.end()) {
				v[p].index = -1;
				//result.pb(v[p]);
				//comb3_erase(p);
			} else {
				cnt++;
				v[p].index = cnt;
				v[mit->se].index = cnt;
				v[mit->th].index = cnt;
				// result.pb(v[p]);
				// result.pb(v[mit->se]);
				// result.pb(v[mit->th]);
				//int t1 = mit->se;
				//int t2 = mit->th;
				//comb3_erase(p);
				//comb3_erase(mit->se);//坑！
				//comb3_erase(mit->th);
				//comb3_erase(t1);
				//comb3_erase(t2);
			}
		}
	}
	//it[1] = lower_bound(comb3.begin(), comb3.end(), mpiii(1, 0, 0));
	// for (int i = 0; i < comb3.size(); ++i) {
	// 	//printf("%d %d %d\n", comb3[i].fi,comb3[i].se,comb3[i].th);
	// }

	for (int p = 0; p < size; ++p) {
		result.pb(v[p]);
	}
	printf("result:\n");
	sort(result.begin(), result.end(), cmp_index);
	for (int i = 0; i < result.size(); ++i) {
		//cout << i << " ";
		result[i].output();
	}
	return result;
}

void gao() {
	//fgets(title,99,stdin);
	cin.getline(title, 99);
	base.clear();
	while (!cin.eof()) {
		//for (int i = 0; i < 540; ++i) {
		Part t;
		t.input();
		base.push_back(t);
	}
	cnt = 0;
	tot = 0;
	base = calc3(base);
	//base=calc4(base);
}

int main(int argc, char const *argv[]) {
	//freopen("data.dat", "r", stdin);
	freopen("test.dat", "r", stdin);
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