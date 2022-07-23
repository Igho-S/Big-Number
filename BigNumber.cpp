#include <bits/stdc++.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
//Хаззан Омотола

typedef unsigned short int BASE;
typedef unsigned int DBASE;
#define BASE_SIZE sizeof(BASE)*8;

using namespace std;

class BN{ 
    BASE *coef;
    int len;
    int maxlen;
    
    public:
    
    BN(int ml=1, int t = 0);
    BN(const BN&);
    ~BN() {
        if(coef){
            delete[] coef;
            coef = 0;
        }
    };
    
    bool operator < (const BN&);
    bool operator <= (const BN&);
    bool operator > (const BN&);
    bool operator >= (const BN&);
    bool operator == (const BN&);
    bool operator != (const BN&);
    BN& operator = (const BN&);
    BN operator + (const BN&);
    BN& operator += (const BN&);
    BN operator - (const BN&);
    BN& operator -= (const BN&);
    BN operator * (const BASE&);
    BN&  operator *= (const BASE&);
    BN  operator * (const BN&);
    BN&  operator *= (const BN&);
    BN operator / (const BASE&);
    BASE operator % (const BASE&);
    BN operator / (const BN&);
    BN operator % (const BN&);
    
    void cin_b10();
    void cout_b10();

    friend BN operator*(BASE num, BN base_num){ return base_num*num;};
    friend ostream& operator << (ostream&, const BN&);
    friend istream& operator >> (istream&, BN&);
};

BN::BN(int ml, int t){
    //srand(time(0));
    coef = new BASE[ml];
    maxlen = ml;
    len = 1;

    for(int i = 0; i<ml; i++){
        coef[i]=0;
    }
    
    if(t==1){
        len = ml;
        unsigned int b = BASE_SIZE;
        for(int i=0; i<len; i++){
            
            for(int j = 0; j*12 < b; j++){
                 coef[i] = coef[i]<<(j*12)|rand();
            }

        }
        while(len>1 && coef[len-1]==0){
            len--;
        }
    }
    else if (t != 0){
        cout << "Error!";
        exit(0);
    }
    
};

BN::BN(const BN& big_n){
    maxlen = big_n.maxlen;
    len = big_n.len;
    coef = new BASE[maxlen];
    for(int i = 0; i<maxlen; i++){
        coef[i]=big_n.coef[i];
    }
};

ostream& operator<<(ostream& out, const BN& big_n){
    int b = BASE_SIZE;
    int k = b - 4;
    int j = big_n.len - 1;
    
    while(j>-1){
        unsigned int tmp = (big_n.coef[j]>>k) & (0xf);

        if(0<=tmp && tmp<10){
            out << (char)(tmp + '0');
        }
        else if(tmp>9 && tmp<16){
            out << (char)(tmp - 10 + 'a');
        }
        k-=4;
        // k = k - 4;
        if(k<0){
            k = b - 4;
            j--;
            out<<" ";
        }
    }
    return out;
}

istream& operator >> (istream &in, BN & big_n){
    char* s = new char[1000];
    int b = BASE_SIZE
    int j = 0;
    int k = 0;
    unsigned int tmp = 0;
    
    in.getline(s, 1000);
    big_n.len = (strlen(s)-1)/(b/4)+1;
    big_n.maxlen = big_n.len;
    big_n.coef = new BASE[big_n.maxlen];
    for(int i = strlen(s)-1; i>-1; i--){
        if('0'<=s[i] && s[i]<='9'){
            tmp = s[i] - '0';
        }
        else if('a'<=s[i] && s[i]<='f'){
            tmp = s[i] - 'a' + 10;
        }
        else if('A'<=s[i] && s[i]<='F'){
            tmp = s[i] - 'A' + 10;
        }
        else{
            cout << "Error!";
            exit(0);
        }

        big_n.coef[j] |= tmp<<(k*4);
        k++;
        if(k>= b / 4){
            k=0;
            j++;
        }
    }
    return in;
}

bool BN::operator <(const BN& big_n){
    if(len < big_n.len){
        return true;
    }
    else if(len > big_n.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] > big_n.coef[i])
        {
            return false;
        }
        else if (coef[i] < big_n.coef[i])
        {
            return true;
        }
    }
    return false;
}

bool BN::operator <=(const BN& big_n){
    if(len < big_n.len){
        return true;
    }
    else if(len > big_n.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] > big_n.coef[i])
        {
            return false;
        }
        else if (coef[i] < big_n.coef[i])
        {
            return true;
        }
    }
    return true;
}

