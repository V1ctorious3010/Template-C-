// g++ test.cpp -o test -mconsole
#include <bits/stdc++.h>
using namespace std;
class A
{
public:
	A() { cout << "A constructor" << endl; }
	~A() { cout << "A destructor" << endl; }
	virtual void print() { cout << "A print" << endl; }
};
class B : public A
{	
public:
	B() { cout << "B constructor" << endl; }
	~B() { cout << "B destructor" << endl; }
	void print() override { cout << "B print" << endl; }
};
class C : public A
{			
public:
	C() { cout << "C constructor" << endl; }
	~C() { cout << "C destructor" << endl; }
	void print() override{ cout << "C print" << endl; }
};
class D :  public B,  public C
{
public:
	D() { cout << "D constructor" << endl; }
	~D() { cout << "D destructor" << endl; }
	void print() override { cout << "D print" << endl; }
};

int main()
{
	D d;
	d.print();
	// A *p = new D();
	// p->print();
}