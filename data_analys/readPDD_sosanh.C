// Read root file and Draw
// data: Dose --> PDD. 
// Matrix Size= (485,485,485)
// Resol      = (97,97,97)
// VoxelSize  = (5,5,5)
// nbVal      = 912673


#include <iostream>
#include <iomanip>
#include <fstream>

#include <Riostream.h> // xuat nhap du lieu, for double_t
#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TPad.h"
#include "TROOT.h"
#include "TStyle.h"
#include "THStack.h"
#include "TLegend.h"



using namespace std;
	///FUNCTION: CHUAN PDD /////
void lieuhapthu(TH1F *histo,TH1F *h1,TH1F *h2){
double dose=0.;
int bin;

for (int z=1;z<98;z++){
 for (int y=48; y<51; y++){
  for (int x=48; x<51; x++){
   dose=dose+histo->GetBinContent(x,y,z);
  }
 }
 bin=98-z;
 dose=dose*pow(10,6);
 h1->SetBinContent(bin,dose);
 dose=0;
}

double max_dose=h1->GetMaximum();
double max_bin=h1->GetMaximumBin();
double pdd;
for (int i=1; i<98; i++){
 pdd = (h1->GetBinContent(i))*100/max_dose;
 h2->SetBinContent(i,pdd);
}
cout << endl;
cout << "The maximum dose is: " << max_dose << " Gy at bin " << max_bin << endl;
}
	///// MAIN////////
int readPDD_sosanh(){
  gROOT->Reset();
  gStyle->SetOptStat(000000000); 

///////NANG LUONG 135 MeV///////
TFile *PDD_1ti135 = TFile::Open("2ti_135r.root");
TH1F *histo135=(TH1F*)PDD_1ti135->Get("histo");

TH1F* h1=new TH1F("h1","Dose vs. mm",97,0,485);
TH1F* h2=new TH1F("h2","PDD vs. mm",97,0,485);

lieuhapthu(histo135,h1,h2);

///////NANG LUONG 14 MeV///////
TFile *PDD_1ti14 = TFile::Open("2ti_14r_2.root");
TH1F *histo14=(TH1F*)PDD_1ti14->Get("histo");

TH1F* h3=new TH1F("h3","Dose vs. mm",97,0,485);
TH1F* h4=new TH1F("h4","PDD vs. mm",97,0,485);

lieuhapthu(histo14,h3,h4);


///////NANG LUONG 145 MeV///////
TFile *PDD_1ti145 = TFile::Open("2ti_sig_14r.root");
TH1F *histo145=(TH1F*)PDD_1ti145->Get("histo");

TH1F* h5=new TH1F("h5","Dose vs. mm",97,0,485);
TH1F* h6=new TH1F("h6","PDD vs. mm",97,0,485);

lieuhapthu(histo145,h5,h6);

///////NANG LUONG 15 MeV///////
TFile *PDD_1ti15 = TFile::Open("2ti_14r_2.root");
TH1F *histo15=(TH1F*)PDD_1ti15->Get("histo");

TH1F* h7=new TH1F("h7","Dose vs. mm",97,0,485);
TH1F* h8=new TH1F("h8","PDD vs. mm",97,0,485);

lieuhapthu(histo15,h7,h8);

////////////////// doc du lieu PDD thuc nghiem ///////////
ifstream in;  
 in.open("PDD_mea.txt");
TGraph *measure = new TGraph("PDD_mea.txt");

//////////////// plot historam //////////////////////
TCanvas* c1 = new TCanvas ("c1", "Histogram",100, 10, 700,900); 
measure->SetTitle ( " DO THI PHAN TRAM LIEU THEO DO SAU " ); // dat tieu de
measure->GetXaxis ()-> SetTitle ( " Do sau z [mm] " ); // gia tri cua truc x
measure->GetYaxis ()-> SetTitle ( "Phan tram lieu [%]" ) ;
measure->Draw("AC*");
measure->SetMarkerSize(3);
measure->SetLineWidth(3);

//h8->SetFillStyle(3004);
//h8->SetFillColor(6);
h8->SetLineColor (3);
h8->SetLineWidth (3);
h8->Draw("same");

//h6->SetFillStyle(3004);
//h6->SetFillColor(4);
h6->SetLineColor (kGreen -6);
h6->SetLineWidth (3);
h6->Draw("same");

//h4->SetFillStyle(3004);
//h4->SetFillColor(3);
h4->SetLineColor (3);
h4->SetLineWidth (3);
h4->Draw("same");

//h2->SetFillStyle(3004);
//h2->SetFillColor(2);
h2->SetLineColor (2);
h2->SetLineWidth (3);
h2->Draw("same");

//////////// BANG CHU GIAI //////
TLegend chugiai(0.7,0.7,0.5,0.5);
//chugiai.SetTextSize (0.04) ; // chon co chu
chugiai.SetTextColor ( kBlack ) ; // chon mau chu
chugiai.SetFillColor (0) ; // chon mau to
chugiai.SetBorderSize (1) ; // khong ve khung bang chu giai

 // dat chu giai cho histogram h1
chugiai.AddEntry ( measure , " Experimental data " ) ;
chugiai.AddEntry ( h8 , " 14 MeV " ) ;
chugiai.AddEntry ( h6 , " 14 MeV (sig 10%E)" ) ;
chugiai.AddEntry ( h4 , " 14 MeV " ) ;
chugiai.AddEntry ( h2 , " 13.5 MeV " ) ;

chugiai.DrawClone() ; 

in.close();

return 0;

}
