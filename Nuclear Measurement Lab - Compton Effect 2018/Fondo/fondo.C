#include <iostream>
#include <fstream>
#include "TH1F.h"
//#include "TPDF.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TAttAxis.h"
#include "TAttLine.h"
#include "TAttFill.h"

using namespace std;

int main (int argc,char **argv) {

	TApplication myApp("myApp", &argc, argv);
	

    char riga[256];
    float y;
    float passox=1.;
    float  x=-passox/2.;
    Double_t par[12],errpar[12];
    int tempovivo,tempo;
  
	
    int Nch=8000;


// lettura file e creazione istrogramma

    fstream ff;
    ff.open("fondo4aprile2018.Spe",fstream::in);
    if (!ff.is_open())  {
        cout << " file non trovato" << endl;
        return 0;
    }

    TH1F *gg = new TH1F("gg", "", Nch, 0., Nch);

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
		ff.close();
	
		gg->GetXaxis()->SetTitle("Canali");
		gg->GetYaxis()->SetTitle("Conteggi");
		gg->GetYaxis()->SetTitleOffset(1.25);
		gg->GetXaxis()->CenterTitle();
		gg->GetYaxis()->CenterTitle();
		gg->SetStats(kFALSE);
		gg->SetLineColor(1);
		gg->SetFillColor(18);
		
		TCanvas* canvas = new TCanvas("canvas");
		//TPDF save("fondo.pdf");
		canvas -> cd();
		gg->Draw("pfc");
    //gg->Write();
		//save.Close();
	
		myApp.Run();

return 0;

}