bool BN::operator > (const BN& big_n){
    if(len > big_n.len){
        return true;
    }
    else if(len < big_n.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] < big_n.coef[i])
        {
            return false;
        }
        else if (coef[i] > big_n.coef[i])
        {
            return true;
        } 
    }
    return false;
}

bool BN::operator >= (const BN& big_n){
    if(len > big_n.len){
        return true;
    }
    else if(len < big_n.len){
        return false;
    }
    for(int i = len-1; i>-1; i--){
        if (coef[i] < big_n.coef[i])
        {
            return false;
        }
        else if (coef[i] > big_n.coef[i])
        {
            return true;
        } 
    }
    return true;
}

bool BN::operator==(const BN& big_n){
    if(len != big_n.len){
        return false;
    }

    for(int i = 0; i<len; i++){
        if (coef[i] != big_n.coef[i])
        {
            return false;
        }   
    }
    return true;
}

bool BN::operator!=(const BN& big_n){
    if(len != big_n.len){
        return true;
    }

    for(int i = 0; i<len; i++){
        if (coef[i] != big_n.coef[i])
        {
            return true;
        }   
    }
    return false;
}

BN& BN::operator = (const BN& big_n){
    if(this != &big_n){
        maxlen = big_n.maxlen;
        len = big_n.len;
        coef = new BASE[maxlen];
        for(int i = 0; i<maxlen; i++){
            coef[i]=big_n.coef[i];
        }
    }
    return *this;
};

BN BN::operator + (const BN& big_n){
    int l = max(len, big_n.len)+1;
    int t = min(len, big_n.len);
    BN sum(l);
    DBASE tmp;
    int j =0;
    int k = 0;
    int b = BASE_SIZE;
    while (j<t)
    {
        tmp = (DBASE)coef[j] + (DBASE)big_n.coef[j] + (DBASE)k;
        sum.coef[j] = (BASE)tmp;
        k = (BASE)(tmp >> b);
        j++;
    }
    while(j < len){
        tmp = coef[j] + k;
        sum.coef[j] = (BASE)tmp;
        k = (BASE)(tmp >> b);
        j++;
    }

    while(j < big_n.len){
        tmp = (DBASE)big_n.coef[j] + (DBASE)k;
        sum.coef[j] = (BASE)tmp;
        k = (BASE)(tmp >> b);
        j++;
    }
    sum.coef[j] = k;
    sum.len = j+1;
    while(sum.len>1 && sum.coef[sum.len-1]==0){
        sum.len--;
    }
    return sum;
}

BN& BN::operator += (const BN& big_n){
    *this = *this + big_n;
    return *this;

}

BN BN::operator - (const BN& big_n){
    if(*this < big_n){
        cout << "Error!";
        exit(0);
    }

    int j=0;
    DBASE k = 0;
    DBASE tmp;
    int b = BASE_SIZE;
    BN sub(len);
    while(j<big_n.len){
        tmp = ((DBASE)1<<b) | (DBASE)coef[j];
        tmp = (DBASE)tmp - (DBASE)big_n.coef[j] - (DBASE)k;
        sub.coef[j] = (BASE)tmp;
        k = !(tmp>>b);

        j++;
    }
    while(j < len){
        tmp = ((DBASE)1<<b) | (DBASE)coef[j];
        tmp -= (DBASE)k;
        sub.coef[j] = (BASE)tmp;
        k = !(tmp>>b);
        j++;
    }
    sub.len = len;
    while(sub.len>1 && sub.coef[sub.len-1]==0){
        sub.len--;
        
    }
    return sub;
}

BN& BN::operator -= (const BN& big_n){
    *this = *this - big_n;
    return *this;

}

BN BN::operator * (const BASE& num){
    int j = 0;
    BASE k = 0;

    BN mul(len+1);
    DBASE tmp;
    
    int b = BASE_SIZE;

    while(j < len){
        tmp = (DBASE)coef[j]* (DBASE)num + (DBASE)k;
        mul.coef[j] = (BASE)tmp;
        k=(BASE)(tmp>>b);
        j++;
    }
    mul.coef[j] = k;
    mul.len = len+1;
    while(mul.len>1 && mul.coef[mul.len-1]==0){
        mul.len--;
    }
    return mul;

}

BN& BN::operator *= (const BASE& num){
    *this = *this * num;
    return *this;
}

