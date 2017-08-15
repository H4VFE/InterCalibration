#define Analysis_cxx
#include "Analysis.h"
#include <iostream>
#include "Math/Interpolator.h"
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


using namespace std;
const int nsamples = 150;

float WF_time[nsamples*25];
float WF_val[nsamples*25];
float hodoX[2];
float hodoY[2];
float WCX[1];
float WCY[1];
float hodo_X[2];
float hodo_Y[2];
float WC_X;
float WC_Y;
float temp_amp[25];
float temp_time[25];
float max_time[25];
float EA_X;
float EA_Y;
float digiMax[25];
unsigned int run;
unsigned int spill;
unsigned int event;
unsigned int Run;
unsigned int Spill;
unsigned int Event;

float B2;
float B3;
float B4;
float C2;
float C3;
float C4;
float D2;
float D3;
float D4;


ROOT::Math::Interpolator inter(nsamples+1, ROOT::Math::Interpolation::kCSPLINE);
double fit_function(double *v,double *par)
{
  return par[0]*inter.Eval(par[2]*(v[0]-263.1)+263.1-par[1]-6)/3308.7;
}

void Analysis::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L Analysis.C
//      Root > Analysis t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile *hodoFile = new TFile("/afs/cern.ch/user/k/kyee/work/vfe_55_WC7290.root");

   TTree *hodoTree = (TTree*) hodoFile->Get("h4");
   hodoTree->SetBranchAddress("X",hodoX);
   hodoTree->SetBranchAddress("Y",hodoY);
   hodoTree->SetBranchAddress("WF_time",WF_time);
   hodoTree->SetBranchAddress("WF_val",WF_val);
   hodoTree->SetBranchAddress("run",&run);
   hodoTree->SetBranchAddress("spill",&spill);
   hodoTree->SetBranchAddress("event",&event);
   //  TFile *WCfile = new TFile("/afs/cern.ch/work/a/ajofrehe/cern-summer-2016/July2017/H4Analysis/ntuples/vfe_55_WC_B3_100.root"); //Same issue as before                                                  
   //  TFile *WCfile = new TFile("/afs/cern.ch/user/k/kyee/work/vfe_ecal_tia_7277.root");                                                                                                                    
   TFile *WCfile = new TFile("/afs/cern.ch/user/k/kyee/work/vfe_55_WC7290.root");

   TTree *WCtree = (TTree*) WCfile->Get("h4");
   WCtree->SetBranchAddress("X",WCX);
   WCtree->SetBranchAddress("Y",WCY);
   TFile *template_recos = new TFile("/afs/cern.ch/user/k/kyee/work/template_recos_C3_100.root","recreate");

   template_recos->cd();
   TTree *template_tree = new TTree("template_tree","template_tree");
   template_tree->Branch("hodo_X",&hodo_X,"hodo_X[2]/F");
   template_tree->Branch("hodo_Y",&hodo_Y,"hodo_Y[2]/F");
   template_tree->Branch("WC_X",&WC_X,"WC_X/F");
   template_tree->Branch("WC_Y",&WC_Y,"WC_Y/F");
   template_tree->Branch("temp_amp",&temp_amp,"temp_amp[25]/F");
   template_tree->Branch("temp_time",&temp_time,"temp_time[25]/F");
   template_tree->Branch("max_time",&max_time,"max_time[25]/F");
   template_tree->Branch("digiMax",&digiMax,"digiMax[25]/F");
   template_tree->Branch("EA_X",&EA_X,"EA_X/F");
   template_tree->Branch("EA_Y",&EA_Y,"EA_Y/F");
   template_tree->Branch("run",&Run,"run/i");
   template_tree->Branch("spill",&Spill,"spill/i");
   template_tree->Branch("event",&Event,"event/i");
   TH1F *amp = new TH1F("amplitude obtained by templates","amplitude obtained by templates",100,0,5000);
   TH1F *template_time = new TH1F("time obtained by templates","time obtained by templates",120,-30,30);
   TH1F *waveform = new TH1F("waveform - C3 - 100 GeV - 1*1 cm^2 at center","waveform - C3 - 100 GeV - 1*1 cm^2 at center;time(ns)",nsamples,-0.125,937.375);
   TH1F*plot = new TH1F("plot", "3x3 Energy Sum", 120, 0.5, 1.6);
   //   plot->GetXaxis()->SetRange(0.5, 3);

   TProfile *XwtoE = new TProfile("XwtoE","Energy", 100, -50, 50, 300, 5000); //                                                                                                                          
   XwtoE->GetXaxis()->SetTitle("Xw");
   XwtoE->GetYaxis()->SetTitle("Energy");
   //Weighted X to energy                                                                                                                                                                                   

   TProfile *YwtoE = new TProfile("YwtoE","Energy", 100, -50, 50, 300, 5000); //                                                                                                                          
   YwtoE->GetXaxis()->SetTitle("Yw");
   YwtoE->GetYaxis()->SetTitle("Energy");
   //Weighted Y to energy                                                                                                                                                                                 

   TH2F*both = new TH2F("both","both", 100, 0, 5000, 100, 0, 5000 );

  
   TProfile *TvM = new TProfile("TvM","TvM", 100, 1000, 5000, 1000, 5000); //                                                                                                                              

   TFile *template_file = new TFile("/afs/cern.ch/user/k/kyee/work/template_July2017_C3_100.root");

   TProfile *mean_waveform = (TProfile*) template_file->Get("mean waveform - C3 - 100 GeV - 1*1 cm^2 at center");
   TProfile *amp_x = new TProfile("template amplitude vs X","template amplitude vs X;X(mm)",30,-15,15);
   TProfile *amp_y = new TProfile("template amplitude vs Y","template amplitude vs Y;Y(mm)",30,-15,15);
   const int nTempBins = 3750; //25*150                                                                                                                                                                   

   double x[nsamples+1],y[nsamples+1];
   for (int i = 0;i < nsamples+1;i++){
     x[i] = 6.25 * i;
     if (i == nsamples) y[i] = 0;
     else y[i] = mean_waveform->GetBinContent(i+1);
   }
   inter.SetData(nsamples+1,x,y);
   TF1 *func = new TF1("fit",fit_function,200,380,3);
   func->SetParNames("amplitude","time","shrink ratio");
   func->SetLineColor(2);
   func->SetParameters(3500,0,1);
   func->SetParLimits(0,30,20000);
   func->SetParLimits(1,-30,30);
   func->SetParLimits(2,0.95,1.1);

   //float channel_peak[25] = {2790,3640,3480,3970,3770,3270,3280,3930,4410,4270,3390,3810,3400,3780,2850,4260,4260,3700,3730,3720,4060,3860,3600,4260,4290};                                                
   float channel_peak[25] = {2850,3740,3620,4044,3940,3320,3400,4010,4590,4530,3510,3970,3520,3800,2980,4310,4260,3740,3790,3750,4160,4020,3650,4330,4400};
   float channel_x[25] = {0,0,0,0,0,2,2,2,2,2,1,1,1,1,1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2};
   float channel_y[25] = {2,1,0,-1,-2,2,1,0,-1,-2,-2,-1,0,1,2,-2,-1,0,1,2,2,1,0,-1,-2};
   //Here are the calibrations. Note: the positions are done likely, with C in the center and with "crystal distances" as units.                                                                          
  
   float energy_sum;
   float position_weight[25];
   float position_weight_sum;

   const Long64_t nentries = hodoTree->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0,ientry;
   float WC_dummy_X[nentries];
   float WC_dummy_Y[nentries];
   for (Long64_t jentry=0; jentry<nentries;jentry++){
     ientry = WCtree->LoadTree(jentry);
     nb = WCtree->GetEntry(jentry);
     WC_dummy_X[jentry] = WCX[0];
     WC_dummy_Y[jentry] = WCY[0];
   }

   for (Long64_t jentry=0; jentry<nentries;jentry++){
     ientry = hodoTree->LoadTree(jentry);
     nb = hodoTree->GetEntry(jentry);   nbytes += nb;
     if (jentry%1000 == 0) cout << jentry << endl;
     hodo_X[0] = hodoX[0];
     hodo_X[1] = hodoX[1];
     hodo_Y[0] = hodoY[0];
     hodo_Y[1] = hodoY[1];
     EA_X = -10000;
     EA_Y = -10000;
     WC_X = WC_dummy_X[jentry];
     WC_Y = WC_dummy_Y[jentry];
     Run = run;
     Spill = spill;
     Event = event;

     for(int channel = 0;channel < 25;channel++){
       for (int i = 0;i < nsamples;i++) waveform->SetBinContent(i+1,WF_val[i+channel*nsamples]);
       max_time[channel] = ( 6.25 * waveform->GetMaximumBin() ) - 3.25;
       digiMax[channel] = waveform->GetMaximum();
       if (waveform->GetMaximum() < 30){
	 temp_amp[channel] = 1;
	 temp_time[channel] = -10000;
       }else{
	 func->SetParameters(1.2*waveform->GetMaximum(),0,1);
	 waveform->Fit("fit","Q","",200,380);
	 //waveform->Fit("fit","Q","",269.1+func->GetParameter(1)-20,269.1+func->GetParameter(1)+30);                                                                                                     
 	 //if (jentry == 44 && channel == 17) break;                                                                                                                                                      
  	 //template_time->Fill(func->GetParameter(1));                                                                                                                                                     
	 temp_amp[channel] = func->GetParameter(0);
	 temp_time[channel] = func->GetParameter(1);
       }
     }

     energy_sum = 0;
     position_weight_sum = 0;

     for (int i = 0;i < 25;i++) energy_sum += temp_amp[i]/channel_peak[i];
     for(int channel = 0;channel < 25;channel++){
       position_weight[channel] = 3 + TMath::Log10(temp_amp[channel]/(channel_peak[channel]*energy_sum));
       if (position_weight[channel] < 0) position_weight[channel] = 0;
       position_weight_sum += position_weight[channel];
     }
     EA_X = 0;
     for(int channel = 0;channel < 25;channel++) EA_X += 22.0 * channel_x[channel] * position_weight[channel]/position_weight_sum;
     EA_Y = 0;
     for(int channel = 0;channel < 25;channel++) EA_Y += 22.0 * channel_y[channel] * position_weight[channel]/position_weight_sum;
     //    cout << EA_Y << endl;                                                                                                                                                                          
  
     template_tree->Fill();

     for(int channel = 0;channel < 25;channel++){
       for (int i = 0;i < nsamples;i++) waveform->SetBinContent(i+1,WF_val[i+channel*nsamples]);
       max_time[channel] = ( 6.25 * waveform->GetMaximumBin() ) - 3.25;
       digiMax[channel] = waveform->GetMaximum();
       if (waveform->GetMaximum() < 30){
	 temp_amp[channel] = 1;
	 temp_time[channel] = -10000;
       }else{
	 func->SetParameters(1.2*waveform->GetMaximum(),0,1);
	 waveform->Fit("fit","Q","",200,380);
	 //waveform->Fit("fit","Q","",269.1+func->GetParameter(1)-20,269.1+func->GetParameter(1)+30);                                                                                                     
	 //if (jentry == 44 && channel == 17) break;                                                                                                                                                       
	 XwtoE->Fill(EA_X , func->GetParameter(0));
	 YwtoE->Fill(EA_Y , func->GetParameter(0));

     	if (EA_X > -6   && EA_X < 1 && EA_Y > -4  && EA_Y < 3 && func->GetParameter(0) > 1000 )
	   {

	     B2 = 0;
	     B3 = 0;
	     B4 = 0;
	     C2 = 0;
	     C3 = 0;
	     C4 = 0;
	     D2 = 0;
	     D3 = 0;
	     D4 = 0;

	     //amp->Fill(func->GetParameter(0))	   
	       ientry = LoadTree(jentry);
	       if (ientry < 0) break;
	       nb = fChain->GetEntry(jentry);
	       //NOTE: Anything having to do with the maximum, VFE#_#, etc... has to be put after something like this. 
	      
	       /*
	       cout << VFE3_2 <<  "test VFE3_2" << endl;                                                                                                                                                  
    	       cout << maximum[VFE3_2] << "test maximum[VFE3_2]" <<endl; 
	       */ //Check successful

	     //From here, I'll try channel plugging. 
	     if(channel == 2)
	       {
		 C3 = func->GetParameter(0)/3640;
	       // plot->Fill(func->GetParameter(0)); 
	       // cout << "Template Amplitude C3 " << func->GetParameter(0)/3640 << endl; 
	       /* //Check seems reasonable. 
	       cout << "Template Amplitude " << func->GetParameter(0)/3640 << endl;
	       cout << "Maximum scaled " << maximum[VFE3_2]/3640 << endl;
	       */
	       }
	    
             if(channel == 18)
	       {
                 B2 = func->GetParameter(0)/3790;
               }

	     if(channel == 17)
	       {
		 B3 = func->GetParameter(0)/3740;
	       }

             if(channel == 16)
	       {
                 B4 = func->GetParameter(0)/4260;
               }
	   
             if(channel == 1)
	       {
		 C2 = func->GetParameter(0)/2850;
	       }
	  
             if(channel == 3)
	       {
		 C4 = func->GetParameter(0)/4044;
               }

	     if(channel == 13)
               {
                 D2 = func->GetParameter(0)/3800;
	       }

             if(channel == 12)
	       {
		 D3 = func->GetParameter(0)/3550;
               }

	     if(channel == 11)
               {
                 D4 = func->GetParameter(0)/3970;
	       }
	   
	     plot->Fill(C3 + C2 + C4 + B2 + B3 + B4 + D2 + D3 + D4);
	       
	       // both->Fill(func->GetParameter(0),maximum[VFE3_2]);

	     }

	   }
	 //template_time->Fill(func->GetParameter(1));                                                                                                                                                     

       }
   }


    /*
       for (Long64_t jentry=0; jentry<nentries;jentry++) {
	 Long64_t ientry = LoadTree(jentry);
	 if (ientry < 0) break;
	 nb = fChain->GetEntry(jentry);   nbytes += nb;

      
     //cout << VFE3_2 <<  "test VFE3_2" << endl;
     //cout << maximum[VFE3_2] << "test maximum[VFE3_2]" <<endl;
      // Check successful. maximum and VFE#_# can be "summoned" here. 

       plot->Fill(maximum[VFE3_2]);
     }
   */


   template_recos->cd();
   template_tree->Write();
   //  cout << VFE3_2 << " test" << endl;                                                                                                                                                                 
   //template_recos->Close();                                                                                                                                                                             
  
   //both->Draw("colz"); //This was used to see correlation between maximum and the template amplitude
   plot->Draw(); //This can be drawn and fitted outside the code. 

   /*  
   TCanvas * c1 = new TCanvas("c", "c", 800, 600);                                                                                                                                                         
   c1->SetCanvasSize(2000,750);                                                                                                                                                                            
                                                                                                                                                                                                           
   c1->Divide(2,1);                                                                                                                                                                                        
   c1->cd(1);                                                                                                                                                                                              
   XwtoE->Draw();                                                                                                                                                                                          
   c1->cd(2);                                                                                                                                                                                             
   YwtoE->Draw(); 
   */
}
