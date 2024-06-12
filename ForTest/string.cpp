#include "string.h"

#include <iostream>
#include <cstring>

String::String()
	: str(nullptr), length(0)
{
	std::cout << "constructor" << std::endl;
}

String::String(const String& other)
	: str(nullptr), length(0)
{
	std::cout << "copy constructor" << std::endl;

	if(other.length != 0)
	{
		this->length = other.length;
		str = new char[length + 1];
		strcpy_s(this->str, length + 1, other.str);
	}
}

String::String(const char* str)
	: str(nullptr), length(0)
{
	std::cout << "str constructor" << std::endl;

	size_t length = std::strlen(str);

	if(str != nullptr && length != 0)
	{
		this->length = length;
		this->str = new char[length + 1];
		strcpy_s(this->str, length + 1, str);
	}
}

String::String(const char arr[], size_t size)
	: str(nullptr), length(0)
{
	std::cout << "arr constructor" << std::endl;

	if(arr != nullptr && size != 0)
	{
		length = size;
		str = new char[length + 1];

		for(size_t i = 0; i < length; i++)
			str[i] = arr[i];

		str[length] = '\0';
	}
}

String::String(int* arr, size_t size)
	: str(nullptr), length(0)
{
	std::cout << "int arr constructor" << std::endl;

	if(arr != nullptr && size != 0)
	{
		length = size;
		str = new char[length + 1];

		for(size_t i = 0; i < length; i++)
			str[i] = static_cast<char>(arr[i]);

		str[length] = '\0';
	}
}

String::~String()
{
	std::cout << "destructor" << std::endl;

	delete[] str;
	str = nullptr;
	length = 0;
}

void String::SetString(const char* str)
{
	size_t length = std::strlen(str);

	if(str != nullptr && length != 0)
	{
		delete[] this->str;

		this->length = length;
		this->str = new char[length + 1];
		strcpy_s(this->str, length + 1, str);
	}
}

void String::SetString(const String& other)
{
	if(other.length != 0)
	{
		delete[] str;

		this->length = other.length;
		str = new char[length + 1];
		strcpy_s(this->str, length + 1, other.str);
	}
}

void String::SetString(const char arr[], size_t size)
{
	if(arr != nullptr && size != 0)
	{
		delete[] str;

		length = size;
		str = new char[length + 1];

		for(size_t i = 0; i < length; i++)
			str[i] = arr[i];

		str[length] = '\0';
	}
}