#include "stdafx.h"
#include <iostream>
#include <algorithm>

using namespace std;

class MyArray {
private:
	int m_size;
public:
	MyArray(int size) : m_size(size) {
		ptr = new int[size];
	}
	int* ptr;

	~MyArray() {
		delete[] ptr;
	}

	//Copy constructor
	MyArray(const MyArray& rhs) : m_size(rhs.m_size), ptr(new int[m_size]){
	//	ptr = new int[m_size];
		//void* ( void* dest, const void* src, std::size_t count );
		std::memcpy(ptr, rhs.ptr, sizeof(int) * rhs.m_size);
		cout << "copy-constrictor is callled\n";
	}

	MyArray& operator=(MyArray& rhs) {
		if (this == &rhs) {
			return *this;
		}
		this->m_size = rhs.m_size;
		int* temp = new int[m_size];
		delete[] this->ptr;
		ptr = temp;
		//void* ( void* dest, const void* src, std::size_t count );
		std::memcpy(ptr, rhs.ptr, sizeof(int) * rhs.m_size); //expensive operation

		cout << "Assignment oper is called\n";

		return *this;
	}

	//Move constructor
	MyArray(MyArray&& rhs) {
		this->ptr = rhs.ptr;
		this->m_size = rhs.m_size;
		rhs.ptr = nullptr;
		rhs.m_size = 0;
		cout << "move constructor is called\n";
	}

	//Assignment move operator
	MyArray& operator=(MyArray&& rhs) {

		if (this == &rhs) {
			return *this;
		}
		this->m_size = rhs.m_size;
		delete[] this->ptr; //Delete the previous data 
		this->ptr = rhs.ptr;
		rhs.ptr = nullptr;
		rhs.m_size = 0;
		cout << "move assignment oper is called\n";
		return *this;
	}


	void printArr() {
		if (ptr != nullptr) {
			for (size_t i = 0; i < m_size; i++) {
				cout << ptr[i] << " ";
			}
			cout << endl;
		}
		else {
			cout << "NULLPTR\n";
		}
		
	}

};

int main()
{
	MyArray a1(3);
	a1.ptr[0] = 12;
	a1.ptr[1] = 23;
	a1.ptr[2] = 56;

	a1.printArr();

	MyArray a2(3);

	a2 = a1;

	a2.printArr();

	MyArray a3 = a1;

	MyArray a4 = move(a1);
	a4.printArr();
	a1.printArr();
	
	a2 = move(a4);

	a2.printArr();

    return 0;
}
