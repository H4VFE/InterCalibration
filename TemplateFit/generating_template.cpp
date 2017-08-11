#include <iostream>
#include "Math/Interpolator.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TMath.h>
#include <string>
#include <TF1.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


//Authored by Arash Jofrehei, modified by Kelsey Yee  
using namespace std;
const int nsamples = 150;

float WF_time[nsamples*25];
float WF_val[nsamples*25];
float X[2];
float Y[2];

void generating_template(){
  TCanvas *canvas = new TCanvas("generating template","generating template");
  //  TFile *file = new TFile("/afs/cern.ch/user/k/kyee/work/vfe_ecal_tia_7277.root");
  TFile *file = new TFile("/afs/cern.ch/user/k/kyee/work/vfe_55_WC7290.root"); 

  TTree *mtree = (TTree*) file->Get("h4");
  mtree->SetBranchAddress("X",X);
  mtree->SetBranchAddress("Y",Y);
  mtree->SetBranchAddress("WF_time",WF_time);
  mtree->SetBranchAddress("WF_val",WF_val);
  TF1 *g = new TF1("g","gaus",0,1000);
  TH1F *waveform = new TH1F("waveform - C3 - 100 GeV - 1*1 cm^2 at center","waveform - C3 - 100 GeV - 1*1 cm^2 at center;time(ns)",nsamples,-0.125,937.375);
  TProfile *mean_waveform = new TProfile("mean waveform - C3 - 100 GeV - 1*1 cm^2 at center","mean waveform - C3 - 100 GeV - 1*1 cm^2 at center;time(ns)",nsamples,-0.5,937);
  
  const Long64_t nentries = mtree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++){
    Long64_t ientry = mtree->LoadTree(jentry);
    nb = mtree->GetEntry(jentry);   nbytes += nb;
    if (TMath::Abs(X[0])<50&&TMath::Abs(Y[0])<50){
      waveform->Reset();
      for (int i = 0;i < nsamples;i++) waveform->SetBinContent(i+1,WF_val[i+17*nsamples]);
      if (waveform->GetMaximum() < 1000) continue;
      g->SetParameters(1.2*waveform->GetMaximum(),6.25*(waveform->GetMaximumBin()-1),6);
      g->SetParLimits(0,800,10000);
      g->SetParLimits(1,240,320);
      waveform->Fit("g","Q");
      waveform->Fit("g","Q","",-18+g->GetParameter(1),18+g->GetParameter(1));
      if (g->GetParameter(1) < 260 || g->GetParameter(1) > 280) continue;
      if (g->GetParameter(0) < 2300) continue;
      for (int i = 0;i < nsamples;i++) mean_waveform->Fill(270+WF_time[i+17*nsamples]-g->GetParameter(1),WF_val[i+17*nsamples]);
    }
  }
  
  const int nTempBins = 3750; //25*150
  TH1F *interpolated_mean_waveform = new TH1F("interpolated mean waveform - C3 - 100 GeV - 1*1 cm^2 at center","interpolated mean waveform - C3 - 100 GeV - 1*1 cm^2 at center;time(ns)",nTempBins,-0.125,937.375);
  double x[nsamples+1],y[nsamples+1];
  for (int i = 0;i < nsamples+1;i++){
    x[i] = 6.25 * i;
    y[i] = mean_waveform->GetBinContent(i+1);
    if (i == nsamples) y[i] = 0;
  }
  ROOT::Math::Interpolator inter(nsamples+1, ROOT::Math::Interpolation::kCSPLINE);
  inter.SetData(nsamples+1,x,y);
  for (int i = 0;i < nTempBins;i++) interpolated_mean_waveform->SetBinContent(i+1,inter.Eval(i*6.25/25.0));
  
  mean_waveform->Draw();
  interpolated_mean_waveform->Draw();
  TFile *template_file = new TFile("/afs/cern.ch/user/k/kyee/work/template_July2017_C3_100.root","recreate");
  template_file->cd();
  mean_waveform->Write();
  template_file->Close();
}
