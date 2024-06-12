#include "vec.h"

#include <iostream>

MyVector::MyVector(size_t mCapacity)
		: mCapacity(mCapacity), mSize(0), mArr(new int[mCapacity])
{
	std::cout << "constructor" << std::endl;
}

MyVector::MyVector(const MyVector& other)
		: mCapacity(other.mCapacity), mSize(other.mSize), mArr(new int[other.mCapacity])

{
	std::cout << "copy constructor" << std::endl;

	for(size_t i = 0; i < other.mSize; i++)
		mArr[i] = other.mArr[i];

}

//MyVector::MyVector(MyVector&& other) noexcept
//		: mSize(other.mSize), mCapacity(other.mCapacity), mArr(other.mArr)
//{
//	std::cout << "move constructor" << std::endl;
//	other.mSize = 0;
//	other.mCapacity = 0;
//	other.mArr = nullptr;
//}

MyVector::MyVector(int* arr, size_t size)
{
	std::cout << "vec constructor" << std::endl;

	mSize = size;
	mCapacity = size;
	mArr = new int[mCapacity];

	for(size_t i = 0; i < size; i++)
	{
		mArr[i] = arr[i];
	}
}

MyVector::~MyVector()
{
	std::cout << "destructor" << std::endl;

	delete[] mArr;
}

void MyVector::push_back(int num)
{
	if(mSize < mCapacity)
	{
		mArr[mSize] = num;
		mSize++;
	}
}

void MyVector::pop_back()
{
	if(mSize > 0)
	{
		mArr[mSize - 1] = 0;
		mSize--;
	}
}

void MyVector::show()
{
	for(size_t i = 0; i < size(); i++)
	{
		std::cout << mArr[i] << " ";
	}
	std::cout << std::endl;
}

int MyVector::size()
{
	return mSize;
}

int& MyVector::operator[](size_t index)
{
	return mArr[index];
}
