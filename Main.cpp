#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>

using namespace std;

//Clase Principal
class Quine
{
public:

int VARIABLES;
string indif;

Quine(int a)
{
   VARIABLES=a;
   indif.append(a,'-');

}

// Paso 1: Convertir los miniterminos en booleanos 
vector<string> getVariables()
{
   vector<string> v;
   string letras[]={"a","b","c","d","e","f","g","h"};
   for(int i=0;i<this->VARIABLES;i++)
    v.push_back(letras[i]);

   return v;
}

// Paso 2: Convierte los miniterminos a binarios

string deciABin(int n)
{
   if ( n == 0 )
       return n+"";

   if ( n % 2 == 0 )
       return deciABin(n / 2) + "0";
   else
       return deciABin(n / 2) + "1";
}

//Función para rellenar ceros con el equivalente binario de dígitos.
string rellenar(string binario)
{
   int max=VARIABLES-binario.length();
   for(int i=0; i<max; i++)
       binario="0"+binario;
   return binario;
}

//función para verificar si dos términos difieren en solo un bit
bool codigoGrey(string a,string b)
{
   int flag=0;
   for(int i=0;i<a.length();i++)
   {
       if(a[i]!=b[i])
        flag++;
   }
   return (flag==1);
}

//Función para reemplazar términos complementarios con indiferentes
string reemplazar_complementarios(string a,string b)
{
   string temp="";
   for(int i=0;i<a.length();i++)
   if(a[i]!=b[i])
       temp=temp+"-";
   else
       temp=temp+a[i];

   return temp;
}

//Función que verifica si el string b existe en el vector a
bool en_vector(vector<string> a,string b)
{
   for(int i=0;i<a.size();i++)
     if(a[i].compare(b)==0)
      return true;
    return false;
}

//Función para reducir miniterminos 
vector<string> reduce(vector<string> miniterminos)
{
/*for (int i=0; i<miniterminos.size(); i++)
       cout << miniterminos[i]<<endl;
       cout <<endl;*/

      vector<string> newMiniterminos;

      int max=miniterminos.size();
      int* comprobado = new int[max];
      for(int i=0;i<max;i++)
      {
          for(int j=i;j<max;j++)
          {
               //If a grey code pair is found, replace the differing bits with don't cares.
               if(codigoGrey(miniterminos[i],miniterminos[j]))
               {
                  comprobado[i]=1;
                  comprobado[j]=1;
                  if(!en_vector(newMiniterminos,reemplazar_complementarios(miniterminos[i],miniterminos[j])))
                     newMiniterminos.push_back(reemplazar_complementarios(miniterminos[i],miniterminos[j]));
               }
          }
      }

      //agregar todos los términos reducidos a un nuevo vector
      for(int i=0;i<max;i++)
      {
          //cout<<comprobado[i]<<endl;
          if(comprobado[i]!=1 && ! en_vector(newMiniterminos,miniterminos[i]))
           newMiniterminos.push_back(miniterminos[i]);
      }

       delete[] comprobado;
   
       return newMiniterminos;
}


//Convertir el minitérmino booleano en las variables
string getValor(string a)
{
   string temp="";
   vector<string> variables=this->getVariables();
   if(a==indif)
     return "1";

   for(int i=0;i<a.length();i++)
   {
     if(a[i]!='-')
     {
        if(a[i]=='0')
         temp=temp+variables[i]+"\'";
        else
         temp=temp+variables[i];
     }
   }
   return temp;
}

//función para comprobar si 2 vectores son iguales
bool VectoresIguales(vector<string> a,vector<string> b)
{
   if(a.size()!=b.size())
      return false;

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    for(int i=0;i<a.size();i++)
    {
        if(a[i]!=b[i])
        return false;
    }
    return true;
}

};

//Interfaz
int main ()
{
   char comprobado='y';
   while(comprobado=='y')
   {
      int numero;
      cout<<endl<<"Ingrese el numero de variables que quisiera introducir:"<<endl;
      cin>>numero;
      if(numero > 8 || numero < 1)
      {
          cout << "Invalido! Ingrese un numero de variables entre 1-8" << endl;
          continue;
      }
      Quine q(numero);

      string temp="";
      cout<<" Ingrese los miniterminos (RANGE = 0-"<<pow(2,numero)-1<<") separados por una coma:"<<endl;
      cin>>temp;

      //Division de la entrada
      vector<string> miniterminos;
      istringstream f(temp);
      string s;
      while (getLinea(f, s, ','))
      {
          //cout << s << endl;
         int t=atoi(s.data());
         miniterminos.push_back(q.rellenar(q.deciABin(t)));
      }

      sort(miniterminos.begin(),miniterminos.end());

      do
      {
         miniterminos=q.reduce(miniterminos);
         sort(miniterminos.begin(),miniterminos.end());
      }while(!q.VectoresIguales(miniterminos,q.reduce(miniterminos)));


      int i;
      cout << "La ecuacion booleana reducida:" << endl;
      for (i=0;i<miniterminos.size()-1; i++)
          cout <<q.getValor(miniterminos[i])<<"+";
      cout<<q.getValor(miniterminos[i])<<endl;

      cout<<"Le gustaria ingresar otra expresion?"<<endl;
      cin>>comprobado;
   }
   cout<<endl<<"---FIN--"<<endl;
   
}