{
    
//#include "TPDF.h"
  gROOT->Reset();
  gStyle->SetOptStat(1111111);

  int y;
  float passox=1.;
  float  x=-passox/2.;
  float tempovivo,tempo;
  int Nch=8000;

  char riga[256];


  fstream ff;
  ff.open("NaI/NaIhv600.Spe",fstream::in);
  if (!ff.is_open())  {
   cout << " file non trovato" << endl;
   return 0;
  }

  TH1F *gg = new TH1F("gg", " spettro", Nch, 0.,Nch );

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
   //TPDF save("plotNaIhv600.pdf")
   //gg->Write();
    //save.Close();
	gg->Draw();
   ff.close();

return ;

}
