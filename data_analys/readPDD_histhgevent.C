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
#define size 60


using namespace std;
	///FUNCTION: CHUAN PDD /////
void NL(TFile *PDD,Double_t per[size]){
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
/////////////THUC NGHIEM///////////
void tgiang(Double_t x[],Double_t y[],Double_t NL[]){
ifstream in("PDD_mea.txt");
  
  Double_t PDD_mea[120],mea[60];

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
   in.close();
}
   
////////////// MAIN_FUNCTION///////////////////
int readPDD_histhgevent(){
  gROOT->Reset();
  gStyle->SetOptStat(000002211); 

///////PHAN BO 500 TRIEU ///////
TFile *PDD_500tr = TFile::Open("500t_145r.root");
Double_t per500tr[size];

NL(PDD_500tr,per500tr);
Double_t x500tr[size],y500tr[size];

tgiang(x500tr,y500tr,per500tr);

///////PHAN BO 1 TI ///////
TFile *PDD_1ti = TFile::Open("1ti_145r_3.root");
Double_t per1ti[size];

NL(PDD_1ti,per1ti);
Double_t x1ti[size],y1ti[size];

tgiang(x1ti,y1ti,per1ti);
///////PHAN BO 1,5 TI ///////
TFile *PDD_1ti5 = TFile::Open("1ti5_145r.root");
Double_t per1ti5[size];

NL(PDD_1ti5,per1ti5);
Double_t x1ti5[size],y1ti5[size];

tgiang(x1ti5,y1ti5,per1ti5);


///////PHAN BO 2 TI ///////
TFile *PDD_2ti = TFile::Open("2ti_145r.root");
Double_t per2ti[size];

NL(PDD_2ti,per2ti);
Double_t x2ti[size],y2ti[size];

tgiang(x2ti,y2ti,per2ti);


///// PHan bo cua than giang ///
TH1F* h500tr=new TH1F("h500","500 trieu",50,-5,5);
TH1F* h1ti=new TH1F("h1ti","1 ti",50,-5,5);
TH1F* h1ti5=new TH1F("h1ti5","1,5 ti",50,-5,5);
TH1F* h2ti=new TH1F("h2ti","2 ti",50,-5,5);

Double_t temp1ti, temp2ti, temp500tr, temp1ti5; 
for (Int_t t=0;t<60;t++){
 temp500tr=y500tr[t]; 
 temp1ti=y1ti[t];
 temp1ti5=y1ti5[t];
 temp2ti=y2ti[t];

   h500tr->Fill(temp500tr);
   h1ti->Fill(temp1ti);
   h1ti5->Fill(temp1ti5);
   h2ti->Fill(temp2ti);
}
//////////////// plot historam //////////////////////
TCanvas* c1 = new TCanvas ("c1", "Histogram",100, 10, 900,500); 
c1->Divide(2,2);
 h500tr->SetFillColor(8) ;
 h500tr->SetLineColor(8); 
 h500tr->SetLineWidth(3);  

 h1ti->SetFillColor(8) ;
 h1ti->SetLineColor(8);
 h1ti->SetLineWidth(3);   

 h1ti5->SetFillColor(8) ;
 h1ti5->SetLineColor(8);
 h1ti5->SetLineWidth(3);

 h2ti->SetFillColor(8);
 h2ti->SetLineColor(8);
 h2ti->SetLineWidth(3);
  
 c1->cd(1);h500tr->Draw();
 c1->cd(2);h1ti->Draw();
 c1->cd(3);h1ti5->Draw();
 c1->cd(4);h2ti->Draw();
 
///////////CHU GIAI///////////////
TLegend leg (0.7 ,0.7 ,0.9 ,0.85) ; // khai bao bang chu giai
//leg.SetTextSize (0.04) ; // chon co chu
leg.SetTextColor ( kBlack ) ; // chon mau chu
leg.SetFillColor (0) ; // chon mau to
leg.SetBorderSize (0) ; // khong ve khung bang chu giai
///////////////
leg.AddEntry (h500tr, "500 trieu ") ; 
leg.AddEntry (h1ti , " 1 ti ") ; 
leg.AddEntry (h1ti5, "1,5 ti ") ; 
leg.AddEntry (h2ti, "2 ti") ; 


//leg.DrawClone () ; // ve bang chu giai



return 0;
}





