#include <bits/stdc++.h>
//#decine _ ios_a::sync_with_stdio(0);cin.tie(0);
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
//#decine mp make_pair
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
//#decine th second.second

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
		if (factory != "yinhe") {
			factory = "baotou";
		}
		cin >> number;
		cin >> type;
		string quality_s; cin >> quality_s;
		if (quality_s == "normal") {
			quality = 0;
		} else if (quality_s == "impurity") {
			quality = 1;
		} else {
			quality = -1;
		}
		cin >> length;
		cin >> matrix;
		group = 0;
		cut = 0;
	}
	void output() {
		cout << "|" ;
		if (factory == "yinhe") {
			cout << "银和";
		} else if (factory == "baotou") {
			cout << "包头";
		} else {
			cout << "包头";
		}
		cout << "\t";
		cout << "|\t" << number << "\t\t";
		cout << "|" << type << "\t\t";
		cout << "|" << ((quality == 0) ? "正常" : "杂质") << "\t";
		printf("|%4d\t", length);
		if (group > 0) {
			printf("|%4d\t", group);
		} else {
			printf("|   无\t");
		}
		cout << "  |" << (cut ? "切" : "") << endl;
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
	return 0;//else if (val > maxlen)
}

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
		if (v.size() < 4) {
			break;
		}
		sort(v.begin(), v.end(), cmp_length);
		reverse(v.begin(), v.end());
		v0 = v[0]; v1 = v[1]; v2 = v[2];
		v.erase(v.begin());
		v.erase(v.begin());
		v.erase(v.begin());
		int add = v0.length + v1.length + v2.length;
		//if (add > maxlen) cout << "debug";
		int need = minlen - add;

		for (std::vector<Part>::iterator it = v.end(); it != v.begin();) {
			--it;
			if (check(it->length + add) == 1) {
				cnt++;
				v0.group = cnt;
				v1.group = cnt;
				v2.group = cnt;
				it->group = cnt;
				result.pb(*it);
				v.erase(it);//
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
		if (v.size() < 3) {
			break;
		}
		sort(v.begin(), v.end(), cmp_length);
		reverse(v.begin(), v.end());
		v0 = v[0]; v1 = v[1];
		v.erase(v.begin());
		v.erase(v.begin());
		int add = v0.length + v1.length;
		int need = minlen - add;
		for (std::vector<Part>::iterator it = v.end(); it != v.begin();) {
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
vector<Part> calc4_op(vector<Part> v) {

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
					if (v[it->se].group == 0 && v[it->third].group == 0 && v[it->forth].group == 0 && p != it->se) {
						if (mit == comb.end() || (it->se > mit->se && check(mit->fi + v[p].length) != 1)) { //启发式
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
vector<Part> calc3_op(vector<Part> v) {
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
			// if(it_low==it_upper) {
			// 	v[p].group = -1;
			// 	continue;
			// }
			mit = comb.end();
			if (it_low != comb.end()) {
				for (std::vector<PIIII>::iterator it = it_low; it != it_upper && it != comb.end(); ++it) {
					if (v[it->se].group == 0 && v[it->third].group == 0 && p != it->se) {
						if (mit == comb.end() || (it->se > mit->se && check(it->fi + v[p].length) == 1)) { //启发式，调优点
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
				// if (cnt == 2) {//debug
				// 	debug(12580);
				// 	cout << endl;
				// 	v[p].output();
				// 	v[mit->se].output();
				// 	v[mit->third].output();

				// }
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
			// if(it_low==it_upper) {
			// 	v[p].group = -1;
			// 	continue;
			// }
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
				//result.pb(v[p]);
				//comb_erase(p);
			} else {
				cnt++;

				v[p].group = cnt;
				v[mit->se].group = cnt;
				v[mit->third].group = cnt;
				// if (cnt == 2) {//debug
				// 	debug(12580);
				// 	cout << endl;
				// 	v[p].output();
				// 	v[mit->se].output();
				// 	v[mit->third].output();

				// }
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
	int rest_cnt = 0;
	int used_cnt = 0;
	printf("|—--------------—--------------—--------------—--------------\n");
	printf("厂家\t\t\t锭号\t\t棒号\t\t杂质情况\t  长度\t   分组\t  切割状况\n");
	sort(a.begin(), a.end(), cmp_group);
	for (std::vector<Part>::iterator it = a.begin(); it != a.end();) {
		if (it->group <= 0) {
			it->output();
			rest_cnt++;
			it = a.erase(it);
		} else {
			used_cnt++;
			++it;
		}
	}
	sort(a.begin(), a.end(), cmp_group);
	int groupid = 0, sum = 0;
	for (int i = 0; i < a.size(); ++i) {
		if ((!groupid) || a[i - 1].group != a[i].group) {
			groupid++;
			if (sum) {
				printf("\n\t\t\t\t\t\t\t拼接长度 = %d%s\n", sum, (check(sum) == 1) ? ", 符合要求" : ".");
			}
			sum = 0;
			printf("第%d组:\n", groupid);
		}
		a[i].output();
		sum += a[i].length;
	}
	printf("\n\t\t\t\t\t\t\t拼接长度 = %d%s\n", sum, (check(sum) == 1) ? ", 符合要求" : ".");
	printf("used_cnt = %d\n", used_cnt);
	printf("rest_cnt = %d\n", rest_cnt);
	printf("tot = %d\n", used_cnt + rest_cnt);
	printf("rate = %.2f%%\n", 1.0 * used_cnt / (used_cnt + rest_cnt) * 100);
	printf("|—--------------—--------------—--------------—--------------\n");
}
vector<Part> calc(vector<Part> db, int if_cut = 0) {
	// db = calc3_op(db);
	// db = calc4_op(db);
	db = calc3(db);
	db = calc4(db);
	if (if_cut) {
		db = calc3(db, 1);
		db = calc4(db, 1);
	}
	return db;
}
vector<Part> mg(vector<Part> a, vector<Part> b) {
	int size = b.size();
	for (int i = 0; i < size; ++i) {
		a.pb(b[i]);
	}
	return a;
}
void select(vector<Part> db, int mod) {
	cnt = 0;
	vector<Part> bt_a_0; bt_a_0.clear();
	vector<Part> bt_a_1; bt_a_1.clear();
	vector<Part> bt_b_0; bt_b_0.clear();
	vector<Part> bt_b_1; bt_b_1.clear();
	vector<Part> bt_c_0; bt_c_0.clear();
	vector<Part> bt_c_1; bt_c_1.clear();
	vector<Part> yh_a_0; yh_a_0.clear();
	vector<Part> yh_a_1; yh_a_1.clear();
	vector<Part> yh_b_0; yh_b_0.clear();
	vector<Part> yh_b_1; yh_b_1.clear();
	vector<Part> yh_c_0; yh_c_0.clear();
	vector<Part> yh_c_1; yh_c_1.clear();
	int size = db.size();
	for (int i = 0; i < size; ++i) {
		if (db[i].factory == "baotou" && db[i].type == 'A' && db[i].quality == 0) {
			bt_a_0.pb(db[i]);
		} else if (db[i].factory == "baotou" && db[i].type == 'A' && db[i].quality == 1) {
			bt_a_1.pb(db[i]);
		}

		else if (db[i].factory == "baotou" && db[i].type == 'B' && db[i].quality == 0) {
			bt_b_0.pb(db[i]);
		} else if (db[i].factory == "baotou" && db[i].type == 'B' && db[i].quality == 1) {
			bt_b_1.pb(db[i]);
		}

		else if (db[i].factory == "baotou" && db[i].type == 'C' && db[i].quality == 0) {
			bt_c_0.pb(db[i]);
		} else if (db[i].factory == "baotou" && db[i].type == 'C' && db[i].quality == 1) {
			bt_c_1.pb(db[i]);
		}

		else if (db[i].factory == "yinhe" && db[i].type == 'A' && db[i].quality == 0) {
			yh_a_0.pb(db[i]);
		} else if (db[i].factory == "yinhe" && db[i].type == 'A' && db[i].quality == 1) {
			yh_a_1.pb(db[i]);
		}

		else if (db[i].factory == "yinhe" && db[i].type == 'B' && db[i].quality == 0) {
			yh_b_0.pb(db[i]);
		} else if (db[i].factory == "yinhe" && db[i].type == 'B' && db[i].quality == 1) {
			yh_b_1.pb(db[i]);
		}

		else if (db[i].factory == "yinhe" && db[i].type == 'C' && db[i].quality == 0) {
			yh_c_0.pb(db[i]);
		} else if (db[i].factory == "yinhe" && db[i].type == 'C' && db[i].quality == 1) {
			yh_c_1.pb(db[i]);
		}
	}
	vector <Part> result; result.clear();
	if (mod == 1) {
		vector<Part> mod1; mod1.clear();
		mod1 = mg(mod1, yh_b_0);
		mod1 = mg(mod1, yh_b_1);
		mod1 = mg(mod1, yh_c_0);
		mod1 = mg(mod1, yh_c_1);
		mod1 = mg(mod1, bt_b_0);
		mod1 = mg(mod1, bt_b_1);
		mod1 = mg(mod1, bt_c_0);
		mod1 = mg(mod1, bt_c_1);
		result = calc(mod1);
	} else if (mod == 2) {
		vector<Part> mod2; mod2.clear();
		mod2 = mg(mod2, bt_b_0);
		mod2 = mg(mod2, bt_b_1);
		mod2 = mg(mod2, bt_c_0);
		mod2 = mg(mod2, bt_c_1);
		result = calc(mod2);
	} else if (mod == 3) {
		vector<Part> mod3; mod3.clear();
		mod3 = mg(mod3, yh_a_1);
		mod3 = mg(mod3, yh_b_1);
		mod3 = mg(mod3, yh_c_1);
		mod3 = mg(mod3, bt_a_1);
		mod3 = mg(mod3, bt_b_1);
		mod3 = mg(mod3, bt_c_1);
		result = calc(mod3);
	}
	report(result);
}
void gao() {
	int mod;
	cin >> mod;
	vector <Part> db;
	db.clear();
	tot = 0;
	while (!cin.eof()) {
		Part t;
		t.input();
		if(t.quality==-1) continue;
		db.push_back(t);
	}
	//select(db,mod);
	select(db, 1);
	select(db, 2);
	select(db, 3);
}

int main(int argc, char const *argv[]) {
	freopen("data300.dat", "r", stdin);
	freopen("result.dat", "w", stdout);
	gao();
	return 0;
}