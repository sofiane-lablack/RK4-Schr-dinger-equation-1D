#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;


/*RK4 Schrödinger equation 1D, psi la fonction d'onde et phi sa dérivée*/
/*Potentiel constant*/


double f( double i , double psi , double phi ) {return phi;}
double g( double i , double psi , double phi , double E , double m ,double hbar , double V ) {return (2*m*(V-E)*psi)/(hbar*hbar);}
double e( double k , double i , double B ) {return (cos(k*i))*(B+1) ;} //psi1 Partie Réelle avant barrière
double v( double k , double i , double B ) {return (sin (k*i))*(B-1) ;} // psi2 Partie imaginaire avant la barrière
double q( double k , double i , double C , double D ) {return C*cos(k*i) + D*cos(k*i) ;} // psi3 Partie réelle avant la barrière
double w( double k , double i , double C , double D ) {return C*sin(k*i) - D*sin(k*i) ;} // psi4 Partie imaginaire après la barrière

int main()

{
ofstream fichierdata;

fichierdata.open("Schrödinger_equation_data.txt");

double i=0; int n=10; double h=1; double psi=1 ; double phi=0; double k1,k2,k3,k4,l1,l2,l3,l4; double hbar = 6.62e-34/(2*3.1415); double E = 1.6e-19 ; double m = 9.1e-31 ; double V; double B; double C; double D; double psi1 ; double psi2; double psi3; double psi4; double k = sqrt(2*m*(V-E));



for (i=0;i<=n;i++)
{
fichierdata<< i << " " << psi << " " << phi << " " << psi1 << " " << psi2 << " " << psi3 << " " << psi4 << endl;

if (i<10)
{V=0;}
else if (i>=10 && i<=20)
{V=2;}
else if (i>20)	
{V=0;}


//Avant barrière

psi1 = e(k,i,B);
psi2 = v(k,i,B);

// Rk4 Dans la barrière
k1 = f(i,psi,phi);
k2 = f(i+h/2,psi+(h*k1)/2,phi+(h*l1)/2);
k3 = f(i+h/2,psi+(h*k2)/2,phi+(h*l2)/2);
k4 = f(i+h,psi+h*k3,phi+h*l3);
l1 = g(i,psi,phi,E,m,hbar,V);
l2 = g(i+h/2,psi+(h*k1)/2,phi+(h*l1)/2,E,m,hbar,V);
l3 = g(i+h/2,psi+(h*k2)/2,phi+(h*l2)/2,E,m,hbar,V);
l4 = g(i+h,psi+h*k3,phi+h*l3,E,m,hbar,V);


psi = psi+h*(k1+2*k2+2*k3+k4)/6;
phi = phi+h*(l1+2*l2+2*l3+l4)/6;

// Après la barrière

psi3 = q(k,i,C,D);
psi4 = w(k,i,C,D);

}

fichierdata.close();

return 0;
}
