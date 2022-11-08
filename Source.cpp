#include<iostream>
#include<string>
#include<fstream>
#include<set>
#include<queue>
using namespace std;


//На случай экстренной ситуации на предприятии имеется список
//сотрудников и список оповещения вида : (фамилия оповещающего, фамилия
//	оповещаемого).Один оповещающий может оповестить за день 3 человек.
//	Определить :
//	1) полон ли список оповещения, то есть будут ли оповещены все
//	сотрудники;
//2) сколько людей будет оповещено за K дней.

int n_people = 13;
int k = 1;


set <string> find_sources(set <pair <string, string>> arcs) {
	set <string> sources;

	//записать все начала рёбер
	for (pair <string, string> arc : arcs) {
		sources.insert(arc.first);
	}
	//удалить все концы рёбер
	for (pair <string, string> arc : arcs) {
		sources.erase(arc.second);
	}
	return sources;
}

//поскольку любой оповещающий автоматически знает информацию
//(иначе - откуда она берётся или кто получает её первым), 
//а оповещаемый её получает, то список будет неполным только в том случае, 
//если кто-то в нём совсем не указан.
bool is_complete(int n_people, set <pair <string, string>> arcs) {
	set <string> ppl;
	for (pair <string, string> arc : arcs) {
		ppl.insert(arc.first);
		ppl.insert(arc.second);
	}
	return(ppl.size() == n_people);
}

//bfs но есть предел на волны (дни) и количество вершин от одной за волну (3)
int how_many(set <pair <string, string>> arcs, int k) {

	//кладу в очередь (и визитед) стартовые вершины
	queue <string> q;
	set <string> visited = find_sources(arcs);
	for (string v : visited) {
		q.push(v);
	}

	int day = 0;
	string v;
	int s; //q size для отслеживания волны
	int limit; //3 человека в день

	//пока не кончился граф или дни
	while (!q.empty() && day < k) {

		s = q.size(); //отслеживать вершины одной волны в очереди запоминая размер
		for (int i = 0; i < s; i++) {
			v = q.front();
			q.pop();

			limit = 0;
			for (pair <string, string> arc : arcs) {
				if (arc.first == v) {
					if (limit == 3) break;
					if (visited.find(arc.second) == visited.end()) { //верш новая
						visited.insert(arc.second);
						limit++;
					}
					q.push(arc.second);
				}
			}
			if (limit >= 3) q.push(v); //если есть ещё вершины проверим их на след день
		}
		day++;
	}
	cout << "Оповещено: ";
	for (string v : visited) {
		cout << v << " ";
	}
	cout << endl;
	return visited.size();
}


//взять из файла потому что вводить долго
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
	if (is_compl) cout << "Список полный. \n"; else cout << "Список неполный. \n";

	cout << "Оповещённых людей за " << k << " дня: " << how_many(arcs, k) << endl;

	return 0;

}