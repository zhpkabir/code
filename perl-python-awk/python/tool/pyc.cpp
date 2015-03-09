#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/to_python_converter.hpp>
#include <vector>
#include <Python.h>

using namespace std;
using namespace boost::python;
namespace HelloPython{
	char const* sayHello(){
		return "Hello from boost::python";
	}
	class HelloClass{
		public:
			HelloClass(const string& name):name(name){
			}
		public:
			string sayHello(){
				return "Hello from HelloClass by : " + name;
			}
		private:
			string name;
	};

	string sayHelloClass(HelloClass& hello){
		return hello.sayHello() + " in function sayHelloClass";
	}

	typedef vector<int> ivector;

	void showPerson(string name,int age=30,string nationality="China"){
		cout << name << " " << age << " " << nationality << endl;
	}

	BOOST_PYTHON_FUNCTION_OVERLOADS(showPerson_overloads,showPerson,1,3) 

		BOOST_PYTHON_MODULE(HelloPython){

			def("sayHello",sayHello);

			class_("HelloClass",init()).def("sayHello",&HelloClass::sayHello);//Add a regular member function
			def("sayHelloClass",sayHelloClass); // sayHelloClass can be made a member of module!!!

			class_("ivector").def(vector_indexing_suite());
			class_ >("ivector_vector").def(vector_indexing_suite >());

			def("showPerson",showPerson,showPerson_overloads());
		}
