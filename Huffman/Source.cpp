//#include <iostream>
//#define ascii 256
//
//int main() {
//	int weight[ascii]; // ���� ������� ������� � ������� ASCII
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
	{ // ��� ������ - ������� ������ ����������� �����
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
	//file.close(); // �������������� ������ ������ ������, ������ �� ����� ������ ���� ������ 
	for (int i = 0; i < ascii; ++i) {
		if (weight[i] > 0) {
			cout << weight[i] << " " << (char)i << endl;
		}
	} // ����� ������� ���� �������� ascii
}