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
#define size 60

using namespace std;

void mea (Double_t x[],Double_t y[],Double_t NL[]){
ifstream in("PDD_mea.txt");  
 
  
  Double_t PDD_mea[120],mea[60]; double TB=0;double tong=0;
for (Int_t i=0;i<120;i++){
         in>>PDD_mea[i];
    }
for (Int_t j=0;j<60;j++){
       mea[j]=PDD_mea[(j*2)+1];
       }
for (Int_t k=0;k<60;k++){
    x[k]=(k+1)*5;
    y[k]=((NL[k]-mea[59-k])/mea[59-k])*100;     
  
}

for (Int_t k=0;k<60;k++){
    tong=tong+y[k];
    TB=tong/60;  
}
 cout<<TB<<endl;
in.close();
}
	///FUNCTION: CHUAN PDD /////
void chuan(TFile *PDD,Double_t per[size]){
Double_t dose=0.;
Int_t bin;

TH1F *histo=(TH1F*)PDD->Get("histo");

TH1F* h1=new TH1F("h1","Dose vs. mm",97,0,485);
TH1F* h2=new TH1F("h2","PDD vs. mm",97,0,485);

for (Int_t z=1;z<98;z++){
 for (Int_t y=48; y<51; y++){
  for (Int_t x=48; x<51; x++){
   dose=dose+histo->GetBinContent(x,y,z);
  }
 }
 bin=98-z;
 h1->SetBinContent(bin,dose);
 dose=0;
}

Double_t max_dose=h1->GetMaximum();
Double_t max_bin=h1->GetMaximumBin();
Double_t pdd;
for (int i=1; i<98; i++){
 pdd = (h1->GetBinContent(i))*100/max_dose;
 h2->SetBinContent(i,pdd);
 
}
for (Int_t l=0;l<60;l++){
      per[l]=h2->GetBinContent(l+1);
      } 
}

////////////// MAIN_FUNCTION///////////////////
int readPDD_DL(){

  gROOT->Reset();
  gStyle->SetOptStat(0000000000); 

///////NANG LUONG 15 MeV///////
TFile *PDD_1ti15 = TFile::Open("2ti_14r_2.root");
Double_t per15[size];

chuan(PDD_1ti15,per15);
Double_t x15[size],y15[size];

mea(x15,y15,per15);

///////NANG LUONG 145 MeV///////
TFile *PDD_1ti145 = TFile::Open("2ti_sig_14r.root");
Double_t per145[size];

chuan(PDD_1ti145,per145);
Double_t x145[size],y145[size];

mea(x145,y145,per145);

///////NANG LUONG 14 MeV///////
TFile *PDD_1ti14 = TFile::Open("2ti_14r_2.root");
Double_t per14[size];

chuan(PDD_1ti14,per14);
Double_t x14[size],y14[size];

mea(x14,y14,per14);

///////NANG LUONG 135 MeV///////
TFile *PDD_1ti135 = TFile::Open("2ti_135r.root");
Double_t per135[size];

chuan(PDD_1ti135,per135);
Double_t x135[size],y135[size];

mea(x135,y135,per135);



//////////plot/////

TGraph *NL_15=new TGraph (60,x15,y15);
NL_15->SetMarkerStyle(20);
NL_15->SetMarkerColor(3);
NL_15->SetMarkerSize(1.5);
NL_15->Draw("ACP");

TGraph *NL_145=new TGraph (60,x145,y145);
NL_145->SetMarkerStyle(21);
NL_145->SetMarkerColor(kGreen -6);
NL_145->SetMarkerSize(1.5);
NL_145->Draw("CP");

TGraph *NL_14=new TGraph (60,x14,y14);
NL_14->SetMarkerStyle(22);
NL_14->SetMarkerColor(3);
NL_14->SetMarkerSize(1.5);
NL_14->Draw("cP");

TGraph *NL_135=new TGraph (60,x135,y135);
NL_135->SetMarkerStyle(29);
NL_135->SetMarkerColor(2);
NL_135->SetMarkerSize(1.5);
NL_135->Draw("cP");

///////////CHU GIAI///////////////
TLegend leg (0.7 ,0.7 ,0.5 ,0.5) ; // khai bao bang chu giai
//leg.SetTextSize (0.04) ; // chon co chu
leg.SetTextColor ( kBlack ) ; // chon mau chu
leg.SetFillColor (0) ; // chon mau to
leg.SetBorderSize (1) ; // khong ve khung bang chu giai
///////////////
leg.AddEntry (NL_15, "14 MeV") ; 
leg.AddEntry (NL_145, "14 (sig 10%E) MeV") ; 
leg.AddEntry (NL_14, "14 MeV") ; 
leg.AddEntry (NL_135 , "13.5 MeV") ; 

leg.DrawClone () ; // ve bang chu giai

return 0;
}
