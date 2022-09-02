#include <iostream>
#include <iomanip>
#include <fstream>

#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1F.h"
#include "TPad.h"
#include "TROOT.h"
#include "TStyle.h"


using namespace std;

void NL_PhaseSpace (TFile* file, TH1F* his){

TTree *t = (TTree*)file->Get ("PhaseSpace");

Float_t E;
t->SetBranchAddress ("Ekine",&E);
Float_t nentries = t->GetEntries();
for (Float_t i =0;i<nentries;i++) {
     t->GetEntry (i);
     his->Fill (E);
   }
}
int readPhS(){
  gROOT->Reset();
  gStyle->SetOptStat(000000000); 


///NL_15/////
TFile* f15 = TFile::Open("PhS_15_30t.root");
TH1F *h15= new TH1F ( " 15 MeV " ," his " ,100 ,0 ,16) ;
NL_PhaseSpace(f15,h15);

///NL_145/////
TFile* f145 = TFile::Open("PhS_145_30t.root");
TH1F *h145= new TH1F ( " 145 MeV " ," his " ,100 ,0 ,16) ;
NL_PhaseSpace(f145,h145);

///NL_14/////
TFile* f14 = TFile::Open("PhS_14_30t.root");
TH1F *h14= new TH1F ( " 14 MeV " ," his " ,100 ,0 ,16) ;
NL_PhaseSpace(f14,h14);

///NL_13.5/////
TFile* f135 = TFile::Open("PhS_135_30t.root");
TH1F *h135= new TH1F ( " 13,5 MeV " ," his " ,100 ,0 ,16) ;
NL_PhaseSpace(f135,h135);

//////////plot//////
 //his15->SetFillColor(6) ;
 h15->SetLineColor(6);
 h15->SetLineWidth(2);

 //his145->SetFillColor(4) ;
 h145->SetLineColor(4);
 h145->SetLineWidth(2);

 //his14->SetFillColor(3) ;
 h14->SetLineColor(3);
 h14->SetLineWidth(2);

 //his135->SetFillColor(2) ;
 h135->SetLineColor(2);
 h135->SetLineWidth(2);

/////
h15 ->Draw ();
h145 ->Draw ("same");
h14 ->Draw ("same");
h135 ->Draw ("same");

///////////CHU GIAI///////////////
TLegend leg (0.7 ,0.7 ,0.9 ,0.85) ; // khai bao bang chu giai
leg.SetTextSize (0.04) ; // chon co chu
leg.SetTextColor ( kBlack ) ; // chon mau chu
leg.SetFillColor (0) ; // chon mau to
leg.SetBorderSize (0) ; // khong ve khung bang chu giai
///////////////
leg.AddEntry (h15, "15 MeV") ;
leg.AddEntry (h145, "14,5 MeV") ; 
leg.AddEntry (h14, "14 MeV") ; 
leg.AddEntry (h135, "13,5 MeV") ; 


//leg.DrawClone () ; // ve bang chu giai
 return 0;
}

