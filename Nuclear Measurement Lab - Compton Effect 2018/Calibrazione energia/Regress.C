{
/*============================*/
/* calibration (E)=>(channel) */
/*============================*/
gROOT->Reset();
Int_t n=20;
Double_t x[n], y[n];
Int_t npoint = 8;

//gStyle->SetOptStat(111111111);
gStyle->SetOptFit(1111);

Double_t par[2];
// energia in keV
x[0]=59.5409;
x[1]=72.873;
x[2]=80.9979;
x[3]=276.4;
x[4]=302.9;
x[5]=356;
x[6]=511;
x[7]=661;

// canali 
y[0]=607.159;
y[1]=740.121;
y[2]=808.746;
y[3]=2948.55;
y[4]=3242.67;
y[5]=3834.57;
y[6]=5799.09;
y[7]=7241.01;

TGraph * gr1 = new TGraph (npoint, x, y);

gr1->Draw("A*");

Int_t inip1=x[0], endp1=x[7];

TF1 *p1 = new TF1("poli1", "pol1", 0., 700.);

gr1->Fit(p1,"R");



}
