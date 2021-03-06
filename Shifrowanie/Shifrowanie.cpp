// Shifrowanie.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Encoder.h"

using namespace std;

int main()
{
	try
	{
		size_t len = 9;
		
		
		shared_ptr<char> fileShared(new char[len]);

		// file.txt
		gets_s(fileShared.get(), len);
			
		Encoder enc(std::move(fileShared));

		enc.Encode();

		return 0;
	}
	catch (const char* str)
	{
		puts(str);
	}
	catch (...)
	{
		puts("error");
	}
}

