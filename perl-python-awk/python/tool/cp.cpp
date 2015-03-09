#include <boost/python.hpp>
#include <iostream>
using namespace boost::python;
class World
{
	public:
		      void set(std::string msg) { this->msg = msg; }
			        std::string greet() { return msg; }
					      std::string msg;
};
typedef boost::shared_ptr < World > world_ptr;
BOOST_PYTHON_MODULE(hello)
{
	      class_ <World>("World")
			            .def("greet", &World::greet)
						          .def("set", &World::set)
								        ;
		        register_ptr_to_python <world_ptr>();
}
int main(int argc, char *argv[])
{

	Py_Initialize();
	world_ptr worldObjectPtr (new World);
	worldObjectPtr->set("Hello from C++!");
	try 
	{        
		inithello();
		PyRun_SimpleString("import hello");

		object module(handle <>(borrowed(PyImport_AddModule("__main__"))));
		object dictionary = module.attr("__dict__");
		dictionary["pyWorldObjectPtr"] = worldObjectPtr;
		PyRun_SimpleString("pyWorldObjectPtr.set('Hello from Python!')");
	} 
	catch (error_already_set) 
	{
		PyErr_Print();
	}
	std::cout << "worldObjectPtr->greet(): " << worldObjectPtr->greet() <<std::endl;
	Py_Finalize();
	return 0;
}
