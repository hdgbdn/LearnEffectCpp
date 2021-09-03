#include <iostream>
#include <string>
#include "Person.h"
#include "Date.h"
#include "Address.h"
#include "PersonInterface.h"


int main()
{
	// so, we just need to include Person here
	// and only when the interface of person is changed, we need to recompile;
	Person("hi", Date(std::string("121212")), Address(std::string("China")));
	// I tested adding a function in PersonImpl.h, and it only re-compile the Person.lib, and the source.cpp only link
	// [1/2] Building CXX object 05_Implementations\31_Minimize_compilation_dependencies\CMakeFiles\31_Minimize_compilation_dependencies.dir\Person.cpp.obj
	// [2/2] Linking CXX executable 05_Implementations\31_Minimize_compilation_dependencies\31_Minimize_compilation_dependencies.exe
	// but adding a function in Person.h, the source.cpp is re-compiled
	// [1/3] Building CXX object 05_Implementations\31_Minimize_compilation_dependencies\CMakeFiles\31_Minimize_compilation_dependencies.dir\Person.cpp.obj
	// [2/3] Building CXX object 05_Implementations\31_Minimize_compilation_dependencies\CMakeFiles\31_Minimize_compilation_dependencies.dir\source.cpp.obj
	// [3/3] Linking CXX executable 05_Implementations\31_Minimize_compilation_dependencies\31_Minimize_compilation_dependencies.exe

	// why? because source.cpp only include Person.h, and Person.h include Data.h Address.h, so the change of PersonImpl.h don't affects the source.cpp
	// Person.cpp is affected by change of the PersonImpl.h because it included it, but just Person.cpp needs re-compile, source.cpp just need to re-link
	// so, as user, source.cpp don't affected by the change or PersonImpl
	//
	// summary: don't let users get involved in definition, only put declaration in header can avoid re-compile,

	std::shared_ptr<PersonInterface> p = PersonInterface::create("hi", Date(std::string("121212")), Address(std::string("China")));
	// first build:
	// [1/3] Building CXX object 05_Implementations\31_Minimize_compilation_dependencies\CMakeFiles\31_Minimize_compilation_dependencies.dir\RealPerson.cpp.obj
	// [2/3] Building CXX object 05_Implementations\31_Minimize_compilation_dependencies\CMakeFiles\31_Minimize_compilation_dependencies.dir\source.cpp.obj
	// [3/3] Linking CXX executable 05_Implementations\31_Minimize_compilation_dependencies\31_Minimize_compilation_dependencies.exe

	// then change the impl in RealPerson.cpp
	// [1/2] Building CXX object 05_Implementations\31_Minimize_compilation_dependencies\CMakeFiles\31_Minimize_compilation_dependencies.dir\RealPerson.cpp.obj
	// [2/2] Linking CXX executable 05_Implementations\31_Minimize_compilation_dependencies\31_Minimize_compilation_dependencies.exe

	// summary:
	// the header file provide to user, only contain pointer reference, and make implementation into a pointer, so the header file won't contain any object memory information
	// so changes of real implementation header file won't make user's code re-compile;
	return 0;
}