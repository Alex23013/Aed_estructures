#include <iostream>
using namespace std;
#include "csparsa.h"
#include "calc.h"
int main()
{
    ///m(3,3);
    ///m(3,3)=8;
    ///a=m(3,3);

    cout<<" --- S.P.A.R.S.A. Matrix ---\n";
   // Csparsa<char,4,6,64> The;
 Csparsa<int ,4,6,0> The;

    cout<<"\nMatriz A \n";
    The.print_matrix_x();//matrix vacia

    for(int i =0;i<4;i++){
        for(int j=0;j<6;j++){
            The.insertar(i,j,i+1);
        }
    }

    The.insertar(0,0,0);
    The.print_matrix_x();

    cout<<"THE[2][2]    : "<<The(2,2)<<endl;//it WORKS
    int gg;
    gg =The(2,2);//it WORKS
    cout<<"THE[2][2] +2 : "<<gg+2;
    gg =The(2,8);//it WORKS
    cout<<"\nTHE[2][8]    :"<<gg<<" out of range\n";
    cout<<"THE[2][2]    : "<<The(2,2)<<endl;//it WORKS


    for(int i=0;i<4;i++){
        The.eliminar(i,3);}
    cout<<"\n";
    The.print_matrix_x();cout<<"\n";
    cout<<"\n y la traspuesta; xD\n";
    The.print_matrix_y();//la traspuesta

        The.insertar(1,3,'+');
        The.print_matrix_x();cout<<"\n";

The(2,2)=8;
The(2,4)=6;
The(0,1)=The(2,2);
The.print_matrix_x();
cout<<"\n finite \n";
/*
print_matriz(The,"The");
Csparsa<int,4,6,-1> B;
print_matriz(B,"B");
sumar(The,B);
restar(The,B);
cout<<"THE END =P"<<endl;
  */  return 1;
}
