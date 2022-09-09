#include <iostream>
#include "module1.h"
#include "module2.h"
#include "module3.h"

int main(int argc, char** argv)
{
	using std::cout;
	cout << "Hello world" << "\n";

	cout << Module1::getMyName() << "\n";
	cout << Module2::getMyName() << "\n";

	using namespace Module1;
	cout << getMyName() << "\n";
	cout << Module2::getMyName() << "\n";

	using namespace Module2;
	cout << Module2::getMyName() << "\n";

	using Module2::getMyName;
	cout << getMyName() << "\n";

	cout << Module3::getMyName() << "\n";
}
