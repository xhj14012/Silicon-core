#include <bits/stdc++.h>
//#define _ ios_a::sync_with_stdio(0);cin.tie(0);
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
const int inf = 0x3f3f3f3f;

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
int min_eligible_len = 685;//最小合格长度
int max_eligible_len = 695;//最大合格长度
int rest_cut_num;
int max_cut_num;
int scrap_len;
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
		cut = 0;
	}
	void output() {
		printf("|%4s\t\t", factory);
		printf("|%4s\t\t", number);
		printf("|%2s\t\t", type);
		printf("|%4s\t\t", quality_s);
		printf("|%4d\t\t", length);
		printf("|%4d\t\t", group);
		printf("|%s\n", (cut ? "切" : ""));
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

bool cmp_length(const silicon a, const silicon b) {
	return a.length < b.length;
}
bool cmp_length_greater(const silicon a, const silicon b) {
	return a.length > b.length;
}
bool cmp_group(const silicon a, const silicon b) {
	return a.group < b.group;
}
bool cmp_id(const silicon a, const silicon b) {
	return a.id < b.id;
}
bool cmp_number(const silicon a, const silicon b) {
	return a.number < b.number;
}

vector<silicon> mg(vector<silicon> a, vector<silicon> b) {
	int size = b.size();
	for (int i = 0; i < size; ++i) {
		a.pb(b[i]);
	}
	return a;
}
int check(int val) {
	if (val < min_eligible_len) return -1;
	else if (val >= min_eligible_len && val <= max_eligible_len) return 1;
	return 0;//else if (val > max_len)
}
vector<silicon> finish;

vector<silicon> calc4_cut(vector<silicon> v) {
	vector<silicon> result;
	result.clear();
	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	silicon v0, v1, v2;
	while (rest_cut_num > 0) {
		if (v.size() < 4) {
			break;
		}
		sort(v.begin(), v.end(), cmp_length_greater);
		v0 = v[0];
		v1 = v[1];
		v2 = v[2];///
		v.erase(v.begin());
		v.erase(v.begin());
		v.erase(v.begin());///
		int add = v0.length + v1.length + v2.length;///
		//if (add > max_len) cout << "debug";
		int need = min_eligible_len - add;

		for (std::vector<silicon>::iterator it = v.end(); it != v.begin();) {
			--it;
			if (check(it->length + add) == 1) {
				cnt++;
				v0.group = cnt;
				v1.group = cnt;
				v2.group = cnt;///
				it->group = cnt;
				result.pb(*it);
				v.erase(it);
				break;
			} else if (check(it->length + add) == 0) {
				cnt++;
				rest_cut_num--;
				v0.group = cnt;
				v1.group = cnt;
				v2.group = cnt;///
				it->cut = 1;
				int rest = it->length - need;
				it->length = need;
				it->group = cnt;
				result.pb(*it);
				it->length = rest;
				if (rest < scrap_len) {//报废
					it->group = inf;
					v.erase(it);
				} else {
					it->group = 0;
				}
				break;
			}
		}
		result.pb(v0);
		result.pb(v1);
		result.pb(v2);///
	}
	v = mg(v, result);
	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	return v;
}
vector<silicon> calc3_cut(vector<silicon> v) {
	vector<silicon> result;
	result.clear();
	silicon v0, v1;
	while (rest_cut_num > 0) {
		if (v.size() < 3) {
			break;
		}
		sort(v.begin(), v.end(), cmp_length_greater);
		v0 = v[0]; v1 = v[1];
		v.erase(v.begin());
		v.erase(v.begin());
		int add = v0.length + v1.length;
		int need = min_eligible_len - add;
		for (std::vector<silicon>::iterator it = v.end(); it != v.begin();) {
			--it;
			if (check(it->length + add) == 1) {
				cnt++;
				v0.group = cnt;
				v1.group = cnt;
				it->group = cnt;
				result.pb(*it);
				v.erase(it);///
				break;
			} else if (check(it->length + add) == 0) {
				cnt++;
				rest_cut_num--;
				v0.group = cnt;
				v1.group = cnt;
				it->cut = 1;
				int rest = it->length - need;
				it->length = need;
				it->group = cnt;
				result.pb(*it);
				it->length = rest;
				if (rest < scrap_len) {//报废
					it->group = inf;
					v.erase(it);
				} else {
					it->group = 0;
				}
				break;
			}
		}
		result.pb(v0);
		result.pb(v1);
	}
	v = mg(v, result);
	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	// printf("result:\n");
	// sort(result.begin(), result.end(), cmp_group);
	// for (int i = 0; i < result.size(); ++i) {
	// 	//cout << i << " ";
	// 	result[i].output();
	// }
	return v;
}
vector<silicon> calc4_oppo(vector<silicon> v) {
	sort(v.begin(), v.end(), cmp_length);
	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 2; i < size; ++i) {
		for (int j = 1; j < i; ++j) {
			for (int k = 0; k < j; ++k) {
				comb.pb(mp(v[i].length + v[j].length + v[k].length, i, j, k));
			}
		}
	}
	sort(comb.begin(), comb.end());
	for (int p = v.size() - 1; p >= 0; --p) {
		if (v[p].group != 0) {
			continue;
		} else {
			vector<PIIII>::iterator mit, it_low, it_upper;
			it_low = lower_bound(comb.begin(), comb.end(), mp(min_eligible_len - v[p].length, 0, 0, 0));
			it_upper = upper_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 1, 0, 0, 0));
			--it_upper;
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != it_upper && it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && v[it->forth].group == 0 && p != it->se) {
						if (mit == comb.end() || (it->se >= mit->se && check(mit->fi + v[p].length) != 1)) { //启发式
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
			} else {
				cnt++;
				v[p].group = cnt;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				v[mit->forth].group = cnt;
			}
		}
	}

	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}

	return v;
}
vector<silicon> calc3_oppo(vector<silicon> v) {
	sort(v.begin(), v.end(), cmp_length);

	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 1; i < size; ++i) { //组对(i+j,i,j)
		for (int j = 0; j < i; ++j) {
			comb.pb(mp(v[i].length + v[j].length, i, j));
		}
	}
	sort(comb.begin(), comb.end());
	for (int p = v.size() - 1; p >= 0; --p) {
		if (v[p].group != 0) {
			continue;
		} else {
			vector<PIIII>::iterator mit, it_low, it_upper;
			it_low = lower_bound(comb.begin(), comb.end(), mp(min_eligible_len - v[p].length, 0, 0));
			it_upper = upper_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 1, 0, 0));
			--it_upper;
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != it_upper && it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && p != it->se) {
						if (mit == comb.end() || (it->se >= mit->se && check(it->fi + v[p].length) == 1)) { //启发式，调优点
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
			} else {
				cnt++;

				v[p].group = cnt;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
			}
		}
	}
	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	return v;
}
vector<silicon> calc4(vector<silicon> v) {
	sort(v.begin(), v.end(), cmp_length);
	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 2; i < size; ++i) {
		for (int j = 1; j < i; ++j) {
			for (int k = 0; k < j; ++k) {
				comb.pb(mp(v[i].length + v[j].length + v[k].length, i, j, k));
			}
		}
	}
	sort(comb.begin(), comb.end());
	for (int p = v.size() - 1; p >= 0; --p) {
		if (v[p].group != 0) {
			continue;
		} else {
			vector<PIIII>::iterator mit, it_low, it_upper;
			it_low = lower_bound(comb.begin(), comb.end(), mp(min_eligible_len - v[p].length, 0, 0, 0));
			it_upper = upper_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 1, 0, 0, 0));
			--it_upper;
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != it_upper && it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && v[it->forth].group == 0 && p != it->se) {
						if (mit == comb.end() || (it->se < mit->se && check(mit->fi + v[p].length) != 1)) { //启发式
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
			} else {
				cnt++;
				v[p].group = cnt;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				v[mit->forth].group = cnt;
			}
		}
	}

	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}

	return v;
}
vector<silicon> calc3(vector<silicon> v) {
	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	sort(v.begin(), v.end(), cmp_length);

	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 1; i < size; ++i) { //组对(i+j,i,j)
		for (int j = 0; j < i; ++j) {
			comb.pb(mp(v[i].length + v[j].length, i, j));
		}
	}
	sort(comb.begin(), comb.end());
	for (int p = v.size() - 1; p >= 0; --p) {
		if (v[p].group != 0) {
			continue;
		} else {
			vector<PIIII>::iterator mit, it_low, it_upper;
			it_low = lower_bound(comb.begin(), comb.end(), mp(min_eligible_len - v[p].length, 0, 0));
			it_upper = upper_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 1, 0, 0));
			--it_upper;
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != it_upper && it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && p != it->se) {
						if (mit == comb.end() || (it->se < mit->se && check(it->fi + v[p].length) == 1)) { //启发式，调优点
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
			} else {
				cnt++;

				v[p].group = cnt;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
			}
		}
	}
	for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
		if (it->group > 0) {
			finish.pb(*it);
			it = v.erase(it);
		} else {
			if (it->group == -1) {
				it->group = 0;
			}
			++it;
		}
	}
	return v;
}
int rest_cnt, used_cnt, scrap_cnt;
void report(vector<silicon> a) {
	// sort(a.begin(), a.end(), cmp_id);
	// for (int i = 0; i < a.size(); ++i) {
	// 	a[i].output();
	// }
	rest_cnt = 0;
	used_cnt = 0;
	scrap_cnt = 0;
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("+厂家\t\t+锭号\t\t+棒号\t\t+杂质情况\t+长度\t\t+分组\t\t+切割状况\n");
	printf("未使用:\n");
	sort(a.begin(), a.end(), cmp_group);
	for (std::vector<silicon>::iterator it = a.begin(); it != a.end();) {
		if (it->group <= 0) {
			it->output();
			rest_cnt++;
			it = a.erase(it);
		} else {
			//used_cnt++;
			++it;
		}
	}
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("报废:\n");
	for (std::vector<silicon>::iterator it = a.begin(); it != a.end();) {
		if (it->group == inf) {
			it->output();
			scrap_cnt++;
			it = a.erase(it);
		} else {
			//used_cnt++;
			++it;
		}
	}
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("拼棒方案\n");
	sort(a.begin(), a.end(), cmp_group);
	int groupid = 0, sum = 0;
	for (int i = 0; i < a.size(); ++i) {
		if ((!groupid) || a[i - 1].group != a[i].group) {
			groupid++;
			if (sum) {
				printf("\n\t\t\t\t\t\t\t拼接长度 = %d%s\n", sum, (check(sum) == 1) ? ", 符合要求" : ".");
			}
			sum = 0;
			printf("第%3d 组:\n", groupid);
		}
		a[i].output();
		used_cnt++;
		sum += a[i].length;
	}
	printf("\n\t\t\t\t\t\t\t拼接长度 = %d%s\n", sum, (check(sum) == 1) ? ", 符合要求" : ".");
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("匹配数 = %d\n", used_cnt);
	printf("未匹配数 = %d\n", rest_cnt);
	printf("报废数 = %d\n", scrap_cnt);
	printf("总数 = %d\n", used_cnt + rest_cnt + scrap_cnt);
	printf("匹配率 = %.2f%%\n", 1.0 * used_cnt / (used_cnt + rest_cnt + scrap_cnt) * 100);
	if (max_cut_num > -1) {
		printf("最大截断刀数 %d\n", max_cut_num);
		printf("实际截断刀数 %d\n", max_cut_num - rest_cut_num);
	}

}
vector<silicon> calc(vector<silicon> db) {
	finish.clear();
	if (1) {
		db = calc3_oppo(db);
		db = calc4_oppo(db);
	} else {
		db = calc3(db);
		db = calc4(db);
	}
	if (rest_cut_num > 0) {
		db = calc3_cut(db);
		if (rest_cut_num > 0) {
			db = calc4_cut(db);
		}
	}
	return mg(db, finish);
}

