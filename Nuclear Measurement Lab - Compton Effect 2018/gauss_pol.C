
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLine.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TStyle.h"
#include "TObjArray.h" 
#include "TRandom.h"
#include <stdlib.h>
  
 int main () {

// root -l
// .L gauss_pol.C
// main()
 
  gROOT->Reset();
  gStyle->SetOptStat(111111111);
  gStyle->SetOptFit(111111);

  char riga[256];
  float y;
  float passox=1.;
  float  x=-passox/2.;
  Double_t par[12],errpar[12];  
  int tempovivo,tempo;
  
  int Nch=8000;
  float inig1=3600.;
  float endg1=4000.;
  float inip=3200;
  float endp=4100;

  for (int i=0; i<10; i++){ 
    par[i]=0;
    errpar[i]=0;
  }

// lettura file e creazione istrogramma

  ifstream ff;
  ff.open("finale60gradi.Spe",fstream::in);
  if (!ff.is_open())  {
   cout << " file non trovato" << endl;
   return 0;
  }

   TH1F *gg = new TH1F("gg", " spettro", Nch, 0.,Nch);

  for (int ii=0; ii<9; ii++) {
    ff.getline(riga,256);
    cout << riga << endl;
  }
  ff >> tempovivo >> tempo;
  cout << "tempovivo(s)= " << tempovivo << ", tempo(s)= "<< tempo << endl; 
  for (int ii=0; ii<3; ii++) {
    ff.getline(riga,256);
    cout << riga << endl;
  }  

  for (int ii=0; ii<Nch; ii++) {
     x+=passox;
     ff >> y;
     gg->Fill(x,y);
   }
   gg->Draw();

   ff.close();


// fit gaus+polinomio 

  TF1 *g1 = new TF1("g1", "gaus", inig1, endg1);
  TF1 *pp = new TF1("pp", "pol1", inip, endp);

  TF1 *total = new TF1("total","gaus(0)+pol1(3)",inip,endp);

// fit con solo gauss per ottenere parametri iniziali
  gg->Fit(g1,"R");
  g1->GetParameters(&par[0]);
  cout << " solo gaus: h=" << par[0] << " mean= " << par[1] << " sig= " << par[2] << endl;
	cout << "area solo gauss = " <<par[0]*par[2]*2.507<< " +/-" << 2.507*pow(pow((par[2]*errpar[0]),2.)+pow((par[0]*errpar[2]),2.),0.5);
  total->SetParameters(par);
  total->SetLineColor(6);
  
  gg->Fit(total,"R+","",inip,endp);

  total->GetParameters(&par[0]);
  errpar[0]=total->GetParError(0);
  errpar[2]=total->GetParError(2);

  cout << " risultati fit globale" << endl;
  cout << " Chi2= " << total->GetChisquare() << " NDF= "<< total->GetNDF() << 
  " prob=" <<  total->GetProb() << endl;
  cout << " Chi2rid= " << total->GetChisquare() / total->GetNDF() << endl;
  cout << " gauss parameters:" << " " << par[0] << " " << par[1] << " " << par[2] << endl;
  cout << " errpar[0]="<< errpar[0] << "   errpar[2]="<< errpar[2] <<endl;
  cout << " sig/mean g1= " << par[2]/par[1] << endl;
  cout << " mean g1= " << par[1]<< endl;
  cout << " sigma g1= " << par[2]<< endl;
	float area_gauss=par[0]*par[2]*2.507;
  double arg=pow((par[2]*errpar[0]),2.)+pow((par[0]*errpar[2]),2.);
  float err_area_gauss=2.507*pow(arg,0.5);
  cout << " area gauss1= " << area_gauss << " +/-" << err_area_gauss << endl;

  gg->Draw("HIST");

// per disegnare le curve parziali
	total->SetLineColor(2);
	total->Draw("same");
  g1->SetParameters(&par[0]);
  g1->SetLineColor(3);
  g1->Draw("same");
  pp->SetParameters(&par[3]);
  pp->SetLineColor(5);
  pp->Draw("same");


	cout << endl << "Integral = " << gg->Integral(inig1, endg1) << endl;
	cout << "fondo = " 	<< gg->Integral(3850,4350) << endl;
	cout << "finale = " << gg->Integral(3300, 3850) - gg->Integral(3850,4400) << endl << endl;
	
	double integral[8];
	double error[8];
	cout << " da	a	integral	fondo	sol" << endl;
	for(int ii=1; ii<9; ii++){
		integral[ii] = gg->Integral(3300-ii*10, 3850+ii*10);
		error[ii] = gg->Integral(4000, 4550+ii*20);
		cout <<3300-ii*10<< "	"<< 3850+ii*10<<"	"<<integral[ii]<<"		"<<error[ii]<<"	"<<integral[ii]-error[ii]<<endl;
	}
return 0;

}

