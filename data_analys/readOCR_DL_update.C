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

      //#____ HISTOGRAM _OCR_MEASUREMENT DATA __#//

void OCR_mea(double mea_per[], TH1 *mea_hist){
    ifstream in ("OCR_mea_new.txt");

    double mea_array[58];

for (int a=0;a<58;a++){
         in>>mea_array[a];
    }

for (int a=0;a<29;a++){
    mea_per[a]=mea_array[2*a+1];
    }

for (int b=1;b<30;b++){
    mea_hist->SetBinContent(b,mea_per[b-1]);  
    }
}
 //#____ HISTOGRAM _OCR_SIMULATION __#//
void OCR_sim(TFile *sim_data, TH1F *sim_hist, double sim_per[]){

TH1F *histo=(TH1F*)sim_data->Get("histo");

TH1F* h1=new TH1F("h1","Dose vs. mm (OCR)",97,-242.5,242.5);

 //##____ OCR_DOSE __##//
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
   //##____ OCR_PERCENTAGE __##//
double dose_at_0cm=h1->GetBinContent(49);
double max_dose=h1->GetMaximum();
double ocr;

for (int i=1; i<98; i++){
 ocr = (h1->GetBinContent(i))*100/dose_at_0cm;
 sim_hist->SetBinContent(i,ocr);
}

for (int i=35;i<=63;i++){
  sim_per[i-35]=sim_hist->GetBinContent(i);
}
}

      //#____ SIMULATION_MEASUREMENT_DEVIATION __#//
void Dev_OCR (double sim_per[], double mea_per[],double bin_dev[],double dev_OCR[]){
double sum=0;
for (int a=0;a<29;a++){
    bin_dev[a]=(a-14)*5;
    dev_OCR[a]=((sim_per[a]-mea_per[a])/mea_per[a])*100;
    sum=sum+dev_OCR[a];
cout<<a<<": "<<dev_OCR[a]<<endl;  
}
double mean=sum/29;
cout<<"Mean= "<<mean<<endl;
}

      //#____MAIN_FUNCTION __#//
int readOCR_DL_update(){

  gROOT->Reset();
  gStyle->SetOptStat(000000000); 

double mea_per[29], sim_per[29];
TH1F* hist=new TH1F("hist","OCR",29,-70,70);
OCR_mea(mea_per,hist); 

TFile *OCR_1ti15 = TFile::Open("2ti_14r_2.root");
TH1F* his15=new TH1F("his15","OCR vs. mm",97,-242.5,242.5);
OCR_sim (OCR_1ti15,his15,sim_per);

double bin_dev[29],dev_OCR[29];
Dev_OCR (sim_per,mea_per,bin_dev,dev_OCR);

 //////// PLOT_HISTOGRAM/////////

 his15->SetLineColor(3);
 his15->SetLineWidth(2);

 hist->SetLineColor(1);
 hist->SetLineWidth(2); 

 hist->Draw();
 his15->Draw("SAME");

    //////// PLOT_GRAPH/////////

TGraph *Dose_15=new TGraph (60,bin_dev,dev_OCR);
Dose_15->SetMarkerStyle(20);
Dose_15->SetMarkerColor(3);
Dose_15->SetMarkerSize(1.5);
Dose_15->Draw("ACP");

   //////////LEGEND///////////////

auto legend = new TLegend(0.1,0.7,0.48,0.9);
     legend->SetHeader("The Legend Title","C"); 
     legend->AddEntry(his15,"15 MeV");
     legend->AddEntry(hist,"Experimental data ");
     legend->Draw();                    


return 0;
}
 
