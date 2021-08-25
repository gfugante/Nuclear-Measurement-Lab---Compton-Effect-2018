// coeff Compton
#include <iostream>
#include <cmath>
using namespace std;

// Variabili globali

double PI=3.14159265;


 int main(){

  double kk=0.;
  double lamda,lamda2,dd,therad;
  double rho,zeta,anucl;
  double lamda1[5]={6.,5.,4.,3.,2.3}; //g/cm2
  double theta[5]= {20.,30.,45.,60.,75.};
	double re=2.8179e-13; // raggio classico dell'elettrone (cm)
  double mele=511.; // massa elettrone in keV
  double Ene=511.,Enetheta=511.;
	double dsdoth=0;
  
  rho=11.36; //  g/cm3
  dd=0.28; // cm
  zeta=82;
  anucl=207; // g/cm3
  lamda=6; // lamda per E=511 keV in g/cm2
  
  for (int ii=0; ii<5; ii++) {
    lamda2=lamda*lamda1[ii]/(lamda1[ii]-lamda);
    therad=theta[ii]*PI/180.;
		
		kk=(lamda2/rho)*exp(-dd*rho/(cos(therad/2.)*lamda1[ii]))*(1.-exp(-dd*rho/(cos(therad/2.)*lamda2)));
    cout << " theta= " <<  theta[ii] << " l1= " << lamda1[ii] << " la2= " << lamda2 << " k= " << kk <<
    endl;
  }
	 
// sezione d'urto teorica
	 
	 cout << endl << " valori teorici con E=511 keV" << endl << endl;
	 for (int ka=0; ka<5; ka++){
		 therad=theta[ka]*PI/180.;
		 Enetheta=Ene*mele/(Ene*(1.-cos(therad))+mele);
		 dsdoth=(re*re/2.)*((Enetheta/Ene)*(Enetheta/Ene))*((Ene/Enetheta)+(Enetheta/Ene)-sin(therad)*sin(therad));
		 cout << "theta " << theta[ka] << "  E'(keV) " << Enetheta << "  ds/Domega " << dsdoth << " (cm2) " << endl;
	 }
		 
// sezione d'urto dai dati sperimentali (vedi articolo)
     double te=15.;
     double att=188080.; // attivita' sorgente (Bq)
     double effA=0.207193111;
     double effB=0.204688262;
     double DomegaA=0.01637662;
     double DomegaB=0.00708822;
     double eventi=2143.607595/443128.; // eventi/sec
     double Nav=6.022e23;// moli-1
     double kk15=0.159;
    
     double nn=2.*att*effA*DomegaA/(4.*PI);
     double Nmat=rho*Nav*zeta/anucl;
     double dsdo=eventi/(nn*Nmat*DomegaB*effB*kk15);
     
     cout << " " << endl;
     cout << " sezione d'urto come da esempio" << endl;
     cout << " eventi=      " << eventi << " s^-1" << endl;
     cout << " nn =         " << nn << endl;
     cout << " N=           " << Nmat << endl;
     cout << " Ds/Domega(15)= " << dsdo << " cm2" << endl;
return 0;
  
}
