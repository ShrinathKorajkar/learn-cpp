#include <iostream>
using namespace std;
/*

int x;
	  int *       p1 = &x;  // non-const pointer to non-const int
const int *       p2 = &x;  // non-const pointer to const int
	  int * const p3 = &x;  // const pointer to non-const int
const int * const p4 = &x;  // const pointer to const int

*p++   // same as *(p++)
*++p   // same as *(++p)
++*p   // same as ++(*p)
(*p)++ // dereference pointer, and post-increment the value it points to

*/
int main()
{
	int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
	int *p = arr;

	cout << "p      : " << p << endl;
	cout << "*p     : " << *p << endl;
	cout << "p++    : " << p++ << endl;
	cout << "++P    : " << ++p << endl;
	cout << "*p++   : " << *p++ << endl;
	cout << "++*p   : " << ++*p << endl;
	cout << "*++p   : " << *++p << endl;

	const int *ptr1 = arr; // cannot change value
	int *const ptr2 = arr; // cannot change reference

	// cout << "*ptr1++:" << ++*ptr1 << endl; // error
	cout << "ptr1++	:" << ++ptr1 << endl;
	cout << "*ptr2++:" << ++*ptr2 << endl;
	// cout << "ptr2++	:" << ptr2++ << endl; // error

	//
	//
	cout << endl;
	int *ptr = new (nothrow) int;
	*ptr = 100;
	cout << "ptr	: " << *ptr << endl;

	int *ptrArr = new int[5];
	for (int i = 0; i < 5; i++)
	{
		cout << ptrArr[i] << " ";
	}
	cout << endl;

	//
	//
	int ar[2][4] = {1, 2, 3, 4, 5, 6, 7, 8};
	cout << *(ar[1] + 2) << *(*(ar + 1) + 2) << 2 [1 [ar]];

	char *lfc[] = {"C", "C++", "Java", "VBA"};
	char *(*pt)[4] = &lfc;
	cout << ++(*pt)[2];

	delete ptr;
	delete[] ptrArr;

	return 0;
}