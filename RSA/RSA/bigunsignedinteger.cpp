#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class bigint {
private:
public:
	string integer = "";
	bigint(string value) {
		integer = value;
	}
	bigint(long long value) {
		integer = to_string(value);
	}
	bigint(int value) {
		integer = to_string(value);
	}

protected:

};