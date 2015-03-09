#include <Python.h>
class MyClass {
	public:
		int add(int x,int y) { return x+y; }
};
extern "C" int add(int x,int y)
{
	MyClass obj;
	return obj.add(x,y);
}
