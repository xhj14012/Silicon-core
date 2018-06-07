#include <bits/stdc++.h>

using namespace std;

// void semirand(vector<int>&v) {
// 	for (int i = v.size() - 1; i > 0; i--) swap(v[i], v[(rand() % (v.size() - i)) + i]);
// }
void semirand(std::vector<int> &v) {
	unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();  
    std::shuffle (v.begin (), v.end (), std::default_random_engine (seed));
}


int main(int argc, char const *argv[]) {
	srand(time(NULL));
	vector<int> v;
	for (int i = 1; i <= 10; ++i) {
		v.push_back(i);
	}
	for (int k = 0; k < 1000; k++) {
		sort(v.begin(), v.end());
		semirand(v);
		for (std::vector<int>::iterator i = v.begin(); i != v.end(); ++i) {
			printf("%d ", *i);
		}
		printf("\n");
		//if (v[0] == 1) break;
	}
	return 0;
}