void gao() {
	int n;
	scanf("%d", &min_eligible_len);
	scanf("%d", &max_eligible_len);
	scanf("%d", &scrap_len);
	scanf("%d", &max_cut_num);
	cnt = 0;
	rest_cut_num = max_cut_num;
	vector<silicon> result;
	result.clear();
	while (~scanf("%d", &n)) {
		vector<silicon>db; db.clear();
		for (int i = 0; i < n; ++i) {
			silicon t;
			t.input();
			if (t.length < scrap_len) {
				t.group = inf;
			}
			db.pb(t);
		}
		result = mg(result, calc(db));
	}
	report(result);
}

int main(int argc, char const *argv[]) {
	//freopen("data.dat", "r", stdin);
	//freopen("data-mod1.dat", "r", stdin);//不区分厂家，BC区自由匹配https://paste.ubuntu.com/26546275/
	//freopen("data-mod2.dat", "r", stdin);//包头区无杂质，BC区自由匹配https://paste.ubuntu.com/26546278/
	freopen("data-mod3.dat", "r", stdin);//不分厂家，所有杂质匹配https://paste.ubuntu.com/26546281/
	//freopen("data-540.dat", "r", stdin);
	//freopen("data-300.dat", "r", stdin);
	freopen("result.out", "w", stdout);
	gao();
	printf("\nEOF\n");
	return 0;
}