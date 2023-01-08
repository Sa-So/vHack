#include<bits/stdc++.h>
using namespace std;

// class Prod {
// };
// nah i'll just use int for products
// Taking inpu is O(k)

class Line {
    public:
    int lineNo; // const (why do we need this ? coz we are making a vector of lines and prob. sorting them :/ )
    
    
    // if i sort, then the line from which i want to reuce capacity , finding that line would be O[n]

    // if I don't sort , finding which prod to fit in first is diff. !


    // vector<int> TypesAllowed; 
    // const again.
    // better to use a map
    map<int,int> isAllowed;
    // now we need count of these.
    int nAllowed;


    // int nDone;

    int capacity; // variable within an year and also after an year.
    // int initialCapacity; // do we need this ?
    // vector<int> TypesHolding;
    map<int,int> isAssigned;     // return 0 if not assigned.
    // do we really need to answer to queries like is this line l given prod. type no. x ? / is x on line l ?

    bool isProdAllowed(int p){
        return isAllowed[p]>=1 ? true : false; // == would work too coz only incrementing once ah
    }

    void allow(int p){
        if(isAllowed[p]>=1){
            cout<<"You've already allowed this type of product !\n";
            return;
        }
        isAllowed[p]++;
        nAllowed++;
    }

    void assign(int p){
        isAssigned[p]++;
        capacity--;
    }
    // Line(){
        
    // }
};
class Compare {
    public:
       bool operator()(Line a, Line b){
           
           // or nLeft - /// ?
           int pa = a.nAllowed - a.capacity;
           int pb = b.nAllowed - b.capacity;


           if(pa==pb){
               if(a.capacity < b.capacity){
                   return true;
               }
               // if the capacities are equal as well then we don't care
               return false;
           }
           // return pa < pb; // short hand but I find this to be very rude.

           if(pa < pb){
               // don't swap , this is good !
               return true;
           }
           return false;
      }
};

// let's think from line perspective, I can fit in 1,2,3
// if a no. x is done , skip !
// if not done & I have a lot of roooooom i.e  c >= allowed_types - done_types or we can say left_ones_that_can_be_added_to_this_line. , assign !
// if not done & I don't have a lot of room wait.? then what ?

// can we remove this product from here and shift it to somewhere else 
// where is the most room / cap?
// even if we know where most cap is at all times we will still have to do O(m) to find space coz may be only the last line can allow prod p.
// we need somethin better.
// a vector of priority queues ?! what.

int main(){
    int n,m,k;cin>>n>>m>>k;
    
    vector<Line> AssemblyLines(m);
    for(int i=0;i<m;i++){

        AssemblyLines[i].lineNo = i+1; // or i ?

    }
    while(k--){
        int x,y;cin>>x>>y;
        AssemblyLines[y-1].allow(x);
    }

    priority_queue<Line, vector<Line>, Compare> Lines;//Lines(m);

    for(int i=0;i<m;i++){
        Lines.push(AssemblyLines[i]);
    }

    for(auto line:Lines){
        
    }
    
    
    int z;cin>>z;
    while(z--){
        
        
        // calc ans in ~ O(m)
         
        
        int r,p;
        cin>>r>>p;
        // remove node r from pq

        // insert node r with capacity of old-p;

        // 
    }

}
