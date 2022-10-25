#include <bits/stdc++.h>
using namespace std;
// class swap {
//     public:
//         long long x,y,c;
// };
const long long MAX = 1e9;
int main() {
    // cout<<"Hello World!";
    string s;
    cin>>s;
 
    // int mat[26][26];
    vector<vector<long long> > mat(26,vector<long long>(26,MAX));
 
    long long n = s.length();// s.size() is same
    // map<char,long long> mp;
    // for(long long i=0;i<n;i++){
    //     mp[s[i]]++;
    // }
 
    long long m;
    cin>>m;
    // swap arr[m];
    for(int i=0;i<26;i++){
        mat[i][i]=0;
    }
    for(long long tt=0;tt<m;tt++){
        char x,y;
		long long c;
 
        cin>>x>>y>>c;
        
		long long X = x-'a';
		long long Y = y-'a';
		
		mat[X][Y]=c;
        mat[Y][X]=c;
        // cin>>arr[i].x>>arr[i].y>>arr[i].z;
 
    }
    // m => b   t => b
    // m t
    // m=> t t=>t
    // __b_____t__
    // t => b
    // 
    
    //   m     m
 
    for(int k=0;k<26;k++){
        for(int i=0;i<26;i++){
            for(int j=0;j<26;j++){
                mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
                mat[j][i]=min(mat[j][i],mat[j][k]+mat[k][i]);
            }
        }
    }
 
    // for(int i=0;i<26;i++){
    //         for(int j=0;j<26;j++){
    //             cout<<mat[i][j]<<" ";
    //             // mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
    //             // mat[j][i]=min(mat[j][i],mat[j][k]+mat[k][i]);
    //         }
    //         cout<<endl;
    //     }
 
    // pali.
    // odd => we have to make n-1/2 same pairs.
    // even => n/2 pairs of same characters.
    long long l=0,r=n-1;
    long long cost = 0; // 1e5 * 1e8 might overflow.
    // for(;l<r;){
    while(l<r){
        if(s[l]!=s[r]){
            long long cst=MAX;
            for(int alp = 0; alp <26; alp++)
            {
               // costof changing both to this alphabet !
                cst=min(cst,mat[s[l]-'a'][alp]+mat[s[r]-'a'][alp]);
            }
            cost+=cst;
            // min(mat[s[l]-'a'][s[r]-'a'],mat[s[r]-'a'][s[l]-'a']);
        }
        l++;
        r--;
    }
    cout<<cost<<endl;
 
    
    // shortest way to make pali.
    // cost of everychar into every other char is 10000
    // but cost of changing a b is 1 
    
    // points missed
    // eg. mat
    // we can change both m to let's say b & t to b to achieve pali. & it may have lesser cost !!!
    // we can change m to something else before making it t to reduce the cost. so m-> b -> t might have smaller cost !!!
    
}
