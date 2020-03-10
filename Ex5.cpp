#include <iostream>
#include <string>
#include <fstream>
//#include <filesystem> C++17
using namespace std;
bool encrypt(string filename, int key)
{
	int len;
	string filetext, buf;
	ifstream infile(filename);
	// Читаем файл
	if (!infile) return 0;
	while (!infile.eof()) {
		getline(infile, buf);
		filetext += buf;
	}

	// int fileSize = filesystem::file_size(filename); Новый способ узнать размер файла в C++17

	// infile.seekg(0, ios::end);     
	// int fileSize = infile.tellg(); Еще один способ
	// Но в данном случае использовал просто длину прочитанной строки, чтобы не считать ничего не значащие переносы строки
	if (filetext.length() / 2 < key || key < 1) return 0;
	if (key == 1)
	{
		ofstream outfile(filename + "_enc.txt");
		outfile << filetext;
		return 1;
	}
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
	delete[] matr;
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
