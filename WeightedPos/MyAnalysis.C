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


  TH2F*C3 = new TH2F("C3","C3", 100, 0, 90, 100, -20, 20 );
  //Units of both X and Xwc should be in mm
  C3->SetXTitle("x_cluster_logE");
  C3->SetYTitle("X");

  TH1F*Ratio = new TH1F("Ratio", "Ratio of X/Xwc", 100, -4, 4);

  TProfile *hprof = new TProfile("hprof","Energy", 100, 0, 100, 2000, 5000);
  hprof->GetXaxis()->SetTitle("Xw");
  hprof->GetYaxis()->SetTitle("Energy");

  TH1F*plot = new TH1F("plot", "Maximum plot C3", 100, 1000, 5000);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) 
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      

      std::map<std::pair<int, int>, float> mapE;

      mapE.insert(make_pair(make_pair(22, 22), maximum[VFE7_3]/3730));
      mapE.insert(make_pair(make_pair(44, 22), maximum[VFE3_1]/3640));
      mapE.insert(make_pair(make_pair(66, 22), maximum[VFE5_3]/3780));

      mapE.insert(make_pair(make_pair(22, 44), maximum[VFE7_2]/3700));
      mapE.insert(make_pair(make_pair(44, 44), maximum[VFE3_2]/3480));
      mapE.insert(make_pair(make_pair(66, 44), maximum[VFE5_2]/3400));

      mapE.insert(make_pair(make_pair(22, 66), maximum[VFE7_1]/4260));
      mapE.insert(make_pair(make_pair(44, 66), maximum[VFE3_3]/3970));
      mapE.insert(make_pair(make_pair(66, 66), maximum[VFE5_1]/3810));


      float energy_cluster = 0;
      float _w0 = 3.8;
      float y_cluster_logE = 0;
      float x_cluster_logE = 0;
      float weight_cluster = 0;      
      float wi = 0;


      if( maximum[VFE3_2] > 1000 && X[0] > -20 )
        // Necessary to cut the pions out                                                                                                                                                                   
        {


	  for(std::map <  std::pair<int, int>, float >::iterator ii = mapE.begin(); ii != mapE.end(); ii++)
            {
              float energy_temp =  ii->second;

              if( energy_temp > 500/3400 )
                {
		  energy_cluster = energy_cluster + energy_temp;
                }

            }

	  for(std::map <  std::pair<int, int>, float >::iterator ii = mapE.begin(); ii != mapE.end(); ii++)
            {                                                                                                                                                                                              \

	      float energy_temp =  ii->second;

              if( energy_temp > 500/3400 )
                // Only execute weighting etc... if energy (which has been scaled) passes a certain threshold.                                                                                              
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


          float x_cluster_final = 0;
          float y_cluster_final = 0;

          if (weight_cluster != 0)
            {

              x_cluster_final = x_cluster_logE / weight_cluster;
              y_cluster_final = y_cluster_logE / weight_cluster;

              C3->Fill(y_cluster_final,Y[0]/2);
              Ratio->Fill(2*x_cluster_final / X[0]);
	      hprof->Fill(x_cluster_final , maximum[VFE3_2]);


	      if(x_cluster_final > 40 && x_cluster_final < 48 && y_cluster_final > 39 && y_cluster_final < 47)
		{
		  plot->Fill(maximum[VFE3_2]);
		}


            }
    



	}
    
	     

      // Energy Plots                                                                                                                                                                               
      /*
      if (maximum[VFE3_2] > 2000 && maximum[VFE3_2] < 5000)

	{ 
	  hprof->Fill(x_cluster_final , maximum[VFE3_2]);
       
	}
      */

      // if (Cut(ientry) < 0) continue; Put cuts etc...
    }
 
  //            hprof->Draw();
	//         C3->Draw("colz");
	 //         Ratio->Draw();

     	plot->Draw();

}
