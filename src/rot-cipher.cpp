#include <iostream>
#include <cctype>  // Used for Testing and Converting Character
#include <cstring> // Used for copying, concatenation, comparison, searching, etc... cstrings
#include <cstdlib> // Used for convert C-style strings to integer, float, long, etc...
#include <string>  // Class in Standard Template Library, C++ strings, dyanamic size, contigous memory, work with IO Streams, easily converted to C-Strings
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// cctype
// Testing Characters
// isalpha(c) isalnum(c) isdigit(c) islower(c) isprint(c) ispunct(c) isupper(c) isspace(c)

// Conversion Functions
// toupper(c) tolower(c)

// cstring
// strcpy(str, "foobar"):str = "foobar" | strcat(str, "foobar"):str + foobar | strlen(str):int | strcmp(str, "foobar"):true or false

// string
// string s1:empty | s2{"foobar"}:foobar | s3{s2}:foobar | s4{"foobar", 3}: foo | s5{s3, 0, 2}:fo | s6(3, 'X'):XXX
// can use [] and at() to access characters in a string
// substr(start_index, length) | length() | getline(input_string, stored_string,'x') get line until \n and discard 'x' characters
// erase(start_index, length) | size_t postion = s1.find(word): get position of substring if in string | s1.swap(s2): swaps s1 with s2 goo for sorting
// Looping: for(size_t i{}; i < s1.length(); ++i) | for(char c: s1)

// Substitution Cipher Program
class Rot_Cipher {
public:
	string encrypt(int rotation, string plain_text) {
		string cipher_text{};
		if (rotation > 26) {
			rotation = rotation % 26;
		}
		for (size_t i{}; i < plain_text.length(); ++i) {
			if (isalpha(plain_text[i])) {
				if (static_cast<int>(plain_text[i] + rotation) >= 65 + rotation && static_cast<int>(plain_text[i] + rotation) <= 90) {
					cipher_text.append(1, plain_text[i] + rotation);
					continue;
				}
				if (static_cast<int>(plain_text[i] + rotation) >= 97 + rotation && static_cast<int>(plain_text[i] + rotation) <= 122) {
					cipher_text.append(1, plain_text[i] + rotation);
					continue;
				}
				if (static_cast<int>(plain_text[i] - (26 - rotation)) >= 65 && static_cast<int>(plain_text[i] - (26 - rotation)) <= 65 + rotation) {
					cipher_text.append(1, plain_text[i] - (26 - rotation));
					continue;
				}
				if (static_cast<int>(plain_text[i] - (26 - rotation)) >= 97 && static_cast<int>(plain_text[i] - (26 - rotation)) <= 97 + rotation) {
					cipher_text.append(1, plain_text[i] - (26 - rotation));
					continue;
				}
			}
			else {
				cipher_text.append(1, plain_text[i]);
			}
		}
		return cipher_text;
	}
	string decrypt(int rotation, string cipher_text) {
		string plain_text{};
		if (rotation > 26) {
			rotation = rotation % 26;
		}
		for (size_t i{}; i < cipher_text.length(); ++i) {
			if (isalpha(cipher_text[i])) {
				if (static_cast<int>(cipher_text[i] - rotation) >= 65 && static_cast<int>(cipher_text[i] - rotation) <= 90 - rotation) {
					plain_text.append(1, cipher_text[i] - rotation);
					continue;
				}
				if (static_cast<int>(cipher_text[i] - rotation) >= 97 && static_cast<int>(cipher_text[i] - rotation) <= 122 - rotation) {
					plain_text.append(1, cipher_text[i] - rotation);
					continue;
				}
				if (static_cast<int>(cipher_text[i] + (26 - rotation)) >= 65 && static_cast<int>(cipher_text[i] + (26 - rotation)) <= 90) {
					plain_text.append(1, cipher_text[i] + (26 - rotation));
					continue;
				}
				if (static_cast<int>(cipher_text[i] + (26 - rotation)) >= 97  && static_cast<int>(cipher_text[i] + (26 - rotation)) <= 122) {
					plain_text.append(1, cipher_text[i] + (26 - rotation));
					continue;
				}
			}
			else {
				plain_text.append(1, cipher_text[i]);
			}
		}
		return plain_text;
	}
	int getrot(string cipher_text, int mode = 0) {
		vector<string> temp_words{};
		vector<vector<string>>str_vector{};
		vector<string> temp_str;
		int speed{};
		switch (mode) {
		case 0:
			speed = 3;
			break;
		case 1:
			speed = 5;
			break;
		case 2:
			speed = 7;
			break;
		default: 
			cout << "Invald Mode" << endl;
			return 0;
		}
		for (int i{}; i < speed; ++i) {
			if (cipher_text.find(" ") != 0) {
				string temp_substr = cipher_text.substr(0, cipher_text.find(" "));
				for (size_t j{}; j < temp_substr.length();++j) {
					temp_substr[j] = toupper(temp_substr[j]);
				}
				temp_words.push_back(temp_substr);
				cipher_text.erase(0, temp_substr.length() + 1);
			}
			else {
				temp_words.push_back(cipher_text);
			}
		}
		for (size_t i{}; i < temp_words.size(); ++i) {
			for (int j{ 1 }; j < 26; ++j) {
				string temp{ decrypt(j, temp_words[i]) };
				temp_str.push_back(temp);
			}
			str_vector.push_back(temp_str);
			temp_str.clear();
		}
		ifstream file;
		file.open("top3000.txt");
		string line{};
		getline(file, line);
		map<int, int> counters{};
		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, line);
				size_t size = str_vector.at(0).size();
				for (size_t j{}; j < str_vector.size(); ++j) {
					for (size_t i{}; i < str_vector.at(j).size(); ++i) {
						if (line == str_vector.at(j).at(i)) {
							++counters[int(i) + 1];
							break;
						}
					}
				}
			}
		}
		map<int, int>::iterator best = max_element(counters.begin(), counters.end(), [](const pair<int, int>& a, const pair<int, int>& b)->bool { return a.second < b.second; });
		return best->first;
	}
	int main() {
		string user_text{};
		cout << "Enter Your Text: ";
		getline(cin, user_text);
		for (int i{ 1 };i < 26;++i) {
			string cipher = encrypt(i, user_text);
			int rot = getrot(cipher, 2);
			cout << "Cipher Text: " << cipher << " ROT" << rot << endl;
			//string plain = decrypt(rot, cipher);
			//cout << "Plain Text:  " << plain << "\n" << endl;
		}
	}
};