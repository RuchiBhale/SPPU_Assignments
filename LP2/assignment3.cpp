#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
class Job{
    string id;
    int deadline;
    int profit;
    public:
    Job(){
        id="";
        deadline=0;
        profit=0;
    }
    friend class Schedule;
};
class Schedule{
    Job *j;
    int n;
    public:
    Schedule(){
        n=0;
        j=nullptr;
    }
    static bool compare(const Job j1,const Job j2){
        return(j1.profit>j2.profit); //compare the jobs based on the profit

    }
    int min(int a, int b){ //return the minimum value
        return (a<b)?a:b; 
    }
    void input(){
        cout<<"Enter the number of jobs: ";
        cin>>n;
        j=new Job[n];
        cout<<"Enter the job details: ";
        for(int i=0;i<n;i++){
            cout<<"Enter the job id: ";
            cin>>j[i].id;
            cout<<"Enter the deadline: ";
            cin>>j[i].deadline;
            cout<<"Enter the profit: ";
            cin>>j[i].profit;
        }
    }
    void order(){
        sort(j,j+n,compare);
        //sort the jobs in descending order of profit
        string jobseq[n];
        bool slot[n]; //to keep a track of free time slots
        for(int i=0;i<n;i++){
            slot[i]=false;
        }
        for(int i=0;i<n;i++){
            for(int k=min(n,j[i].deadline)-1;k>=0;k--){ //search from last free slot
                if(slot[k]==false){
                    jobseq[k]=j[i].id;
                    slot[k]=true; //mark the slot as occupied
                    break;

                }

            }
        }
        for(int i=0;i<n;i++){
            if(slot[i])
                cout<<jobseq[i]<<"  ";
        }


    }
    void display(){
        cout<<"ID"<<setw(10)<<"Deadline"<<setw(10)<<"Profit\n";
        for(int i=0;i<n;i++){
            cout<<j[i].id<<"\t"<<j[i].deadline<<"\t"<<j[i].profit<<"\n";
        }
    }

};
int main(){
    Schedule s;
    cout<<"INPUT: \n";
    s.input();
    cout<<"Entered jobs are as follows: \n";
    s.display();
    cout<<"Job Scheduling using greedy search approach: \n";
    s.order();
    return 0;

}