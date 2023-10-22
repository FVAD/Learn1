# include <iostream>
# include <vector>
using namespace std;

int main(){
    int a;
    int* pA;

    a = 5;
    pA = &a;
    cout <<"1234" << *pA    << "\n";
    
    int ray2[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++)
    {
        printf("%d", ray2[i]);
    }
    printf("\n-----\n");
    for (int a:ray2)
    {
        printf("%d", a);
    }
    printf("\n-----\n");
    
    cout << ray2 << endl;
    cout << &ray2[0] << endl;
    cout << *ray2 << endl;
    cout << ray2[0] << endl;
    int aray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    vector<int> v1(aray, aray+10);
    for (int i = 0; i < 10; i++)
    {
        cout << v1[i] << ' ';
    }
    vector<int> v2;
    v2.assign(v1.begin(), v1.end());
    for (int  i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << ' ';
    }
    cout << endl;
    int bray[] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> v3(bray, bray+10);
    v2.swap(v3);
    for (int  i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << ' ';
    }
    cout << endl;
    return 0;
}