BN BN::operator * (const BN& big_n){
    int j = 0;

    BN mul(len + big_n.len);
    DBASE tmp;
    
    int b = BASE_SIZE;

    while(j<big_n.len){
        if(big_n.coef[j]!=0){
            BASE k = 0;
            int i = 0;
            while (i<len)
            {
                tmp = ((DBASE)coef[i]*big_n.coef[j] + (DBASE)mul.coef[i+j] + (DBASE)k);
                mul.coef[i+j] = (BASE)tmp;
                k=(BASE)(tmp>>b);
                i++;
            }
            mul.coef[len+j] = k;  
        }
        j++;
    }
    mul.len = len + big_n.len;
   while(mul.len>1 && mul.coef[mul.len-1]==0){
        mul.len--;
    }
    
    return mul;

}

BN& BN::operator *= (const BN& big_n){
    *this = *this * big_n;
    return *this;
}

BN BN::operator / (const BASE& num){
    int j = 0;

    DBASE tmp = 0;
    BN divv(len);

    BASE r = 0;
    int b = BASE_SIZE;

    while (j<len)
    {
        tmp = (((DBASE)r<<b) + (DBASE)coef[len-1-j]);

        divv.coef[len-1-j] = (BASE) (tmp / (DBASE)num);
        r = (BASE)(tmp % (DBASE)num);
        j++;
    }
    
    divv.len = len;
    while(divv.len>1 && divv.coef[divv.len-1]==0){
        divv.len--;
    }
    
    return divv;
}

BASE BN::operator % (const BASE& num){
    int j = 0;

    DBASE tmp = 0;

    BASE r = 0;
    int b = BASE_SIZE;

    while (j<len)
    {
        tmp = (((DBASE)r<<b) + (DBASE)coef[len-1-j]);
        r = (BASE)(tmp % (DBASE)num);
        j++;
    }
    
    
    return r;
}

BN BN::operator / (const BN& num){

    if(num.len == 1 && num.coef[0] == 0){
        cout << "Error!";
        exit(0);
    }
    
    if(*this < num){
        BN res(1);
        return res;
    }
    
    if(num.len == 1){
        return *this/num.coef[0];
    }
    
    int m = len-num.len;
    int base_size = BASE_SIZE
    DBASE b = ((DBASE)1 << base_size);
    DBASE d = b/(DBASE)(num.coef[num.len-1] + (BASE)1);
    int j = m;
    int k = 0;

    BN newNum = *this; //dividend
    newNum *= d;
    BN div_sor = num; //divisor
    div_sor *= d;
    
    BN res(m+1); 
    res.len = m+1; 

    if(newNum.len == len){
        newNum.maxlen++;
        newNum.len = maxlen;
        newNum.coef = new BASE[maxlen];
        for (int i = 0; i <  len; i++){
            newNum.coef[i] = coef[i];
        }
        newNum *= d;
        newNum.len++;
        newNum.coef[newNum.len-1] = 0;
    }

    while (j>-1){
        DBASE q = (DBASE)((DBASE)((DBASE)((DBASE)(newNum.coef[j + div_sor.len]) * (DBASE)(b)) + (DBASE)( newNum.coef[j + div_sor.len - 1] )) / (DBASE)( div_sor.coef[div_sor.len - 1]));
        DBASE r = (DBASE)((DBASE)((DBASE)((DBASE)(newNum.coef[j + div_sor.len]) * (DBASE)(b)) + (DBASE)( newNum.coef[j + div_sor.len - 1] )) % (DBASE)( div_sor.coef[div_sor.len - 1]));
        
        if(q == b || (DBASE)((DBASE)(q) * (DBASE)( div_sor.coef[div_sor.len-2] )) > (DBASE)((DBASE)((DBASE)(b) * (DBASE)(r)) + (DBASE)( newNum.coef[j+div_sor.len-2]))){
            q--;
            r = (DBASE)(r) + (DBASE)(div_sor.coef[div_sor.len - 1]);
            if((DBASE)(r)<b){
                if(q == b || (DBASE)((DBASE)(q) * (DBASE)(div_sor.coef[div_sor.len-2])) > (DBASE)((DBASE)((DBASE)(b) * (DBASE)(r)) + (DBASE)( newNum.coef[j+div_sor.len-2]))){
                    q--;
                }
            }
        }
        //12300

        BN u(div_sor.len + 1);
        u.len = div_sor.len + 1;
        for(int i = 0; i < div_sor.len + 1; i++){
            u.coef[i] = newNum.coef[j+i];
        }

        if(u < (BASE)(q) * div_sor){
            q--;
        }

        u = u - (BASE)(q) * div_sor;
        res.coef[j] = (BASE)(q);
        
        for(int i = 0; i < div_sor.len + 1; i++){
            newNum.coef[j+i] = u.coef[i];
        }

        j--;
    }

    while(res.len>1 && res.coef[res.len-1]==0){
        res.len--;
    }

    return res;
}

