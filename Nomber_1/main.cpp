#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ret {
	bool fl = false;
	int m = 0;
};

struct id {
	string i;
	vector <string> mov;
	bool start = false;
	bool end = false;
};

ret maxString(vector <string> str, vector <id> ID, int pos) {
	ret A;
	vector <string> x;
	string l;
	int s, e;

	for (int i = 0; i < ID.size(); i++) // Находим номера стартового и конечного элемента
		if (ID[i].start == true)
			s = i;
		else if (ID[i].end == true)
			e = i;

	x.push_back(ID[s].i); // Загружаем стартовый символ

	for (int i = pos; i < str.size(); i++) { // Пробегаемся по всей строке
		bool fl = false;
		for (int j = 0; j < x.size(); j++) // Сравниваем букву со смежным алфовитом
			if (str[i] == x[j]) {
				l = str[i];
				A.fl = true;
				A.m = i - pos;
				fl = true;
				if (str[i] == ID[e].i) {
					fl = false;
					A.m = i + 1 - pos;
				}
				x.clear();
				break;
			}
		for (int k = 0; k < ID.size(); k++) // Перезаписываем смежный алфавит
			if (l == ID[k].i)
				for (int j = 0; j < ID[k].mov.size(); j++)
					x.push_back(ID[k].mov[j]);
		if (fl == false)
			break;
	}
	return A;
}

int main() {
	setlocale(LC_ALL, "RUS");
	string a;
	ret M;
	id x;
	vector<id> ID;
	vector<string> alph, str;
	int c;
	cout << "Введите размерность алфавита: ";
	cin >> c;

	system("cls");

	for (int i = 0; i < c; i++) {
		do {
			bool fl = false;
			cout << "Введите [" << i << "] элемент алфавита: ";
			cin >> a;
			if (a.size() == 1) {
				for (int j = 0; j < alph.size(); j++)
					if (a == alph[j]) {
						fl = true;
						i--;
					}
				if (fl == false)
					alph.push_back(a);
				else
					cout << "Элемент [" << a << "] уже присутствует в алфавите!\n";
			}
			else
				cout << "Элемент алфавита должен быть длиной в 1 символ\n";
			if (a.size() != 1 || fl == true)
				system("pause");
			system("cls");
		} while (a.size() != 1);
	}

	for (int i = 0; i < alph.size(); i++) {
		system("cls");
		int c;
		string m;
		cout << "Задайте таблицу переходов для символа: " << alph[i] << endl;
		cout << endl;
		for (int j = 0; j < alph.size(); j++)
			cout << alph[j] << " ";
		cout << endl;
		do {
			cout << "\nВведите количество смежных символов для [" << alph[i] << "] " << "(0 - " << alph.size() << "): ";
			cin >> c;
		} while (c < 0 || c > alph.size());
		x.i = alph[i];
		for (int j = 0; j < c; j++) {
			bool fl = false;
			do {
				cout << "Введите [" << j << "] смежность: ";
				cin >> m;
				for (int k = 0; k < alph.size(); k++)
					if (alph[k] == m)
						fl = true;
			} while (fl == false);
			x.mov.push_back(m);
		}
		ID.push_back(x);
		x.mov.clear();
		system("pause");
	}

		system("cls");
		for (int i = 0; i < alph.size(); i++)
			cout << alph[i] << " ";
		cout << "\nВведите начальный символ: ";
		cin >> a;
		for (int i = 0; i < ID.size(); i++)
			if (ID[i].i == a)
				ID[i].start = true;
		cout << "\nВведите конечный символ: ";
		cin >> a;
		for (int i = 0; i < ID.size(); i++)
			if (ID[i].i == a)
				ID[i].end = true;

		system("cls");
		cout << "Введите строку для проверки: ";
		cin >> a;

		for (int i = 0; i < a.size(); i++) {
			str.push_back(a.substr(i, 1));
		}

		system("cls");
		cout << "===Был получен следующий алфавит===\n\n";
		for (int i = 0; i < alph.size(); i++)
			cout << alph[i] << " ";
		cout << "\n\n===Была получена следующая смежность===\n\n";
		for (int i = 0; i < ID.size(); i++) {
			cout << ID[i].i << ": ";
			for (int j = 0; j < ID[i].mov.size(); j++)
				cout << ID[i].mov[j] << " ";
			cout << endl;
		}
		cout << "\n";
		cout << "===Была получена следующая строка===\n\n";
		for (int i = 0; i < str.size(); i++)
			cout << i << " ";
		cout << endl;
		for (int i = 0; i < str.size(); i++)
			if (i < 10)
				cout << str[i] << " ";
			else
				cout << str[i] << "  ";
		cout << endl;

		cout << "\n";
		for (int i = 0; i < ID.size(); i++)
			if (ID[i].start == true)
				cout << "Начальный символ: " << ID[i].i << endl;
			else if (ID[i].end == true)
				cout << "Конечный символ: " << ID[i].i << endl;

		cout << endl;
		cout << "\nВведите с какой позиции начать поиск (0 - " << a.size() - 1 << "): ";
		cin >> c;
		M = maxString(str, ID, c);
		cout << "\n Нашлась ли необходимая строка: ";
		if (M.fl)
			cout << "Да";
		else
			cout << "Нет";
		cout << "\n Максимальная длина строки, начиная с позиции [" << c << "]: " << M.m;
		cout << "\n Найденная строка: ";
		for (int i = c; i < c + M.m; i++)
			cout << str[i] << " ";
		cout << "\n" << endl;
		system("pause");
		return 0;
	}