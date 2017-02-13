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
	int len = 0;
	bool dirty = false;
	bigint() {
		string integer = "";
		bool positive = true;
		int len = 0;
		
	}
	bigint(bigint a,int start,int unit=0) {
		string integer = a.integer;
		bool positive = a.positive;
		if (unit == 0) {
			unit = a.number.size()-start;
		}
		int len = unit;
		for (unsigned int i = start; i < start+unit;i++) {
			number.push_back(a.number[i]);
		}
	}
	bigint(string value) {
		integer = value;
		bool positive = true;
		len = value.length();
		int x = 7;
		
	while(value.length()>0) {
			if (value.length() <= 7) {
				number.push_back(stoull(value));
	
				break;
			}
			number.push_back(stoull(value.substr(value.length()-7, 7)));
			value = value.substr(0,value.length()-7 );
			
		}
		
	
	}
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
				
				temp_string.insert(0, zeros,0,l );
			}
			
			integer.insert(0, temp_string);
			//cout << temp_string << endl << integer<<endl;
		}
		integer = to_string(number[number.size()-1]) + integer.substr(7);
		dirty = false;
		//cout << integer << endl;
		return integer;
	}
	void print() {

		cout << getinstring() << endl;
	}
	int length() {
		return getinstring().length();
	}
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
	unsigned long long getnum (){
		return stoull(integer);
	}
	string getvalue() { return integer; }
	bigint add(bigint b, bool print = false) {
		bigint sum;
		sum.dirty = true;
		//unsigned long long po = 100000000000000000;
		unsigned long long po = 10000000;
		int		tt =  b.number.size();
		if (tt > number.size()) tt = number.size();
		int i = 0;
		int carry = 0;
		for (; i < tt;i++) {
			unsigned long long m = number[i] + b.number[i] + carry;
			sum.number.push_back(m%po);
			carry= (m/po) ? 1 : 0;
		}
		if (number.size() > b.number.size()) {
			int diff = number.size() - b.number.size();
			for (; i < number.size(); i++) {
				sum.number.push_back(number[i]+carry);
				unsigned long long m = number[i] +  carry;
				carry= (m / po) ? 1 : 0;
			}
		}
		else if (number.size() < b.number.size()) {
			int diff = b.number.size() - number.size();
			for (; i < b.number.size(); i++) {
				sum.number.push_back(b.number[i]+carry);
				unsigned long long m = b.number[i] + carry;
				carry = (m / po) ? 1 : 0;
			}
		}
		
		return sum;
	}
	
	bigint sub(bigint b, bool print = false) {
		bigint final;
		final.dirty = true;
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
	bigint remove(bigint a) {
		
		if ( a.number[a.number.size()-1] != 0)
			return a;
		while (a.number[a.number.size()-1] == 0) {

			a.number.pop_back();
		}
		return a;
	}
	void shift(int units, bool left = true) {

		if (left) {
			for (int i = 0; i < units; i++)	number.push_back(0);
			
		}
		else {
			for (int i = 0; i < units; i++)	number.insert(number.begin(),0);

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
	
	void fit(int size) {
		int k = number.size() - size;
		if (k < 0) {
			for (int i = 0; i <size - number.size();i++)	number.push_back(0);
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
			for (unsigned int i = 0; i < a.length() - 1; i++) {
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

	bigint subtruct(bigint a, bigint b) {
		if (a.positive == false && b.positive == false) {
			//b-a
			bigint newb = b;
			newb.positive = true;
			return subtruct(newb, a);
		}
		if (a.positive == true && b.positive == false) {
			return a.add(b);
		}
		if (b.positive == true && a.positive == false) {
			bigint r = a.add(b);
			r.positive = false;
			return r;
		}

		int k = max_min(a.getinstring(), b.getinstring());
		if (k == 2) {
			return bigint(0);
		}
		else if (k == 0) {
			return bigint(a).sub(bigint(b));

		}
		else {
			bigint r = bigint(b).sub(bigint(a));
			r.positive = false;
			return  r;
		}
	}
	bigint add(bigint a, bigint b) {
		if (a.positive == false && b.positive == false) {
			//-(b+a)
			bigint r = a.add(b);
			r.positive = false;
			return r;
			bigint newb = b;
			newb.positive = true;
			return subtruct(newb, a);
		}
		if (a.positive == true && b.positive == false) {
			bigint newb = b;
			newb.positive = true;
			return subtruct(a, newb);
		}
		if (b.positive == true && a.positive == false) {
			bigint newa = a;
			newa.positive = true;
			return subtruct(b, newa);
		}

		return a.add(b);
	}
	string remove(string a) {
		if (a[0] != '0')
			return a;
		while (a[0] == '0') {

			a = a.substr(1);
		}
		return a;
	}

	string multiply_1(unsigned long long aa, unsigned long long bb) {
		string product;
		string x = to_string(aa);
		string y = to_string(bb);
		if (x.length() + y.length() <= 18) return to_string((stoull(x)*stoull(y)));
		int n1 = x.length();
		int n2 = y.length();
		x = fit(x, n2);
		y = fit(y, n1);
		int m = x.length();
		int n = m / 2;
		int sm = m - n;
		string a = x.substr(0, n);
		string b = x.substr(n);
		string c = y.substr(0, n);
		string d = y.substr(n);

		string ac = multiply_1(stoull(a), stoull(c));
		string bd = multiply_1(stoull(b), stoull(d));
		string abcd = multiply_1(stoull(add_string(a, b)), stoull(add_string(c, d)));


		abcd = sub_string(abcd, ac);
		abcd = sub_string(abcd, bd);

		ac = shift(ac, 2 * (sm));
		abcd = shift(abcd, sm);

		product = add_string(ac, abcd);
		product = add_string(product, bd);

		return remove(product);

	}
	bigint multiply(bigint bb, bool print = false) {
		if (number.size() + bb.number.size() <= 2) {
			if (to_string(number[0]).length() + to_string(bb.number[0]).length() <= 15) {
				return bigint(number[0] * bb.number[0]);
			}
			else {
				return bigint(multiply_1(number[0], bb.number[0]));//to be 
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
		bigint b(*this,0, n);
		bigint a(*this,n);
		bigint d(bb,0, n);
		bigint c(bb,n);

		bigint ac = a.multiply(c);
		bigint bd = b.multiply(d);

		bigint ab = (a.add(b));
		bigint cd = (c.add(d));
		bigint abcd = ab.multiply(cd);

		abcd =remove(subtruct(abcd, ac));
		abcd = remove(subtruct(abcd, bd));
		ac = shift(ac.getinstring(), 2 * (n));
		abcd = shift(abcd.getinstring(), n);
		product = ac.add(abcd);
		product = remove( product.add(bd));
		

		return product;
	}
	bigint linear_mult(bigint bb) {

		 string output="";
		 int m = 1;
		 string sum="";
	for (int i = 0; i <number.size(); i++) {
        
		unsigned long long carry=0;
       
        for (int j = 0; j <bb.number.size();j++){
            unsigned long long multi=(number[i]*bb.number[j])+carry;
            unsigned long long res=multi%10000000;
            carry=multi/10000000;
			string re = to_string(res);
			if (to_string(res).length() < 7) {
				for (int i = 0; i < 7 - to_string(res).length(); i++) {
					re.insert(0, "0");
				}
			}
            output.insert(0,re);
        }
        if(carry!=0)
            output.insert(0,to_string(carry));
        //cout << "======"<<endl;
        for(int x=m-1;x>0;x--)
            output=output+"0000000";
        //cout <<m <<"    " <<output<<endl;
        sum=add_string(sum,(output));
        output="";
        m++;
    }
    return bigint(sum);

	}
};
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
		for (unsigned int i = 0; i < a.length() - 1; i++) {
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

string subtruct(string a , string b ) {
	int k = max_min(a, b);
	if(k==2) {
		return "0";
	}
	else if (k == 0) {
		return bigint(a).sub(bigint(b)).getinstring();
		
	}
	else {
		return "-"+ bigint(b).sub(bigint(a)).getinstring();
	}
}

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
	//	p = "666666666666666";
	//q = "111111111111111";
	//pq= "74074074074073925925925925926";
//	p = "1234506700891999";
//	q = "1234506700891999";
//	pq = "15241556995136506682262216001";
	string plus = "14434991882189650601164503865937815847492418889689094004379178704306717906888169281455304737785263329866414023102299767933866532533834460051500344439767344";
	string minus = "10304151175305660995055873707196545671761402041764747108755418614434081589256563733014494127869688400512871405033372646666439537585110014500132424380388398";
	bigint minus2(minus);

	//string plus = "35005132";
	
	bigint y(p);

	bigint x(q);
	bigint z(pq);

	cout <<pq <<endl<<endl;
	cout << y.linear_mult(x).getinstring() <<endl;
	clock_t t = clock();
	for (int i = 0; i < 1000; i++) y.linear_mult(x);;
	t = clock() - t;
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;

	//test(y.add(x).getvalue(),plus);
	cout << "end....\n";
	return 0;
}