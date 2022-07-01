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


	///FUNCTION: CHUAN OCR /////
void chuanOCR(TFile *OCR, TH1F *h2, Double_t perOCR[29]){

TH1F *histo=(TH1F*)OCR->Get("histo");

TH1F* h1=new TH1F("h1","Dose vs. mm (OCR)",97,-242.5,242.5);

double dose =0.;
int bin;

for (int y=1; y<98; y++){
 for (int x=48; x<51; x++){
  for (int z=88; z<91; z++){
    dose=dose+histo->GetBinContent(x,y,z);
  }
 }
 bin = y;
 h1->SetBinContent(bin,dose);
 dose=0;
}
///////////////////////chuan theo OCR - phan tram /////
double dose_at_0cm=h1->GetBinContent(49);
double max_dose=h1->GetMaximum();
double ocr;
for (int i=1; i<98; i++){
 ocr = (h1->GetBinContent(i))*100/dose_at_0cm;
 h2->SetBinContent(i,ocr);
 }
for (int i=35;i<=63;i++){
  perOCR[i-35]=h2->GetBinContent(i);
}
}

////////////// MAIN_FUNCTION///////////////////
int readOCR_NL_TB(){

  gROOT->Reset();
  gStyle->SetOptStat(000000000); 

///////NANG LUONG 15 MeV////////
TFile *OCR_1ti15 = TFile::Open("2ti_14r_2.root");
TH1F* his15=new TH1F("his15","OCR vs. mm",97,-242.5,242.5);
Double_t perOCR[29];
chuanOCR(OCR_1ti15,his15, perOCR);

/*
///////NANG LUONG 14.5 MeV///////
TFile *OCR_1ti145 = TFile::Open("2ti_145r.root");
TH1F* his145=new TH1F("h145","OCR vs. mm",97,-242.5,242.5);
chuanOCR(OCR_1ti145,his145);

///////NANG LUONG 14 MeV///////
TFile *OCR_1ti14 = TFile::Open("2ti_14r_2.root");
TH1F* his14=new TH1F("h14","HISTOGRAM GOM BIN 97",97,-242.5,242.5);
chuanOCR(OCR_1ti14,his14);

///////NANG LUONG 13.5 MeV///////
TFile *OCR_1ti135 = TFile::Open("2ti_135r.root");
TH1F* his135=new TH1F("h135","OCR vs. mm",97,-242.5,242.5);
chuanOCR(OCR_1ti135,his135);

*///////////////////// TAO HISTOGRAM _ EXPERIMENTAL DATA _ TRUNG BINH ////////////////
ifstream in("OCR_mea_chuan_KL.txt");  
 
  
  Double_t OCR_mea[58],per[29];
for (Int_t i=0;i<58;i++){
         in>>OCR_mea[i];
    }
for (Int_t i=0;i<29;i++){
    per[i]=OCR_mea[2*i+1];
}

TH1F* hist=new TH1F("hist","OCR",29,-70,70);
for (int i=1;i<30;i++){
    hist->SetBinContent(i,per[i-1]);
}

Double_t dolechOCR[29];Double_t TONG=0;
for (int i=0;i<29;i++){
    dolechOCR[i]=(abs(perOCR[i]-per[i])/per[i])*100;
    TONG=TONG+dolechOCR[i];   
}
Double_t TB=TONG/29;
cout<<TB<<endl;

////////// PLOT  //////

 hist->SetLineColor(1);
 hist->SetLineWidth(2); 

 his15->SetLineColor(3);
 his15->SetLineWidth(2);

/*
 his145->SetLineColor(4);
 his145->SetLineWidth(2);


 his14->SetLineColor(3);
 his14->SetLineWidth(2); 

 
 his135->SetLineColor(2);
 his135->SetLineWidth(2);

 his135->Draw();
*/
 his15->Draw();
 hist->Draw("SAME");

 
 //his145->Draw("Same");
 //his14->Draw("SAME");
  
  
///////////CHU GIAI///////////////
TLegend leg (0.7 ,0.7 ,0.9 ,0.85) ; // khai bao bang chu giai
//leg.SetTextSize (0.04) ; // chon co chu
leg.SetTextColor ( kBlack ) ; // chon mau chu
leg.SetFillColor (0) ; // chon mau to
leg.SetBorderSize (1) ; // khong ve khung bang chu giai

///////////////

leg.AddEntry (his15, "14 MeV (3 bin new) ") ;
//leg.AddEntry (his145, "14,5 MeV") ; 
//leg.AddEntry (his14, "14 MeV") ; 
//leg.AddEntry (his135, "13,5 MeV") ; 
leg.AddEntry (hist, "Experimental data") ; 
leg.DrawClone () ; // ve bang chu giai


return 0;
}


