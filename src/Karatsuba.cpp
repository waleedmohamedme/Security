#include <iostream>
#include <ctime>
#include <string>
using namespace std;

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

//using recursive mode;
string mult_2(string x, string y) {
	if (x.length() <= 4 && y.length() <= 4) {
		return to_string((stoi(x)*stoi(y)));
	}
	string product;
	int n1 = x.length();
	int n2 = y.length();
	int n = min(n1, n2,false);//max 
	
	string a = x.substr(0, n/2);
	string b = x.substr(n/2);
	string c = x.substr(0,n/2);
	string d = x.substr(n/2);
	
	
	string ac = mult_2(a, c);
	string abcd = mult_2(addbig(a , b), addbig(c , d));
	string bd = mult_2(b, d);
	return "0";

}
int main() {
	
	string p = "12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
	string q = "2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
	string pq = "25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336041031200174441223836394229943651678525471050219216183727749114047330431603023948126844573697946795476319956787513765533596926704755530772983549787878951983";
	clock_t t = clock();
	
	cout << "testing multiply function 1 ..\n";
	test(mult_1(p, q), pq);
	t = clock() - t;
	cout << "time :" << ( ((float)t) / CLOCKS_PER_SEC) << "seconds" <<endl;


	cout << "testing multiply function 2 ..\n";
	test(mult_2(p, q), pq);
	t = clock() - t;
	cout << "time :" << (((float)t) / CLOCKS_PER_SEC) << "seconds" << endl;
	
	
	return 0;
}
