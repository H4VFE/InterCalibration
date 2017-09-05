#define ESUM_cxx
#include "ESUM.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>

void ESUM::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ESUM.C
//      root> ESUM t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
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
   TH1F*plot = new TH1F("plot", "C3 with Weighted X and Y Cuts", 100, 0, 3);
 
   TProfile *XwtoE = new TProfile("XwtoE","Energy", 100, -50, 50, 0, 3); //                                                                                                                            
   XwtoE->GetXaxis()->SetTitle("Xw");
   XwtoE->GetYaxis()->SetTitle("Energy");

   TProfile *YwtoE = new TProfile("YwtoE","Energy", 100, -50, 50, 0, 3); // 
   YwtoE->GetXaxis()->SetTitle("Yw");
   YwtoE->GetYaxis()->SetTitle("Energy");

  Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

	if(EA_X > -5 && EA_X < 5 && EA_Y > -5 && EA_Y < 5)
	{
	//plot->Fill(temp_amp[20]/4430 + temp_amp[21]/4230 + temp_amp[22]/3800 + temp_amp[23]/4600 + temp_amp[24]/4680 + temp_amp[19]/3840 + temp_amp[18]/3950 + temp_amp[17]/3950 + temp_amp[16]/4500 + temp_amp[15]/4550 + temp_amp[0]/2800 + temp_amp[1]/3940 + temp_amp[2]/3850 + temp_amp[3]/4300 + temp_amp[4]/4150 + temp_amp[14]/3180 + +temp_amp[13]/4010 + temp_amp[12]/3750 + temp_amp[11]/4180 + temp_amp[10]/3400 + temp_amp[5]/3450 + temp_amp[6]/3600 + temp_amp[7]/4210 + temp_amp[8]/4820 + temp_amp[9]/4740);

	plot->Fill(temp_amp[18]/3950 + temp_amp[17]/3950 + temp_amp[16]/4500 + temp_amp[1]/3940 + temp_amp[2]/3830 + temp_amp[3]/4300 + temp_amp[13]/4010 + temp_amp[12]/3750 + temp_amp[11]/4180);

	//plot->Fill(temp_amp[2]);

	}

//XwtoE->Fill(EA_X, temp_amp[18]/3950 + temp_amp[17]/3950 + temp_amp[16]/4500 + temp_amp[1]/3940 + temp_amp[2]/3830 + temp_amp[3]/4300 + temp_amp[13]/4010 + temp_amp[12]/3750 + temp_amp[11]/4180);
//YwtoE->Fill(EA_Y, temp_amp[18]/3950 + temp_amp[17]/3950 + temp_amp[16]/4500 + temp_amp[1]/3940 + temp_amp[2]/3830 + temp_amp[3]/4300 + temp_amp[13]/4010 + temp_amp[12]/3750 + temp_amp[11]/4180);

	XwtoE->Fill(EA_X, temp_amp[2]);
	YwtoE->Fill(EA_Y, temp_amp[2]);

      // if (Cut(ientry) < 0) continue;
   }
	plot->Draw();
	//XwtoE->Draw();
	//YwtoE->Draw();
}
