#pragma once
#include"BitMap.h"

size_t BKDRHash(const char *str)  
{  
	register size_t hash = 0;  
    while (size_t ch = (size_t)*str++)  
    {         
        hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..         
	}      
	return hash;  
}    

size_t SDBMHash(const char *str)  
{  
	register size_t hash = 0;  
    while (size_t ch = (size_t)*str++)  
    {  
        hash = 65599 * hash + ch;         
        //hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
    }  
    return hash;  
}  
 
size_t RSHash(const char *str)  
{  
    register size_t hash = 0;  
    size_t magic = 63689;     
    while (size_t ch = (size_t)*str++)  
    {  
        hash = hash * magic + ch;  
        magic *= 378551;  
	}  
    return hash;  
}  
  
size_t APHash(const char *str)  
{  
    register size_t hash = 0;  
    size_t ch;  
    for (long i = 0; ch = (size_t)*str++; i++)  
    {  
        if ((i & 1) == 0)  
        {  
            hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
        }  
        else  
        {  
            hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
        }  
    }  
    return hash;  
}    

size_t JSHash(const char *str)  
{  
    if(!*str)        
        return 0;  
    register size_t hash = 1315423911;  
    while (size_t ch = (size_t)*str++)  
    {  
        hash ^= ((hash << 5) + ch + (hash >> 2));  
    }  
    return hash;  
}  
 
struct HashFunction1
{
	size_t operator () (const char *str)
	{
		return BKDRHash(str);
	}
};

struct HashFunction2
{
	size_t operator () (const char *str)
	{
		return SDBMHash(str);
	}
};

struct HashFunction3
{
	size_t operator () (const char *str)
	{
		return RSHash(str);
	}
};

struct HashFunction4
{
	size_t operator () (const char *str)
	{
		return APHash(str);
	}
};

struct HashFunction5
{
	size_t operator () (const char *str)
	{
		return JSHash(str);
	}
};

template<class K = char *,
	     class HashFunc1 = HashFunction1,
		 class HashFunc2 = HashFunction2,
         class HashFunc3 = HashFunction3,
		 class HashFunc4 = HashFunction4,
		 class HashFunc5 = HashFunction5>
class BloomFilter{
public:
	 BloomFilter(size_t size)
	 {
		 _capacity = _GetNextPrime(size);
		 bitmap.Resize(size);
	 }

	 bool Set(const K & key)
	 {
		 int num1 = HashFunc1()(key);
		 int num2 = HashFunc2()(key);
		 int num3 = HashFunc3()(key);
		 int num4 = HashFunc4()(key);
		 int num5 = HashFunc5()(key);

		 bool ret1 = bitmap.Set(num1 % _capacity);
		 bool ret2 = bitmap.Set(num2 % _capacity);
		 bool ret3 = bitmap.Set(num3 % _capacity);
		 bool ret4 = bitmap.Set(num4 % _capacity);
		 bool ret5 = bitmap.Set(num5 % _capacity);

		 return ret1 & ret2 & ret3 & ret4 & ret5; 
	 }

	 bool Find(const K &key)
	 {
		 int num1 = HashFunc1()(key);
		 int num2 = HashFunc2()(key);
		 int num3 = HashFunc3()(key);
		 int num4 = HashFunc4()(key);
		 int num5 = HashFunc5()(key);

		 if(!bitmap.Find(num1 % _capacity))
			 return false;
		 if(!bitmap.Find(num2 % _capacity))
			 return false;
		 if(!bitmap.Find(num3 % _capacity))
			 return false;
		 if(!bitmap.Find(num4 % _capacity))
			 return false;
		 if(!bitmap.Find(num5 % _capacity))
			 return false;

		 return true;
	 }
protected:
	size_t _GetNextPrime(size_t size)
	{
		static const int _PrimeSize = 28;
		static const unsigned long _PrimeList [_PrimeSize] =
		{
			53ul,         97ul,         193ul,       389ul,       769ul,
			1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
			49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
			1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
			50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for(int i = 0;i < 28;++i)
		{
			if(_PrimeList [i] > size)
				return _PrimeList [i];
		}
	}
private:
	BitMap bitmap;
	size_t _capacity;
};