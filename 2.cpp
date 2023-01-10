#include<bits/stdc++.h>
using namespace std;

// class Prod {
// };
// nah i'll just use int for products

class Line {
    public:
    int lineNo; 
    // const (why do we need this ? coz we are making a vector of lines and prob. sorting them :/ )
    // if i sort, then the line from which i want to reuce capacity , finding that line would be O[n]
    // if I don't sort , finding which prod to fit in first is diff. !
    // should I create a mapping of which index has line no. x ?


    vector<int> TypesAllowed; 
    // const again.
    // better to use a map
    map<int,int> isAllowed;
    // now we need count of these if using a map
    int nAllowed;
    // int nDone;
    int capacity; // variable within an year and also after an year.
    int initialCapacity; // do we need this ?

    vector<int> assigned;
    map<int,int> isAssigned;     // return 0 if not assigned.?
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
        TypesAllowed.push_back(p);
    }

    void assign(int p){
        if(capacity < 1){
            cout<<"Underflow !"<<endl;
        }
        isAssigned[p]++;
        assigned.push_back(p);
        capacity--;
    }

    void printAllowed(){
        cout<<lineNo<<": ";
        cout<<"("<<capacity<<")[";
        for(auto typ:TypesAllowed){
            cout<<typ<<", ";
        }
        cout<<" ] ";
        // <<endl; // put endl as per your wish in code.
    }

    void printAssigned(){
        cout<<lineNo<<": ";
        cout<<"("<<capacity<<")[";
        for(auto al:assigned){
            cout<<al<<", ";
        }
        cout<<" ] ";
    }

    void refresh(){
        assigned.clear();
        capacity=initialCapacity;
    }

    int getPriority(){
        // return TypesAllowed.size()-capacity;
        return nAllowed-capacity;
    }
};
bool compare(Line a, Line b){
    
    int pa = a.getPriority();
    int pb = b.getPriority();
    if(pa==pb){
        return a.capacity < b.capacity;
    }
    // jiski capacity kum hai usse pehle fill karenge 
    return pa < pb;
}

// for pq
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
    
    vector<Line> assemblyLines(m);
    for(int i=0;i<m;i++){

        assemblyLines[i].lineNo = i+1; // or i ?

    }
    while(k--){
        int x,y;cin>>x>>y;
        assemblyLines[y-1].allow(x);
    }

    // for(int i=0)

    // priority_queue<Line, vector<Line>, Compare> Lines;//Lines(m);

    for(int i=0;i<m;i++){
    //     // Lines.push(AssemblyLines[i]);
        cin>>assemblyLines[i].capacity;
        assemblyLines[i].initialCapacity = assemblyLines[i].capacity;
    }

    // debug
//     for(auto line:assemblyLines){
//         line.printAllowed();
//         cout<<endl;
//     }
    // cout<<endl;

    

    // set<int> leftProdsSet;
    // vector<int> gleftProds;

    // for(int i=0;i<n;i++){
    //     gleftProds.push_back(i+1);
    // }
    vector<bool> gIsProdLeft(n+1,true);
    
    
    
    vector<Line> sortedAssemblyLines = assemblyLines;
    sort(sortedAssemblyLines.begin(),sortedAssemblyLines.end(),compare);
    
    int z;cin>>z;
    // int Z;
    int r=-1,p=0;
    while(z--){
        
        int ans = 0; // max ans = n
        vector<bool> isProdLeft = gIsProdLeft;
        // vector<int> leftProds = gleftProds;

        bool flag = false; // are we swapping ?
        for(int i=0;i<m;i++){
            sortedAssemblyLines[i].refresh();

            if(sortedAssemblyLines[i].lineNo == r){// no need of r-1 here.
                sortedAssemblyLines[i].capacity-=p;
                sortedAssemblyLines[i].initialCapacity-=p;
                flag = true;
            }

            if(flag && i+1<n){
                if(compare(sortedAssemblyLines[i],sortedAssemblyLines[i+1])){
                    flag=false;
                }else{
                    swap(sortedAssemblyLines[i],sortedAssemblyLines[i+1]);
                    sortedAssemblyLines[i].refresh();
                }
            }

            // sortedAssemblyLines[i].assignAll(leftProds);
            for(int j=0;j<sortedAssemblyLines[i].TypesAllowed.size();j++){
                if(sortedAssemblyLines[i].capacity>0 && isProdLeft[sortedAssemblyLines[i].TypesAllowed[j]]){
                    isProdLeft[sortedAssemblyLines[i].TypesAllowed[j]]=false;
                    sortedAssemblyLines[i].assign(sortedAssemblyLines[i].TypesAllowed[j]); // cap-- happens inside here
                    ans++;
                }
            }
        }
        
        // calc ans in ~ O(m)
        
        // debug 
//         for(auto line:sortedAssemblyLines){
//             line.printAssigned();
//             cout<<endl;
//         }


        cout<<ans<<endl;
        // int r,p;
        cin>>r>>p;
         
        
        // assemblyLines[r-1].capacity-=p;

        /*
        if(assemblyLines[r-1].capacity - p < assemblyLines[r-1].assigned.size()){
            // remove all ?
            assemblyLines[r-1].capacity-=p;
            for(auto p:assemblyLines[r-1].assigned){
                isProdLeft[p]=true;
            }
            assemblyLines[r-1].assigned.clear();
        
        }else{
            assemblyLines[r-1].capacity-=p;
        }
        */

        // remove node r from pq

        // insert node r with capacity of old-p;

        // 
        // cout<<ans;



        // cout<<endl;
    }

}
// Update / What addition did I do ?
// We can optimize the sorting to just swaping.
// as only 1 line has changed it's capacity we keep swapping it with the next line
// until priority (n-cap.) doesn't become < than it's right one !


// but complexity redN = z * n * log (n) to z* n
// and since n is only uptil  2000 i don't think it really matters much
// and it will also require clearing assigned prods every time 
