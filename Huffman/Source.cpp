//#include <iostream>
//#define ascii 256
//
//int main() {
//	int weight[ascii]; // веса каждого символа в таблице ASCII
//	for (auto &i : "./test.txt") {
//
//	}
//
//}

#include <iostream>
#include <fstream>
#define ascii 256
using namespace std;

int main() {
	system("chcp 1251");
	system("cls");
	int weight[ascii];
	for (auto& i : weight)
		i = 0;
	{ // эти скобки - область чтения содержимого файла
		ifstream file("ZXC.txt");
		char ch;
		while (file.get(ch)) {
			++weight[(unsigned char)ch];
		}
		file.close();
	}
	//ifstream file("./test.txt");
	//if (file.is_open()) {
	//	unsigned char ch;
	//	file.read((char*)&ch, sizeof(ch));
	//	cout << ch << endl;
	//	++weight[ch];
	//}
	//file.close(); // альтернативный способ чтения файлов, ОДНАКО он блять читает один символ 
	for (int i = 0; i < ascii; ++i) {
		if (weight[i] > 0) {
			cout << weight[i] << " " << (char)i << endl;
		}
	} // вывод сколько веса символов ascii
}