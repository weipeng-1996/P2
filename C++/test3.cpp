#include"test.h"
namespace CppTest{

void test3( )
{
	cout<<"========== test3 =========="<<endl;

	Person* people[4];
	for ( int i = 0; i < 2; i ++ )
		people[i] = new Man( );

	for ( int i = 2; i < 4; i ++ )
		people[i] = new Woman( );

	for ( int i = 0; i < 4; i ++ )
		delete people[i];

	if ( manNumber != 0 )
		cout<<"Please check, man leak : "<<manNumber<<endl;

	if ( womanNumber != 0 )
		cout<<"Please check, woman leak : "<<womanNumber<<endl;
}

}