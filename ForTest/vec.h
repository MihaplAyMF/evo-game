#pragma once

#include <vector>

class MyVector
{
private:

	int mSize;
	int mCapacity;
	int* mArr;

public:
	MyVector(size_t mCapacity = 0);
	MyVector(const MyVector& other);
	//MyVector(MyVector&& other) noexcept;
	MyVector(int* arr, size_t size);
	~MyVector();

	void push_back(int num);
	void pop_back();
	void show();

	int size();
	int& operator[](size_t index);
};
