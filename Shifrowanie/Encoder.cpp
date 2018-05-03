#include "stdafx.h"
#include "Encoder.h"

//функция шифрования
void Encoder::EncodeWordIntoString(char* str, const char encryptedWord)
{
	for (int i(0); i < 7; ++i)
	{
		int mask = 1; 
		mask <<= i; //побитовый сдвиг единицы

		if (encryptedWord & mask) //проверка на единицу в побитовом сравнении
			str[i] |= mask; //если 1, то заносим ее в 8 бит, если 0, то так и оставляем
	}
}

//сеттер имени файла
void Encoder::SetFileName(const char *ifileName)
{
	if (!ifileName)
		throw "File Name is NULL. Encoder::initFileName";

	size_t size(0);
	for (; ifileName[size]; ++size);

	if (_fileName)//если память занята. освобождаем память
		delete[] _fileName;

	if (!(_fileName = new char[size + 1]))
		throw "Memory leack. Encoder::initFileName";

	for (size_t i(0); i < size; ++i)//записываем имя файла, для возможного его дальнейшего использования
		_fileName[i] = ifileName[i];

	_fileName[size] = '/0';
}
//шифрование данных из файла
void Encoder::Encode()
{
	ifstream fin("file.txt"/*_fileName*/);
	if(!fin.is_open())//проверяем на открытие
		throw "Cannot open input file. Encoder::Encode";
	
	ofstream fout("encodedFile.txt");
	if (!fout.is_open())
		throw "Cannot open output file. Encoder::Encode";

	const size_t len(8);
	char str[len];
	char encryptedWord;
	while (!fin.eof())//пока не конец файла
	{
		fin.get(str, len);

		//если общее количество символов в файле не кратно 8, 
		//то записываем оставшиеся символы без шифровки
		if (fin.eof())
		{
			fout << str;
			break;
		}
		fin.get(encryptedWord);

		EncodeWordIntoString(str, encryptedWord);

		fout << str;//записываем зашифрованные символы
	}
}

Encoder::Encoder()
{
	_fileName = nullptr;
}

Encoder::Encoder(const char *ifileName)
{
	SetFileName(ifileName);//устанавливаем имя файлу
}


Encoder::~Encoder()
{
	if (_fileName)
		delete []_fileName;

	_fileName = nullptr;
}
