#define MyAnalysis_cxx
#include "MyAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <initializer_list>

using namespace std;

void MyAnalysis::Loop()
{

//  std::cout << "test" << std::endl;

//   In a ROOT session, you can do:
//      Root > .L MyAnalysis.C
//      Root > MyAnalysis t
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

//   std::cout << "test1" << std::endl;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      //Attempting vector pairs with position and energy                                                                                                                                                  
   
      vector<pair<float,float> > posE;
      posE.reserve(5);
      posE.push_back(make_pair(0, maximum[VFE8_2]/3600));
      posE.push_back(make_pair(2.2, maximum[VFE7_2]/3700));
      posE.push_back(make_pair(4.4, maximum[VFE3_2]/3480));
      posE.push_back(make_pair(6.6, maximum[VFE5_2]/3400));
      posE.push_back(make_pair(8.8, maximum[VFE4_2]/3930));
      
      float energy_cluster = 0;
      float _w0 = 3.8;
      float x_cluster_logE = 0;

      for(vector<pair<float, float> >::iterator ii = posE.begin(); ii != posE.end(); ii++) {
	//   std::cout << " energy = " << - ii->first << std::endl;
	  float energy_temp = - ii->second;
	  energy_cluster = energy_cluster + energy_temp;
      }

      for(vector<pair<float, float> >::iterator ii = posE.begin(); ii != posE.end(); ii++)
	{                                                                                                       
	//    	cout << "(" << ii->first << ", " << ii->second << ")" << endl;
	  float energy_temp = - ii->second; 
	  float wi = (_w0 + log(energy_temp/energy_cluster));
	  if (wi > 0)
	  {
	    x_cluster_logE = x_cluster_logE + (ii->first) * wi ;
	  }

	}



      // Energy Plots                                                                                                                                                                               
      /*
   if (X[0] > -5 && X[0] < 7 && maximum[VFE3_2] > 2000 && maximum[VFE3_2] < 5000)                                                                                                                          
 
        {                                                                                                                                                                                                  
          hprof->Fill(Y[1]/2,maximum[VFE3_2]);                                                                                                                                                             
        }                                                                                                                                                                                                 
      */                                                                                                                                                                                                


      // if (Cut(ientry) < 0) continue; Put cuts etc...
   }

   //     hprof->Draw();

}
