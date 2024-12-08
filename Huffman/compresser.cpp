#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#define ascii 256
using namespace std;

int main() {
	system("chcp 1251");
	system("cls");
	int weight[ascii];
	for (auto& i : weight)
		i = 0;
	{ // ��� ������ - ������� ������ ����������� �����, ����� �� �������
		ifstream file("text.txt");
		char ch;
		while (file.get(ch)) {
			++weight[(unsigned char)ch]; // ��� ������ �������
		}
		/*file.close();*/
	}
	/*for (int i = 0; i < ascii; ++i) {
		if (weight[i] > 0) {
			cout << weight[i] << " " << (char)i << endl;
		}
	}*/ // ����� ������� ���� �������� ascii
	multimap <int, int> sortedWeight; // ������� � ������ �������� (���, ����). ������ int ��������� �� ������ � ��������� ������

	struct Node // ����
	{
		char ch; // ������, ������������� ����
		int parent; // ��� ��������
		int zero; // ��� ����� � 1 
		int one; // ��� ����� � 0
		bool branch; // ����� �� �������� � ����
	};

	vector<Node> tree; // ���� ������ (��������� �����)
	map<char, int> charMap;
	for (size_t i = 0; i < ascii; ++i) 
	{
		if (weight[i] > 0) 
		{
			tree.push_back(Node{ (char)i, -1, -1, -1, false }); // � ������ ������ ���� (����� ������� (�������))
			charMap[i] = tree.size() - 1;
			sortedWeight.insert(make_pair(weight[i], tree.size() - 1)); // tree.size-1 - ������ ������ ������. ����� ������ ������, ��� ��������� � ����� ������
		}
	}
	while (sortedWeight.size() > 1) // ������� ��������� ����� (������ ��������)  
	{
		int w0 = begin(sortedWeight)->first;
		int n0 = begin(sortedWeight)->second;
		sortedWeight.erase(begin(sortedWeight));
		int w1 = begin(sortedWeight)->first;
		int n1 = begin(sortedWeight)->second;
		sortedWeight.erase(begin(sortedWeight));
		tree.push_back(Node{'\0', -1, n0, n1, false});
		tree[n0].parent = tree.size() - 1;
		tree[n0].branch = false;
		tree[n1].parent = tree.size() - 1;
		tree[n1].branch = true;
		sortedWeight.insert(make_pair(w0 + w1, tree.size() - 1));
	}

	vector<bool> data;

	{ // ��� ������ - ������� ������ ����������� �����, ����� �� �������
		ifstream file("text.txt");
		char ch;
		while (file.get(ch)) // ��������� 1 ������ �� �����
		{
			auto n = tree[charMap[ch]];
			vector<bool> compressedChar;
			while (n.parent != -1) 
			{
				compressedChar.push_back(n.branch);
				n = tree[n.parent];
			}
			data.insert(end(data), compressedChar.rbegin(), compressedChar.rend()); // ���������� � �������� �������, ������ ��� �� �������. (���������� � ������������ � ������ ��������)
		}
		/*file.close();*/
	}
	ofstream file("text.huff");
	int treeSize = tree.size();
	file.write((char *)&treeSize, sizeof(treeSize));
	for (auto i : tree)
		file.write((char *)&i, sizeof(i));

	for (size_t i = 0; i < data.size() / 8; ++i) // �� ���� ���� i <= data.size() / 8 ����� �� ���� ������ ��������, ������ ������ ������ (g++ �� ������)
	{
		unsigned char ch = 0;
		for (int j = 0; j < 8; ++j)
			if (data[i * 8 + j])
				ch |= (1 << j);
		file.write((char *)&ch, sizeof(ch));
	}
}