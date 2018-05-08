#include "stdafx.h"
#include "Encoder.h"


/// <summary>
///		шифрование символа среди последних битов 7 симолов
/// </summary>
/// <param name="str">строка из 7 символов</param>
/// <param name="encryptedWord">шифруемое слово</param>
/// <remarks>
///		чтобы закодировать все 255 симовлов 
///		в кодировке ASCII достаточно 7 бит, 
///		т.к. тип char занимает в памяти 8 бит 
///		мы можем произвести сжатие через этот незначащий бит
/// </remarks>
void Encoder::EncodeWordIntoString(char *str, const char encryptedWord)
{ 
	// количество бит, которые несут смысловую нагрузку
	size_t countSignificantBits = 7;

	for (size_t i(0); i < countSignificantBits; ++i)
	{
		unsigned char mask = 1; 
		mask <<= i; //побитовый сдвиг единицы

		// если в 8 бите шифруемого слова единица
		if (encryptedWord & mask)
		{
			// досдвинем единицу в маске до 8 бита
			mask <<= countSignificantBits - i;

			// заносим единицу в 8 бит
			str[i] |= mask;
		}
		// если в 8 бите 0
		else 
		{
			// досдвинем единицу в маске до 8 бита
			mask <<= countSignificantBits - i;

			// обезопасим себя от 
			// возможно стоящей в 8 бите единицы
			str[i] &= ~mask;
		}
	}
}

/// <summary>
///		сеттер имени файла
/// </summary>
/// <param name="ifileName">
///		устанавливаемое имя файла 
/// </param>
void Encoder::SetFileName(shared_ptr<char> &&ifileName)
{
	if (!ifileName)
		throw "File Name is NULL. Encoder::initFileName";

	ifileName.swap(_fileName);;
}

/// <summary>
///		функция сжатия файла методом 
///		свободного последнего бита
/// </summary>
/// <returns>
///		true	удачное сжатие
///		false	неудачное
/// </returns>
/// <remarks>only for ASCII</remarks>
bool Encoder::Encode()
{
	// не шифруем если не указан источник
	if (!_fileName)
		return false;

	ifstream fin(_fileName.get());
	if(!fin.is_open())//проверяем на открытие
		throw	"Cannot open input file. Encoder::Encode";
	
	ofstream fout("encodedFile.txt");
	if (!fout.is_open())
		throw	"Cannot open output file. Encoder::Encode";

	const size_t len(8);
	char str[len];
	char encryptedWord;

	// шифруем весь файл
	while (!fin.eof())
	{
		fin.get(str, len);

		// если количество символов в файле не кратно 8, 
		// записываем оставшиеся символы без шифровки
		if (fin.eof())
		{
			fout << str;
			break;
		}
		fin.get(encryptedWord);

		EncodeWordIntoString(str, encryptedWord);

		// выводим зашифрованные символы
		fout << str;
	}
}

Encoder::Encoder()
{
	_fileName = nullptr;
}

Encoder::Encoder(shared_ptr<char> && ifileName)
{
	SetFileName(std::move(ifileName));//устанавливаем имя файлу
}

