#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
using namespace std;
class Process{
    int ct;
    int at;
    int bt;
    int wt;
    int tat;
    string pname;
    int pr;
    public:
    friend class Schedule;
    Process(){
        pname="";
        at=0;
        bt=0;
        ct=0;
        wt=0;
        tat=0;
        pr=0;
    }
    Process(string name,int atime,int btime){
        pname=name;
        at=atime;
        bt=btime;
    }
    

};
class Schedule{
    Process *p;
    int n;
    public:

    void input(){
        string process_name;
        int arrival_t,burst_t;
        cout<<"Enter the no of processes: ";
        cin>>n;
        p=new Process[n];
        for(int i=0;i<n;i++){
            cout<<"---------------------------------"<<endl;
            cout<<"Enter name of process: ";
            cin>>process_name;
            cout<<"Enter the arrival time: ";
            cin>>arrival_t;
            cout<<"Enter the burst time: ";
            cin>>burst_t;
            p[i]=Process(process_name,arrival_t,burst_t);
            
        }
       
    }
    void getpriority(){
        
        cout<<"Enter the no of processes: ";
        cin>>n;
        p=new Process[n];
        for(int i=0;i<n;i++){
            cout<<"---------------------------------"<<endl;
            cout<<"Enter name of the process: ";
            cin>>p[i].pname;
            cout<<"Enter the burst time: ";
            cin>>p[i].bt;
            cout<<"Enter the priority: ";
            cin>>p[i].pr;
            
        }
    }
    static bool compare_pt(Process p1,Process p2){
        return p1.pr<p2.pr;
    }
    static bool compare_at(Process p1,Process p2){
        return p1.at<p2.at;
    }
    void ganttChart() {
        cout<<"\n------------------------------------\n";
        cout<<"|";
        for (int i=0; i<n; i++) {
            cout<<"  "<<p[i].pname<<"  |";
        }
        cout<<"\n------------------------------------\n";
        cout<<0<<"      ";
        for (int j=0; j<n; j++) {
            cout<<p[j].ct<<"     ";
        }
        cout<<endl;
    }
    void fcfs(){
        int curr_time=0;
        int time=0;
        bool *visited= new bool[n];
        for(int i=0;i<n;i++){
            visited[i]=0;
        }
        int completedtask=0;
        while(completedtask<n){
            for(int i=0;i<n;i++){
                if(time>=p[i].at && visited[i]==0){
                    p[i].ct=curr_time+p[i].bt;
                    curr_time=p[i].ct;
                    visited[i]=1;
                    completedtask++;
                     
                }      
            }
            time++;
        }
       

    }
    void sjf_preemp(){
        int remaining[n];
        for(int i=0;i<n;i++)
            remaining[i]=p[i].bt;
        int curr_time=0,ctask=0,shortest=0,finish=0;
        int min=999;
        bool active=false; //tells if task is active or not;
        while(ctask<n){
                for(int j=0;j<n;j++){
                    if(p[j].at<=curr_time && p[j].bt<min && remaining[j]>0){
                        shortest=j;
                        min=p[j].bt;
                        active=true;
                    }
                }
                if(active==false){
                    curr_time++;
                    continue;
                }
                remaining[shortest]--;
                min=remaining[shortest];
                if(min==0){
                    min=999;
                }
                if(remaining[shortest]==0){
                    ctask++;
                    finish=curr_time+1;
                    p[shortest].ct=finish;                    
                    active=false;
                }
                curr_time++;

            }
            for(int i=0;i<n;i++){
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
        }
        }
    void Priority_s(){
        
        sort(p,p+n,compare_pt);
        
        int curr_time=0;
        for(int i=0;i<n;i++){
            curr_time+=p[i].bt;
            p[i].ct=curr_time;
        }
        
    }
    
    void calculations(){
        for(int i=0;i<n;i++){
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
        }
    }
    void display_priority(){
        cout<<"Process"<<setw(8)<<"BT"<<setw(8)<<"Prior"<<setw(8)<<"CT"<<setw(8)<<"TAT"<<setw(8)<<"WT"<<endl;
        calculations();
         
        for(int i=0;i<n;i++){
            cout<<p[i].pname<<setw(10)<<p[i].bt<<setw(10)<<p[i].pr<<setw(10)<<p[i].ct<<setw(10)<<p[i].tat<<setw(10)<<p[i].wt<<endl;
        }
        print_average();
        ganttChart();
        
    }
    void print_average(){
        float sum_tat=0;
        float sum_wt=0;
        for(int i=0;i<n;i++){
            sum_tat=sum_tat+p[i].tat;
            sum_wt=sum_wt+p[i].wt;
        }
        cout<<"Average turnaround time: "<<(sum_tat/n)<<endl;
        cout<<"Average waiting time: "<<(sum_wt/n)<<endl;

    }
    void display(){
        cout<<"Process"<<setw(8)<<"AT"<<setw(8)<<"BT"<<setw(8)<<"CT"<<setw(8)<<"TAT"<<setw(8)<<"WT"<<endl;
        calculations();
         
        for(int i=0;i<n;i++){
            cout<<p[i].pname<<setw(10)<<p[i].at<<setw(10)<<p[i].bt<<setw(10)<<p[i].ct<<setw(10)<<p[i].tat<<setw(10)<<p[i].wt<<endl;
        }  
        print_average();
        //ganttChart();
    }
    void roundrobin(){
        int curr_time=0,ctask=0;
        queue <int>q1;
        int curr;
        int remaining[n];
        int ts;
        cout<<"Enter the time slice: ";
        cin>>ts;
        for(int i=0;i<n;i++){
            if(p[i].at<=curr_time){
                q1.push(i);

            }
        }
        for(int i=0;i<n;i++){
            remaining[i]=p[i].bt;
        }
        while(ctask!=n){
            int cntr=0;
            curr=q1.front();
            q1.pop();
           
            while(cntr!=ts && cntr!=remaining[curr]){
                curr_time++;
                cntr++;
                for(int j=0;j<n;j++){
                    if(p[j].at==curr_time){
                        q1.push(j);

                    }
                }
                }
                cout<<p[curr].pname<<":"<<curr_time-cntr<<"-"<<curr_time<<endl;
                remaining[curr]-=cntr;
                if(remaining[curr]==0){
                    p[curr].ct=curr_time;
                    ctask++;
                }
                else{
                    q1.push(curr);
                }      
        }
        
    }


};
int main(){
    Schedule s;
    int ch;
    cout<<"\nMENU!!\n";
    cout<<"\n1.FCFS\n2.SRTF\n3.Priority\n4.Round Robin\n";
    cout<<"Enter you choice: ";
    cin>>ch;
    switch(ch){
        case 1:
            s.input();
            s.fcfs();
            cout<<"-----------------------------------"<<endl;
            cout<<" Process Table "<<endl;
            cout<<"-----------------------------------"<<endl;
            s.display();
            break;
        case 2:
            s.input();
            s.sjf_preemp();
            cout<<"-----------------------------------"<<endl;
            cout<<" Process Table "<<endl;
            cout<<"-----------------------------------"<<endl;
            s.display();
            break;
        case 3:
            s.getpriority();
            s.Priority_s();
            cout<<"-----------------------------------"<<endl;
            cout<<" Process Table "<<endl;
            cout<<"-----------------------------------"<<endl;
            s.display_priority();
            break;
        case 4:
            s.input();
            s.roundrobin();
            cout<<"-----------------------------------"<<endl;
            cout<<" Process Table "<<endl;
            cout<<"-----------------------------------"<<endl;
            s.display();
            break;

    }
    return 0;
}

