// Shifrowanie.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Encoder.h"

using namespace std;


int main()
{
	Encoder enc("file.txt");
	enc.Encode();
    return 0;
}

