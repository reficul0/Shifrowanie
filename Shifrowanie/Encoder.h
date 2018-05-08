#pragma once
#include "IEncoder.h"
#include <fstream>
#include <memory>

using namespace std;
class Encoder : public IEncoder
{
private:
	shared_ptr<char> _fileName;

	// шифрование символа среди последних битов 7 симолов
	void EncodeWordIntoString(char *str, const char encryptedWord);

public:
	// сеттер имени файла
	void SetFileName(shared_ptr<char> && ifileName);

	// Зашифровать файл
	bool Encode();

	Encoder();
	Encoder(shared_ptr<char> &&ifileName);
};

