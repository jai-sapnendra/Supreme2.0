#include<iostream>
#include<queue>
#include<stack>
using namespace std;

void interLeaveQueue(queue<int> &first) {
    queue<int> second;

    // push first half of first queue in second queue
    int size = first.size();
    for(int i=0; i<size/2; i++) {
        int temp = first.front();
        first.pop();

        second.push(temp);
    }

    // merge both the halves into the original queue - named as first
    for(int i=0; i<size/2; i++) {
        int temp = second.front();
        second.pop();

        first.push(temp);

        temp = first.front();
        first.pop();
        first.push(temp);
    }
}

int main() {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);
    q.push(50);
    q.push(60);

    interLeaveQueue(q);

    cout <<"Printing Queue After reverse k element : "<<endl;
    while(!q.empty()) {
        int element = q.front();
        q.pop();

        cout << element << " ";
    }
    cout << endl;
}