BN BN::operator % (const BN& num){

    if(num.len == 1 && num.coef[0] == 0){
        cout << "Error!";
        exit(0);
    }
    
    if(*this < num){
        return *this;
    }

    if(num.len == 1){
        return *this % num.coef[0];
    }

    int m = len-num.len;
    int base_size = BASE_SIZE;
    DBASE b = ((DBASE)(1)<<( base_size));
    BASE d = (BASE)((DBASE)( b ) / (DBASE)((num.coef[num.len-1]) + (BASE)(1)));
    int j = m;
    int k = 0;

    BN newNum = *this;
    newNum *= d; 
    BN div_sor = num;
    div_sor *= d;
    if(newNum.len == len){
        newNum.maxlen++;
        newNum.len = maxlen;
        newNum.coef = new BASE[maxlen];
        for (int i = 0; i <  len; i++){
            newNum.coef[i] = coef[i];
        }
        newNum *= d;
        newNum.len++;
        newNum.coef[newNum.len-1] = 0;
    }
    
    while (j>-1){
        DBASE q = (DBASE)((DBASE)((DBASE)((DBASE)(newNum.coef[j + div_sor.len]) * (DBASE)(b)) + (DBASE)(newNum.coef[j + div_sor.len - 1] )) / (DBASE)(div_sor.coef[div_sor.len - 1] ));
        DBASE r = (DBASE)((DBASE)((DBASE)((DBASE)(newNum.coef[j + div_sor.len]) * (DBASE)(b)) + (DBASE)(newNum.coef[j + div_sor.len - 1] )) % (DBASE)(div_sor.coef[div_sor.len - 1] ));
        if(q == b || (DBASE)((DBASE)(q) * (DBASE)( div_sor.coef[div_sor.len-2] )) > (DBASE)((DBASE)((DBASE)(b) * (DBASE)(r)) + (DBASE)( newNum.coef[j+div_sor.len-2] ))){
            q--;
            r = (DBASE)(r) + (DBASE)(div_sor.coef[div_sor.len - 1]);
            if((DBASE)(r)<b){
                if(q == b || (DBASE)((DBASE)(q) * (DBASE)( div_sor.coef[div_sor.len-2])) > (DBASE)((DBASE)((DBASE)(b) * (DBASE)(r)) + (DBASE)( newNum.coef[j+div_sor.len-2] ))){
                    q--;
                }
            }
        }
        BN u(div_sor.len + 1);
        u.len = div_sor.len + 1;
        for(int i = 0; i < div_sor.len + 1; i++){
            u.coef[i] = newNum.coef[j+i];
        }

        if(u < (BASE)(q) * div_sor){

            q--;
        }

        u = u - ((BASE)(q) * div_sor);

        
        for(int i = 0; i < div_sor.len + 1; i++){
            newNum.coef[j+i] = u.coef[i];
        }

        
        j--;
    }
    while(newNum.len>1 && newNum.coef[newNum.len-1]==0){
        newNum.len--;
    }
    
    return newNum / d;
}

void BN::cout_b10(){
    
    BN newNun = *this;
    BN zero(newNun.len);
    string s;
    zero.len = newNun.len;
    while (newNun != zero)
    {
        int t = newNun%10;
        s.push_back(t + '0');

        newNun = newNun/10;
        zero.len = newNun.len;
    }
    reverse(s.begin(),s.end());
    cout<<s<<endl;
}

void BN::cin_b10(){
    int j = 0;
    string s;
    cout<<"Base10: ";
    getline(cin, s);
    int k = s.length();
    BASE t = 0;
    DBASE tmp = 0;

    int b = BASE_SIZE;
    
    BN big_n((k - 1)/(b/4)+1);
    
    while (j<k){
        if('0' > s[j] || s[j] > '9'){
            cout << "Error!";
            exit(0);
        }
        
        t = s[j] - '0';
        big_n = big_n*((BASE)10);
    
        BN newNum;
        newNum.coef[0] = (BASE)t;
        big_n+=newNum;
        j++;

    }

    big_n.len = big_n.maxlen;
    while(big_n.len>1 && big_n.coef[big_n.len-1]==0){
        big_n.len--;
    }
    *this = big_n;


}

