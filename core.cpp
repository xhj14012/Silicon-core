#include <bits/stdc++.h>
#define _ ios_a::sync_with_stdio(0);fin.tie(0);
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
fstream fin;
fstream fout1("single_factory.out", ios::out);
fstream fout2("mixup_factory.out", ios::out);
int cnt = 0;
int tot;
int cut_num;
vector<string> factory_cant_mix;
struct Part {
	void input() {
		id = tot++;
		fin >> factory;
		fin >> number;
		fin >> type;
		string quality_s; fin >> quality_s;
		quality = (quality_s == "normal") ? 0 : 1;
		fin >> length;
		fin >> matrix;
		group = 0;
		cut = 0;
		//output();
	}
	void output() {
		cout << id << "\t";
		cout << factory << "\t";
		cout << number << "\t";
		cout << type << "\t\t";
		cout << ((quality == 0) ? "normal  " : "impurity") << "\t";
		cout << length << "\t\t";
		//cout << matrix << "\t";
		cout << group << "\t\t";
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
int reportid;
void report(vector<Part> a) {
	printf("/************report************\n");
	printf("id\tfactory\tmodel\ttype\tquality\t\tlength\tgroup\tifcut\n");
	sort(a.begin(), a.end(), cmp_group);
	//a = a;
	//reverse(a.begin(), a.end());
	//
	// for (int i = 0; i < a.size(); ++i) {
	// 	a[i].output();
	// }
	for (int i = 0; i < a.size(); ++i) {
		//a[i].output();
		if (a[i].group <= 0) continue;
		reportid++;
		printf("group(%d):\n", reportid);
		int sum = a[i].length;
		a[i].output();
		while (i + 1 < a.size() && a[i].group == a[i + 1].group) {
			sum += a[i + 1].length;
			a[i + 1].output();
			++i;
		}
		printf("------------------------------------sum=%d\n", sum);
		if(check(sum)!=1) cout << "error"<< endl;
		if (i + 1 == a.size()) break;
	}
	printf("/************report************\n");
}
vector<Part> calc(vector<Part> db) {
	db = calc3(db);
	//report(a);
	db = calc4(db);
	//report(a);
	db = calc3(db, 1);
	//report(a);
	db = calc4(db, 1);
	//report(a);
	return db;
}
vector<Part> mg(vector<Part> a, vector<Part> b) {
	int size = b.size();
	for (int i = 0; i < size; ++i) {
		a.pb(b[i]);
	}
	return a;
}
void select(vector<Part> db) {
	cnt = 0;
	//cut_num = 50;
	reportid = 0;
	vector<Part> bt_a_zc;
	bt_a_zc.clear();
	vector<Part> bt_a_zz;
	bt_a_zz.clear();
	vector<Part> bt_b_zc;
	bt_b_zc.clear();
	vector<Part> bt_b_zz;
	bt_b_zz.clear();
	vector<Part> bt_c_zc;
	bt_c_zc.clear();
	vector<Part> bt_c_zz;
	bt_c_zz.clear();
	vector<Part> yh_a_zc;
	yh_a_zc.clear();
	vector<Part> yh_a_zz;
	yh_a_zz.clear();
	vector<Part> yh_b_zc;
	yh_b_zc.clear();
	vector<Part> yh_b_zz;
	yh_b_zz.clear();
	vector<Part> yh_c_zc;
	yh_c_zc.clear();
	vector<Part> yh_c_zz;
	yh_c_zz.clear();
	int size = db.size();
	for (int i = 0; i < size; ++i) {//暂只指定工厂
		if (db[i].factory == "baotou" && db[i].type == 'A' && db[i].quality == 0) {
			bt_a_zc.pb(db[i]);
		} else if (db[i].factory == "baotou" && db[i].type == 'A' && db[i].quality == 1) {
			bt_a_zz.pb(db[i]);
		}
		
		else if (db[i].factory == "baotou" && db[i].type == 'B' && db[i].quality == 0) {
			bt_b_zc.pb(db[i]);
		} else if (db[i].factory == "baotou" && db[i].type == 'B' && db[i].quality == 1) {
			bt_b_zz.pb(db[i]);
		}

		else if (db[i].factory == "baotou" && db[i].type == 'C' && db[i].quality == 0) {
			bt_c_zc.pb(db[i]);
		} else if (db[i].factory == "baotou" && db[i].type == 'C' && db[i].quality == 1) {
			bt_c_zz.pb(db[i]);
		}

		else if (db[i].factory == "yinhe" && db[i].type == 'A' && db[i].quality == 0) {
			yh_a_zc.pb(db[i]);
		} else if (db[i].factory == "yinhe" && db[i].type == 'A' && db[i].quality == 1) {
			yh_a_zz.pb(db[i]);
		}

		else if (db[i].factory == "yinhe" && db[i].type == 'B' && db[i].quality == 0) {
			yh_b_zc.pb(db[i]);
		} else if (db[i].factory == "yinhe" && db[i].type == 'B' && db[i].quality == 1) {
			yh_b_zz.pb(db[i]);
		}

		else if (db[i].factory == "yinhe" && db[i].type == 'C' && db[i].quality == 0) {
			yh_c_zc.pb(db[i]);
		} else if (db[i].factory == "yinhe" && db[i].type == 'C' && db[i].quality == 1) {
			yh_c_zz.pb(db[i]);
		}
	}
	int flag = 1;

	if (flag == 1) {
		cnt = 0;
		vector<Part> c;
		printf("yinghe A normal single:\n");
		c.clear();
		c = calc(yh_a_zc);
		report(c);

		printf("yinghe A impurity single:\n");
		c.clear();
		c = calc(yh_a_zz);
		report(c);

		printf("yinghe B normal single:\n");
		c.clear();
		c = calc(yh_b_zc);
		report(c);

		printf("yinghe B impurity single:\n");
		c.clear();
		c = calc(yh_b_zz);
		report(c);

		printf("yinghe C normal single:\n");
		c.clear();
		c = calc(yh_c_zc);
		report(c);
//
		printf("yinghe C impurity single:\n");
		c.clear();
		c = calc(yh_c_zz);
		report(c);

		printf("baotou A normal+impurity single:\n");
		c.clear();
		c = calc(mg(bt_a_zz, bt_a_zc));
		report(c);

		printf("baotou B+C normal single:\n");
		c.clear();
		c = calc(mg(bt_b_zc, bt_c_zc));
		report(c);

		printf("baotou B+C impurity single:\n");
		c.clear();
		c = calc(mg(bt_b_zz, bt_c_zz));
		report(c);
	} else {
		cnt = 0;
		vector<Part> c, result;
		result.clear();
	}
}
void gao() {
	fin.close();
	cut_num=50;
	// printf("input max cut_num:");
	// cut_num=50;
	// cin >> cut_num;
	// system("pause");
	// printf("print any key to start calc\n");
	//fin.open("data.dat", ios::in);
	fin.open("data300.dat", ios::in);
	fout1.close();
	//fout1.open("test.out",ios::out);
	//fgets(title,99,stdin);
	fin.getline(title, 99);
	vector <Part> db;
	db.clear();
	tot = 0;

	while (!fin.eof()) {
		//for (int i = 0; i < 540; ++i) {
		Part t;
		t.input();
		db.push_back(t);
	}
	fin.close();

	select(db);
	//select2(db);
	//fout1.close();
}

int main(int argc, char const *argv[]) {
	//freopen("data.dat", "r", stdin);
	freopen("result.txt", "w", stdout);
	//freopen("test.out", "w", stdout);
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