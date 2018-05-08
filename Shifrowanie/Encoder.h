#pragma once
#include "IEncoder.h"
#include <fstream>
#include <memory>

using namespace std;
class Encoder : public IEncoder
{
private:
	shared_ptr<char> _fileName;

	// ���������� ������� ����� ��������� ����� 7 �������
	void EncodeWordIntoString(char *str, const char encryptedWord);

public:
	// ������ ����� �����
	void SetFileName(shared_ptr<char> && ifileName);

	// ����������� ����
	bool Encode();

	Encoder();
	Encoder(shared_ptr<char> &&ifileName);
};

