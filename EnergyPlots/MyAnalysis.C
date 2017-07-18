#define MyAnalysis_cxx
#include "MyAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>

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

   TProfile *hprof = new TProfile("hprof","Energy",100,-20,20,2000,5000);
      hprof->GetXaxis()->SetTitle("Y mm");
      hprof->GetYaxis()->SetTitle("Energy");


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
     {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;


      /*            if ( maximum[VFE8_0] > 2000 && maximum[VFE8_0] < 5000)                                                                                                                      
        {                                                                                                                                                                                                   
	  // hprof->Fill(maximum[VFE8_0]);                                                                                                                                                                      
       std::cout << maximum[VFE8_0] << std::endl;                                                                                                                                                                                               
        }  
      */
    

      /*           if (X[1] > -10)
	{
	  std::cout << X[0] << std::endl << X[1] <<std::endl << X[2] << std::endl ;
	}
      */

   if (X[0] > -5 && X[0] < 7 && maximum[VFE8_0] > 2000 && maximum[VFE8_0] < 5000 && X[1] > -5 && X[1] < 7)

	{ 
	  hprof->Fill(Y[0]/2,maximum[VFE8_0]);
       
        }
   

      // if (Cut(ientry) < 0) continue; Put cuts etc...
   }

   //   std::cout << "number of entries" <<  hprof->GetEntries() << std::endl;

   //   std::cout << "Congratulations you've reached the end of the code!" << std::endl;

      hprof->Draw();

}
