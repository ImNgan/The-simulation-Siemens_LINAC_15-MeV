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
            //#____ HISTOGRAM _PDD_MEASUREMENT DATA __#//

void PDD_mea(double mea_per[], TH1 *mea_hist){
    ifstream in ("PDD_mea.txt");             

    double mea_array[120];      

for (int a=0;a<120;a++){                   //Tranfer data from txt (2 column) to an array (Position-even, Dose-odd ) 
         in>>mea_array[a];
    }

for (int a=0;a<60;a++){                    // An array of dose 
    mea_per[a]=mea_array[2*a+1];
    }

for (int b=1;b<61;b++){                    // A histogram for experimental data
    mea_hist->SetBinContent(61-b,mea_per[b-1]);  
}
in.close();

// Note: An element of an array starts from 0, a bin of a histogram starts from 1
}

            //#____ HISTOGRAM _OCR_SIMULATION __#//
void PDD_sim(TFile *sim_data, TH1F *sim_hist, double sim_per[]){

TH1F *histo=(TH1F*)sim_data->Get("histo");

TH1F* h1=new TH1F("h1","Dose vs. mm",97,0,485);
    //##____ PDD_DOSE __##//
double dose =0.;
int bin;  

for (int z=1;z<98;z++){ 
 for (int y=48; y<51; y++){                         // Add dose of 3 bins for x,y
  for (int x=48; x<51; x++){
   dose=dose+histo->GetBinContent(x,y,z);       
  }
 }
 bin=98-z;                                         
 h1->SetBinContent(bin,dose);
 dose=0;
}
   //##____ PDD_PERCENTAGE __##//
double max_dose=h1->GetMaximum();
double max_bin=h1->GetMaximumBin();
double pdd;
for (int i=1; i<98; i++){
 pdd = (h1->GetBinContent(i))*100/max_dose;
 sim_hist->SetBinContent(i,pdd);
 
}
for (int i=0;i<60;i++){
      sim_per[i]=sim_hist->GetBinContent(i+1);
      } 
}

            //#____ SIMULATION_MEASUREMENT_DEVIATION __#//

void Dev_PDD (double sim_per[], double mea_per[],double bin_dev[],double dev_PDD[]){
double sum=0;
for (int a=0;a<60;a++){
    bin_dev[a]=(a+1)*5;
    dev_PDD[a]=((sim_per[a]-mea_per[59-a])/mea_per[59-a])*100;
    sum=sum+dev_PDD[a];
cout<<a<<": "<<dev_PDD[a]<<endl;  
}
double mean=sum/60;
cout<<"Mean= "<<mean<<endl;
}


            ////////////// MAIN_FUNCTION///////////////////
int readPDD_DL_update(){

  gROOT->Reset();
  gStyle->SetOptStat(0000000000); 

  
double mea_per[60], sim_per[60];

   //////SIMULATION//////////////
TFile *OCR_1ti15 = TFile::Open("2ti_14r_2.root");
TH1F* his15=new TH1F("his15","OCR vs. mm",97,0,485);
PDD_sim (OCR_1ti15,his15,sim_per);

   /////////////MEASUREMENT////////
TH1F* hist=new TH1F("hist","PDD",60,0,300);
PDD_mea(mea_per,hist); 


   /////////////DEVIATION_PDD///////
double bin_dev[60],dev_PDD[60];
Dev_PDD (sim_per,mea_per,bin_dev,dev_PDD);

   //////// PLOT_HISTOGRAM/////////

 his15->SetLineColor(3);
 his15->SetLineWidth(2);

 hist->SetLineColor(1);
 hist->SetLineWidth(2); 

 hist->Draw();
 his15->Draw("SAME");

    //////// PLOT_GRAPH/////////

TGraph *Dose_15=new TGraph (60,bin_dev,dev_PDD);
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