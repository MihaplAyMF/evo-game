#pragma once

class String
{
public:
	String();
	String(const String& other);
	String(const char* str);
	String(const char arr[], size_t size);
	String(int* arr, size_t size);

	//String(String&& other);

	~String();

	const char* GetString() const { return str ? str : ""; }
	size_t GetLenght() const { return length; }
	bool IsEmpty() const { return length == 0; }

	void SetString(const char* str);
	void SetString(const String& other);
	void SetString(const char arr[], size_t size);

private:
	char* str;
	size_t length;


};