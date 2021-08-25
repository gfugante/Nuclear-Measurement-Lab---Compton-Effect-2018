

//
//	Il programma crea dei grafici per l'analisi del VOLTAGGIO
//	partendo da un file di testo che va creato con:
//	- la prima riga contenente il numero di dati
//	- la prima colonna riempita dei valori del voltaggio
//	- la seconda riempita con i valori medi
//	- la terza con gli errori
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
//	g++ -o plateau.x plateau.C `root-config --cflags` `root-config --libs`
//	oppure con un makefile
//
//


#include <iostream>
#include <fstream>
#include "TGraphErrors.h"
#include "TF1.h"
#include "TPDF.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TAxis.h"
#include "TAttLine.h"


using namespace std;

int main (int argc, char **argv) {

	TApplication myApp("myApp", &argc, argv);
	
	

//	apre il file di dati

	ifstream txt;
	txt.open("dati.txt");
	
	if (!txt.is_open())  {
		cout << " File non trovato" << endl;
		return 0;
	}

	int n;
	txt >> n;
	cout << n<<endl;
//	creo i vettori necessari

	float* V = new float[n];
	float* y = new float[n];
	float* err = new float[n];
	float* zero = new float[n];
	
//	riempio i vettori

	for(int i=0; i<n; i++){
		txt >> V[i];
		cout << V[i]<<"	";
		txt >> y[i];
		cout << y[i]<<"	";
		txt >> err[i];
		cout << err[i]<<endl;
		zero[i] = 0.;
	}
	txt.close();


//	GRAFICO


	TGraphErrors *grafico = new TGraphErrors(n, V, y, zero, err);




// LINEA PLATEAU
	
	
	TF1* plateau = new TF1("plateau", "13000.", 715., 765.);



	grafico->SetTitle("Test Plateau");
	grafico->GetXaxis()->SetTitle("Voltaggio [V]");
	grafico->GetXaxis()->CenterTitle();
	grafico->GetYaxis()->SetTitle("Area");
	grafico->GetYaxis()->CenterTitle();
	plateau->SetLineColor(1);
	plateau->SetLineWidth(1);
	
	
	TCanvas* canvas = new TCanvas("canvas");
	TPDF save("test.pdf");
	canvas -> cd();
	grafico->Draw("AP");
	grafico->Write();
	plateau->Draw("same");
	plateau->Write("same");
	save.Close();
	
	myApp.Run();
	return 0;

}
