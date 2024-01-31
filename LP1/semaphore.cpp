#include<iostream>
#include<mutex>
using namespace std;
struct semaphore
{
    /* data */
    int mutex;
    int rcount;
    int rwait;
    bool wrt;
};
void addR(struct semaphore *s){
    if(s->mutex==0 && s->rcount==0){
        cout<<"\nSorry,file open in write mode!\n";
        s->rwait++;

    }
    else{
        s->rcount++;
        s->mutex--;
        cout<<"\nReader added\n";

    }
}
void addW(struct semaphore *s){
    if(s->mutex==1){
        cout<<"\nWriter added\n";
        s->wrt=1;
        s->mutex--;
    }
    else if(s->wrt) cout<<"\nWriter already operational\n";
    else{
        cout<<"\nSorry,File open in read mode\n";
    }
}
void remR(struct semaphore *s){
    if(s->rcount==0) cout<<"\nNo reader to remove\n";
    else{
        s->rcount--;
        s->mutex++;
        cout<<"\nReader removed\n";
    }
}
void remW(struct semaphore *s){
    if(s->wrt==0)
    cout<<"\nNo writer to remove\n";
    else{
        s->mutex++;
        s->wrt=0;
        cout<<"\nWriter removed\n";
        if(s->rwait!=0){
            s->mutex-=s->rwait;
            s->rcount=s->rwait;
            s->rwait=0;

        }
    }
}
int main()
{
	struct semaphore S1 = { 1, 0, 0 };
	while (1)
	{
		cout<< "Options :-\n1.Add Reader.\n2.Add Writer.\n3.Remove Reader.\n4.Remove Writer.\n5.Exit.\n\n\tChoice : ";
		int ch;
		cin >> ch;
		switch (ch)
		{
		case 1:
			addR(&S1);
			break;

		case 2:
			addW(&S1);
			break;

		case 3:
			remR(&S1);
			break;

		case 4:
			remW(&S1);
			break;

		case 5:
			cout << "\n\tGoodBye!";
			break;

		default:
			cout << "\nInvalid Entry!";

		}
	}
	return 0;
}
