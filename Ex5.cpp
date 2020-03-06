#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool encrypt(string filename, int key)
{
	string filetext, buf;
	ifstream infile(filename);

// Читаем файл
	if (!infile) return 0;
	while (!infile.eof()) {
		getline(infile, buf);
		filetext += buf;
	}

	if (filetext.length() / 2 < key) return 0;

// Инициализируем массив
	char* matr = new char[key * filetext.length()]();
	bool dir = 0;
	int row = 0, col = 0;

// Записываем содержимое файла в массив, меняя направление при достижении 0 или key-1
	for (int i = 0; i < filetext.length(); i++) {
		if (row == 0 || row == key - 1) dir = !dir;
		matr[row * filetext.length() + col++] = filetext[i];
		dir ? row++ : row--;
	}

//Записываем строку, игнорируя \0.
	string result;
	for (int i = 0; i < key; i++)
		for (int j = 0; j < filetext.length(); j++)
			if (matr[i * filetext.length() + j] != '\0')
				result.push_back(matr[i * filetext.length() + j]);
	ofstream outfile(filename + "_enc.txt");
	outfile << result;
	outfile.close();
	infile.close();
	return 1;
}

int main(int argc, char* argv[])
{
	int key = 3;
	//Для проверки работы принимаем путь к файлу как аргумент командной строки
	if (argc == 1)
	{
		cout << "Please write command line agruments" << endl;
		return -1;
	}
	return encrypt(argv[1], key);
}
