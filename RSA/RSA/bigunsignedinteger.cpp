#include <iostream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

class bigint {
private:
	
public:
	string integer = "";
	vector<unsigned long long > number;
	bool positive = true;
	int len = 0;
	bool dirty = false;
	bigint() {
		string integer = "";
		bool positive = true;
		int len = 0;
		
	}
	bigint(string value) {
		integer = value;
		bool positive = true;
		len = value.length();
		int x = 17;
		
	while(value.length()>0) {
			if (value.length() <= 17) {
				number.push_back(stoull(value));
	
				break;
			}
			number.push_back(stoull(value.substr(value.length()-17, 17)));
			value = value.substr(0,value.length()-17 );
			
		}
		
	
	}
	bigint(long long value) {
		if (value < 0) {
			positive = false;
			value = value*(-1);
		}
		integer = to_string(value);
		number.push_back((value));
	}
	bigint(unsigned long long value) {
		if (value < 0) {
			positive = false;
			value = value*(-1);
		}
		integer = to_string(value);
		number.push_back((value));
	}
	bigint(int value) {
		
		if (value < 0) {
			positive = false;
			value = value*(-1);
		}
		integer = to_string(value);
		integer = to_string(value);
		number.push_back((value));
	}
	bool ispositive(bigint x) {
		return positive;
	}
	string getinstring() {
		if (!dirty) {
		//	return integer;
		}
		integer = "";
		string zeros = "00000000000000000";
		string temp_string;
		for (unsigned long long n : number) {
			temp_string = to_string(n);
			
			if (temp_string.length() < 17) {
				int l = (17 - temp_string.length());
				
				temp_string.insert(0, zeros,0,l );
			}
			
			integer.insert(0, temp_string);
			//cout << temp_string << endl << integer<<endl;
		}
		integer = to_string(number[number.size()-1]) + integer.substr(17);
		dirty = false;
		//cout << integer << endl;
		return integer;
	}
	void print() {

		cout << integer << endl;
	}
	int length() {
		return integer.length();
	}
	void insert(int pos, string value) {
		integer.insert(pos,value);
	}
	char getnum(int pos) {
		return integer[pos];
	}
	unsigned long long getnum (){
		return stoull(integer);
	}
	string getvalue() { return integer; }
	bigint add(bigint b, bool print = false) {
		bigint sum;
		unsigned long long po = 100000000000000000;
		int		tt =  b.number.size();
		if (tt > number.size()) tt = number.size();
		int i = 0;
		for (int carry = 0; i < tt;i++) {
			unsigned long long m = number[i] + b.number[i] + carry;
			sum.number.push_back(m%po);
			carry= (m/po) ? 1 : 0;
		}
		if (number.size() > b.number.size()) {
			int diff = number.size() - b.number.size();
			for (; i < number.size(); i++) {
				sum.number.push_back(number[i]);
			}
		}
		else if (number.size() < b.number.size()) {
			int diff = b.number.size() - number.size();
			for (; i < b.number.size(); i++) {
				sum.number.push_back(b.number[i]);
			}
		}

		return sum;
	}
	bigint sub(bigint b, bool print = false) {
		bigint final;
		int finalzero = 0;
		if (number.size() == 1 && b.number.size() == 1) {
			if (number[0]>=b.number[0]) {

				final.number.push_back((number[0] - b.number[0]));
				return final;
			}
			else if (number[0] < b.number[0]) {

				final.positive = false;
				final.number.push_back((b.number[0] - number[0]));
				return final;
			}
			
		}

		int	tt = b.number.size();
		int bb = b.number.size();
		if (tt > number.size()) tt = number.size();
		int i = 0;
		for (int borrow = 0; i < tt; i++) {
			unsigned long long temp1 = number[i];
			unsigned long long temp2 = b.number[i];
			long long temp = temp1 - temp2;
			if (temp<0) {
				//need carry 
				for (int j = i + 1; j < bb ; j++) {
					if (number[j]>0) {
						number[j]= (number[j] - 1);
						break;
					}
					else if (number[j] == 0) {
							number[j]= 99999999999999999;
					}


				}
				final.number.push_back((100000000000000000 + number[i]) - b.number[i]);
			}
			else if (temp>0) {

				final.number.push_back((temp1)-(temp2));

			}
			else {
				final.number.push_back((temp1)-(temp2));
			}


		}
		return final;

	}
	string shift(string input, int units, bool left = true) {

		if (left) {
			for (int i = 0; i < units; i++) {
				input.append("0");
			}
			return input;
		}
		else {
			for (int i = 0; i < units; i++) {
				input.insert(0, "0");
			}
			return input;

		}

	}
	bigint multiply(bigint bb, bool print = false) {
		if (number.size() + bb.number.size() <= 2) {
			if (to_string(number[0]).length() + to_string(bb.number[0]).length() <= 15) {
				return bigint(number[0] * bb.number[0]);
			}
		
		} 

		bigint product;
		int n1 = this->len;
		int n2 = bb.len;
		string x = getinstring();
		string y = bb.getinstring();

		//x = fit(x, n2);
		//y = fit(y, n1);
		int m = x.length();
		int n = m / 2;
		int sm = m - n;
		bigint a(x.substr(0, n));
		bigint b(x.substr(n));
		bigint c(y.substr(0, n));
		bigint d(y.substr(n));

		bigint ac = a.multiply(c);
		bigint bd = b.multiply(d);
		bigint abcd = (a.add(b)).multiply(c.add(b));


	//	abcd = abcd.sub(ac);
		//abcd = abcd.sub(bd);

//		ac = shift(ac.getinstring(), 2 * (sm));
//		abcd = shift(abcd.getinstring(), sm);

		product = ac.add(abcd);
		product = product.add(bd);

		return product;
	}


};


void test(string p, string original) {
	if (original == p) {
		cout << "Correct Answer \n";
	}
	else {
		cout << "Wrong Answer \n";
	}
}
int main() {
	string p = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
	string q = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
	//p = "654321";
	//q = "333333";
	string plus = "14434991882189650601164503865937815847492418889689094004379178704306717906888169281455304737785263329866414023102299767933866532533834460051500344439767344";
	string minus = "10304151175305660995055873707196545671761402041764747108755418614434081589256563733014494127869688400512871405033372646666439537585110014500132424380388398";
	bigint minus2(minus);
	//string plus = "35005132";
	
	bigint y(p);

	bigint x(q);
	bigint res = x.multiply(y);
	
	clock_t t = clock();
	for (int i = 0; i < 1000; i++) x.multiply(y);;
	t = clock() - t;
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;

	//test(y.add(x).getvalue(),plus);
	cout << "end....\n";
	return 0;
}