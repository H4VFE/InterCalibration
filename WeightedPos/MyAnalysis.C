#define MyAnalysis_cxx
#include "MyAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <initializer_list>
#include <string>
#include <TF1.h>


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

  TH1F*Ratio = new TH1F("Ratio", "Ratio of Weighted X/ Hodo X", 100, -50, 50);

  TProfile *xprof = new TProfile("xprof","Energy", 100, 0, 100, 2000, 5000);
  xprof->GetXaxis()->SetTitle("Xw");
  xprof->GetYaxis()->SetTitle("Energy");

  TProfile *yprof = new TProfile("yprof","Energy", 100, 0, 100, 2000, 5000);
  yprof->GetXaxis()->SetTitle("Yw");
  yprof->GetYaxis()->SetTitle("Energy");

  float rbot = 0.5;
  float rtop = 1.8;

  TH1F*plot = new TH1F("plot", "Maximum plot C3", 100, rbot, rtop);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) 
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      int num = VFE3_2;
      float xmin = 39;
      float xmax = 51;
      float ymin = 39;
      float ymax = 51;      

      std::map<std::pair<int, int>, float> mapE;

      mapE.insert(make_pair(make_pair(0, 0), maximum[VFE8_0]/4160));
      mapE.insert(make_pair(make_pair(22, 0), maximum[VFE7_4]/3750));
      mapE.insert(make_pair(make_pair(44, 0), maximum[VFE3_0]/2850));
      mapE.insert(make_pair(make_pair(66, 0), maximum[VFE5_4]/2980));
      mapE.insert(make_pair(make_pair(88, 0), maximum[VFE4_0]/3320));

      mapE.insert(make_pair(make_pair(0, 22), maximum[VFE8_1]/4020));
      mapE.insert(make_pair(make_pair(22, 22), maximum[VFE7_3]/3790));
      mapE.insert(make_pair(make_pair(44, 22), maximum[VFE3_1]/3740));
      mapE.insert(make_pair(make_pair(66, 22), maximum[VFE5_3]/3800));
      mapE.insert(make_pair(make_pair(88, 22), maximum[VFE4_1]/3400));

      mapE.insert(make_pair(make_pair(0, 44), maximum[VFE8_2]/3650));
      mapE.insert(make_pair(make_pair(22, 44), maximum[VFE7_2]/3740));
      mapE.insert(make_pair(make_pair(44, 44), maximum[VFE3_2]/3620));
      mapE.insert(make_pair(make_pair(66, 44), maximum[VFE5_2]/3520));
      mapE.insert(make_pair(make_pair(88, 44), maximum[VFE4_2]/4010));


      mapE.insert(make_pair(make_pair(0, 66), maximum[VFE8_3]/4330));
      mapE.insert(make_pair(make_pair(22, 66), maximum[VFE7_1]/4260));
      mapE.insert(make_pair(make_pair(44, 66), maximum[VFE3_3]/4044));
      mapE.insert(make_pair(make_pair(66, 66), maximum[VFE5_1]/3970));
      mapE.insert(make_pair(make_pair(88, 66), maximum[VFE4_3]/4590));

      mapE.insert(make_pair(make_pair(0, 88), maximum[VFE8_4]/4400));
      mapE.insert(make_pair(make_pair(22, 88), maximum[VFE7_0]/4310));
      mapE.insert(make_pair(make_pair(44, 88), maximum[VFE3_4]/3940));
      mapE.insert(make_pair(make_pair(66, 88), maximum[VFE5_0]/3510));
      mapE.insert(make_pair(make_pair(88, 88), maximum[VFE4_4]/4530));


      float energy_cluster = 0;
      float _w0 = 3.8;
      float y_cluster_logE = 0;
      float x_cluster_logE = 0;
      float weight_cluster = 0;      
      float wi = 0;


      if( maximum[num] > 1000 )
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
	      xprof->Fill(x_cluster_final , maximum[num]);
	      yprof->Fill(y_cluster_final , maximum[num]);


	      if(x_cluster_final > xmin && x_cluster_final < xmax && y_cluster_final > ymin && y_cluster_final < ymax)
		{
	       		  plot->Fill(maximum[VFE3_1]/3740 + maximum[VFE3_2]/3670 + maximum[VFE3_3]/4044 + maximum[VFE7_3]/3790 + maximum[VFE7_2]/3740 + maximum[VFE7_1]/4260 + maximum[VFE5_3]/3800 + maximum[VFE5_2]/3520 + maximum[VFE5_1]/3970);

		  //		  plot->Fill(maximum[VFE3_2]/3670);

		}



            }
    



	}	     


      // if (Cut(ientry) < 0) continue; Put cuts etc...
    }
 
  //         xprof->Draw();
  //         yprof->Draw();
  //         C3->Draw("colz");
  //         Ratio->Draw();
  //         plot->Draw();

  plot->Draw();

  float constant = 1;
  float mean = 1;
  float sig = 1;
  float alpha = 1;
  float N = 1;


  TF1*f_cb    = new TF1("f_cb","crystalball", rbot, rtop);
  f_cb -> SetParameters(constant, mean, sig, alpha, N);
  plot->Fit("f_cb","R");

  constant = f_cb->GetParameter(0);
  mean = f_cb->GetParameter(1);
  float errmean = f_cb->GetParError(1);
  sig = f_cb->GetParameter(2);
  float errsig = f_cb->GetParError(2);
  float error =  (sig/mean)* sqrt( pow((errmean/mean),2) + pow((errsig/sig),2)) ;
  alpha = f_cb->GetParameter(3);
  N = f_cb->GetParameter(4);

  TF1*f_cb2    = new TF1("f_cb2","crystalball", mean - sig, mean + 3*sig);
  f_cb2 -> SetParameters(constant,mean,sig,alpha,N);
  plot->Fit("f_cb2","R");

  mean = f_cb2->GetParameter(1);
  errmean = f_cb2->GetParError(1);
  sig = f_cb2->GetParameter(2);
  errsig = f_cb2->GetParError(2);
  error =  (sig/mean)* sqrt( pow((errmean/mean),2) + pow((errsig/sig),2)) ;

  std::cout << " ~~~~~~~~~~~ " << std::endl;
  std::cout << " Peak  = " <<  mean << "+/-" << errmean  << std::endl;
  std::cout << " Sigma  = " <<  sig << "+/-" << errsig << std::endl;
  std::cout << " sigma/mean  = " <<  sig/mean << "+/-" << error  << std::endl;
  std::cout << " ~~~~~~~~~~~ " << std::endl;
           

}
