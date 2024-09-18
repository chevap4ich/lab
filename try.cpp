#include <iostream>
using namespace std;

int main()
{
    int size = 0;
    int pr = 1;
    cout << "size of array - ";
    cin >> size;
    cout << "enter the numbers" << endl;
    int* d_arr = new int[size];
    for(int i = 0; i < size; i++){
        cin >> d_arr[i];
        pr = pr*d_arr[i];
    }
    cout << pr << endl;
    cout << d_arr;


}
