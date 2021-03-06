#include <iostream>

using namespace std;

long long dp[1001] = {0};

struct big_number
{
    int arr[500];
    bool visit;
    void operator= (int A)
    {
        for(int i = 0;i < 500;i++)
        {
            this->arr[i] = A % 10;
            A /= 10;
        }
        /*
        for(int i = 0;i < 500;i++)
        {
            cout << arr[i];
        }
        */

    }
    
};

big_number array[1001] = { { {0}, false } };

big_number operator + (big_number A, big_number B)
{
    big_number T = { {0}, false };
    bool carry_flag = 0;
    for(int i = 0;i < 500;i++)
    {
        T.arr[i] = A.arr[i] + B.arr[i];
        if(carry_flag)
        {
            carry_flag = 0;
            T.arr[i]++;
        }
        if(T.arr[i] >= 10)
        {
            carry_flag = 1; 
            T.arr[i] -= 10;
        }
    }
    return T;
}

big_number operator * (big_number A, int B)
{
    big_number T = { {0}, false };
    bool carry_flag = 0;
    for(int i = 0;i < 500;i++)
    {
        T.arr[i] = A.arr[i] * 2;
        if(carry_flag)
        {
            carry_flag = 0;
            T.arr[i]++;
        }
        if(T.arr[i] >= 10)
        {
            carry_flag = 1; 
            T.arr[i] -= 10;
        }
    }
    return T;
}

/*
*/

big_number bignum1, bignum2;

big_number fun(int n)
{
    if(array[n].visit != 0)
        return array[n];
    array[n].visit = true;
    if(n == 1)
        return array[n] = bignum2;
    if(n == 2)
        return array[n] = fun(1) * 2 + bignum1;
    if(n == 3)
        return array[n] = fun(1) + fun(2) * 2 + bignum1;
    return array[n] = fun(n - 1) * 2 + fun(n - 2) + fun(n - 3);
}

int main()
{
    bignum1 = 1; 
    bignum2 = 2;
    
    int n;
    while(cin >> n)
    {
        big_number ANS;
        ANS = fun(n);
        bool flag = 0;
        for(int i = 499;i >= 0;i--)
        {
            if(!flag && ANS.arr[i])
                flag = 1;
            if(flag)
                cout << ANS.arr[i];
        } 
        cout << endl;
    }
    
    /*
    int n;
    big_number A;
    cin >> n;
    A = n;
    */
    //A = A = n;
    //cout << A.operater=(n);
    //cout << endl;
    /*
    for(int i = 0;i < 500;i++)
    {
        cout << A.arr[i];
    }*/
    /*
    big_number A, B;
    A = B;
    for(int i = 0;i < 500;i++)
    {
        cout << A.arr[i];
    }
    cout << endl;
    for(int i = 0;i < 500;i++)
    {
        cout << B.arr[i];
    }
    */
    return 0;
}
