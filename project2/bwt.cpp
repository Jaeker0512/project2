#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <hash_map>
#include <algorithm>

using namespace std;
extern hash_map <char, int> C;

int Occ(char c, char order) {

}

void Backward_search(string input, string First_str, string Last_str) {
	int i = input.length() - 1;
	char c = input[-1];
	int First, Last;
	First = C[c];
	Last = C[input[1]] - 1;
	while (First <= Last && i >= 1) {
		c = input[i - 1];
		First = C[c]  + Occ(c, First - 1);
		Last = C[c] + Occ(c, Last) - 1;
		i = i - 1;
	}

}




int main() {
	string L_line = "ipssm#pissi";
	string F_line = L_line;
	sort(F_line.begin(), F_line.end());
	return 0;
}
