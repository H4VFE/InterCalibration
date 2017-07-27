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


      //      for(vector<pair<float, float> >::iterator it = posE.begin(); it != posE.end(); it++)                                                                                                        
      //    	cout << "(" << it->first << ", " << it->second << ")" << endl;


      // Energy Plots                                                                                                                                                                               
      /*
   if (X[0] > -5 && X[0] < 7 && maximum[VFE3_2] > 2000 && maximum[VFE3_2] < 5000)                                                                                                                          
 
        {                                                                                                                                                                                                  
          hprof->Fill(Y[1]/2,maximum[VFE3_2]);                                                                                                                                                             
        }                                                                                                                                                                                                 
      */                                                                                                                                                                                                



  /*    
      // Andrea's Code Part
      int  num_clusters = 0;
      float _w0 = 3.8;
      float x_cluster_logE = 0;
      float y_cluster_logE = 0;
      float weight_cluster = 0;
      float energy_cluster = 0;
      float x_cluster_max = -1000;
      float y_cluster_max = -1000;
      std::map < float, std::pair<float, float> > map_of_calo_clusters;

      //---- first calculate cluster energy
      for( std::map < float, std::pair<float, float> >::iterator ii=map_of_calo_clusters.begin(); ii!=map_of_calo_clusters.end(); ii++) {
	//   std::cout << " energy = " << - ii->first << std::endl;
	if (x_cluster_max == -1000) {
	  x_cluster_max = (ii->second.first); //---- seed position X
	  y_cluster_max = (ii->second.second); //---- seed position X   
	  float energy_temp = - ii->first;
	  energy_cluster = energy_cluster + energy_temp;
	  _vector_energies.push_back(energy_temp);
	  num_clusters++;
	}
	else {
	  if (DR(ii->second.first, x_cluster_max, ii->second.second, y_cluster_max) < maxDR) {
	    float energy_temp = - ii->first;
	    energy_cluster = energy_cluster + energy_temp;
	    _vector_energies.push_back(energy_temp);
	    num_clusters++;
	  }
	}
      }


      // Highlighted Code
      num_clusters = 0;

      if (energy_cluster > 0)
	{
	  for( std::map < float, std::pair<float, float> >::iterator ii = map_of_calo_clusters.begin(); ii != map_of_calo_clusters.end(); ii++)
	    {
	      //   std::cout << " energy = " << - ii->first << std::endl;                                                                                                                   
	      //   One task: Find out the equivalent to ii->first                        
	      if (DR(ii->second.first, x_cluster_max, ii->second.second, y_cluster_max) < maxDR)
		{
		  float energy_temp = - ii->first;
		  // Find the equivalent to ii->first;
		  float wi = (_w0 + log(energy_temp/energy_cluster));
		  // energy_cluster = energy_cluster + energy_temp;
		  if (wi > 0)
		    {
		      x_cluster_logE = x_cluster_logE + (ii->second.first)  * wi ;
		      // x_cluster_logE starts at 0, and then is increased as such. 
		      weight_cluster = weight_cluster + wi;
		      // starts at zero and is increased like this. 
		      
		      num_clusters++;
		      // Just a counter
		    }


		}
	    }
	}
*/


      // if (Cut(ientry) < 0) continue; Put cuts etc...
   }

   //     hprof->Draw();

}
