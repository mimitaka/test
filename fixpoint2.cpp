#include <bits/stdc++.h>
using namespace std;


map<string,vector<string>> mp;
map<string,queue<string>> omp;
map<string,queue<string>> oomp;

void span(string address,string pingtime){
    char TimeDiff[16];
    int h,m,s;
    int fh,fm,fs;
    int sh,sm,ss;
    
    cout << "failure period : ";
    
    sh = atoi(pingtime.substr(8,2).c_str());
    sm = atoi(pingtime.substr(10,2).c_str());
    ss = atoi(pingtime.substr(12,2).c_str());
    fh = atoi(mp[address][0].substr(8,2).c_str());
    fm = atoi(mp[address][0].substr(10,2).c_str());
    fs = atoi(mp[address][0].substr(12,2).c_str());

    if(ss >= fs){
        s = ss-fs;
    }
    else{
        sm--;
        if(sm < 0){
            sm = 59;
            sh--;
            if(sh<0){
                sh = 23;
            }
        }
        ss+=60;
        s=ss-fs;
    }
    if(sm >= fm){
        m = sm-fm;
    }
    else{
        sh--;
        if(sh < 0){
            sh = 23;
        }
        sm+=60;
        m=sm-fm;
    }
    if(sh >= fh){
        h = sh-fh;
    }
    else{
        sh+=24;
        h=sh-fh;
    }
    cout << address << " : ";
    cout << fh << "." << fm << "." << fs << " : ";
    sprintf(TimeDiff,"%d",h);
    cout << TimeDiff << ".";
    sprintf(TimeDiff,"%d",m);
    cout << TimeDiff << ".";
    sprintf(TimeDiff,"%d",s);
    cout << TimeDiff << endl;
    
    auto itr = mp.find(address);
    mp.erase(itr);
}

void overspan(string address,queue<string> time){
    char TimeDiff[16];
    int h,m,s;
    int fh,fm,fs;
    int sh,sm,ss;
    
    cout << "overload period : ";
    
    sh = atoi(time.back().substr(8,2).c_str());
    sm = atoi(time.back().substr(10,2).c_str());
    ss = atoi(time.back().substr(12,2).c_str());
    fh = atoi(time.front().substr(8,2).c_str());
    fm = atoi(time.front().substr(10,2).c_str());
    fs = atoi(time.front().substr(12,2).c_str());
    
    if(ss >= fs){
        s = ss-fs;
    }
    else{
        sm--;
        if(sm < 0){
            sm = 59;
            sh--;
            if(sh<0){
                sh = 23;
            }
        }
        ss+=60;
        s=ss-fs;
    }
    if(sm >= fm){
        m = sm-fm;
    }
    else{
        sh--;
        if(sh < 0){
            sh = 23;
        }
        sm+=60;
        m=sm-fm;
    }
    if(sh >= fh){
        h = sh-fh;
    }
    else{
        sh+=24;
        h=sh-fh;
    }
    cout << address << " : ";
    cout << fh << "." << fm << "." << fs << " : ";
    sprintf(TimeDiff,"%d",h);
    cout << TimeDiff << ".";
    sprintf(TimeDiff,"%d",m);
    cout << TimeDiff << ".";
    sprintf(TimeDiff,"%d",s);
    cout << TimeDiff << endl;

}


int main(){
    string nm_fin;
    cout << "Input Log File Name = ";
    cin >> nm_fin;
    ifstream fin;
    fin.open(nm_fin);
    if(fin.fail()){
        cout << "fin.open() failed." << endl;
        return 0;
    }
    int n;
    cout << "Input Timeout Parameter = ";
    cin >> n;
    int m;
    cout << "Input Overload Judgment Count = ";
    cin >> m;
    int t;
    cout << "Input Average of Ping = ";
    cin >> t;

    while(true){
        string str,time;
        fin >> str;
        int length = str.size();
        if(fin.fail()) break;

        int first_comma,second_comma,address_length;
        first_comma = str.find_first_of(",");
        second_comma = str.find_last_of(",");
        address_length = second_comma - first_comma;
        
        int average,sum,count;
        queue<string> tmp;
        if(str.substr(second_comma+1)!="-"){
            omp[str.substr(first_comma+1,address_length-1)].push(str.substr(second_comma+1));
            oomp[str.substr(first_comma+1,address_length-1)].push(str.substr(0,14));
        }
        
        
        if(omp[str.substr(first_comma+1,address_length-1)].size() >= m){
            count = 0;
            sum = 0;
            while(!omp[str.substr(first_comma+1,address_length-1)].empty()){ 
                sum+=atoi(omp[str.substr(first_comma+1,address_length-1)].front().c_str());
                count++;
                tmp.push(omp[str.substr(first_comma+1,address_length-1)].front());
                omp[str.substr(first_comma+1,address_length-1)].pop();                
            }
            if(count > 0)average = sum /count;
            omp[str.substr(first_comma+1,address_length-1)] = tmp;
            while(!tmp.empty()){
                tmp.pop();
            }
            omp[str.substr(first_comma+1,address_length-1)].pop();
            if(average>=t){
                overspan(str.substr(first_comma+1,address_length-1),oomp[str.substr(first_comma+1,address_length-1)]);
            }
            oomp[str.substr(first_comma+1,address_length-1)].pop();
        }

        if(str.at(length-1) != '-' && mp.count(str.substr(first_comma+1,address_length-1)) && mp[str.substr(first_comma+1,address_length-1)].size() >= n){
            span(str.substr(first_comma+1,address_length-1),str.substr(0,14));
        }
        if(str.at(length-1) == '-'){
            mp[str.substr(first_comma+1,address_length-1)].push_back(str.substr(0,14));
        }
    }
    fin.close();
}