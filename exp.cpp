#include <bits/stdc++.h>

using namespace std;

std::tuple<std::string, std::string> ext(const std::string& path) {
	std::regex re(R"((.+?)(\.[^.]+)?)");
	std::smatch results;

	std::regex_match(path, results, re);

	return std::make_tuple(results[1], results[2]);
	//get<>()
}

int main(int argc, char const *argv[]) {
	// if (argc != 2) {
	// 	printf("example :core [input]\n");
	// 	return 0;
	// }
	//cout << ext(argc[1]).first;
	auto t = ext("argv.dat");
	//cout << get<0>(t);
	cout << get<1>(t);



	return 0;
}