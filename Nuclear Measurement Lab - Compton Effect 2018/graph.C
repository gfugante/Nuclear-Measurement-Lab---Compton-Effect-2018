
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
  float inig1=4000.;
  float endg1=5000.;
  float inip=inig1;
  float endp=endg1;

  for (int i=0; i<10; i++){ 
    par[i]=0;
    errpar[i]=0;
  }

// lettura file e creazione istrogramma

  ifstream ff;
  ff.open("notaghetta_finale4maggio.Spe",fstream::in);
  if (!ff.is_open())  {
   cout << " file non trovato" << endl;
   return 0;
  }

   TH1F *gg = new TH1F("gg", " spettro", Nch, 0.,Nch);
	 TGraph *gg2 = new TGraph(Nch);
	 
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
		 //if(y>=1.){
	     gg2->SetPoint(ii,x,y);
		 //}else{
		 	 //gg2->SetPoint(ii,x, 1);
		 //}
		 gg->Fill(x,y);
   }
	 ff.close();

		TCanvas *c1 = new TCanvas("c1");
	c1->cd();
		
	
  ff.open("finale.Spe",fstream::in);
  if (!ff.is_open())  {
   cout << " file non trovato" << endl;
   return 0;
  }

   TH1F *gg0 = new TH1F("gg0", " spettro0", Nch, 0.,Nch);
	 TGraph *gg20 = new TGraph(Nch);
	 
  for (int ii=0; ii<9; ii++) {
    ff.getline(riga,256);
    cout << riga << endl;
  }
	double tempovivo0;
  ff >> tempovivo0 >> tempo;
  cout << "tempovivo(s)= " << tempovivo0 << ", tempo(s)= "<< tempo << endl;
  for (int ii=0; ii<3; ii++) {
    ff.getline(riga,256);
    cout << riga << endl;
  }  
	
	x=-passox/2.;
	
  for (int ii=0; ii<Nch; ii++) {
     x+=passox;
     ff >> y;
		 //if(y>=1.){
	     gg20->SetPoint(ii,x,y*tempovivo*0.001/tempovivo0);
		 //}else{
		 	 //gg2->SetPoint(ii,x, 1);
		 //}
		 gg0->Fill(x,y);
   }
	 ff.close();

	TGraph *ggf = new TGraph(Nch);
	x=-passox/2.;
	
  for (int ii=0; ii<Nch; ii++) {
		x+=passox;
		y = gg2->Eval(x) - gg20->Eval(x);
		if(y<0) y=0;
		ggf->SetPoint(ii,x,y);
		
		gg0->Fill(x,y);
   }


	//TCanvas *c2 = new TCanvas("c2");
	//c2->cd();
	 //gg2->SetLineColorAlpha(7, 1.);
	 //gg20->SetMarkerColor(2);
	  //gg20->SetLineColor(2);
	 //gg20->Draw();
	 
	 
	 gg2->Draw();
	 gg20->SetLineColor(2);
	 gg20->SetMarkerColor(2);
	 gg20->Draw("same");
	 //ggf->SetLineColor(3);
	 //ggf->SetMarkerColor(3);
	 ggf->Draw();

	 //gg->Smooth();
	 //gg->SetLineColorAlpha(4, 0.);
	 //gg->Draw("samehist");
	 
	 

// fit gaus+polinomio 

  TF1 *g1 = new TF1("g1", "gaus", inig1, endg1);
  TF1 *pp = new TF1("pp", "pol1", inip, endp);

  TF1 *total = new TF1("total","gaus(0)+pol1(3)",inip,endp);

// fit con solo gauss per ottenere parametri iniziali
  ggf->Fit(g1,"R");
  g1->GetParameters(&par[0]);
  cout << " solo gaus: h=" << par[0] << " mean= " << par[1] << " sig= " << par[2] << endl;
	cout << "area solo gauss = " <<par[0]*par[2]*2.507<< " +/-" << 2.507*pow(pow((par[2]*errpar[0]),2.)+pow((par[0]*errpar[2]),2.),0.5);
  total->SetParameters(par);
  total->SetLineColor(6);
  
  ggf->Fit(total,"R+","",inip,endp);

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

  //gg->Draw("HIST");

// per disegnare le curve parziali
	total->SetLineColor(2);
	total->Draw("same");
  g1->SetParameters(&par[0]);
  g1->SetLineColor(3);
  g1->Draw("same");
  pp->SetParameters(&par[3]);
  pp->SetLineColor(5);
  pp->Draw("same");

	
return 0;

}

