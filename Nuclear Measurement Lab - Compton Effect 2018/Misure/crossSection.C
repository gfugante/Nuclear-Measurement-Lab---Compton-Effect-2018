#include <iostream>
#include <cmath>

double pi=3.14159265;

using namespace std;

int main(){

	double kk=0.;
  double lamda,lamda2,dd,therad;
  double rho,zeta,anucl;
  double lamda1[5]={6.,5.,4.,3.,2.3}; //g/cm2
  double theta[5]= {15.,30.,45.,60.,75.};
	double re=2.8179e-13; // raggio classico dell'elettrone (cm)
  double mele=511.; // massa elettrone in keV
  double Ene=511.,Enetheta=511.;
	double dsdoth=0;
	
	
	
	rho=11.36; //  g/cm3
  dd=0.28; // cm
  zeta=82;
  anucl=207; // g/cm3
  lamda=6.; // lamda per E=511 keV in g/cm2
	
	
	// sezione d'urto teorica
	cout << endl;
	cout << "--------------------------------------------" << endl << endl;
	cout << "Sezione d'urto teorica (E=511keV)" << endl << endl;
	cout << "theta			lambda1			lambda2			k" << endl;
	for (int ii=0; ii<5; ii++) {
		lamda2=lamda*lamda1[ii]/(lamda1[ii]-lamda);
    therad=theta[ii]*pi/180.;
   
		kk=(lamda2/rho)*exp(-dd*rho/(cos(therad/2.)*lamda1[ii]))*(1.-exp(-dd*rho/(cos(therad/2.)*lamda2)));
    cout <<  theta[ii] << "			" << lamda1[ii] << "			" << lamda2 << "			" << kk << endl;
  }
	cout << endl;
	
	/*
	cout << "theta			E'(keV)			ds/domega(cm2)" << endl;
	for (int ka=0; ka<5; ka++){
		 therad=theta[ka]*pi/180.;
		 Enetheta=Ene*mele/(Ene*(1.-cos(therad))+mele);
		 dsdoth=(re*re/2.)*((Enetheta/Ene)*(Enetheta/Ene))*((Ene/Enetheta)+(Enetheta/Ene)-sin(therad)*sin(therad));
		 cout << theta[ka] << "			" << Enetheta << "			" << dsdoth << endl;
	 }
	
	cout << endl;
	cout << "--------------------------------------------" << endl << endl;

// sezione d'urto dai dati sperimentali (vedi articolo)
	
	double att=15540.; // attivita' sorgente (Bq) (VEDI QUADERNO!)
	double effA=0.207193111;
	double effB=0.204688262;
  double DomegaA=0.01637662;
  double DomegaB=0.00708822;

	double te=443128.;
	double integrale = 2143.60759544;
	double eventi = 0.002; // eventi/sec
	
	double Nav=6.022e23;// moli-1
  double kk15=0.165;
	// teta 	K
	// 0 			0.165
	// 15			0.165
	// 30			0.159
	// 45			0.149
	// 60			0.131
	// 75			0.111
    
  double nn=2.*att*effA*DomegaA/(4.*pi);
  double Nmat=rho*Nav*zeta/anucl;
  double dsdo=eventi/(nn*Nmat*DomegaB*effB*kk15);
	
	cout << "Sezione d'urto sperimentale" << endl << endl;
	cout << " eventi =      " << eventi << " s^-1" << endl;
	cout << " nn =         " << nn << endl;
  cout << " N =           " << Nmat << endl;
  cout << " Ds/Domega(15)(cm2) = " << dsdo << endl;
	
	cout << endl;
	cout << "--------------------------------------------" << endl << endl;
*/
	return 0;
}



