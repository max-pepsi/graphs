#include<iostream>
#include<string>
#include<fstream>
#include<set>
#include<queue>
using namespace std;


//�� ������ ���������� �������� �� ����������� ������� ������
//����������� � ������ ���������� ���� : (������� ������������, �������
//	������������).���� ����������� ����� ���������� �� ���� 3 �������.
//	���������� :
//	1) ����� �� ������ ����������, �� ���� ����� �� ��������� ���
//	����������;
//2) ������� ����� ����� ��������� �� K ����.

int n_people = 13;
int k = 1;


set <string> find_sources(set <pair <string, string>> arcs) {
	set <string> sources;

	//�������� ��� ������ ����
	for (pair <string, string> arc : arcs) {
		sources.insert(arc.first);
	}
	//������� ��� ����� ����
	for (pair <string, string> arc : arcs) {
		sources.erase(arc.second);
	}
	return sources;
}

//��������� ����� ����������� ������������� ����� ����������
//(����� - ������ ��� ������ ��� ��� �������� � ������), 
//� ����������� � ��������, �� ������ ����� �������� ������ � ��� ������, 
//���� ���-�� � �� ������ �� ������.
bool is_complete(int n_people, set <pair <string, string>> arcs) {
	set <string> ppl;
	for (pair <string, string> arc : arcs) {
		ppl.insert(arc.first);
		ppl.insert(arc.second);
	}
	return(ppl.size() == n_people);
}

//bfs �� ���� ������ �� ����� (���) � ���������� ������ �� ����� �� ����� (3)
int how_many(set <pair <string, string>> arcs, int k) {

	//����� � ������� (� �������) ��������� �������
	queue <string> q;
	set <string> visited = find_sources(arcs);
	for (string v : visited) {
		q.push(v);
	}

	int day = 0;
	string v;
	int s; //q size ��� ������������ �����
	int limit; //3 �������� � ����

	//���� �� �������� ���� ��� ���
	while (!q.empty() && day < k) {

		s = q.size(); //����������� ������� ����� ����� � ������� ��������� ������
		for (int i = 0; i < s; i++) {
			v = q.front();
			q.pop();

			limit = 0;
			for (pair <string, string> arc : arcs) {
				if (arc.first == v) {
					if (limit == 3) break;
					if (visited.find(arc.second) == visited.end()) { //���� �����
						visited.insert(arc.second);
						limit++;
					}
					q.push(arc.second);
				}
			}
			if (limit >= 3) q.push(v); //���� ���� ��� ������� �������� �� �� ���� ����
		}
		day++;
	}
	cout << "���������: ";
	for (string v : visited) {
		cout << v << " ";
	}
	cout << endl;
	return visited.size();
}


//����� �� ����� ������ ��� ������� �����
set <pair <string, string>> read_arcs() {
	ifstream inp_file("D:\\in-outs\\arcs.txt");
	set <pair <string, string>> arcs;
	pair <string, string> arc;
	while (!inp_file.eof()) {
		inp_file >> arc.first >> arc.second;
		arcs.insert(arc);
	}
	inp_file.close();
	return arcs;
}
set <string> read_people() {
	ifstream inp_file("D:\\in-outs\\people.txt");
	set <string> people;
	string person;
	int n = 0;
	while (!inp_file.eof()) {
		getline(inp_file, person);
		if (!person.empty()) {
			people.insert(person);
			n++;
		}
	}
	inp_file.close();
	n_people = n;
	return people;
}


int main() {
	setlocale(LC_ALL, "rus");

	set <string> people = read_people();
	set <pair <string, string>> arcs = read_arcs();

	bool is_compl = is_complete(n_people, arcs);
	if (is_compl) cout << "������ ������. \n"; else cout << "������ ��������. \n";

	cout << "����������� ����� �� " << k << " ���: " << how_many(arcs, k) << endl;

	return 0;

}