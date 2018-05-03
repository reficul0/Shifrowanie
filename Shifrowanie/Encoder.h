#pragma once
#include "IEncoder.h"
#include <fstream>

using namespace std;
class Encoder : public IEncoder
{
private:
	char* _fileName;

	void EncodeWordIntoString(char *str, const char encryptedWord);

public:
	void SetFileName(const char *ifileName);

	void Encode();

	Encoder();
	Encoder(const char *ifileName);
	~Encoder();
};

