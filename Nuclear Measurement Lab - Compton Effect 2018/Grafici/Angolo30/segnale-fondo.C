
#include <iostream>
#include <fstream>
#include <string>

int main(){

	gROOT->Reset();
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);



//****** attenti alla normalizzazione del Potassio: ridefinizione di passox*/
// **** normalizzazione ai tempi di presa dati


  float tempofondo;
  float tempomis,tempo;
  float wtempo;
  int Nch=8000;
  float Ch=8000.;
  char riga[256];

  double binContent1[Nch];
  double binContent2[Nch];
  double par[7],errpar[7];
	
  float x=-0.5, y,yp;
  float passox=1.;

  TH1F *hh  = new TH1F("hh ", " spettro dati ", Nch, 0.,Nch);
  TH1F *hhf = new TH1F("hhf", " fondo        ", Nch, 0.,Nch);
  TH1F *gg  = new TH1F("gg ", " spettro-fondo", Nch, 0.,Nch);
	TGraph *hh2 = new TGraph(Nch);
	TGraph *hhf2 = new TGraph(Nch);
	TGraph *gg2 = new TGraph(Nch);

  for (int ii=0; ii<7; ii++) {
     par[ii]=0.;
     errpar[ii]=0;
  }

  TCanvas *c1 = new TCanvas("c1");

// lettura file e creazione istrogramma

  ifstream ff;
  ff.open("finale.Spe",fstream::in);
  if (!ff.is_open())  {
   cout << " file non trovato" << endl;
   return 0;
  }

  for (int ii=0; ii<9; ii++) {
    ff.getline(riga,256);
  }
  ff >> tempomis >> tempo;
  cout << "tempomis(s)= " << tempomis << ", tempo(s)= "<< tempo << endl; 
  for (int ii=0; ii<3; ii++) {
    ff.getline(riga,256);
  }

  for (int ii=0; ii<Nch; ii++) {
     x+=passox;
     ff >> y;
     hh->Fill(x,y);
		 hh2->SetPoint(ii,x,y);

   }
   //gg->Draw();

   ff.close();

// file di fondo
  ff.open("notaghetta_finale4maggio.Spe",fstream::in);
  if (!ff.is_open())  {
   cout << " file non trovato" << endl;
   return 0;
  }

  for (int ii=0; ii<9; ii++) {
    ff.getline(riga,256);
  }
  ff >> tempofondo >> tempo;
  cout << "tempofondo(s)= " << tempofondo << ", tempo(s)= "<< tempo << endl; 
  wtempo = tempomis/tempofondo;

  for (int ii=0; ii<3; ii++) {
    ff.getline(riga,256);
  }
 
	x=-0.5;
  passox=1.;
  for (int ii=0; ii<Nch; ii++) {
     x+=passox;
     ff >> y;
		 y=y*0.6;
     hhf->Fill(x,y*wtempo);
		 hhf2->SetPoint(ii,x,y*wtempo);
   }
   ff.close();


// sottrazione del fondo
  x=-0.5;
  passox=1.;
	double a,b;
  for (int ii=0;ii<Nch;++ii) {
		a=hh2->Eval(x);
		b=hhf2->Eval(x);
		
		
   	if(a>b) y = a-b;
		else y = a;
		
    x+=passox;
    gg->Fill(x,y);
		gg2->SetPoint(ii,x,y);
  }

  hh->SetLineColor(4);
	hh->SetFillColor(4);
	hhf->SetLineColor(4);
	hhf->SetFillColor(4);
  gg2->SetLineColorAlpha(4, 0.8);
	
	hhf->SetTitle("30#circ senza targhetta");
	hhf->GetXaxis()->SetTitle("Canali");
	hhf->GetXaxis()->CenterTitle();
	hhf->GetYaxis()->SetTitle("Conteggi");
	hhf->GetYaxis()->CenterTitle();
	hh->SetTitle("30#circ originale");
  //hh->Draw("hist");
	hhf->Draw("hist");
	//gg2->Draw("same");



// se si desidera fare il fit del segnale - fondo

  float inig1=4650.;
  float endg1=5150.;
  float inip=4550.;
  float endp=5210.;

  TCanvas *c2 = new TCanvas("c2");
  //gg2->Draw();

// fit gaus+polinomio 

  TF1 *g1 = new TF1("g1", "gaus", inig1, endg1);
  TF1 *pp = new TF1("pp", "pol1", inip, endp);

  TF1 *total = new TF1("total","gaus(0)+pol1(3)",inip,endp);



// fit con solo gauss per ottenere parametri iniziali
  gg2->Fit(g1,"R");
  g1->GetParameters(&par[0]);
  cout << " solo gaus: h=" << par[0] << " mean= " << par[1] << " sig= " << par[2] << endl;
	float area_gaussiana_utile =par[0]*par[2]*2.507;
	double argg=pow((par[2]*errpar[0]),2.)+pow((par[0]*errpar[2]),2.);
  	float err_area_gaussiana_utile =2.507*pow(argg,0.5);
  cout << " area gaussiana_utile= " << area_gaussiana_utile << " +/-" << err_area_gaussiana_utile << endl;

  total->SetParameters(par);
  total->SetLineColor(6);
  
  gg2->Fit(total,"R+","",inip,endp);

  total->GetParameters(&par[0]);
  errpar[0]=total->GetParError(0);
  errpar[2]=total->GetParError(2);

  cout << " risultati fit globale" << endl;
  cout << " Chi2= " << total->GetChisquare() << " NDF= "<< total->GetNDF() << 
  " prob=" <<  total->GetProb() << endl;
  cout << " gauss" << endl;
  cout << " parameters:" << " " << par[0] << " " << par[1] << " " << par[2] << endl;
  cout << " errpar[0]="<< errpar[0] << "   errpar[2]="<< errpar[2] <<endl;
  cout << " sig/mean g1= " << par[2]/par[1] << endl;
  float area_gauss=par[0]*par[2]*2.507;
  double arg=pow((par[2]*errpar[0]),2.)+pow((par[0]*errpar[2]),2.);
  float err_area_gauss=2.507*pow(arg,0.5);
  cout << " area gauss1= " << area_gauss << " +/-" << err_area_gauss << endl;
  float FWHM=2*sqrt(2*log(2))*par[2];
  cout<<"FWHM = "<<FWHM<<endl;	
  cout<<"R(%) = "<<FWHM*100/par[1]<<endl;		

	gg2->SetTitle("Angolo 30#circ");
	gg2->GetXaxis()->SetLimits(0.,8000.);
	gg2->SetLineColor(4);
	//gg->SetFillColor(4);
	gg2->SetMarkerColor(4);
	gg2->GetXaxis()->SetTitle("Canali");
	gg2->GetXaxis()->CenterTitle();
	gg2->GetYaxis()->SetTitle("Conteggi");
	gg2->GetYaxis()->CenterTitle();
	gg2->Draw();
	
 //per disegnare le curve parziali
 	//total->Draw("same");
  g1->SetParameters(&par[0]);
  g1->SetLineColor(3);
  g1->Draw("same");
  pp->SetParameters(&par[3]);
  pp->SetLineColor(5);
  pp->Draw("same");


	
return 0;

}
