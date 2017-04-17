#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
string L_line,F_line, uniq_line,temp;
unordered_map <char, int> C; // need to clear.
int flag = 1;
int correct_search = 0;
int First, Last;

int Occ(char c, int order, string str = L_line) {
	vector <vector<int>> array_cnt(str.length());
	for (unsigned int i = 0; i < str.length(); i++) { array_cnt[i].resize(128); }
	for (unsigned int j = 0; j < str.length(); j++) {
		for (unsigned int k = 0; k < j+1; k++) {
			if (array_cnt[j][int(str[k])] != 0) { array_cnt[j][int(str[k])] += 1; }
			else { array_cnt[j][int(str[k])] = 1; }
		}
	}
	return array_cnt[order][int(c)];
}

void Count() {
	for (unsigned int m = 0; m < F_line.length(); m++) {
		if (!C[F_line[m]]) {
			C[F_line[m]] = m;
			uniq_line += F_line[m];
		}
	}
}

void Backward_search(string input, int *First, int *Last) {
	int i = input.length() - 1;
	char c = input[i];
	*First = C[c];
	unsigned int pos = uniq_line.find(c, 0);
	if (uniq_line[pos + 1]) { *Last = C[uniq_line[pos + 1]] - 1; }
	else { *Last = L_line.length() - 1; }
	while (*First <= *Last && i >= 1) {
		c = input[i - 1];
		*First = C[c] + Occ(c, *First - 1);
		*Last = C[c] + Occ(c, *Last) - 1;
		i = i - 1;
	}
}

void Backward_decode(int index) {
	char b ;
	while (flag) {
		b = L_line[index];
		stringstream ss;
		ss << b;
		string b_tmp = ss.str();
		temp.insert(0,b_tmp);
		if (b == '[') { 
			flag = 0;
		}
		if (b == ']') {
			correct_search = 1;
		}
		index = C[b] + Occ(b, index) - 1;
	}
}

void Forward_decode(int index) {
}

void output() {
	if ((First - Last) <= 0) {
		for (int r = First; r <= Last; r++) {
			Backward_decode(r);
			if (correct_search) {
				cout << temp << endl;
			}
			correct_search = 0;
			flag = 1;
			temp.clear();
			string(temp).swap(temp);
		}
	}
}

int main(int argc, char* argv[]) {
	L_line = "[[an12nbnb]]aaa";
	string P = "an";
	F_line = L_line;
	sort(F_line.begin(), F_line.end());
	
	Count();
	Backward_search(P, &First, &Last);
	output();


	cout <<"F_line: " << F_line << endl;
	cout << "L_line: " << L_line << endl;
	cout << uniq_line << endl;
	system("pause");
	return 0;
}
