#include <iostream>
#include <cmath>
using namespace std;
string addbig(string a, string b){
    string sum="";
    if(a.length()>b.length()){
        int zeros= a.length()-b.length();
        for(int i =0;i<zeros;i++)
           b.insert(0,to_string(0));

    }else if(a.length()<b.length()){
         int zeros= b.length()-a.length();
         for(int i =0;i<zeros;i++)
           a.insert(0,to_string(0));
    }

    int carry=0;
    
    for (int i = a.length()-1 ; i>=0 ;i--){
       
            string temp1="0";
            string temp2="0";
            temp1+=a[i]; 
            temp2+=b[i];
            sum.insert(0,to_string((stoi(temp1)+stoi(temp2)+carry)%10));
            carry= ((stoi(temp1)+stoi(temp2)+carry)/10)?1:0;
        
    }
    if(carry!=0)
    sum.insert(0,to_string(carry));
    return sum;
}

string mult(string p, string q){
    string output="";
    int m=1;
    string sum="";
    for (int i = q.length()-1 ; i>=0 ;i--){
        
        int carry=0;
       
        for (int j = p.length()-1 ; j>=0 ;j--){
            string temp1="0";
            string temp2="0";
            temp1+=q[i];  
            temp2+=p[j];
            int multi=(stoi(temp1)*stoi(temp2))+carry;
            int res=multi%10;
            carry=multi/10;
            output.insert(0,to_string(res));
        }
        if(carry!=0)
            output.insert(0,to_string(carry));
        //cout << "======"<<endl;
        for(int x=m-1;x>0;x--)
            output=output+"0";
        //cout <<m <<"    " <<output<<endl;
        sum=addbig(sum,output);
        output="";
        m++;
    }
    return sum;
}
string minusone(string s){
    bool notfin = true;
    int index= s.length()-1 ;
    while (notfin){
        if('0'==s[index]){
            s[index]='9';
            index--;
        }else if('0' != s[index]){
            string temp="0";
            temp+=s[index]; 
            s.replace(index,1,to_string( stoi(temp)-1  ));
            break;
        }
    }
    return s;
}

string calcphi(string p,string q){
    
    return mult(minusone(p),minusone(q));
}
int main() {
    string p="12369571528747655798110188786567180759626910465726920556567298659370399748072366507234899432827475865189642714067836207300153035059472237275816384410077871";
    string q="2065420353441994803054315079370635087865508423962173447811880044936318158815802774220405304957787464676771309034463560633713497474362222775683960029689473";
    /*
    if (mult(p,q)=="25548364798832019218170326077010425733930233389897468141147917831084690989884562791601588954296621731652139141347541240725432606132471100644835778517336041031200174441223836394229943651678525471050219216183727749114047330431603023948126844573697946795476319956787513765533596926704755530772983549787878951983")
        cout << mult(p,q)<<endl;
        cout << "sucess"<<endl;
        
    cout << calcphi(p,q);
    */
    string command ="";
    cin >> command;
    while(command != "Quit"){
        if(command=="PrintN" ){
            cout << mult(p,q)<<endl;
        }else if(command=="PrintPhi" ){
            cout << calcphi(p,q)<<endl;
            
        }
        cin >> command;
    }
    return 0;
}
