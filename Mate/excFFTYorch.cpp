 #include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

struct complejo{
    double a, b;
    complejo() {a = 0.0; b = 0.0;}
    complejo(double na, double nb) {a = na; b = nb;}
    const complejo operator+(const complejo &c) const
        {return complejo(a + c.a, b + c.b);}
    const complejo operator-(const complejo &c) const
        {return complejo(a - c.a, b - c.b);}
    const complejo operator*(const complejo &c) const
        {return complejo(a*c.a - b*c.b, a*c.b + b*c.a);}
    double magnitude() {return sqrt(a*a+b*b);}
    void print() {printf("(%.3f %.3f)\n", a, b);}
};
typedef complejo C;

const double PI = acos(0)*2;
const int MAX = 1e5+10;

vector <complejo> fta[MAX][25]; //auxiliary for fourier transform
vector <complejo> fti[MAX][25]; //auxiliary for inverse transform
int len;

complejo raiz[MAX*4];

int rev[MAX*4];

inline complejo root(int i,int n){
    return complejo(cos((2*PI*i)/n),sin((2*PI*i)/n) ) ;
}

int reverse(int x){
    int i = 0;
    int res = 0;
    while(x){
        res+= (x%2) << (len-1-i);
        i++;
        x/=2;
    }
    return res;
}


void fill( int x, int length, vector<complejo> & V){
    fta[x][length] = vector<complejo> ( 1 <<  length);
    if( length == 0){
        fta[x][length][0] = V[rev[x]];
        return;
    }
    complejo primroot = raiz[length];
    int giro = 1 << ( len - length);
    int currgir = 0;
    
    fill(2*x,length - 1, V);
    fill(2*x+1,length - 1, V);
    for(int i = 0; i< ( 1 << (length-1));i++){
        complejo root = raiz[currgir];
        fta[x][length][i] = fta[x*2][length-1][i] + fta[x*2+1][length-1][i]*root;
        fta[x][length][i + (1 << (length -1) )] = fta[x*2][length-1][i] - fta[x*2+1][length-1][i]*root;
        currgir += giro;
        if( currgir >= 1 << len) currgir -= 1 << len;
    }
}

void ifill( int x,int length,vector<complejo>& V){
    fti[x][length] = vector<complejo> ( 1 <<  length);
    if( length == 0){
        fti[x][length][0] = V[rev[x]];
        return;
    }
    int giro = 1 << (len - length);
    int currgir = 0;

    ifill(2*x,length - 1, V);
    ifill(2*x+1,length - 1, V);
    for(int i = 0; i< ( 1 << (length-1));i++){
        complejo root = raiz[currgir];
        fti[x][length][i] = fti[x*2][length-1][i] + fti[x*2+1][length-1][i]*root;
        fti[x][length][i + (1 << (length -1) )] = fti[x*2][length-1][i] - fti[x*2+1][length-1][i]*root;
        currgir -= giro;
        if( currgir < 0) currgir += 1 << len; 
    }
}

vector <complejo> fft( vector <complejo>& V, int k){
    fill(0,k,V);
    return fta[0][k];
}

vector <complejo> ifft( vector <complejo>& V, int k){
    ifill(0,k,V);
    for(int i = 0;i< (1 << k); i++){
        fti[0][k][i].a /= (1 << k);
        fti[0][k][i].b /= (1 << k);
    }
    return fti[0][k];
}

void imprime( vector<complejo>& A){
    for(int i=0;i<A.size();i++){
        printf("(%f %f) ",A[i].a,A[i].b);
    }
    printf("\n");
}

vector <complejo> multpoli( vector <complejo>& A, vector<complejo>& B){
    int prodlen = A.size() + B.size();
    int pot = 1;
    len = 0;
    while( pot <= prodlen ){
        pot*=2;
        len ++;
    }
    for(int i = 0;i<pot;i++){
        raiz[i] = root( i, pot);
        rev[i] = reverse(i);
    }
    while( A.size() < pot){
        A.push_back( complejo(0,0) );
    }
    while( B.size() < pot){
        B.push_back( complejo(0,0) );
    }
    vector <complejo> tA = fft(A,len);
    vector <complejo> tB = fft(B,len);
    vector <complejo> tR(A.size());
    vector <complejo> A2 = ifft(tA,len);
    for(int i = 0;i<tA.size();i++){
        tR[i] = tA[i]*tB[i];
    }
    vector <complejo> R = ifft(tR,len);
    while( R.back().magnitude() < 0.001){
        R.pop_back();
    }
    return R;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<complejo> P(n + 1), Q(n + 1);
        for(int i = 0; i <= n; i++)
            cin >> P[i].a;
        for(int i = 0; i <= n; i++)
            cin >> Q[i].a;
        auto R = multpoli(P, Q);
        for(int i = 0; i <= 2*n; i++)
            cout << (long long)round(R[i].a) << " ";
        cout << '\n';
    }
}