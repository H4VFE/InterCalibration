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

float rbot = 1.5;
float rtop = 3;
float coff = 1500;

float scale = 1.5;

float xmin = -6;
float xmax = 4;
float ymin = -6;
float ymax = 4;


ROOT::Math::Interpolator inter(nsamples+1, ROOT::Math::Interpolation::kCSPLINE);
double fit_function(double *v,double *par)
{
  return par[0]*inter.Eval(par[2]*(v[0]-263.1)+263.1-par[1]-6)/(3308.7*scale);
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

   TFile *hodoFile = new TFile("/afs/cern.ch/user/k/kyee/work/vfe_55_WC7200.root");
   TFile *WCfile = new TFile("/afs/cern.ch/user/k/kyee/work/vfe_55_WC7200.root");
   TFile *template_recos = new TFile("/afs/cern.ch/user/k/kyee/work/template_recos_C3_150.root","recreate");
   TH1F *waveform = new TH1F("waveform - C3 - 150 GeV - 1*1 cm^2 at center","waveform - C3 - 150 GeV - 1*1 cm^2 at center;time(ns)",nsamples,-0.125,937.375);
   TFile *template_file = new TFile("/afs/cern.ch/user/k/kyee/work/template_July2017_C3_150.root");
   TProfile *mean_waveform = (TProfile*) template_file->Get("mean waveform - C3 - 150 GeV - 1*1 cm^2 at center");


   TTree *hodoTree = (TTree*) hodoFile->Get("h4");
   hodoTree->SetBranchAddress("X",hodoX);
   hodoTree->SetBranchAddress("Y",hodoY);
   hodoTree->SetBranchAddress("WF_time",WF_time);
   hodoTree->SetBranchAddress("WF_val",WF_val);
   hodoTree->SetBranchAddress("run",&run);
   hodoTree->SetBranchAddress("spill",&spill);
   hodoTree->SetBranchAddress("event",&event);
  
   TTree *WCtree = (TTree*) WCfile->Get("h4");
   WCtree->SetBranchAddress("X",WCX);
   WCtree->SetBranchAddress("Y",WCY);

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
   TH1F *template_time = new TH1F("time obtained by templates","time obtained by templates",120,-30,30);
   TH1F*plot = new TH1F("plot", "3x3 Energy Sum", 100, rbot, rtop);
   TH1F*plot2 = new TH1F("plot2", "Second plot", 100, rbot, rtop);

   TProfile *XwtoE = new TProfile("XwtoE","Energy", 100, -50, 50, 300, 6000); //
   XwtoE->GetXaxis()->SetTitle("Xw");
   XwtoE->GetYaxis()->SetTitle("Energy");
 
   TProfile *YwtoE = new TProfile("YwtoE","Energy", 100, -50, 50, 300, 6000); //                                                                                                                          
   YwtoE->GetXaxis()->SetTitle("Yw");
   YwtoE->GetYaxis()->SetTitle("Energy");

   TH2F*both = new TH2F("both","both", 100, 0, 4000*scale, 100, 0, 4000*scale );  

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
   func->SetParameters(3600*scale,0,1);
   func->SetParLimits(0,30,20000);
   func->SetParLimits(1,-30,30);
   func->SetParLimits(2,0.95,1.1);
  
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
	 waveform->Fit("fit","Q","",269.1+func->GetParameter(1)-20,269.1+func->GetParameter(1)+30);                                                                                                     

	 ientry = LoadTree(jentry);
	 if (ientry < 0) break;
	 nb = fChain->GetEntry(jentry);
	
	 std::map<std::pair<int, int>, float> mapE;
    
	 mapE.insert(make_pair(make_pair(-44, 44), maximum[VFE8_0]/4160));
	 mapE.insert(make_pair(make_pair(-22, 44), maximum[VFE7_4]/3750));
	 mapE.insert(make_pair(make_pair(0, 44), maximum[VFE3_0]/2850));
	 mapE.insert(make_pair(make_pair(22, 44), maximum[VFE5_4]/2980));
	 mapE.insert(make_pair(make_pair(44, 44), maximum[VFE4_0]/3320));

	 mapE.insert(make_pair(make_pair(-44, 22), maximum[VFE8_1]/4020));
	 mapE.insert(make_pair(make_pair(-22, 22), maximum[VFE7_3]/3790));
	 mapE.insert(make_pair(make_pair(0, 22), maximum[VFE3_1]/3740));
	 mapE.insert(make_pair(make_pair(22, 22), maximum[VFE5_3]/3800));
	 mapE.insert(make_pair(make_pair(44, 22), maximum[VFE4_1]/3400));

	 mapE.insert(make_pair(make_pair(-44, 0), maximum[VFE8_2]/3650));
	 mapE.insert(make_pair(make_pair(-22, 0), maximum[VFE7_2]/3740));
	 mapE.insert(make_pair(make_pair(0, 0), maximum[VFE3_2]/3620));
	 mapE.insert(make_pair(make_pair(22, 0), maximum[VFE5_2]/3520));
	 mapE.insert(make_pair(make_pair(44, 0), maximum[VFE4_2]/4010));


	 mapE.insert(make_pair(make_pair(-44, -22), maximum[VFE8_3]/4330));
	 mapE.insert(make_pair(make_pair(-22, -22), maximum[VFE7_1]/4260));
	 mapE.insert(make_pair(make_pair(0, -22), maximum[VFE3_3]/4044));
	 mapE.insert(make_pair(make_pair(22, -22), maximum[VFE5_1]/3970));
	 mapE.insert(make_pair(make_pair(44, -22), maximum[VFE4_3]/4590));

	 mapE.insert(make_pair(make_pair(-44, -44), maximum[VFE8_4]/4400));
	 mapE.insert(make_pair(make_pair(-22, -44), maximum[VFE7_0]/4310));
	 mapE.insert(make_pair(make_pair(0, -44), maximum[VFE3_4]/3940));
	 mapE.insert(make_pair(make_pair(22, -44), maximum[VFE5_0]/3510));
	 mapE.insert(make_pair(make_pair(44, -44), maximum[VFE4_4]/4530));

	 int num = VFE3_2;
	 float energy_cluster = 0;
	 float _w0 = 3.8;
	 float x_cluster_logE = 0;
	 float y_cluster_logE = 0;
	 float weight_cluster = 0;
	 float wi = 0;

	 if( maximum[num] > coff )  // Necessary to cut the pions out
	   {
	     for(std::map <  std::pair<int, int>, float >::iterator ii = mapE.begin(); ii != mapE.end(); ii++)
	       {
		 float energy_temp =  ii->second;
		 if( energy_temp > 1000/3000) energy_cluster = energy_cluster + energy_temp;
	       }



	     for(std::map <  std::pair<int, int>, float >::iterator ii = mapE.begin(); ii != mapE.end(); ii++)
	       {		 float energy_temp =  ii->second;
		 if( energy_temp > 1000/3400 )
		   {
		     wi = (_w0 + log(energy_temp/energy_cluster));
		     if (wi > 0)
		       {
			 x_cluster_logE = x_cluster_logE + (ii->first.first) * wi ;
			 y_cluster_logE = y_cluster_logE + (ii->first.second) * wi;
			 weight_cluster = weight_cluster + wi;
		       }
		   }
	       }
	   }
 
	 float x_cluster_final = 0;
	 float y_cluster_final = 0;

	 if (weight_cluster != 0)
	   {
	     x_cluster_final = x_cluster_logE / weight_cluster;
	     y_cluster_final = y_cluster_logE / weight_cluster;
	     XwtoE->Fill(x_cluster_final , maximum[num]);
	     YwtoE->Fill(y_cluster_final , maximum[num]);


	 if(x_cluster_final > xmin  && x_cluster_final < xmax  && y_cluster_final > ymin  && y_cluster_final < ymax && func->GetParameter(0) > coff)
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

	       ientry = LoadTree(jentry);
	       if (ientry < 0) break;
	       nb = fChain->GetEntry(jentry);
	       //NOTE: Anything having to do with the maximum, VFE#_#, etc... has to be put after something like this. 
	      
	     if(channel == 2)
	       {
		 C3 = func->GetParameter(0)/3640;
		 plot2->Fill(C3);
		 both->Fill(func->GetParameter(0),maximum[VFE3_2]);
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

	   }
	   }
       }

     }
   }

   template_recos->cd();
   template_tree->Write();
   //  cout << VFE3_2 << " test" << endl;                                                                                                                                                                 
   //template_recos->Close();                                                                                                                                                                             
  
   //both->Draw("colz"); //This was used to see correlation between maximum and the template amplitude
   plot->Draw(); //This can be drawn and fitted outside the code. 

  
   TCanvas * c1 = new TCanvas("c", "c", 800, 600);                                                                                                                                                         
   c1->SetCanvasSize(2000,750);                                                                                                                                                                            
                                                                                                                                                                                                           
   c1->Divide(2,1);                                                                                                                                                                                        
   c1->cd(1);                                                                                                                                                                                              
   XwtoE->Draw();                                                                                                                                                                                          
   c1->cd(2);                                                                                                                                                                                             
   YwtoE->Draw(); 
 
}
