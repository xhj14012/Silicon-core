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
int cut_num;
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
		cut = 0;
		//output();
	}
	void output() {
		cout << id << "\t";
		cout << factory << "\t";
		cout << number << "\t";
		cout << type << "\t";
		cout << ((quality == 0) ? "normal  " : "impurity") << "\t";
		cout << length << "\t";
		//cout << matrix << "\t";
		cout << group << "\t";
		cout << (cut ? "cut" : "-") << endl;
	}
	int id;//硅棒序号
	string factory;
	string number;
	char type;
	int quality;
	int length;
	int matrix;
	int group;//拼接方案组号
	int cut;
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
//
vector<Part> calc4(vector<Part> v, int if_cut) {

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
	Part v0, v1, v2;
	while (cut_num) {
		if (v.size() <= 4) {
			break;
		}
		sort(v.begin(), v.end(), cmp_length);
		reverse(v.begin(), v.end());
		v0 = v[0]; v1 = v[1]; v2 = v[2];
		v.erase(v.begin());
		v.erase(v.begin());
		v.erase(v.begin());
		int add = v0.length + v1.length + v2.length;
		int need = minlen - add;
		for (std::vector<Part>::iterator it = v.end(); it != v.begin(); --it) {
			if (check(it->length + add) == 1) {
				cnt++;
				v0.group = cnt;
				v1.group = cnt;
				v2.group = cnt;
				it->group = cnt;
				result.pb(*it);
				break;

			} else if (check(it->length + add) == 0) {
				cnt++;
				cut_num--;
				v0.group = cnt;
				v1.group = cnt;
				v2.group = cnt;
				it->cut = 1;
				int tmp = it->length - need;
				it->length = tmp;
				it->length = need;
				it->group = cnt;

				result.pb(*it);
				it->length = tmp;
				it->group = 0;
				break;
			}
		}
		result.pb(v0);
		result.pb(v1);
		result.pb(v2);
	}
	for (int p = 0; p < v.size(); ++p) {
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
vector<Part> calc3(vector<Part> v, int if_cut) {

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
	Part v0, v1;
	while (cut_num) {
		if (v.size() <= 3) {
			break;
		}
		sort(v.begin(), v.end(), cmp_length);
		reverse(v.begin(), v.end());
		v0 = v[0]; v1 = v[1];
		v.erase(v.begin());
		v.erase(v.begin());
		int add = v0.length + v1.length;
		int need = minlen - add;
		for (std::vector<Part>::iterator it = v.end(); it != v.begin(); --it) {
			if (check(it->length + add) == 1) {
				cnt++;
				v0.group = cnt;
				v1.group = cnt;
				it->group = cnt;
				result.pb(*it);
				break;

			} else if (check(it->length + add) == 0) {
				cnt++;
				cut_num--;
				v0.group = cnt;
				v1.group = cnt;
				it->cut = 1;
				int tmp = it->length - need;
				it->length = tmp;
				//rest.pb(*it);
				it->length = need;
				it->group = cnt;

				result.pb(*it);
				it->length = tmp;
				it->group = 0;
				//v.erase(it);
				break;
			}
		}
		result.pb(v0);
		result.pb(v1);
	}
	for (int p = 0; p < v.size(); ++p) {
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

vector<Part> calc4(vector<Part> v) {

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
vector<Part> calc3(vector<Part> v) {

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
	//reverse(a.begin(), a.end());
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
vector<Part> calc(vector<Part> a) {
	a = calc3(a);
	//report(a);
	a = calc4(a);
	//report(a);
	a = calc3(a, 1);
	//report(a);
	a = calc4(a, 1);
	//report(a);
	return a;
}
void select() {
	
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
	cut_num = 100;
	a = calc(a);
	report(a);
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

/*
test.dat
factory   number type	quality	length	matrix
baotou		3601	A	impurity	174	36
baotou		3601	A	impurity	117	36
baotou		6501	A	normal  	235	36
baotou		8701	A	normal  	255	36
baotou		5501	A	impurity	260	36
baotou		7801	A	normal  	265	36
baotou		4801	A	impurity	222	36
baotou		7801	A	normal  	49	36
baotou		3601	A	impurity	83	36
baotou		8701	A	impurity	172	36
baotou		4801	A	impurity	246	36
baotou		7801	A	impurity	40	36
baotou		5501	A	impurity	273	36
baotou		7801	A	impurity	161	36
baotou		4801	A	normal  	87	36
baotou		5501	A	normal  	250	36
baotou		4801	A	normal  	262	36
baotou		7801	A	normal  	260	36
baotou		4801	A	impurity	90	36
baotou		8701	A	normal  	80	36
baotou		7801	A	normal  	263	36
baotou		8701	A	impurity	89	36
baotou		7501	A	impurity	260	36
baotou		7501	A	normal  	270	36
baotou		7501	A	impurity	266	36
baotou		6501	A	impurity	271	36
baotou		3101	A	normal  	53	36
baotou		5401	A	normal  	76	36
baotou		5401	A	impurity	182	36
yinhe		3702	A	impurity	263	36
yinhe		3101	A	impurity	263	36
yinhe		5401	A	normal  	267	36
yinhe		4701	A	normal  	269	36
yinhe		3702	A	normal  	259	36
yinhe		4701	A	impurity	267	36
yinhe		5001	A	normal  	264	36
yinhe		5001	A	normal  	253	36
yinhe		5001	A	normal  	237	36
yinhe		5401	A	normal  	263	36
yinhe		6401	A	normal  	114	36
yinhe		3101	A	impurity	218	36
yinhe		7101	A	impurity	233	36
yinhe		6502	A	impurity	270	36
yinhe		6401	A	impurity	266	36
yinhe		6401	A	impurity	259	36
yinhe		3702	A	normal  	151	36
yinhe		5207	A	impurity	186	36
yinhe		5102	A	impurity	260	36
yinhe		4701	A	impurity	59	36
yinhe		4701	A	normal  	131	36
yinhe		4802	A	normal  	263	36
yinhe		2301	A	normal  	191	36
yinhe		6101	A	impurity	128	36
yinhe		6101	A	normal  	176	36
yinhe		3302	A	impurity	262	36
yinhe		2201	A	normal  	264	36
yinhe		3302	A	normal  	234	36
yinhe		2201	A	impurity	225	36
yinhe		7701	B	impurity	232	36
yinhe		2201	B	impurity	261	36
yinhe		7201	B	normal  	255	36
yinhe		6101	B	normal  	256	36
yinhe		7101	B	normal  	172	36
yinhe		4802	B	impurity	238	36
yinhe		6101	B	normal  	82	36
yinhe		6101	B	normal  	97	36
yinhe		2301	B	normal  	284	36
yinhe		7101	B	normal  	94	36
yinhe		2102	B	normal  	64	36
yinhe		2302	B	normal  	49	36
yinhe		7401	B	impurity	133	36
yinhe		2302	B	impurity	133	36
yinhe		1601	B	normal  	46	36
yinhe		7502	B	normal  	230	36
yinhe		1601	B	normal  	50	36
yinhe		7602	B	normal  	71	36
yinhe		1601	B	normal  	138	36
yinhe		1601	B	normal  	260	36
yinhe		7602	B	normal  	199	36
yinhe		2102	B	normal  	177	36
yinhe		7602	B	impurity	154	36
yinhe		2302	B	normal  	75	36
yinhe		7401	B	normal  	252	36
yinhe		1601	B	impurity	194	36
yinhe		2302	B	normal  	170	36
yinhe		2302	B	normal  	260	36
yinhe		1002	B	normal  	245	36
yinhe		2102	B	impurity	245	36
yinhe		1002	B	normal  	239	36
yinhe		7ZU086	B	impurity	293	36
yinhe		7ZU086	B	impurity	302	36
yinhe		7YY085	B	impurity	280	36
yinhe		7YY085	B	impurity	281	36
yinhe		7YY085	B	impurity	282	36
yinhe		7YY085	B	normal  	284	36
yinhe		7ZU086	B	impurity	297	36
yinhe		7YY085	B	impurity	283	36
yinhe		7YG083	B	impurity	291	36
yinhe		7YG083	B	impurity	234	36
yinhe		7YG083	B	normal  	292	36
yinhe		7YG083	B	normal  	286	36
yinhe		7XE086	B	normal  	297	36
yinhe		7XE086	B	normal  	290	36
yinhe		7XE086	B	normal  	290	36
yinhe		7XE086	B	normal  	290	36
yinhe		7XE086	B	normal  	290	36
yinhe		7XE086	B	normal  	294	36
yinhe		7XK079	B	impurity	299	36
yinhe		7XK079	B	normal  	302	36
yinhe		7XK079	B	normal  	299	36
yinhe		7XK079	B	normal  	236	36
yinhe		7XK079	B	normal  	56	36
yinhe		7XK079	B	normal  	210	36
yinhe		7YY085	B	normal  	271	36
yinhe		7XK079	B	normal  	302	36
yinhe		7ZJ085	B	normal  	205	36
yinhe		7ZJ085	B	normal  	286	36
yinhe		7ZJ085	B	normal  	285	36
yinhe		7XH086	B	normal  	281	36
yinhe		7XH086	B	normal  	281	36
yinhe		7ZJ085	B	normal  	282	36
yinhe		7ZJ085	B	impurity	289	36
yinhe		7XW082	B	normal  	66	36
yinhe		7XN085	B	normal  	278	36
yinhe		7XN085	B	normal  	285	36
yinhe		7ZJ085	B	impurity	290	36
yinhe		7XN085	B	normal  	263	36
yinhe		7XN085	B	impurity	245	36
yinhe		7XN085	B	impurity	280	36
yinhe		7XN085	B	impurity	196	36
yinhe		7YD086	B	normal  	299	36
yinhe		7YD086	B	normal  	294	36
yinhe		7YD086	B	impurity	295	36
yinhe		7XL086	B	normal  	292	36
yinhe		7XP087	B	impurity	287	36
yinhe		7XP087	B	normal  	295	36
yinhe		7XL086	B	normal  	283	36
yinhe		7XL086	B	normal  	288	36
yinhe		7YD086	B	impurity	267	36
yinhe		7YD086	B	normal  	288	36
yinhe		7XL086	B	impurity	237	36
yinhe		7XL086	B	impurity	246	36
yinhe		7XP087	B	normal  	293	36
yinhe		7XP087	B	impurity	291	36
yinhe		7XL086	B	normal  	230	36
yinhe		7XP087	B	normal  	291	36
yinhe		7XP087	B	impurity	284	36
yinhe		7XW087	B	normal  	266	36
yinhe		7XW087	B	normal  	263	36
yinhe		7XW087	B	normal  	280	36
yinhe		7XW087	B	normal  	279	36
yinhe		7YB080	B	normal  	281	36
yinhe		7YB080	B	impurity	252	36
yinhe		7YT077	B	impurity	289	36
yinhe		7YS080	B	impurity	243	36
yinhe		7ZL087	B	impurity	263	36
yinhe		7ZL087	B	impurity	266	36
yinhe		7ZL087	B	normal  	274	36
yinhe		7ZL087	B	impurity	269	36
yinhe		7ZL087	B	normal  	277	36
yinhe		7YT077	B	impurity	295	36
yinhe		7YS080	B	normal  	278	36
yinhe		7XM084	B	normal  	285	36
yinhe		7YF087	B	impurity	280	36
yinhe		7YF087	B	impurity	259	36
yinhe		7XM084	B	normal  	285	36
yinhe		7YF087	B	normal  	285	36
yinhe		7XM084	B	normal  	215	36
yinhe		7XM084	B	normal  	287	36
yinhe		7XM084	B	normal  	278	36
yinhe		7XM084	B	normal  	195	36
yinhe		7XK080	B	normal  	270	36
yinhe		7XK080	B	normal  	262	36
yinhe		7XK080	B	normal  	290	36
yinhe		7XK080	B	normal  	239	36
yinhe		7XK080	B	normal  	283	36
yinhe		7XS076	B	impurity	299	36
yinhe		7ZT087	B	normal  	172	36
baotou		7ZE088	B	normal  	291	36
baotou		8902	B	impurity	214	36
baotou		6002	B	impurity	265	36
baotou		6002	B	normal  	276	36
baotou		5202	B	normal  	253	36
baotou		2602	B	impurity	275	36
baotou		8902	B	impurity	259	36
baotou		2602	B	normal  	272	36
baotou		2602	B	impurity	259	36
baotou		8902	B	normal  	261	36
baotou		4502	B	impurity	235	36
baotou		4502	B	normal  	261	36
baotou		2602	B	normal  	270	36
baotou		4502	B	normal  	262	36
baotou		2602	B	normal  	258	36
baotou		2602	B	impurity	96	36
baotou		2602	B	impurity	184	36
baotou		6002	B	impurity	252	36
baotou		6002	B	impurity	147	36
baotou		6002	B	impurity	272	36
baotou		6002	B	impurity	152	36
baotou		6002	B	normal  	147	36
baotou		6002	B	impurity	265	36
baotou		6002	B	normal  	52	36
baotou		6002	B	impurity	63	36
baotou		2602	B	normal  	262	36
baotou		4502	B	normal  	266	36
baotou		6002	B	normal  	255	36
baotou		6002	B	normal  	247	36
baotou		4002	B	impurity	266	36
baotou		5401	B	normal  	251	36
baotou		4002	B	impurity	280	36
baotou		7101	B	normal  	232	36
baotou		6401	B	normal  	273	36
baotou		4002	B	normal  	242	36
baotou		4002	B	normal  	269	36
baotou		4002	B	normal  	254	36
baotou		5401	B	normal  	260	36
baotou		5401	B	normal  	220	36
baotou		5401	B	normal  	280	36
baotou		5401	B	impurity	287	36
baotou		5401	B	normal  	276	36
baotou		5401	B	normal  	286	36
baotou		5401	B	normal  	273	36
baotou		5401	B	normal  	281	36
baotou		5401	B	normal  	278	36
baotou		5401	B	normal  	264	36
baotou		4002	B	normal  	55	36
baotou		7201	B	normal  	235	36
baotou		3702	B	normal  	231	36
baotou		7201	B	normal  	119	36
baotou		3702	B	normal  	282	36
baotou		4002	B	normal  	264	36
baotou		3702	B	normal  	266	36
baotou		4002	B	impurity	222	36
baotou		4002	B	impurity	280	36
baotou		4002	B	normal  	87	36
baotou		4002	B	normal  	163	36
baotou		7201	B	normal  	135	36
baotou		3702	B	impurity	253	36
baotou		4002	B	normal  	250	36
baotou		1501	B	normal  	278	36
baotou		6901	B	impurity	252	36
baotou		1501	B	impurity	285	36
baotou		6901	B	impurity	195	36
baotou		1501	B	impurity	288	36
baotou		1501	B	normal  	74	36
baotou		1501	B	normal  	178	36
baotou		1501	B	normal  	261	36
baotou		1501	B	impurity	263	36
baotou		6901	B	normal  	89	36
baotou		1501	B	impurity	270	36
baotou		1501	B	impurity	271	36
baotou		6901	B	impurity	241	36
baotou		1501	B	impurity	176	36
baotou		1501	B	impurity	85	36
baotou		6901	B	impurity	267	36
baotou		6901	B	impurity	282	36
baotou		3601	B	impurity	125	36
baotou		3601	B	impurity	279	36
baotou		3601	B	impurity	266	36
baotou		3601	B	impurity	254	36
baotou		3601	B	impurity	262	36
baotou		3601	B	impurity	215	36
baotou		3601	B	impurity	238	36
baotou		3601	B	normal  	266	36
baotou		3601	B	normal  	265	36
baotou		7501	B	normal  	280	36
baotou		7501	B	impurity	191	36
baotou		7501	B	impurity	135	36
baotou		7501	B	impurity	182	36
baotou		7YY085	B	normal  	285	36
baotou		7YY085	B	impurity	284	36
baotou		7YU082	B	normal  	266	36
baotou		7YU082	B	normal  	279	36
baotou		7XN086	B	impurity	295	36
baotou		7XN086	B	impurity	294	36
baotou		7YU082	B	normal  	284	36
baotou		7XN086	B	normal  	298	36
baotou		7YI077	B	normal  	200	36
baotou		7XD089	B	normal  	302	36
baotou		7YU077	B	normal  	197	36
baotou		7YI077	B	normal  	191	36
baotou		7ZJ086	B	normal  	171	36
baotou		7ZJ086	B	normal  	263	36
baotou		7ZJ086	B	normal  	292	36
baotou		7XD089	B	normal  	302	36
baotou		7YD089	B	normal  	305	36
baotou		7YO083	B	normal  	287	36
baotou		7YO083	B	normal  	288	36
baotou		7YO083	B	normal  	291	36
baotou		7XD089	B	normal  	305	36
baotou		7ZA088	B	normal  	304	36
baotou		7ZA088	B	normal  	292	36
baotou		7XO088	B	normal  	291	36
baotou		7XO088	B	normal  	288	36
baotou		7XO088	B	normal  	282	36
baotou		7XO088	B	normal  	285	36
baotou		7XJ083	B	normal  	254	36
baotou		7ZA088	B	normal  	295	36
baotou		7YG083	C	impurity	288	36
baotou		7XE086	C	impurity	289	36
baotou		7XU064	C	normal  	274	36
baotou		7XM083	C	normal  	300	36
baotou		7XU064	C	normal  	270	36
baotou		7XU064	C	normal  	288	36
baotou		7XS074	C	normal  	85	36
baotou		7XU064	C	normal  	277	36
baotou		7XM083	C	normal  	304	36
baotou		7XK079	C	impurity	294	36
baotou		7XK079	C	normal  	294	36
baotou		7XR085	C	normal  	293	36
baotou		7YP081	C	normal  	295	36
baotou		7YP081	C	normal  	299	36
baotou		7YP081	C	normal  	297	36
baotou		7YP081	C	normal  	276	36
baotou		7XR085	C	normal  	287	36
baotou		7YU085	C	impurity	65	36
baotou		7YC085	C	normal  	279	36
baotou		7XS074	C	normal  	207	36
baotou		7YC085	C	normal  	277	36
baotou		7YC085	C	normal  	282	36
baotou		7ZV087	C	impurity	237	36
baotou		7ZV087	C	normal  	93	36
baotou		7YC085	C	normal  	281	36
baotou		7XK079	C	impurity	298	36
baotou		7YY085	C	normal  	282	36
baotou		7XK079	C	normal  	86	36
baotou		7XK079	C	impurity	299	36
baotou		7XK079	C	normal  	301	36
baotou		7XK079	C	normal  	204	36
baotou		7ZJ085	C	normal  	293	36
baotou		7XH086	C	normal  	297	36
baotou		7XH086	C	normal  	269	36
baotou		7ZJ085	C	impurity	298	36
baotou		7XN085	C	impurity	277	36
baotou		7XN085	C	normal  	222	36
baotou		7YD086	C	impurity	295	36
baotou		7YD086	C	normal  	297	36
baotou		7XL086	C	normal  	286	36
baotou		7XL086	C	impurity	296	36
baotou		7XP087	C	impurity	296	36
baotou		7XP087	C	impurity	295	36
baotou		7ZV086	C	normal  	290	36
baotou		7ZV086	C	normal  	166	36
baotou		7ZV086	C	impurity	296	36
baotou		7ZV086	C	normal  	288	36
baotou		7YP080	C	normal  	291	36
baotou		7ZV086	C	normal  	125	36
baotou		7YU081	C	normal  	261	36
baotou		7YU081	C	normal  	290	36
baotou		7YU081	C	normal  	288	36
baotou		7YH088	C	normal  	308	36
baotou		7YH088	C	normal  	306	36
baotou		7YU081	C	normal  	290	36
baotou		7XR084	C	normal  	290	36
baotou		7XR084	C	normal  	291	36
baotou		7YH088	C	impurity	297	36
baotou		7YH088	C	normal  	315	36
baotou		7XR084	C	normal  	288	36
baotou		7XR084	C	normal  	293	36
baotou		7YY085	C	normal  	268	36
baotou		7YU082	C	normal  	287	36
baotou		7YU082	C	normal  	285	36
baotou		7XN086	C	normal  	290	36
baotou		7YU082	C	impurity	281	36
baotou		7XN086	C	normal  	290	36
baotou		7XN086	C	normal  	286	36
baotou		7YI077	C	normal  	141	36
baotou		7XD089	C	normal  	231	36
baotou		7YI077	C	normal  	276	36
baotou		7XD089	C	normal  	243	36
baotou		7YI077	C	normal  	302	36
baotou		7XO088	C	normal  	279	36
baotou		7XO088	C	impurity	272	36
baotou		7XO088	C	normal  	258	36
baotou		7XJ083	C	normal  	279	36
baotou		7ZJ086	C	normal  	249	36
baotou		7ZJ086	C	normal  	123	36
baotou		7ZJ086	C	normal  	92	36
baotou		7ZJ086	C	normal  	74	36
baotou		7ZJ086	C	normal  	247	36
baotou		7ZJ086	C	normal  	290	36
baotou		7YR087	C	normal  	241	36
baotou		7YR087	C	normal  	236	36
baotou		7YR087	C	normal  	250	36
baotou		7XD089	C	normal  	311	36
baotou		7YO083	C	normal  	275	36
baotou		7YO083	C	normal  	288	36
baotou		7YO083	C	normal  	287	36
baotou		7XD089	C	normal  	307	36
baotou		7YO083	C	normal  	275	36
baotou		7XJ083	C	normal  	264	36
baotou		7ZA088	C	normal  	261	36
baotou		7XO088	C	normal  	283	36
baotou		7ZA088	C	normal  	106	36
baotou		7YG083	C	normal  	290	36
baotou		7XE086	C	impurity	269	36
baotou		7XU064	C	normal  	234	36
baotou		7XM083	C	impurity	293	36
baotou		7XU064	C	impurity	267	36
baotou		7XU064	C	normal  	275	36
baotou		7XU064	C	normal  	233	36
baotou		7XV084	C	normal  	271	36
baotou		7XK079	C	normal  	282	36
baotou		7XK079	C	normal  	299	36
baotou		7YY085	C	impurity	258	36
baotou		7XR085	C	normal  	274	36
baotou		7XR085	C	normal  	231	36
baotou		7XR085	C	normal  	288	36
baotou		7YP081	C	normal  	300	36
baotou		7YP081	C	normal  	275	36
baotou		7YP081	C	normal  	278	36
baotou		7YP081	C	normal  	302	36
baotou		7XR085	C	normal  	276	36
baotou		7ZV087	C	normal  	282	36
baotou		7ZV087	C	normal  	231	36
baotou		7YC085	C	normal  	277	36
baotou		7YC085	C	normal  	281	36
yinhe		7YC085	C	normal  	270	36
yinhe		7ZV087	C	normal  	258	36
yinhe		7ZV087	C	normal  	285	36
yinhe		7XK079	C	normal  	301	36
yinhe		7XK079	C	impurity	292	36
yinhe		7XK079	C	normal  	283	36
yinhe		7XK079	C	normal  	278	36
yinhe		7YY085	C	normal  	277	36
yinhe		7ZJ085	C	normal  	296	36
yinhe		7ZJ085	C	impurity	286	36
yinhe		7XN085	C	impurity	282	36
yinhe		7XN085	C	normal  	289	36
yinhe		7YD086	C	normal  	292	36
yinhe		7XL086	C	normal  	296	36
yinhe		7XL086	C	impurity	277	36
yinhe		7XP087	C	impurity	294	36
yinhe		7XP087	C	impurity	127	36
yinhe		7ZV086	C	normal  	265	36
yinhe		7ZV086	C	normal  	265	36
yinhe		7ZV086	C	normal  	286	36
yinhe		7ZV086	C	impurity	217	36
yinhe		7YP080	C	normal  	291	36
yinhe		7YP080	C	normal  	284	36
yinhe		7YU081	C	normal  	112	36
yinhe		7YU081	C	normal  	280	36
yinhe		7YU081	C	normal  	239	36
yinhe		7YU081	C	normal  	239	36
yinhe		7YU081	C	normal  	87	36
yinhe		7YH088	C	normal  	300	36
yinhe		7YH088	C	normal  	290	36
yinhe		7YH088	C	impurity	295	36
yinhe		7501	C	normal  	284	36
yinhe		6501	C	impurity	273	36
yinhe		6501	C	normal  	280	36
yinhe		7501	C	normal  	270	36
yinhe		7501	C	normal  	280	36
yinhe		7501	C	normal  	278	36
yinhe		7501	C	impurity	274	36
yinhe		7501	C	normal  	278	36
yinhe		5501	C	impurity	235	36
yinhe		6501	C	impurity	165	36
yinhe		5501	C	normal  	288	36
yinhe		5501	C	impurity	290	36
yinhe		5501	C	normal  	274	36
yinhe		5501	C	impurity	290	36
yinhe		5501	C	impurity	285	36
yinhe		5501	C	normal  	281	36
yinhe		5501	C	normal  	287	36
yinhe		7501	C	normal  	274	36
yinhe		6501	C	impurity	263	36
yinhe		6501	C	impurity	287	36
yinhe		6501	C	normal  	262	36
yinhe		6501	C	normal  	284	36
yinhe		6501	C	impurity	278	36
yinhe		6501	C	normal  	282	36
yinhe		6501	C	impurity	263	36
yinhe		6002	C	normal  	270	36
yinhe		5202	C	normal  	270	36
yinhe		4502	C	normal  	257	36
yinhe		8902	C	normal  	239	36
yinhe		6002	C	impurity	272	36
yinhe		8902	C	normal  	248	36
yinhe		8902	C	normal  	256	36
yinhe		8902	C	impurity	250	36
yinhe		8902	C	normal  	251	36
yinhe		8902	C	normal  	253	36
yinhe		8902	C	normal  	254	36
yinhe		2602	C	normal  	261	36
yinhe		4502	C	normal  	270	36
yinhe		4502	C	normal  	260	36
yinhe		2602	C	normal  	220	36
yinhe		4502	C	impurity	261	36
yinhe		8902	C	normal  	252	36
yinhe		8902	C	impurity	257	36
yinhe		4502	C	normal  	240	36
yinhe		4502	C	normal  	259	36
yinhe		4502	C	normal  	261	36
yinhe		8902	C	impurity	249	36
yinhe		4502	C	normal  	239	36
yinhe		6002	C	normal  	270	36
yinhe		2602	C	normal  	228	36
yinhe		8902	C	impurity	256	36
yinhe		5501	C	normal  	47	36
yinhe		7801	C	impurity	283	36
yinhe		7801	C	normal  	288	36
yinhe		7801	C	impurity	237	36
yinhe		7801	C	impurity	282	36
yinhe		5501	C	normal  	286	36
yinhe		5501	C	normal  	279	36
yinhe		5501	C	normal  	290	36
yinhe		5501	C	normal  	290	36
yinhe		5501	C	normal  	284	36
yinhe		5501	C	normal  	284	36
yinhe		7801	C	normal  	265	36
yinhe		5501	C	normal  	283	36
yinhe		6501	C	normal  	275	36
yinhe		6501	C	normal  	267	36
yinhe		6501	C	normal  	288	36
yinhe		6501	C	normal  	275	36
yinhe		5501	C	normal  	215	36
yinhe		5501	C	impurity	60	36
yinhe		7801	C	normal  	280	36
yinhe		7801	C	normal  	283	36
yinhe		7801	C	impurity	281	36
yinhe		6002	C	normal  	260	36
yinhe		6002	C	impurity	125	36
yinhe		6002	C	normal  	257	36
yinhe		6002	C	normal  	269	36
yinhe		4502	C	normal  	267	36
yinhe		6002	C	normal  	256	36
yinhe		4502	C	normal  	264	36
yinhe		4502	C	normal  	272	36
yinhe		4502	C	normal  	268	36
yinhe		4502	C	normal  	264	36
yinhe		6002	C	impurity	133	36
yinhe		6002	C	impurity	221	36
yinhe		6002	C	normal  	234	36
yinhe		4002	C	normal  	226	36
yinhe		4002	C	impurity	274	36
yinhe		4002	C	normal  	270	36
yinhe		4002	C	normal  	258	36

 */