int main(void){
    
    /*BN bn1(3, 1);
    BN bn2(2, 1);
    BN a, bn3, bn4, bn5, bn6;

    cout << "bn1 = " << bn1 << endl;
    cout << "bn2 = " << bn2 << endl;

    bn3 = bn1 + bn2;
    cout << "bn3 = bn1 + bn2 = " << bn3 << endl;

    bn4 = bn1 - bn2;
    cout << "bn4 = bn1 - bn2 = " << bn4 << endl;

    bn5 = bn1 * bn2;
    cout << "bn5 = bn1 * bn2 = " << bn5 << endl;

    cout << "Enter a: " << endl;
    std::cin >> a;
    cout << "a = " << a << endl;*/

    /*int n;
    cout << "Enter A n Value...";
    cin >> n;
    std::cout << n <<" in hex = ";
    std::cout << std::hex << n <<endl;*/

    /*if(bn1 == bn2){
        cout << "bn1 == bn2" << endl;
    }
    else cout << "bn1 != bn2" <<endl;

    if(bn1 > bn2){
        cout << "bn1 > bn2" << endl;
    }
    else if (bn1 < bn2) {
        cout << "bn1 < bn2" <<endl;
    }
    else if(bn1 == bn2){
        cout << "bn1 == bn2" <<endl;
    }
//
    if(bn3 > bn2){
        cout << "bn3 > bn2" << endl;
    }
    else if(bn3 < bn2){
        cout << "bn3 < bn2" <<endl;
    }
    else if(bn3 == bn2){
        cout << "bn3 == bn2" <<endl;
    }
//
    if(bn4 > bn2){
        cout << "bn4 > bn2" << endl;
    }
    else if(bn4 < bn2){
        cout << "bn4 < bn2" <<endl;
    }
    else if(bn4 == bn2){
        cout << "bn4 == bn2" <<endl;
    }
//
    if(bn5 > bn2){
        cout << "bn5 > bn2" << endl;
    }
    else if(bn5 < bn2){
        cout << "bn5 < bn2" <<endl;
    }
    else if(bn5 == bn2){
        cout << "bn5 == bn2" <<endl;
    }
    cout << "///////////////////" << endl;
//
//
    cout << "BASE 10: " << endl;
    cout << " " << endl;

    BN z(5, 1);
    cout << "Enter a number in b10: " << endl;
    z.cout_b10();
    z.cin_b10();
    z.cout_b10();
    cout << "////////////////////////////////////////" << endl;

    BN bn8, bn9, b, c, d, e, g;
    cout << "Enter A number A In Base 10: " << endl;
    bn8.cin_b10();
    cout << "Number A In Base 10 = ";
    bn8.cout_b10();
    cout << endl;

    cout << "Enter A Number B In Base 10: " << endl;
    bn9.cin_b10();
    cout << "Number B In Base 10 = ";
    bn9.cout_b10();
    cout << endl;*/
    
    /*int v;
    cout << "Enter divisor: ";
    cin >> v;*/

    /*b = bn8 + bn9;
    c = bn8 - bn9;
    d = bn8 * bn9;
    e = bn8 / bn9;
    g = bn8 % bn9;

    cout << "A + B = ";
    b.cout_b10();
    cout << endl;

    cout << "A - B = ";
    if (bn9 > bn8){cout <<"Unsigned Subtraction Impossible! B > A"<< endl;}
    else if (bn9 < bn8){c.cout_b10();}
    cout << endl;

    cout << "A * B = ";
    d.cout_b10();
    cout << endl;
    
    cout << "A / B = ";
    if (bn9 != 0){e.cout_b10();}
    cout << endl;
    
    cout << "A mod B = ";
    if (bn9 != 0){g.cout_b10();}
    cout << endl;*/
    
    cout << "TEST: " << endl;
    /*for test, take two numbers, make a cycle 1000 times
    m = 1000;
    t = 1000;
    do {
        n = rand()%M+1;
        m = rand()%m +1;
    //}
    a = random numbers of size n
    b = random numbers of size m
    
    c = a/b (the whole number part)
    d = a%b (the remainder)
    }
    while (a== c*b+d && a-d == c*b && d < b && --t)
    these three conditions must be fulfilled.*/
    
    BN bna, bnb, bnc, bnd, bne, bnf, bng;
    srand(time(0));
    int w = 1000;
    int x = 1000;

    do{
        int n = rand()%w + 1;
        int m = rand()%w + 1;
        BN bne(n, 1); 
        BN bnf(m, 1);
        cout << "x;n;m: " << x << " " << n << " " << m << endl; 
        bna = bne;
        bnb = bnf;
        bnc = bna / bnb;
        bnd = bna % bnb;
    }
    while (bna == bnc * bnb + bnd && bna - bnd == bnc*bnb && bnd<bnb && --x);
    cout << x << endl;
    
    return 0;
}



