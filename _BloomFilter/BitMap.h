#pragma once
#include<iostream>
#include<vector>
using namespace std;

class BitMap
{
public:
	BitMap()
		:_size(0)
	{}
	BitMap(size_t size)
		:_size(0)
	{
		_array.resize((size>>5) + 1);
	}
	bool Set(const int num)
	{
		size_t index = num >> 5;
		size_t bit = num % 32;
		if( (_array[index]  & (1<<bit) ) > 0)   //����Ѿ�����
		{
			return false;
		}
		_array[index] |= (1<<bit);
		++_size;
		return true;
	}
	bool Reset(const int num)     //���ĳһ����
	{
		size_t index = num >> 5;    //�������һ����
		size_t bit = num % 32;   //������ĸ�λ
		if(_array[index]  & (1<<bit) > 0)
		{
			_array[index] &= ~(1<<bit); 
			--_size;
			return true;
		}
		return false;
	}
	bool Find(const int num)
	{
		size_t index = num>>5;
		size_t bit = num % 32;
		if( (_array[index]  & (1<<bit)) > 0)
		{
			return true;
		}
		return false;
	}
	void Clear()
	{
		_array.assign(_array.size(),0);
	}
	void Resize(size_t size)
	{
		_array.resize(size);
	}
private:
	vector<int> _array;
	size_t _size;
};