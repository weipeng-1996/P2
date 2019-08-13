#include"test.h"
namespace CppTest{

void test1( )
{
	cout << "--------------各个类型的size----------------" << endl;
	cout << "int:" << sizeof(int) << endl;
	cout << "long:" << sizeof(long) << endl;
	cout << "char:" << sizeof(char) << endl;
	cout << "short:" << sizeof(short) << endl;
	cout << "double:" << sizeof(double) << endl;
	cout << "float:" << sizeof(float) << endl;
	cout << "unsigned:" << sizeof(unsigned) << endl;
	cout << "unsigned char:" << sizeof(unsigned char) << endl;
	cout << "3.14:" << sizeof(3.14) << endl;
	cout << "3.14f:" << sizeof(3.14f) << endl;
	cout << "3:" << sizeof(3) << endl;
	cout << "0xABC:" << sizeof(0xABC) << endl;
	cout << "a:" << sizeof('a') << endl;
	cout << "abc:" << sizeof("abc") << endl;
	cout << "1e-5f:" << sizeof(1e-5f) << endl;
	cout << "L\"ab\":" << sizeof(L"ab") << endl;
	cout<<typeid(L"ab").name()<<endl;
}

}