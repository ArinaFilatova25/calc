#include <iostream>
#include <locale.h>
#include <cstring>
#include <cstdlib>

using namespace std;

template <typename T>
struct list
{
    T id;
    list*next;
};
list<char>*Y=NULL;
list<double>*X=NULL;

template <typename T>
void push(list<T> *& head, T x)
{

    list<T>*tmp=new(list<T>);
    tmp->id=x;
    tmp->next=head;
    head=tmp;
}

template < typename T >
void print(list<T>* ptr)
{
    while(ptr)
    {
        cout<<ptr->id<<" ->";
        ptr=ptr->next;
    }
}

template <typename T>
T pop(list<T> *& head)
{
    list<T> * tmp = head;
    T val=tmp->id;
    head= head->next;
    delete(tmp);
    return val;
}

template < typename T >
T top(list<T>* head)
{
    list<T> * tmp = head;
    T val=tmp->id;
    head= head->next;
    return val;
}

double OP(char c)
{
    double a=pop(X);
    double b=pop(X);
    if(c=='-')
        return b-a;
    else if(c=='+')
        return b+a;
    else if(c=='*')
        return b*a;
    else if(c=='/' )
    {
        if(a!=0)  //??
            return b/a;
        else
            cout<<"На ноль делить нельзя!";
        exit(0); //
    }

}
int Prior(char x)
{
    switch(x)
    {
    case '*':
    case '/':
        return 3;
    case '+':
    case'-':
        return 2;
    case '(':
        return 1;
    case '=':
        return 0;
    }


}

int main ()
{
    setlocale(LC_ALL, "Rus");
    char ent_exp[100]="7+((6+2)/(1+1)-3)*(9+(2+5)*2)=", OPN_mas[100]="";
    int k=0, sl=strlen(ent_exp);
    cout <<"Введите выражение для вычисления:";
    //    cin>> ent_exp;


    while(k<=sl)

    {
        if (ent_exp[0]=='-')
        {
            OPN_mas[0]='-';
            k++;
        }

        if(ent_exp[k]>='0' && ent_exp[k]<='9')
        {

            int kol=k;
            while (ent_exp[kol]>='0' && ent_exp[kol]<='9')
                kol++;

            if (ent_exp[kol]==',')
                kol++;

            while (ent_exp[kol]>='0' && ent_exp[kol]<='9')
                kol++;

            if (ent_exp[kol]=='e')
                kol+=4;
            //cout<<kol<<ent_exp[kol]<<"------------------------------------"<<endl;
            char num[100]="";
            //int p = strlen(num);

            for (int i=k; i<kol; i++)
            {
                num[i-k] = ent_exp[i];

            }
            num[kol-k+1] = '\0';
            double dob=atof(num);
            //cout<<dob<<endl;
            push(X,dob);
            strcat(OPN_mas, num);
            strcat(OPN_mas, " ");
            k=kol-1;
        }
        //cout<<OPN_mas<<"_______________"<<endl;


        if(ent_exp[k]=='(')
        {
            push(Y,ent_exp[k]);
            if( ent_exp[k+1]=='-')
            {
                push(X,ent_exp[k+1]);
                k++;
            }
        }

        if(ent_exp[k]==')')
        {
            char c=pop(Y);
            while(c!='(')
            {

                int h_1 = strlen(OPN_mas);
                OPN_mas[h_1]=c;
                OPN_mas[h_1 + 1] = '\0';
                strcat(OPN_mas, " ");
                push(X, OP(c));
                c=pop(Y);
            }

        }

        if(ent_exp[k]=='+'|| ent_exp[k]=='*'|| ent_exp[k]=='-'||  ent_exp[k]=='=' || ent_exp[k]=='/')
        {
            while( Y!=NULL && Prior(top(Y))>=Prior(ent_exp[k]))
            {

                int h_2 = strlen(OPN_mas);
                OPN_mas[h_2]=top(Y);
                OPN_mas[h_2 + 1] = '\0';
                strcat(OPN_mas, " ");
                push(X,OP(pop(Y)));
            }
            push(Y,ent_exp[k]);

        }
        k++;
    }
    cout<<X->id<<endl;
    //cout<<"_______________________"<<endl;
    cout<<OPN_mas<<endl;
    return 0;
}
