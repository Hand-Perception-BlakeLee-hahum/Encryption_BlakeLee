#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <random>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class main_class {
private:
	string vectortostring(vector<int> main) {
		string main_string = "";
		for (int i = 0; i < main.size(); i++) {
			main_string += to_string(main[i]);
		}
		return main_string;
	}
	string vectortostring_blank(vector<int> main) {
		string main_string = "";
		for (int i = 0; i < main.size(); i++) {
			main_string += (to_string(main[i]) + " ");
		}
		return main_string;
	}
	void save_file(string main, string path) {
		ofstream writeFile;
		writeFile.open(path + ".txt");
		writeFile.write(main.c_str(), main.size());
		writeFile.close();
	}
	string get_file(string path) {
		ifstream readFile;
		readFile.open(path + ".txt");
		string str;
		getline(readFile, str);
		return str;
	}
	vector <int> stringtovector(string main_string) {
		vector <int> main;
		istringstream ss(main_string);
		string check_string;
		while (getline(ss, check_string, ' ')) {
			main.push_back(stoi(check_string));
		}
		return main;
	}
	int give_random(int start, int stop) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(start, stop);
		return dis(gen);
	}
	vector<int> stringtoascii(string check) {
		vector<int> test;
		for (int i = 0; i < check.size(); i++) {
			int dd = check.at(i);
			test.push_back(dd);
		}
		return test;
	}
	vector<int>delete_base(vector <int> main, string check_string) {
		vector <int> main_int;
		for (int i = check_string.size() + 4; i < main.size(); i++) {
			main_int.push_back(main[i]);
		}
		return main_int;
	}
	int two_vector_like(string main, string main1) {
		return (strcmp(main.c_str(), main1.c_str()) != 0) ? 0 : 1;
	}
	string change(string check, string path) {
		vector<int> key = { give_random(400, 499) };
		vector<int> main1 = stringtoascii(check);
		for (int i = 0; i < key[0]; i++) {
			int a = give_random(0, main1.size() - 1);
			int b = give_random(0, main1.size() - 1);
			key.push_back(a);
			key.push_back(b);
			main1.push_back(main1[a] + main1[main1.size() - a - 1]);
			main1.push_back(main1[b] + main1[main1.size() - b - 1]);
			main1.push_back(main1[a] * main1.size() + main1[b] * main1.size());
		}
		vector<int> main2 = delete_base(main1, check);
		string last_string = vectortostring(main2);
		save_file(last_string, path);
		save_file(vectortostring_blank(key), "key" + path);
		return last_string;
	}
	int two_vector_check(string check, string path) {
		vector <int> main1 = stringtoascii(check);
		vector<int> key = stringtovector(get_file("key" + path));
		for (int i = 0; i < key[0]; i++) {
			int a = key[i * 2 + 1];
			int b = key[(i + 1) * 2];
			if (a > main1.size() || b > main1.size()) {
				return 0;
			}
			main1.push_back(main1[a] + main1[main1.size() - a - 1]);
			main1.push_back(main1[b] + main1[main1.size() - b - 1]);
			main1.push_back(main1[a] * main1.size() + main1[b] * main1.size());
		}
		vector<int> main2 = delete_base(main1, check);
		string check_vector = get_file(path);
		return two_vector_like(check_vector, vectortostring(main2));
	}
public:
	void vector_all_print(vector<int> test) {
		for (int i = 0; i < test.size(); i++) {
			printf("%d ", test[i]);
		}
		printf("\n");
	}
	void vector_all_print_str(vector<string> test) {
		for (int i = 0; i < test.size(); i++) {
			printf("%s", test[i]);
		}
		printf("\n");
	}
	void make(string main, string path) {
		string hh = change(main, path);
	}
	void check(string main, string path) {
		printf("결과: %s\n", (two_vector_check(main, path) == 0) ? "불일치" : "일치");
	}
};

int main() {
	ios::sync_with_stdio();
	main_class main = main_class();
	string check_str = "master";
	string check_str1 = "test";
	main.make(check_str, "id");
	main.make(check_str1, "pass");
	string user_input;
	string user_input1;
	getline(cin, user_input);
	getline(cin, user_input1);
	main.check(user_input, "id");
	main.check(user_input1, "pass");

}