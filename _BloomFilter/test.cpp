#include<stdlib.h>
//#include<iostream>
#include"BloomFilter.h"
using namespace std;


void test()
{
	BloomFilter<> b(100);
	b.Set("����");
	b.Set("������");

	bool ret1 = b.Find("����");
	bool ret2 = b.Find("������");

	cout<<ret1<<endl;
	cout<<ret2<<endl;

}
int main()
{
	test();
	system("pause");
	return 0;
}