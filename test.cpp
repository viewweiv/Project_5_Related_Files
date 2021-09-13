#include <iostream>
#include <vector>
#include "Dlist.h"
using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    Dlist<int> ilist2;
//    vector<CanonK<string, int>> airport;
    int *ip = new int(1);
    ilist.insertFront(ip);
    ilist2.insertFront(ip);

    int *p1 = ilist.removeFront();
    cout<<*p1<<endl;
    delete p1;
    int *p2 = ilist2.removeFront();
    cout<<*p2<<endl;
    delete p2;
//    ip = ilist.removeFront();
    if(*ip != 1)
        result = -1;
    delete ip;

    if(!ilist.isEmpty())
        result = -1;


    return result;
}

//int main(){
//    int *x=new int(1);
//    delete x;
//    *x=2;
//    cout<<*x<<endl;
//    cout<<(x == nullptr)<<endl;
//    return 0;
//}