#include "stdafx.h"
#include "Encoder.h"

//������� ����������
void Encoder::EncodeWordIntoString(char* str, const char encryptedWord)
{
	for (int i(0); i < 7; ++i)
	{
		int mask = 1; 
		mask <<= i; //��������� ����� �������

		if (encryptedWord & mask) //�������� �� ������� � ��������� ���������
			str[i] |= mask; //���� 1, �� ������� �� � 8 ���, ���� 0, �� ��� � ���������
	}
}

//������ ����� �����
void Encoder::SetFileName(const char *ifileName)
{
	if (!ifileName)
		throw "File Name is NULL. Encoder::initFileName";

	size_t size(0);
	for (; ifileName[size]; ++size);

	if (_fileName)//���� ������ ������. ����������� ������
		delete[] _fileName;

	if (!(_fileName = new char[size + 1]))
		throw "Memory leack. Encoder::initFileName";

	for (size_t i(0); i < size; ++i)//���������� ��� �����, ��� ���������� ��� ����������� �������������
		_fileName[i] = ifileName[i];

	_fileName[size] = '/0';
}
//���������� ������ �� �����
void Encoder::Encode()
{
	ifstream fin("file.txt"/*_fileName*/);
	if(!fin.is_open())//��������� �� ��������
		throw "Cannot open input file. Encoder::Encode";
	
	ofstream fout("encodedFile.txt");
	if (!fout.is_open())
		throw "Cannot open output file. Encoder::Encode";

	const size_t len(8);
	char str[len];
	char encryptedWord;
	while (!fin.eof())//���� �� ����� �����
	{
		fin.get(str, len);

		//���� ����� ���������� �������� � ����� �� ������ 8, 
		//�� ���������� ���������� ������� ��� ��������
		if (fin.eof())
		{
			fout << str;
			break;
		}
		fin.get(encryptedWord);

		EncodeWordIntoString(str, encryptedWord);

		fout << str;//���������� ������������� �������
	}
}

Encoder::Encoder()
{
	_fileName = nullptr;
}

Encoder::Encoder(const char *ifileName)
{
	SetFileName(ifileName);//������������� ��� �����
}


Encoder::~Encoder()
{
	if (_fileName)
		delete []_fileName;

	_fileName = nullptr;
}
