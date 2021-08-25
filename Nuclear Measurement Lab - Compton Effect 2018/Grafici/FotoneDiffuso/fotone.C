

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
	float* errX = new float[n];
	float* errY = new float[n];
//	riempio i vettori

	for(int i=0; i<n; i++){
		txt >> x[i];
		txt >> errX[i];
		txt >> y[i];
		txt >> errY[i];
	}
	txt.close();



//	GRAFICO
	TGraphErrors *grafico = new TGraphErrors(n, x, y, errX, errY);
	TF1 *teo = new TF1("teo","511./(2-cos(x*3.1415/180.))", 0., 70.);


	TCanvas* canvas = new TCanvas("canvas");

	canvas -> cd();
	grafico->SetTitle("Energia del fotone diffuso");
	grafico->GetXaxis()->SetLimits(0., 70.);
	grafico->GetXaxis()->SetTitle("Angolo [#circ]");
	grafico->GetXaxis()->CenterTitle();
	grafico->GetYaxis()->SetTitle("Energia [keV]");
	grafico->GetYaxis()->CenterTitle();
	grafico->Draw("AP");
	teo->SetLineWidth(1);
	teo->SetLineColor(1);
	teo->Draw("same");
	
	
	return 0;

}
