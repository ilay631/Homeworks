#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<class Type>
class MySharedPointer {
	typedef MySharedPointer<Type> t_SharedPointer;
private:
	Type* p;
	unsigned int referenceCount = 0;

public: //Constructors and destructor.
	MySharedPointer() {
		this->p = nullptr;
	}

	MySharedPointer(Type* pObj) {
		this->p = pObj;
		this->referenceCount++;
	}
	// Move constructor;
	MySharedPointer(t_SharedPointer&& uniquePTR) noexcept{ 
		this->p = uniquePTR.get();
		this->referenceCount++;
		uniquePTR.release();
	}

	MySharedPointer(const t_SharedPointer& ptr) {
		this->p = ptr.get();
		this->referenceCount++;
	}

	~MySharedPointer() {
		delete this->p;
	}
public: // Assignment
	t_SharedPointer& operator=(t_SharedPointer&& sharedPointer) {
		this->p = sharedPointer.get();
		this->referenceCount++;
		sharedPointer.release();
	}
	
	t_SharedPointer& operator=(Type* pObject) {
		this->p = pObject;
		this->referenceCount++;
	}

	t_SharedPointer& operator=(const t_SharedPointer& sharedPointer) {
		this->p = sharedPointer.get();
		this->referenceCount++;
	}
public: // Observers.
	Type& operator*() const{
		return *this->p;
	}

	Type* operator->() const {
		return this->p;
	}

	Type* get() const {
		return this->p;
	}

	operator bool() const {
		return this->p != nullptr;
	}

public: // Modifiers.
	void release() {
		this->p = nullptr;
		this->referenceCount = 0;
	}

	void reset(Type* pObject = nullptr) {
		this->p = pObject;
		this->referenceCount = 1;
	}
};


int main() {
	vector<MySharedPointer<int>> vect;
	for (int i = 0; i < 5; i++) {
		int a = rand();
		int* p_a = &a;
		vect.push_back(MySharedPointer<int>(p_a));
	}

	for (int i = 0; i < 5; i++)
		cout << vect[i] << endl;
	


	return 0;
}
