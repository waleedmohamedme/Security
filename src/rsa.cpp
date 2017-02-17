#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <deque>
using namespace std;

class bigint {
private:

public:

	string integer = "";
	deque<unsigned long long > number;
	bool positive = true;
	
	bool dirty = false;
	bigint() {
		string integer = "";
		bool positive = true;
		

	}
	bigint(bigint a, int start, int unit = 0) {
		string integer = a.integer;
		bool positive = a.positive;
		if (unit == 0) {
			unit = a.number.size() - start;
		}
		
		for (unsigned int i = start; i < start + unit; i++) {
			number.push_back(a.number[i]);
		}
	}
	bigint(string value) {
		integer = value;
		if (value.empty() == true) {
			value = "0";
		}
		if (value[0] == '-') {
			positive = false;
			value = value.substr(1);
		}
		else {
			positive = true;
		}
		int x = 7;

		while (value.length()>0) {
			if (value.length() <= 7) {
				number.push_back(stoull(value));

				break;
			}
			number.push_back(stoull(value.substr(value.length() - 7, 7)));
			value = value.substr(0, value.length() - 7);

		}


	}
	//deprecated -- feha  bug wkda kda msh used 
	bigint(long long value) {
		if (value < 0) {
			positive = false;
			value = value*(-1);
		}
		integer = to_string(value);
		if (integer.length()>7) {
			bigint x = bigint(integer);
			x.positive = positive;
			*this = x;
		}
		else {
			number.push_back((value));
		}
	}
	bigint(unsigned long long value) {
		if (value < 0) {
			positive = false;
			value = value*(-1);
		}
		integer = to_string(value);
		if (integer.length()>7) {
			bigint x = bigint(integer);
			x.positive = positive;
			*this = x;
		}
		else {
			number.push_back((value));
		}

	}
	bigint(int value) {
		if (value == 0) {
			integer = "0";
		}
		if (value < 0) {
			positive = false;
			value = value*(-1);
		}
		integer = to_string(value);
		if (integer.length()>7) {
			bigint x = bigint(integer);
			x.positive = positive;
			*this = x;
		}
		else {
			number.push_back((value));
		}
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

			if (temp_string.length() < 7) {
				int l = (7 - temp_string.length());

				temp_string.insert(0, zeros, 0, l);
			}

			integer.insert(0, temp_string);
			//cout << temp_string << endl << integer<<endl;
		}
		integer = to_string(number[number.size() - 1]) + integer.substr(7);
		dirty = false;
		//cout << integer << endl;
		if (integer.empty()) {
			integer = "0";
			number.push_back(0);
		}
		return integer;
	}
	void print() {cout << getinstring() << endl;}
	int length() {return getinstring().length();}
	int toint(char x) {
		string temp = "0";
		temp += x;
		return stoi(temp);
	}
	string sub_string(string a, string b) {
		string final = "";
		int finalzero = 0;
		if (a.length()>b.length()) {
			int zeros = a.length() - b.length();
			for (int i = 0; i<zeros; i++)
				b.insert(0, to_string(0));

		}
		else if (a.length()<b.length()) {
			int zeros = b.length() - a.length();
			for (int i = 0; i<zeros; i++)
				a.insert(0, to_string(0));
		}
		for (unsigned int i = 0; i<a.length(); i++)
		{
			if (toint(a[i]) != 0) {
				finalzero = i;
				break;
			}
		}
		for (int i = a.length() - 1; i >= 0; i--) {
			string temp1 = "0";
			string temp2 = "0";
			temp1 += a[i];
			temp2 += b[i];
			if (stoi(temp2) - stoi(temp1)>0) {

				for (int j = i - 1; j >= 0; j--) {
					if (toint(a[j])>0) {
						a.replace(j, 1, to_string(toint(a[j]) - 1));
						break;
					}
					else if (toint(a[j]) == 0) {
						if (j >= finalzero) {
							a[j] = '9';
						}
						continue;
					}


				}
				final.insert(0, to_string((10 + toint(a[i])) - toint(b[i])));
			}
			else if ((stoi(temp2) - stoi(temp1))<0) {

				final.insert(0, to_string((toint(a[i])) - toint(b[i])));

			}
			else {
				final.insert(0, to_string((toint(a[i])) - toint(b[i])));
			}


		}
		return final;
	}
	string add_string(string a, string b) {
		string sum = "";
		if (a.length()>b.length()) {
			int zeros = a.length() - b.length();
			for (int i = 0; i<zeros; i++)
				b.insert(0, to_string(0));

		}
		else if (a.length()<b.length()) {
			int zeros = b.length() - a.length();
			for (int i = 0; i<zeros; i++)
				a.insert(0, to_string(0));
		}

		int carry = 0;

		for (int i = a.length() - 1; i >= 0; i--) {

			string temp1 = "0";
			string temp2 = "0";
			temp1 += a[i];
			temp2 += b[i];
			sum.insert(0, to_string((stoi(temp1) + stoi(temp2) + carry) % 10));
			carry = ((stoi(temp1) + stoi(temp2) + carry) / 10) ? 1 : 0;

		}
		if (carry != 0)
			sum.insert(0, to_string(carry));
		return sum;
	}
	unsigned long long getnum() {
		return stoull(integer);
	}
	//signed add
	bigint add(bigint a, bigint b) {
		if (a.positive == false && b.positive == false) {
			//-(b+a)
			bigint r = a.add(b);
			r.positive = false;
			return r;
		}
		if (a.positive == true && b.positive == false) {
			//a-b
			bigint newb = b;
			newb.positive = true;
			return subtruct(a, newb);
		}
		if (b.positive == true && a.positive == false) {
			//b-a
			bigint newa = a;
			newa.positive = true;
			return subtruct(b, newa);
		}

		return a.add(b);
	}
	//unsigned add	
	bigint add(bigint b, bool print = false) {
		bigint sum;
		sum.dirty = true;
		//unsigned long long po = 100000000000000000;
		unsigned long long po = 10000000;
		int		tt = b.number.size();
		if (tt > number.size()) tt = number.size();
		int i = 0;
		int carry = 0;
		for (; i < tt; i++) {
			unsigned long long m = number[i] + b.number[i] + carry;
			sum.number.push_back(m%po);
			carry = (m / po) ? 1 : 0;
		}
		if (number.size() > b.number.size()) {
			int diff = number.size() - b.number.size();
			for (; i < number.size(); i++) {
				sum.number.push_back(number[i] + carry);
				unsigned long long m = number[i] + carry;
				carry = (m / po) ? 1 : 0;
			}
		}
		else if (number.size() < b.number.size()) {
			int diff = b.number.size() - number.size();
			for (; i < b.number.size(); i++) {
				sum.number.push_back(b.number[i] + carry);
				unsigned long long m = b.number[i] + carry;
				carry = (m / po) ? 1 : 0;
			}
		}

		return sum;
	}
	//signed subtract 
	bigint subtruct( bigint b) {
		bigint a = (*this);
		if (a.positive == false && b.positive == false) {
			//b-a
			bigint newb = b;
			newb.positive = true;
			return subtruct(newb, a);
		}
		if (a.positive == true && b.positive == false) {
			//a--b == a+b
			return a.add(b);
		}
		if (b.positive == true && a.positive == false) {
			//-a-b == -(a+b)
			bigint r = a.add(b);
			r.positive = false;
			return r;
		}
		// +v - +v 
		int k = max_min(a.getinstring(), b.getinstring());
		if (k == 2) {
			//both equal 
			return bigint(0);
		}
		else if (k == 0) {
			//a is bigger 
			bigint r = a.sub((b));
			r.positive = true;
			return r;

		}
		else {
			//b is bigger 
			bigint r = (b).sub((a));
			r.positive = false;
			return  r;
		}
	}

	bigint subtruct(bigint a, bigint b) {
		
		if (a.positive == false && b.positive == false) {
			//b-a
			bigint newb = b;
			newb.positive = true;
			return subtruct(newb, a);
		}
		if (a.positive == true && b.positive == false) {
			//a--b == a+b
			return a.add(b);
		}
		if (b.positive == true && a.positive == false) {
			//-a-b == -(a+b)
			bigint r = a.add(b);
			r.positive = false;
			return r;
		}
		// +v - +v 
		int k = max_min(a.getinstring(), b.getinstring());
		if (k == 2) {
			//both equal 
			return bigint(0);
		}
		else if (k == 0) {
			//a is bigger 
			bigint r = a.sub((b));
			r.positive = true;
			return r;

		}
		else {
			//b is bigger 
			bigint r = (b).sub((a));
			r.positive = false;
			return  r;
		}
	}
	//unsigned subtract
	bigint sub(bigint b, bool print = false) {
		bigint final;
		final.dirty = true;
		int finalzero = 0;
		if (number.size() == 1 && b.number.size() == 1) {
			if (number[0] >= b.number[0]) {

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
		int bb = number.size();
		if (tt > number.size()) tt = number.size();
		int i = 0;
		for (int borrow = 0; i < tt; i++) {
			unsigned long long temp1 = number[i];
			unsigned long long temp2 = b.number[i];
			long long temp = temp1 - temp2;
			if (temp<0) {
				//need carry 
				for (int j = i + 1; j < bb; j++) {
					if (number[j]>0) {
						number[j] = (number[j] - 1);
						break;
					}
					else if (number[j] == 0) {
						//number[j]= 99999999999999999;
						number[j] = 9999999;
					}


				}
				//final.number.push_back((100000000000000000 + number[i]) - b.number[i]);
				final.number.push_back((10000000 + number[i]) - b.number[i]);
			}
			else if (temp>0) {

				final.number.push_back((temp1)-(temp2));

			}
			else {
				final.number.push_back((temp1)-(temp2));
			}


		}
		if (number.size() > b.number.size()) {
			for (; i < number.size(); i++) {
				final.number.push_back(number[i]);
			}
		}
		else if (number.size() < b.number.size()) {
			for (; i < b.number.size(); i++) {
				final.number.push_back(b.number[i]);
			}
		}
		return final;

	}
	//unsigned multiply
	bigint linear_mult(bigint bb) {

		string output = "";
		int m = 1;
		string sum = "";
		for (int i = 0; i <number.size(); i++) {

			unsigned long long carry = 0;

			for (int j = 0; j <bb.number.size(); j++) {
				unsigned long long multi = (number[i] * bb.number[j]) + carry;
				unsigned long long res = multi % 10000000;
				carry = multi / 10000000;
				string re = to_string(res);
				if (to_string(res).length() < 7) {
					for (int i = 0; i < 7 - to_string(res).length(); i++) {
						re.insert(0, "0");
					}
				}
				output.insert(0, re);
			}
			if (carry != 0)
				output.insert(0, to_string(carry));
			//cout << "======"<<endl;
			for (int x = m - 1; x>0; x--)
				output = output + "0000000";
			//cout <<m <<"    " <<output<<endl;
			sum = add_string(sum, (output));
			output = "";
			m++;
		}
		return bigint(sum);

	}
	//unsigned divison
	string unsigned_division(string a, string divisor, bool r = true) {
		//if r == true >>> divison else reminder
		vector<string> m;
		string d = divisor.substr(0, 1);
		int dd = stoi(d);
		string answer = "";
		int j = divisor.length();
		string aa;
		string tobesubbed;
		m.push_back(divisor);
		m.push_back(bigint("2").linear_mult(bigint(divisor)).getinstring());
		m.push_back(bigint("4").linear_mult(bigint(divisor)).getinstring());
		m.push_back(bigint("8").linear_mult(bigint(divisor)).getinstring());
		string leftover = a;
		string result = "", tempresult = "", zeros = "";
		if (max_min(leftover, divisor) == 2) {
			result = "1";
			leftover = "0";
			if (!r)return leftover;
			return result;
		}
		else if ((max_min(leftover, divisor) == 1)) {
			result = "0";
			if (!r)return leftover;
			return result;
		}
		while (max_min(leftover, divisor) == 0) {

			int i = 0;
			int k = 0;
			while (i < leftover.length() && k == 0) {
				k = stoi(leftover.substr(0, ++i)) / dd;
			}
			/*test modification*/
		
			/*end test modification*/
			int ll = 0;
			if (k >= 8) {
				aa = "8";
				ll = 3;
				tobesubbed = m[3];
			}
			else if (k >= 4) {
				aa = "4"; ll = 2;
				tobesubbed = m[2];
			}
			else if (k >= 2) {
				aa = "2"; ll = 1;
				tobesubbed = m[1];
			}
			else if (k >= 1) {
				aa = "1"; ll = 0;
				tobesubbed = m[0];
			}

			zeros = "";
			if (max_min(tobesubbed, leftover) == 0) {
				tobesubbed = m[--ll];
			}
			for (i = 0; i < (leftover.length() - tobesubbed.length()); i++) zeros.append("0");
			if (max_min(tobesubbed + zeros, leftover) == 0) {
				zeros = zeros.substr(0, zeros.length() - 1);
			}
			tobesubbed = tobesubbed + zeros;
			leftover = remove(subtruct(bigint(leftover), bigint(tobesubbed)).getinstring());
			if (ll == 3) {
				aa = "8";

			}
			else if (ll == 2) {
				aa = "4";
			}
			else if (ll == 1) {
				aa = "2";
			}
			else if (ll == 0) {
				aa = "1";
			}

			tempresult = aa + zeros;
			result = add(bigint(result), bigint(tempresult)).getinstring();
		}
		if (leftover == divisor) {
			result = add(bigint(leftover), bigint("1")).getinstring();
			leftover = "0";
		}
		if (!r)return leftover;
		return result;
	}
	//signed division
	bigint divide(bigint bb, bool div = true) {
		string a = getinstring();
		string b = bb.getinstring();
		bool aa_positive = (*this).positive;
		bool bb_positive = bb.positive;
		bool result_sign;
		string co_r;
		if (div) {
			co_r = unsigned_division(a, b);
		}
		else {
			co_r = unsigned_division(a, b, false);
		}


		if ((aa_positive && bb_positive) || (!bb_positive && !aa_positive)) {
			result_sign = true;
		}
		else {
			result_sign = false;
		}
		bigint result(co_r);
		result.positive = result_sign;
		return result;

	}
	//signed multiply
	bigint Multiply(bigint bb) {
		bool aa_positive = (*this).positive;
		bool bb_positive = bb.positive;
		bool result_sign;
		if ((aa_positive && bb_positive) || (!bb_positive && !aa_positive)) {
			result_sign = true;
		}
		else {
			result_sign = false;
		}
		bigint result = (*this).linear_mult(bb);
		result.positive = result_sign;

		return result;
	}
	
	bigint remove(bigint a) {

		if (a.number[a.number.size() - 1] != 0)
			return a;
		while (a.number[a.number.size() - 1] == 0) {

			a.number.pop_back();
		}
		return a;
	}
	string remove(string a) {
		if (a[0] != '0')
			return a;
		while (a[0] == '0') {

			a = a.substr(1);
		}
		return a;
	}
	void shift(int units, bool left = true) {

		if (left) {
			for (int i = 0; i < units; i++)	number.push_back(0);

		}
		else {
			for (int i = 0; i < units; i++)	number.insert(number.begin(), 0);

		}

	}
	string shift(string input, int units, bool left = true) {

		if (left) {
			for (int i = 0; i < units; i++) {
				input.append("0000000");
			}
			return input;
		}
		else {
			for (int i = 0; i < units; i++) {
				input.insert(0, "00000000");
			}
			return input;

		}

	}
	string fit(string a, int size) {
		int amount = size - a.length();
		if (amount <= 0) {
			return a;
		}
		return shift(a, amount, false);

	}
	string shift_2(string input, int units, bool left = true) {

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

	void fit(int size) {
		int k = number.size() - size;
		if (k < 0) {
			for (int i = 0; i <size - number.size(); i++)	number.push_back(0);
		}

	}
	int max_min(string a, string b, bool max = true) {
		//if 0 >> a 
		//if 1 >> b 
		//if 2 equal
		if (a.length() > b.length()) {
			if (max) { return 0; }
			return 1;
		}
		else if (b.length() > a.length()) {
			if (max) { return 1; }
			return 0;
		}
		else {
			for (unsigned int i = 0; i < a.length() ; i++) {
				if (a[i] > b[i]) {
					if (max) { return 0; }
					return 1;
				}
				else if (a[i] < b[i]) {
					if (max) { return 1; }
					return 0;
				}
			}
		}

		return 2;
	}
	
	bigint multiply_kara(bigint bb, bool print = false) {
		if (number.size() + bb.number.size() <= 2) {
			if (to_string(number[0]).length() + to_string(bb.number[0]).length() <= 15) {
				return bigint(number[0] * bb.number[0]);
			}

		}

		bigint product;
		int n1 = number.size();
		int n2 = bb.number.size();
		fit(n2);
		bb.fit(n1);
		int m = number.size();
		int n = m / 2;
		int sm = m - n;
		bigint b(*this, 0, n);
		bigint a(*this, n);
		bigint d(bb, 0, n);
		bigint c(bb, n);

		bigint ac = a.multiply_kara(c);
		bigint bd = b.multiply_kara(d);

		bigint ab = (a.add(b));
		bigint cd = (c.add(d));
		bigint abcd = ab.multiply_kara(cd);

		abcd = remove(subtruct(abcd, ac));
		abcd = remove(subtruct(abcd, bd));
		ac = shift(ac.getinstring(), 2 * (n));
		abcd = shift(abcd.getinstring(), n);
		product = ac.add(abcd);
		product = remove(product.add(bd));


		return product;
	}
	bigint phin( bigint b) {
		return (subtruct((*this), bigint(1)).Multiply(subtruct(b, bigint(1))));
	}
	bigint calculate_n(bigint b) {
		return ((*this).Multiply(b));
	}
	bigint extended_euclidian(bigint e, bigint mod) {
		bigint A1, A2, A3, B1, B2, B3;
		bigint A2_next, A3_next, B2_next, B3_next;
		bigint Q;
		A2=(bigint("0"));
		A3 = mod;
		B2 = (bigint("1"));
		B3 = e;

		while (B3.getinstring() != "1"  && B3.getinstring() != "0") {
			A2_next = B2;
			A3_next = B3;
			Q = A3.divide(B3);
			B2 = subtruct(A2,Q.Multiply(B2));
			B3 = A3.divide(B3, false);//A3%B3;
			if (B3.getinstring() == "1") {
				return B2;
			}
			A2 = A2_next;
			A3 = A3_next;
		}
	}
	bigint expo_mod(bigint message, bigint e, bigint mod) {
		//e=0 message^0
		if (e.getinstring() == "0") {
			return bigint("1");
		}
		if (e.getinstring() == "1" || e.getinstring() == "1") {
			return message.divide(mod,false);
		}
		if (e.divide(bigint("2"),false).getinstring() == "" || e.divide(bigint("2"),false).getinstring() == "0") {
			//even n ;
			bigint y = expo_mod(message, e.divide(bigint("2")), mod);
			return expo_mod(y.Multiply(y), bigint("1"), mod);
		}
		else {
			// n is odd ;
			
			bigint b = expo_mod(message, bigint("1"), mod);
			bigint a = expo_mod(message, subtruct(e,bigint("1")), mod);
			return expo_mod(a.Multiply(b), bigint("1"), mod);
		}

	}
	bigint encrypt(bigint e, bigint mod) {

		return expo_mod((*this), e, mod);
	}
	bigint decrypt(bigint e, bigint phin,bigint n) {
		return expo_mod((*this), e.inverse(phin), n);
	}
	bigint decrypt(bigint d, bigint mod) {
		return expo_mod((*this), d, mod);
	}
	bigint inverse( bigint mod) {
		return extended_euclidian((*this), mod);
	}
	//////fixes
	/*
	string enc(string x, string n, string m) {

		if (remove(n) == "0") {
			return "1";
		}

		if (remove(divbig(n, "2")) == "" || remove(divbig(n, "2")) == "0") {
			//even n ;
			string y = enc(x, remove(divbig(n, "2")), m);
			return enc(multiply(y, y), "1", m);//to be checked not sure (y*y % m)
		}
		else {
			// n is odd ;
			string b = enc(x, "1", m);
			string a = enc(x, minusone(n), m);
			return (multiply(a, b), "1", m);
		}

	}
	*/
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
	string pq = "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336041031200174441223836394229943651678525471050219216183727749114047330431603023948126844573697946795476319956787513765533596926704755530772983549787878951983";
	string plus = "14434991882189650601164503865937815847492418889689094004379178704306717906888169281455304737785263329866414023102299767933866532533834460051500344439767344";
	string minus = "10304151175305660995055873707196545671761402041764747108755418614434081589256563733014494127869688400512871405033372646666439537585110014500132424380388398";
	string phi = "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336026596208292251573235229726077713862677978631329527089723369935343023713696135778845389268960161532146453542764411465765663060172221696312932049443439184640";
	string E = "65537";
	string d = "25051719899710729069339146813050963409059898810366373119834423967819636191509401691818253978210229371822961344590338934536803264841097247978074700319812702399440521918349189245279566231685265955731649745935378380489722580113725907099133943430294137060596724659637599737926649148356615085679203385772673944833";
	string ec_88 = "4397678428390379126255360246165021910057442267382175543246817108158797115317154540746718616555865161372450860559307149988169566508274711121236049281217144195628407516579953387138808449458611836421032431582081899650685651973204503916459595600207918950383877057152533041873901965623112895996177941667469292738";

	bigint e(E);
	bigint minus2(minus);
		
	
	clock_t t = clock();
	bigint x(p);
	bigint y(q);
	bigint message("88");
	cout << "TEST N " << endl;
	bigint xy = x.Multiply(y);
	test(pq, xy.getinstring());
	bigint pphii = x.subtruct(bigint("1")).Multiply(y.subtruct(bigint("1")));
	cout << "TEST PHI " << endl;
	test(phi, pphii.getinstring());
	bigint ecc = message.encrypt(e, xy);
	cout << "TEST ecryption of 88 " << endl;
	test(ec_88, ecc.getinstring());
	cout << "TEST inverse of e " << endl;
	bigint d_k(d);
	bigint dd = e.inverse(pphii);
	test(dd.getinstring(), d);
	cout << "TEST decryption" << endl;
	bigint dec = ecc.decrypt(d_k,xy);
	test(dec.getinstring(), "88");
	t = clock() - t;
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;
	cout << endl << pq.length() << endl;

	bigint coo = x.divide(y);
	bigint r = x.divide(y,false);
	bigint original =(coo.linear_mult(y)).add((r));
	cout << coo.getinstring()<<endl<<p<<endl;
	cout << endl << "Test divison reminder using recomposition" << endl;
	test(original.getinstring(), p);
	cout << endl << "Test calculate n"<<endl;
	test(x.calculate_n(y).getinstring(), pq);
	cout << endl << "Test calculate Phi(n)" << endl;
	test(x.phin(y).getinstring(), phi);
	t = clock();
	for (int i = 0; i < 1000; i++) x.Multiply(y);;
	t = clock() - t;
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;
	 t = clock();
	for (int i = 0; i < 1000; i++) x.divide(y);;
	t = clock() - t;
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;
	
	cout << "end....\n";
	return 0;
}
