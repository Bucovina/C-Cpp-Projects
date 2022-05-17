#include <iostream>
#include <algorithm>

using namespace std;

int mat[101][101], contor = 1;
int sol[101][101];
int num[10];
int v, b, k, l, r;

bool solpartnumber(int p) {
    for (int i = 1; i < p; i++)
        if (num[p] <= num[i])
            return false;
    return true;
}

void number(int p) {
    int i;
    for (i = 1; i <= v; i++) {
        num[p] = i;
        if (solpartnumber(p) == 1)
            if (p == k) {
                for (int j = 1; j <= p; j++)
                    mat[contor][j] = num[j];
                contor++;
            } else
                number(p + 1);
    }
}

void atribuire(int p, int n) {
    for (int i = 1; i <= k; i++)
        sol[p][i] = mat[n][i];
}

void afis(int p){
    int i,j;
    for(i=1;i<=p;i++)
    {for(j=1;j<=k;j++)
            cout << sol[i][j];
        cout << " ";
    }
    cout<<"\n";
}

int makenumer(int n)
{
    int rez=0;
    for(int i=1;i<=k;i++)
        rez=rez*10+sol[n][i];
    return rez;
}

bool ord(int p){
    int nump= makenumer(p);
    for (int i = 1; i < p; i++)
        if (nump<= makenumer(i))
            return false;
    return true;
}

bool solpart(int p){
    int i,j,o;
    int index[11][11]={};
    for(i=1;i<=p;i++)
        for(j=1;j<k;j++)
            for(o=j+1;o<=k;o++)
                index[sol[i][j]][sol[i][o]]++;
    for(i=1;i<v;i++)
        for(j=i+1;j<=v;j++)
            if(index[i][j]>l)
                return false;
    return true;
}

bool solbkt(int p){
    int index[11];
    int i,j;
    if(p==b){
        for(i=1;i<=p;i++)
            for(j=1;j<=k;j++)
                index[sol[i][j]]++;
        for(i=1;i<=v;i++)
            if(index[i]!=r)
                return false;
        return true;
    }
    else return false;
}

void bkt(int p) {
    int i;
    for (i = p; i < contor; i++) {
        atribuire(p, i);
        if(ord(p) && solpart(p))
            if (solbkt(p)) {
                afis(p);
            } else bkt(p + 1);
    }
}

int main() {
    v = 6, b = 10, k = 3, l = 2, r = 5;
    ///v = 7, b = 7, k = 3, l = 1, r = 3;
    ///v=4,b=4,k=2,l=2,r=2;
    number(1);
    bkt(1);
    return 0;
}
