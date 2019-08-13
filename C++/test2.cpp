#include"test.h"
namespace CppTest{
template <class T>

int getArrayLen(T& array){
	return (sizeof(array) / sizeof(array[0]));
}

void quickSort(int arr[],int l, int r) {
	if (l < r) {
		int i = l, j = r;
		int key = arr[l];
		while(i < j) {
			while (i < j && arr[j] >= key) {
				j--;
			}
			if (i < j) {
				arr[i++] = arr[j];
			}
			while (i < j && arr[i] < key) {
				i++;
			}
			if (i < j) {
				arr[j--] = arr[i];
			}
		}
		arr[i] = key;
		for (int i = 0; i < 12; i++) {
			if (i == 11) {
				cout << arr[i] << endl;
				break;
			}
			cout << arr[i] << "¡¡";
		}
		quickSort(arr, l, i - 1);
		quickSort(arr, i + 1, r);
	}
}

int binary_search(int arr[], int low, int high, int x) {
	if (low > high) {
		if (high < 0)
			return 0;
		else
			return high;
	}
	int mid = low + (high - low) / 2;
	if (x == arr[mid]) {
		return mid;
	}
	else if (x < arr[mid]) {
		if (x >= arr[mid-1])
			return mid;
		else
			binary_search(arr, low, mid - 1, x);
	}
	else {
		if (mid == high)
			return high + 1;
		else
			binary_search(arr, mid + 1, high, x);
	}
}

void test2( )
{
	cout<<"========== test2 =========="<<endl;
	
	int a[] = {10,47,21,33,15,26,87,8,2,99,5,54 };
	
	const int length = sizeof( a ) / sizeof( a[0] );
	quickSort(a, 0, length - 1);
	int target[] = { -1, 8, 55, 102 };
	for (int i = 0; i < 4; i++) {
		cout << binary_search(a, 0, length - 1, target[i]) << endl;
	}
}

}