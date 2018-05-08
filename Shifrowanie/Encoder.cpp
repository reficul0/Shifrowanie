#include "stdafx.h"
#include "Encoder.h"


/// <summary>
///		���������� ������� ����� ��������� ����� 7 �������
/// </summary>
/// <param name="str">������ �� 7 ��������</param>
/// <param name="encryptedWord">��������� �����</param>
/// <remarks>
///		����� ������������ ��� 255 �������� 
///		� ��������� ASCII ���������� 7 ���, 
///		�.�. ��� char �������� � ������ 8 ��� 
///		�� ����� ���������� ������ ����� ���� ���������� ���
/// </remarks>
void Encoder::EncodeWordIntoString(char *str, const char encryptedWord)
{ 
	// ���������� ���, ������� ����� ��������� ��������
	size_t countSignificantBits = 7;

	for (size_t i(0); i < countSignificantBits; ++i)
	{
		unsigned char mask = 1; 
		mask <<= i; //��������� ����� �������

		// ���� � 8 ���� ���������� ����� �������
		if (encryptedWord & mask)
		{
			// ��������� ������� � ����� �� 8 ����
			mask <<= countSignificantBits - i;

			// ������� ������� � 8 ���
			str[i] |= mask;
		}
		// ���� � 8 ���� 0
		else 
		{
			// ��������� ������� � ����� �� 8 ����
			mask <<= countSignificantBits - i;

			// ���������� ���� �� 
			// �������� ������� � 8 ���� �������
			str[i] &= ~mask;
		}
	}
}

/// <summary>
///		������ ����� �����
/// </summary>
/// <param name="ifileName">
///		��������������� ��� ����� 
/// </param>
void Encoder::SetFileName(shared_ptr<char> &&ifileName)
{
	if (!ifileName)
		throw "File Name is NULL. Encoder::initFileName";

	ifileName.swap(_fileName);;
}

/// <summary>
///		������� ������ ����� ������� 
///		���������� ���������� ����
/// </summary>
/// <returns>
///		true	������� ������
///		false	���������
/// </returns>
/// <remarks>only for ASCII</remarks>
bool Encoder::Encode()
{
	// �� ������� ���� �� ������ ��������
	if (!_fileName)
		return false;

	ifstream fin(_fileName.get());
	if(!fin.is_open())//��������� �� ��������
		throw	"Cannot open input file. Encoder::Encode";
	
	ofstream fout("encodedFile.txt");
	if (!fout.is_open())
		throw	"Cannot open output file. Encoder::Encode";

	const size_t len(8);
	char str[len];
	char encryptedWord;

	// ������� ���� ����
	while (!fin.eof())
	{
		fin.get(str, len);

		// ���� ���������� �������� � ����� �� ������ 8, 
		// ���������� ���������� ������� ��� ��������
		if (fin.eof())
		{
			fout << str;
			break;
		}
		fin.get(encryptedWord);

		EncodeWordIntoString(str, encryptedWord);

		// ������� ������������� �������
		fout << str;
	}
}

Encoder::Encoder()
{
	_fileName = nullptr;
}

Encoder::Encoder(shared_ptr<char> && ifileName)
{
	SetFileName(std::move(ifileName));//������������� ��� �����
}

