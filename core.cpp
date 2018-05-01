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
int sgn(double x) {
	if (fabs(x) < eps) return 0;
	if (x < 0) return -1;
	else return 1;
}
bool flag_detail=1;
bool flag_report=1;
int cnt = 0;
int tot;
int cnt_calc;//计算批数
int min_eligible_len = 685;//最小合格长度
int max_eligible_len = 695;//最大合格长度
int rest_cut_num;//剩余可截断数
int max_cut_num;//最大可截断数
int scrap_len;//报废长度

int cnt_rest;//当前未匹配
int cnt_used;//当前匹配
int cnt_scrap;//当前报废
int cnt_cut_num;//当前截断数
double cut_stop_rate;//目标匹配率
int total;//原始总数
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
		if (flag_detail) {
			printf("|%4s\t\t", factory);
			printf("|%4s\t\t", number);
			printf("|%2s\t\t", type);
			printf("|%4s\t\t", quality_s);
			printf("|%4d\t\t", length);
			printf("|%4d\t\t", group);
			printf("|%s\n", (cut ? "切" : ""));
		}
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
	else if (val >= min_eligible_len && val <= max_eligible_len) return 0;
	return 1;//else if (val > max_len)
}
vector<silicon> finish;
double calc_rate(int _used, int _rest, int _scrap) {
	return (1.0 * _used / (_used + _rest + _scrap) * 100);
}
double calc_cur_rate() {
	return calc_rate(cnt_used, cnt_rest, cnt_scrap);
}
void report_cut() {
	if (cnt_cut_num == 1) {
		printf("匹配数\t\t未匹配数\t\t报废数\t\t总数\t\t目标匹配率\t实际匹配率\t实际截断刀数\n");
		printf("第 %d批截断\n", cnt_calc);
	}
	printf("|%4d\t\t", cnt_used);
	printf("|%4d\t\t", cnt_rest);
	printf("|%4d\t\t", cnt_scrap);
	printf("|%4d\t\t", cnt_used + cnt_rest + cnt_scrap);
	printf("|%.2f%%\t\t", cut_stop_rate);
	printf("|%.2f%%\t\t", 1.0 * cnt_used / (cnt_used + cnt_rest + cnt_scrap) * 100);
	//printf("最大截断刀数 %d\t", max_cut_num);
	printf("|%4d\n", cnt_cut_num);
}
vector<silicon> calc_cut_pro(vector<silicon> v) {
	if (rest_cut_num <= 0) return v;
	if (v.size() < 4) return v;
	sort(v.begin(), v.end(), cmp_length);

	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 2; i < size; ++i) { //记忆化
		if (v[i].group != 0) continue;
		for (int j = 1; j < i; ++j) {
			if (v[j].group != 0) continue;
			for (int k = 0; k < j; ++k) {
				if (v[k].group != 0) continue;
				comb.pb(mp(v[i].length + v[j].length + v[k].length, i, j, k));
			}
		}
	}
	sort(comb.begin(), comb.end());
	// printf("%d %d %d %d\n", comb[0].first,comb[0].se,comb[0].third,comb[0].forth);//539 2 1 0
	// printf("%d %d %d %d\n", comb[1].first,comb[1].se,comb[1].third,comb[1].forth);//540 3 1 0
	size = v.size();
	for (int p = 0; p < size - 3; ++p) {
		if (!(rest_cut_num > 0 && calc_cur_rate() < cut_stop_rate)) break;
		if (v[p].group != 0) {
			continue;
		} else {
			vector<PIIII>::iterator mit, it_low;
			it_low = lower_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 50, 0, 0, 0));
			//it_upper = upper_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 1, 0, 0));
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && v[it->forth].group == 0 && p != it->forth) {
						if (check(it->fi + v[p].length) > 0
						        && check(v[p].length + v[it->third].length + v[it->forth].length) < 0
						        && (v[p].length + mit->first) - min_eligible_len >= scrap_len) { //注意p+j+k已经过大的情况
							if (mit == comb.end() || (it->forth >= mit->forth)) { //启发式
								mit = it;
							}
						}
					}
				}
			}
			if (mit == comb.end()) {
				v[p].group = -1;
			} else {
				cnt++;
				cnt_used += 4;
				cnt_rest -= 4;
				cnt_rest++;
				cnt_cut_num++;
				rest_cut_num--;
				v[mit->se].cut = 1;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				v[mit->forth].group = cnt;
				v[p].group = cnt;
				int cut_rest_len = (v[p].length + mit->first) - min_eligible_len; //截断剩余
				int cut_used_len = v[mit->se].length - cut_rest_len;
				v[mit->se].length = cut_used_len;
				v.pb(v[mit->se]);
				v[v.size() - 1].length = cut_rest_len;
				v[v.size() - 1].group = 0;
				report_cut();


				// for (std::vector<silicon>::iterator it = v.begin(); it != v.end();) {
				// 	if (it->group > 0) {
				// 		finish.pb(*it);
				// 		it = v.erase(it);
				// 	} else {
				// 		if (it->group == -1) {
				// 			it->group = 0;
				// 		}
				// 		++it;
				// 	}
				// }
				sort(v.begin(), v.end(), cmp_length);
				comb.clear();
				size = v.size();
				for (int i = 2; i < size; ++i) { //记忆化
					if (v[i].group != 0) continue;
					for (int j = 1; j < i; ++j) {
						if (v[j].group != 0) continue;
						for (int k = 0; k < j; ++k) {
							if (v[k].group != 0) continue;
							comb.pb(mp(v[i].length + v[j].length + v[k].length, i, j, k));
						}
					}
				}
			}
			p = -1;
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
vector<silicon> calc4_cut_pro(vector<silicon> v) {
	if (rest_cut_num <= 0) return v;
	if (v.size() < 4) return v;
	sort(v.begin(), v.end(), cmp_length);

	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 2; i < size; ++i) { //记忆化
		for (int j = 1; j < i; ++j) {
			for (int k = 0; k < j; ++k) {
				comb.pb(mp(v[i].length + v[j].length + v[k].length, i, j, k));
			}
		}
	}
	sort(comb.begin(), comb.end());
	// printf("%d %d %d %d\n", comb[0].first,comb[0].se,comb[0].third,comb[0].forth);//539 2 1 0
	// printf("%d %d %d %d\n", comb[1].first,comb[1].se,comb[1].third,comb[1].forth);//540 3 1 0
	size = v.size();
	for (int p = 0; p < size; ++p) {
		if (!(rest_cut_num > 0 && calc_cur_rate() < cut_stop_rate)) break;
		if (v[p].group != 0) {
			continue;
		} else {
			vector<PIIII>::iterator mit, it_low;
			it_low = lower_bound(comb.begin(), comb.end(), mp(min_eligible_len - v[p].length, 0, 0, 0));
			//it_upper = upper_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 1, 0, 0));
			mit = comb.end();
			std::vector<PIIII>::iterator it = comb.end();
			--it;
			if (it_low != comb.end())
				for (; it != it_low; --it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && v[it->forth].group == 0 && p != it->forth) {
						if (check(it->fi + v[p].length) > 0
						        && v[p].length + it->first - min_eligible_len >= scrap_len
						        && min_eligible_len - v[p].length + v[it->third].length + v[it->forth].length >= scrap_len
						        && check(v[p].length + v[it->third].length + v[it->forth].length) < 0) { //注意p+j+k已经过大的情况
							if (mit == comb.end() || (it->se > mit->se)) { //启发式
								mit = it;
								//break;
							}
						}
					}
				}
			if (mit == comb.end()) {
				v[p].group = -1;
			} else {
				cnt++;
				cnt_used += 4;
				cnt_rest -= 4;
				cnt_rest++;
				cnt_cut_num++;
				rest_cut_num--;
				v[mit->se].cut = 1;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				v[mit->forth].group = cnt;
				v[p].group = cnt;
				int cut_rest_len = (v[p].length + mit->first) - min_eligible_len; //截断剩余
				int cut_used_len = v[mit->se].length - cut_rest_len;
				v[mit->se].length = cut_used_len;
				v.pb(v[mit->se]);
				v[v.size() - 1].length = cut_rest_len;
				v[v.size() - 1].group = 0;
				report_cut();
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
vector<silicon> calc3_cut_pro(vector<silicon> v) {
	if (rest_cut_num <= 0) return v;
	if (v.size() < 4) return v;
	sort(v.begin(), v.end(), cmp_length);

	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 1; i < size; ++i) { //记忆化
		for (int j = 0; j < i; ++j) {
			comb.pb(mp(v[i].length + v[j].length, i, j));
		}
	}
	sort(comb.begin(), comb.end());
	size = v.size();
	for (int p = 0; p < size; ++p) {
		if (!(rest_cut_num > 0 && calc_cur_rate() < cut_stop_rate)) break;
		if (v[p].group != 0) {
			continue;
		} else {
			vector<PIIII>::iterator mit, it_low;
			it_low = lower_bound(comb.begin(), comb.end(), mp(min_eligible_len - v[p].length, 0, 0, 0));
			//it_upper = upper_bound(comb.begin(), comb.end(), mp(max_eligible_len - v[p].length + 1, 0, 0));
			mit = comb.end();
			std::vector<PIIII>::iterator it = comb.end();
			--it;
			if (it_low != comb.end())
				for (; it != it_low; --it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && p != it->third) {
						if (check(it->fi + v[p].length) > 0
						        && v[p].length + it->first - min_eligible_len >= scrap_len
						        && min_eligible_len - v[p].length + v[it->third].length >= scrap_len
						        && check(v[p].length + v[it->third].length) < 0) { //注意p+j已经过大的情况
							if (mit == comb.end() || (it->se > mit->se )) {//启发式
								mit = it;
								//break;
							}
						}
					}
				}
			if (mit == comb.end()) {
				v[p].group = -1;
			} else {
				cnt++;
				cnt_used += 3;
				cnt_rest -= 3;
				cnt_rest++;
				cnt_cut_num++;
				rest_cut_num--;
				v[mit->se].cut = 1;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				v[p].group = cnt;
				int cut_rest_len = (v[p].length + mit->first) - min_eligible_len; //截断剩余
				int cut_used_len = v[mit->se].length - cut_rest_len;
				v[mit->se].length = cut_used_len;
				v.pb(v[mit->se]);
				v[v.size() - 1].length = cut_rest_len;
				v[v.size() - 1].group = 0;
				report_cut();
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
vector<silicon> calc4_cut(vector<silicon> v) {
	if (rest_cut_num <= 0) return v;
	vector<silicon> result;
	result.clear();
	silicon v0, v1, v2;
	while (rest_cut_num > 0 && calc_cur_rate() < cut_stop_rate) {
		if (rest_cut_num <= 0) break;
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
			if (check(it->length + add) == 0) {
				cnt++;
				printf("debug calc4_cut%d\n", cnt);
				cnt_used += 4;
				cnt_rest -= 4;
				v0.group = cnt;
				v1.group = cnt;
				v2.group = cnt;///
				it->group = cnt;
				result.pb(*it);
				v.erase(it);
				break;
			} else if (check(it->length + add) > 0) {
				cnt++;
				cnt_used += 4;
				cnt_rest -= 3;
				rest_cut_num--;
				cnt_cut_num++;
				report_cut();
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
					cnt_scrap++;
					cnt_rest--;
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
	if (rest_cut_num <= 0) return v;
	vector<silicon> result;
	result.clear();
	silicon v0, v1;
	while (rest_cut_num > 0 && calc_cur_rate() < cut_stop_rate) {
		if (rest_cut_num <= 0) break;
		//while (rest_cut_num > 0 && 100.0 * cnt_used / (mg(mg(v, result), finish).size()) < cut_stop_rate) {
		//while (rest_cut_num > 0) {
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
			if (check(it->length + add) == 0) {

				cnt++;
				//printf("debug calc3_cut%d\n", cnt);
				cnt_used += 3;
				cnt_rest -= 3;
				v0.group = cnt;
				v1.group = cnt;
				it->group = cnt;
				result.pb(*it);
				v.erase(it);///
				break;
			} else if (check(it->length + add) > 0) {
				cnt++;
				cnt_used += 3;
				cnt_rest -= 3;
				cnt_rest++;
				rest_cut_num--;
				cnt_cut_num++;
				report_cut();
				v0.group = cnt;
				v1.group = cnt;
				it->cut = 1;
				int rest = it->length - need;
				it->length = need;
				it->group = cnt;
				result.pb(*it);
				it->length = rest;
				if (rest < scrap_len) {//报废
					cnt_scrap++;
					cnt_rest--;
					it->group = inf;
					v.erase(it);
				} else {
					it->group = 0;
					// std::vector<silicon>::iterator mit = it;
					// v.erase(it);
					// for (int i = 1; i < v.size() && mit != v.end(); ++i) { //记忆化
					// 	for (int j = 0; j < i; ++j) {
					// 		if (check(v[i].length + v[j].length + mit->length) == 0) {
					// 			cnt++;
					// 			cnt_used += 3;
					// 			printf("debug2%d\n", cnt);
					// 			v[i].group = cnt;
					// 			v[j].group = cnt;
					// 			mit->group = cnt;
					// 			result.pb(v[i]);
					// 			result.pb(v[j]);
					// 			result.pb(*mit);
					// 			mit = v.end();
					// 			break;
					// 		}
					// 	}
					// }
					// if (mit != v.end()) {
					// 	v.pb(*mit);
					// }
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

vector<silicon> calc4_pro(vector<silicon> v) {
	if (v.size() < 4) return v;
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
						if (check(mit->fi + v[p].length) != 0) {
							if (mit == comb.end() || it->se >= mit->se) { //启发式
								mit = it;
							}
						}
					}
				}
			}
			if (check(mit->fi + v[p].length) != 0) {
				mit = comb.end();
			}
			if (mit == comb.end()) {
				v[p].group = -1;
			} else {
				cnt++;
				cnt_used += 4;
				cnt_rest -= 4;
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
vector<silicon> calc3_pro(vector<silicon> v) {
	if (v.size() < 3) return v;
	sort(v.begin(), v.end(), cmp_length);

	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 1; i < size; ++i) { //记忆化
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
						if (mit == comb.end() || (it->se >= mit->se && check(it->fi + v[p].length) == 0)) { //启发式
							mit = it;
						}
					}
				}
			}
			if (check(mit->fi + v[p].length) != 0) {
				mit = comb.end();
			}
			if (mit == comb.end()) {
				v[p].group = -1;
			} else {
				cnt++;
				cnt_used += 3;
				cnt_rest -= 3;
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
						if (mit == comb.end() || (it->se < mit->se && check(mit->fi + v[p].length) != 0)) { //启发式
							mit = it;
						}
					}
				}
			}
			if (check(mit->fi + v[p].length) != 0) {
				mit = comb.end();
			}
			if (mit == comb.end()) {
				v[p].group = -1;
			} else {
				cnt++;
				cnt_used += 4;
				cnt_rest -= 4;
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
	sort(v.begin(), v.end(), cmp_length);

	vector<PIIII> comb;
	comb.clear();
	int size = v.size();
	for (int i = 1; i < size; ++i) { //记忆化
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
						if (mit == comb.end() || (it->se < mit->se && check(it->fi + v[p].length) == 0)) { //启发式
							mit = it;
						}
					}
				}
			}
			if (check(mit->fi + v[p].length) != 0) {
				mit = comb.end();
			}
			if (mit == comb.end()) {
				v[p].group = -1;
			} else {
				cnt++;
				cnt_used += 3;
				cnt_rest -= 3;
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
vector<vector<silicon> > tot_db;
vector<int> tot_cnt_rest, tot_cnt_used, tot_cnt_scrap;
void report(vector<silicon> a, int p) {
	int realused1 = 0, realused2 = 0;
	sort(a.begin(), a.end(), cmp_id);
	for (int i = 0; i < a.size(); ++i) {
		if (a[i].length < scrap_len) continue;
		//a[i].output();
		if (a[i].cut == 1 || a[i].group != 0) { //
			//if (a[i].cut == 1 || a[i].group > 0) { //不含报废
			realused2++;
			//printf("%d\n", realused);

		}
		if (i != 0 && a[i].id == a[i - 1].id) continue;

		//a[i].output();
		if (a[i].cut == 1 || a[i].group != 0) { //
			//if (a[i].cut == 1 || a[i].group > 0) { //不含报废
			realused1++;
			//printf("%d\n", realused);

		}

	}
	// cnt_rest = 0;
	// cnt_used = 0;
	// cnt_scrap = 0;
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("+厂家\t\t+锭号\t\t+棒号\t\t+杂质情况\t+长度\t\t+分组\t\t+切割状况\n");
	printf("未使用:\n");
	sort(a.begin(), a.end(), cmp_group);
	for (std::vector<silicon>::iterator it = a.begin(); it != a.end();) {
		if (it->group <= 0) {
			it->output();
			//cnt_rest++;
			it = a.erase(it);
		} else {
			//cnt_used++;
			++it;
		}
	}
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("报废:\n");
	for (std::vector<silicon>::iterator it = a.begin(); it != a.end();) {
		if (it->group == inf) {
			it->output();
			//cnt_scrap++;
			it = a.erase(it);
		} else {
			//cnt_used++;
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
				printf("\n\t\t\t\t\t\t\t拼接长度 = %d%s\n", sum, (check(sum) == 0) ? ", 符合要求" : ".");
			}
			sum = 0;
			printf("第%3d 组:\n", groupid);
		}
		a[i].output();
		//cnt_used++;
		sum += a[i].length;
	}
	printf("\n\t\t\t\t\t\t\t拼接长度 = %d%s\n", sum, (check(sum) == 0) ? ", 符合要求" : ".");
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("成功匹配组数 = %d\n", cnt);
	printf("匹配数 = %d\n", tot_cnt_used[p]);
	printf("未匹配数%s = %d\n", (max_cut_num > 0) ? "(按切割后计算)" : "", tot_cnt_rest[p]);
	printf("实际使用数 = %d\n", realused1);
	printf("报废数 = %d\n", tot_cnt_scrap[p]);
	printf("逻辑总数 = 匹配数+未匹配数+报废数 = %d\n", tot_cnt_used[p] + tot_cnt_rest[p] + tot_cnt_scrap[p]);
	printf("原始总数 = %d\n", total);
	printf("预设匹配率 = %.2f%%\n", cut_stop_rate);
	printf("实际匹配率1 = 匹配数/逻辑总数 = %.2f%%\n", 1.0 * tot_cnt_used[p] / (tot_cnt_used[p] + tot_cnt_rest[p] + tot_cnt_scrap[p]) * 100);
	printf("实际匹配率2 = 匹配数/原始总数 = %.2f%%\n", min(1.0 * tot_cnt_used[p] / total * 100, 100.0));
	printf("实际使用率1 = 实际使用数/原始总数 = %.2f%%\n", 1.0 * realused1 / total * 100);
	if (max_cut_num > 0) {
		printf("实际使用率2 = 切后实际使用数/逻辑总数 = %.2f%%\n", 1.0 * realused2 / (tot_cnt_used[p] + tot_cnt_rest[p] + tot_cnt_scrap[p]) * 100);
	}

	if (max_cut_num > 0) {
		printf("预设截断刀数 %d\n", max_cut_num);
		printf("实际截断刀数 %d\n", max_cut_num - rest_cut_num);
	}

}


vector<silicon> calc(vector<silicon> db) {
	cnt_rest = 0;
	cnt_used = 0;
	cnt_scrap = 0;
	cnt_cut_num = 0;
	int size = db.size();
	for (int i = 0; i < size; ++i) {
		cnt_rest++;
		if (db[i].length < scrap_len) {
			db[i].group = inf;
			cnt_scrap++;
			cnt_rest--;
		}
	}
	finish.clear();
	int flag = 6;
	if (flag == 1) {
		db = calc3(db);
		db = calc4(db);
		db = calc3_cut(db);
		db = calc4_cut(db);
	} else if (flag == 2) {
		db = calc3_pro(db);
		db = calc4_pro(db);
		db = calc3_cut(db);
		db = calc4_cut(db);
	} else if (flag == 3) {
		db = calc3_pro(db);
		db = calc4_pro(db);
		db = calc3_cut_pro(db);
		db = calc4_cut_pro(db);
	} else if (flag == 4) {
		db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc4_cut_pro(db); // printf("calc4_cut_pro-%d\n", cnt);
		db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc3_cut_pro(db); // printf("calc3_cut_pro-%d\n", cnt);
		db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc4_cut_pro(db); // printf("calc4_cut_pro-%d\n", cnt);
		db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc3_cut_pro(db); // printf("calc3_cut_pro-%d\n", cnt);
		db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
	} else if (flag == 5) {
		db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc3_cut_pro(db); // printf("calc3_cut_pro-%d\n", cnt);
		// db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc4_cut_pro(db); // printf("calc4_pro-%d\n", cnt);
		// db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc3_cut_pro(db); // printf("calc3_cut_pro-%d\n", cnt);
		// db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
		db = calc4_cut_pro(db); // printf("calc4_cut_pro-%d\n", cnt);
		// db = calc3_pro(db); // printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db); // printf("calc4_pro-%d\n", cnt);
	} else if (flag == 6) {
		db = calc3_pro(db);// printf("calc3_pro-%d\n", cnt);
		db = calc4_pro(db);// printf("calc4_pro-%d\n", cnt);
		if (db.size() <= 100)
			db = calc4_cut_pro(db);// printf("calc4_pro-%d\n", cnt);
		db = calc3_cut_pro(db);// printf("calc3_cut_pro-%d\n", cnt);
		// db = calc3_pro(db);// printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db);// printf("calc4_pro-%d\n", cnt);

		db = calc4_cut_pro(db);// printf("calc4_pro-%d\n", cnt);
		db = calc3_cut_pro(db);// printf("calc3_cut_pro-%d\n", cnt);
		// db = calc3_pro(db);// printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db);// printf("calc4_pro-%d\n", cnt);
		// db = calc3_cut_pro(db); printf("calc3_cut_pro-%d\n", cnt);
		// db = calc3_pro(db); printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db); printf("calc4_pro-%d\n", cnt);
		// db = calc4_cut_pro(db); printf("calc4_cut_pro-%d\n", cnt);
		// db = calc3_pro(db); printf("calc3_pro-%d\n", cnt);
		// db = calc4_pro(db); printf("calc4_pro-%d\n", cnt);
	}
	return mg(db, finish);
}

void gao() {
	int n;
	scanf("%d", &min_eligible_len);
	scanf("%d", &max_eligible_len);
	scanf("%d", &scrap_len);
	scanf("%d", &max_cut_num);
	scanf("%lf", &cut_stop_rate);
	total = 0;
	cnt = 0;
	cnt_calc = 0;
	tot_db.resize(1);
	tot_db[0].clear();
	tot_cnt_rest.resize(1);
	tot_cnt_used.resize(1);
	tot_cnt_scrap.resize(1);
	tot_cnt_rest[0] = 0;
	tot_cnt_used[0] = 0;
	tot_cnt_scrap[0] = 0;
	rest_cut_num = max_cut_num;
	vector<silicon> result;
	result.clear();
	while (~scanf("%d", &n)) {
		total += n;
		cnt_calc++;
		vector<silicon>db; db.clear();
		for (int i = 0; i < n; ++i) {
			silicon t; t.input(); db.pb(t);
		}
		db = calc(db);
		tot_db.pb(db);
		tot_db[0] = mg(tot_db[0], db);
		tot_cnt_rest.pb(cnt_rest);
		tot_cnt_used.pb(cnt_used);
		tot_cnt_scrap.pb(cnt_scrap);
		tot_cnt_rest[0] += tot_cnt_rest[cnt_calc];
		tot_cnt_used[0] += tot_cnt_used[cnt_calc];
		tot_cnt_scrap[0] += tot_cnt_scrap[cnt_calc];
	}
	report(tot_db[0], 0);
}

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		printf("example :core [input]\n");
		return 1;
	}
	freopen(argv[1], "r", stdin);
	//freopen("data-mod1.dat", "r", stdin);//不区分厂家，BC区自由匹配
	//freopen("data-mod2.dat", "r", stdin);//包头区无杂质，BC区自由匹配
	//freopen("data-mod3.dat", "r", stdin);//不分厂家，所有杂质匹配
	//freopen("data-540.dat", "r", stdin);
	//freopen("data-300.dat", "r", stdin);
	//freopen("data-mod51-1.dat", "r", stdin);
	//freopen("data-mod51-2.dat", "r", stdin);
	//freopen("data-mod51-3.dat", "r", stdin);
	//freopen("result.out", "w", stdout);
	gao();
	printf("\nEOF\n");
	return 0;
}