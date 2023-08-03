#include <iostream>
#include <string>
using namespace std;
class Hamming{
    char st;
    int num;
    int arr[12];
    int binary[8];
    int p1,p2,p3,p4;
    public:
    Hamming(){
        for(int i=0;i<8;i++){
            binary[i]=0;
        }
        for(int i=0;i<12;i++){
            arr[i]=0;
        }
        p1=0;
        p2=0;
        p3=p4=0;
    }
    void input(){
        cout<<"Enter an alphabet: ";
        cin>>st;
        num=int(st);
        int i=7;
        while(num>0){
            binary[i]=num%2;
            num=num/2;
            i--;
        }
        for(int i=0;i<8;i++){
            cout<<binary[i];
        }
        cout<<endl;
    }
    
    void cal_p1(int arr[]){
        
        cout<<endl;
        int count=0;
        for(int i=11;i>=0;i-=2){
            if(arr[i]==1){
                count++;

            }
        }
        cout<<"count1: "<<count<<endl;
        if(count%2==0){
            p1=0;
        }
        else
            p1=1;
    
    }
    void cal_p2(int arr[]){
        int i=10;
        int count1=0;
        int cnt=0;
        while(i>=0){
            
            if(cnt!=2){
                if(arr[i]==1){
                    count1++;
                }
                
                i--;
                cnt++;
            }
        else
            i-=2;
            cnt=0;
            

        }
        cout<<"count2: "<<count1<<endl;
        if(count1%2==0)
            p2=0;
        else
            p2=1;
        
    }
    void cal_p3(int arr[]){
        int i=8;
        int count=0;
        int cnt=0;
        while(i>=0){
            
            if(count!=3){
                if(arr[i]==1){
                    cnt++;
                }
                 i--;
                 count++;
                
            }
        else
            i-=3;
            count=0;

        }
        cout<<"count3: "<<cnt<<endl;
        if(cnt%2==0){
            p3=0;
        }
        else
            p3=1; 
    }
    void cal_p4(int arr[]){
        int i=4;
        int cnt=0;
        while(i>=0){
           if(arr[i]==1){
                cnt++;
               
           }
            i--;  
        }
        cout<<"count4: "<<cnt<<endl;
        if(cnt%2==0)
            p4=0;
        else
            p4=1;
        
    }
    void print(){
        cout<<p1<<endl;
        cout<<p2<<endl;
        cout<<p3<<endl;
        cout<<p4<<endl;
    }
    void calculations(int arr[]){
        cal_p1(arr);
        cal_p2(arr);
        cal_p3(arr);
        cal_p4(arr);
    }
    void final_cal(){
        int arr[12];
        int j=0;
        for(int i=0;i<12;i++){
            if(i!=4 && i!=8 && i!=10 && i!=11){
                arr[i]=binary[j];
                j++;
            }
            else
                arr[i]=3;
        }
        cout<<"First Iteration"<<endl;
        calculations(arr);
        print();
        arr[4]=p4;
        arr[8]=p3;
        arr[10]=p2;
        arr[11]=p1;
        cout<<"\nSecond iteration"<<endl;
        calculations(arr);
        print();
        if(p1==0 && p2==0 && p3==0 && p4==0)
            cout<<"No error"<<endl;
        else{
            cout<<"Error found!"<<endl;
        }    
    }
};
int main(){
    
    Hamming h;
    h.input();
    h.final_cal();
    
    return 0;
}
