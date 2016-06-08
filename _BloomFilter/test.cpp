#include<stdlib.h>
//#include<iostream>
#include"BloomFilter.h"
using namespace std;


void test()
{
	BloomFilter<> b(100);
	b.Set("土豪");
	b.Set("土豪金");

	bool ret1 = b.Find("土豪");
	bool ret2 = b.Find("土豪金");

	cout<<ret1<<endl;
	cout<<ret2<<endl;

}
int main()
{
	test();
	system("pause");
	return 0;
}