#include <iostream>
#include <ctime>
#include <string>
using namespace std;

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

long long min(long long x, long long y ,bool min=true) {
	if (x < y) { if (min) { return x; } else return y; }
	else { if (min) { return y; } else return x; };
}
void test(string p, string original) {
	if (original == p) {
		cout << "Correct Answer \n";
	}
	else {
		cout << "Wrong Answer \n";
	}
}
int toint(char x) {
	string temp = "0";
	temp += x;
	return stoi(temp);
}
string addbig(string a, string b) {
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
string mult_1(string p, string q) {
	string output = "";
	int m = 1;
	string sum = "";
	for (int i = q.length() - 1; i >= 0; i--) {

		int carry = 0;

		for (int j = p.length() - 1; j >= 0; j--) {
			string temp1 = "0";
			string temp2 = "0";
			temp1 += q[i];
			temp2 += p[j];
			int multi = (stoi(temp1)*stoi(temp2)) + carry;
			int res = multi % 10;
			carry = multi / 10;
			output.insert(0, to_string(res));
		}
		if (carry != 0)
			output.insert(0, to_string(carry));
		//cout << "======"<<endl;
		for (int x = m - 1; x>0; x--)
			output = output + "0";
		//cout <<m <<"    " <<output<<endl;
		sum = addbig(sum, output);
		output = "";
		m++;
	}
	return sum;
}

string subbig(string a, string b) {
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

string fit(string a, int size) {
	int amount = size - a.length();
	if (amount <= 0) {
		return a;
	}
	return shift(a, amount, false);
	
}
string remove(string a) {
	if (a[0] != '0')
		return a;
	while (a[0] == '0') {

		a = a.substr(1);
	}
	return a;
}
//using recursive karatsuba method;
string multiply(string x, string y) {
	if(x.length()+y.length() <=9) return to_string((stoi(x)*stoi(y)));
	/*if (x.length() <= 4 && y.length() <= 4) {
		return to_string((stoi(x)*stoi(y)));
	}*/
	string product;
	int n1 = x.length();
	int n2 = y.length();
	x = fit(x, n2);
	y = fit(y, n1);
	int m = x.length();
	int n = m / 2 ;
	int sm = m - n;
	string a = x.substr(0,n);
	string b = x.substr(n);
	string c = y.substr(0,n);
	string d = y.substr(n);
	
	string ac = multiply(a, c);
	string bd = multiply(b, d);
	string abcd = multiply(addbig(a , b), addbig(c , d));
	
	
	abcd = subbig(abcd, ac);
	abcd = subbig(abcd, bd);

	ac = shift(ac, 2 * (sm));
	abcd = shift(abcd, sm);
	
	product = addbig(ac, abcd);
	product = addbig(product, bd);
	
	return remove(product);

}


string minusone(string s) {
	bool notfin = true;
	int index = s.length() - 1;
	while (notfin) {
		if ('0' == s[index]) {
			s[index] = '9';
			index--;
		}
		else if ('0' != s[index]) {
			string temp = "0";
			temp += s[index];
			s.replace(index, 1, to_string(stoi(temp) - 1));
			break;
		}
	}
	return s;
}
string divbig(string a, string divisor) {
	
	string final_co = "";
	string final_reminder = "";
	string co = "";
	long long k = 0.0;
	//step 1
	int start_limit = divisor.length();
	int limit = 0;
	string d = divisor.substr(0, 1);
	if (max_min(divisor, a) == 1) {
		//a is bigger ok
		unsigned int i = 1;
		do {
			k = stoi(a.substr(0, i)) / stoi(d);
			if (k == 0)
			{
				i++;
			}
			else {
				co = to_string(k);
				break;
			}
		} while (i <= a.length());

		string product = remove(multiply(co, divisor));
		product = shift(product, a.length() - product.length());
		if (max_min(product, a) == 0) {
			k = k - 1;
			co = to_string(k);
			product = remove(multiply(co, divisor));
		}

		string next = remove(subbig(a, product));

		return co + divbig(next, divisor);

	}
	else if (max_min(divisor, a) == 2) {
		//same shit 
		//co = 1;
		co = "1";
		return co;
	}
	else {
		co = "";
		return co;
	}

	

}


string enc(string x, string n, string m) {

	if (remove(n) == "0") {
		return "1";
	}

	if (remove(divbig(n,"2")) == "" || remove(divbig(n,"2")) =="0") {
		//even n ;
		string y = enc(x, remove(divbig(n, "2")), m);
		return enc(multiply(y,y),"1",m);//to be checked not sure (y*y % m)
	}
	else {
		 // n is odd ;
		string b = enc(x, "1", m);
		string a = enc(x, minusone(n), m);
		return (multiply(a, b), "1", m);
	}

}
string calcphi(string p, string q) {

	return multiply(minusone(p), minusone(q));
}

string div_mod(string p, string q, bool div = true) {

	if (div == true) return divbig(p, q);

	return remove(subbig(p, multiply(q, divbig(p, q))));

}
string d2b(string input) {
	string output = "";
	string a;
	int i = 0;
	
	input = div_mod(input, "2");

	cout << input;
	return input;
}
int main() {
 #define _test =false 
	string p = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
	string q = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
	string pq = "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336041031200174441223836394229943651678525471050219216183727749114047330431603023948126844573697946795476319956787513765533596926704755530772983549787878951983";
	
	/* TESTS	*/
#ifdef _test
	clock_t t = clock();
	d2b(p);
	t = clock() - t;
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;

	t = clock();
	
	cout << "testing multiply function 1 ..\n";
	test(mult_1(p, q), pq);
	t = clock() - t;
	cout << "time :" << ( ((float)t) / CLOCKS_PER_SEC) << " seconds" <<endl;

	cout << "testing multiply function 2 ..\n";
	test(multiply(p, q), pq);
	t = clock() - t;
	
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << " seconds" << endl;
	cout << endl; cout << endl;

	cout << "test calc n , multiply function ..\n";
	test(multiply(p, q), "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336041031200174441223836394229943651678525471050219216183727749114047330431603023948126844573697946795476319956787513765533596926704755530772983549787878951983");
	cout << "test calc phi(n) , multiply function ..\n";
	test(calcphi(p, q), "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336026596208292251573235229726077713862677978631329527089723369935343023713696135778845389268960161532146453542764411465765663060172221696312932049443439184640");

	cout << "\ntest division" << endl;
	if ("3352" == divbig("8896208", "2654"))cout << "1 sucess\n";
	if ("185" == divbig("986594", "5316"))cout << "2 sucess\n";
	if ("95738" == divbig("5953191492", "62182"))cout << "3 sucess\n";
	if ("1" == divbig("5953191492", "3265582558"))cout << "4 sucess\n";
	if ("34" == addbig(divbig("5956", "42"), (subbig("5956", (multiply("42", divbig("5956", "42"))))))) cout << "sucess\n\n";

	string co = div_mod(p, q);
	string r = div_mod(p, q, false);
	string original = addbig(multiply(co, q), r);
	test(original, p);
#endif
	//	*/
	
	string command ="";
	cin >> command;
	while(command != "Quit"){
		if(command=="PrintN" ){
			cout << multiply(p,q)<<endl;
		}else if(command=="PrintPhi" ){
			cout << calcphi(p,q)<<endl;
		}
		cin >> command;
	}
	
	
	return 0;
}
