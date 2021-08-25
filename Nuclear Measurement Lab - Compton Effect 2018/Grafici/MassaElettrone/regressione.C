

//
//	Il programma crea dei grafici per l'analisi della calibrazione
//	dell'ENERGIA partendo da un file di testo che va creato con:
//	- la prima riga contenente il numero di dati
//	- la prima colonna riempita dei valori teorici dei picchi
//	- la seconda riempita con i valori dei canali dei picchi
//	- la terza riempita con le sigma sui canali (sigma fit gauss)
//	ognuna distanziata dall'altra con un tab
//	(formato pensato per copiare semplicemente le colonne di
//	excell in un file che deve chiamarsi dati.txt)
//
//	IMPORTANTISSIMO!!
//	prima di passare i dati bisogna sostituire le virgole coi punti o per il compilatore non sono numeri!!!
//	Il programma crea un file grafico.png
//	utile per essere incluso nella relazione scritta in latex
//
//	Per compilare:
//	g++ -o regressione.x regressione.C `root-config --cflags` `root-config --libs`
//	oppure con un makefile
//
//


#include <iostream>
#include <fstream>
#include <cmath>
#include "TGraphErrors.h"
#include "TF1.h"
#include "TPDF.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TAttLine.h"
#include "TAttMarker.h"
#include "TAttAxis.h"


using namespace std;

int main () {

	
	

//	apre il file di dati

	ifstream txt;
	txt.open("datiEnergia.txt");
	
	if (!txt.is_open())  {
		cout << " File non trovato" << endl;
		return 0;
	}

	int n;
	txt >> n;
	cout << n<<endl;
//	creo i vettori necessari

	float* x = new float[n];
	float* y = new float[n];
	float* err = new float[n];
	float* zero = new float[n];
//	riempio i vettori

	for(int i=0; i<n; i++){
		txt >> x[i];
		cout << x[i]<<"	";
		txt >> y[i];
		cout << y[i]<<"	";
		txt >> err[i];
		cout << err[i]<<endl;
		zero[i] = 0.;
	}
	txt.close();



//	GRAFICO


	TGraphErrors *grafico = new TGraphErrors(n, x, y, zero, err);


// FIT
	
	
	grafico->Fit("pol1");
	TF1* fit = (TF1*)grafico->GetFunction("pol1");


// CALCOLO CHI QUADRO (quello di root non conta gli errori)
// y = A + xB

	float A = fit->GetParameter(0);
	float errA = fit->GetParError(0);
	float B = fit->GetParameter(1);
	float errB = fit->GetParError(1);
	float yth;
	float chi2 = 0.;
	for(int i=0; i<n; i++){
		yth = A + x[i]*B;
		chi2 += pow( (y[i]-yth)/err[i], 2);
	}
	cout << endl;
	cout << "Chi2 = " << chi2<< endl;
	cout << "Chi2rid = " << chi2/(n-1) << endl;
	cout << "A = " << A << "+-" << errA << endl;
	cout << "B = " << B << "+-" << errB << endl << endl;
	
	
	grafico->SetTitle("Massa elettrone");
	grafico->GetXaxis()->SetTitle("1/(2-cos(#theta))");
	grafico->GetXaxis()->CenterTitle();
	grafico->GetYaxis()->SetTitle("Energia [keV]");
	grafico->GetYaxis()->CenterTitle();
	fit->SetLineColor(1);
	fit->SetLineWidth(1);
	
	TCanvas* canvas = new TCanvas("canvas");
	//TPDF save("regressione.pdf");
	canvas -> cd();
	grafico->Draw("AP");
	//grafico->Write();
	fit->Draw("same");
	//fit->Write("same");
	//save.Close();
	
	
	return 0;

}
