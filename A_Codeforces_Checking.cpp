#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    string b = "codeforces";
    set<char> s;
        for(int i=0;i<b.size();++i){
            s.insert(b[i]);
        }
    while(t--){
        string a;
        cin.ignore();
        cin>>a;
        
        if (s.find(a[0]) != s.end()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}