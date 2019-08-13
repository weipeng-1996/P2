#include<iostream>
#include <typeinfo>
using namespace std;

namespace CppTest {

// 补全函数
void test1();
void test2();
void test3();
static int peopleNumber = 0;
static int manNumber = 0;
static int womanNumber = 0;
// 补全类的定义
class Person{

public:
	Person( )
		{ peopleNumber ++; cout<<"person"<<endl; }
	virtual ~Person() {
		peopleNumber--; cout << "person--" << endl;
	}
};

class Man : public Person{

public:
	Man() {
		manNumber++;
		cout << "man" << endl;
	}
	~Man() {
		manNumber--;
		cout << "man--" << endl;
	}
};

class Woman :public Person {

public:
	Woman(){
		womanNumber++;
		cout << "woman" << endl;
	}
	~Woman() {
		womanNumber--;
		cout << "woman--" << endl;
	}
};
}