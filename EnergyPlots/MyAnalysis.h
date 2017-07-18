//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 18 09:40:46 2017 by ROOT version 5.34/36
// from TTree /main_h4reco_tree
// found on file: vfe_ecal_tia_7262.root
//////////////////////////////////////////////////////////

#ifndef MyAnalysis_h
#define MyAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class MyAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   ULong64_t       index;
   ULong64_t       start_time;
   ULong64_t       time_stamp;
   UInt_t          evt_flag;
   UInt_t          run;
   UInt_t          spill;
   UInt_t          event;
   Int_t           VFE3_0;
   Int_t           VFE3_1;
   Int_t           VFE3_2;
   Int_t           VFE3_3;
   Int_t           VFE3_4;
   Int_t           VFE4_0;
   Int_t           VFE4_1;
   Int_t           VFE4_2;
   Int_t           VFE4_3;
   Int_t           VFE4_4;
   Int_t           VFE5_0;
   Int_t           VFE5_1;
   Int_t           VFE5_2;
   Int_t           VFE5_3;
   Int_t           VFE5_4;
   Int_t           VFE7_0;
   Int_t           VFE7_1;
   Int_t           VFE7_2;
   Int_t           VFE7_3;
   Int_t           VFE7_4;
   Int_t           VFE8_0;
   Int_t           VFE8_1;
   Int_t           VFE8_2;
   Int_t           VFE8_3;
   Int_t           VFE8_4;
   Int_t           CLK;
   Int_t           MCP1;
   Int_t           MCP2;
   Int_t           TRG;
   Int_t           LED;
   Int_t           CFD;
   UInt_t          n_channels;
   UInt_t          n_timetypes;
   Float_t         b_charge[29];   //[n_channels]                                                                                                                                                          
   Float_t         b_slope[29];   //[n_channels]                                                                                                                                                           
   Float_t         b_rms[29];   //[n_channels]                                                                                                                                                             
   Float_t         time[58];   //[n_timetypes]                                                                                                                                                             
   Float_t         time_chi2[58];   //[n_timetypes]                                                                                                                                                        
   Float_t         maximum[29];   //[n_channels]                                                                                                                                                           
   Float_t         time_maximum[29];   //[n_channels]                                                                                                                                                      
   Float_t         amp_max[29];   //[n_channels]                                                                                                                                                           
   Float_t         time_max[29];   //[n_channels]                                                                                                                                                          
   Float_t         chi2_max[29];   //[n_channels]                                                                                                                                                          
   Float_t         charge_tot[29];   //[n_channels]                                                                                                                                                        
   Float_t         charge_sig[29];   //[n_channels]                                                                                                                                                        
   Float_t         fit_ampl[29];   //[n_channels]                                                                                                                                                          
   Float_t         fit_time[29];   //[n_channels]                                                                                                                                                          
   Float_t         fit_chi2[29];   //[n_channels]                                                                                                                                                          
   Float_t         calibration[29];   //[n_channels]     
   Float_t         X[2];   //[n_planes]                                                                                                                                                                    
   Float_t         Y[2];   //[n_planes]  


   // List of branches
   TBranch        *b_index;   //!
   TBranch        *b_start_time;   //!
   TBranch        *b_time_stamp;   //!
   TBranch        *b_evt_flag;   //!
   TBranch        *b_run;   //!
   TBranch        *b_spill;   //!
   TBranch        *b_event;   //!

   TBranch        *b_VFE3_0;   //!                                                                                                                                                                         
   TBranch        *b_VFE3_1;   //!                                                                                                                                                                         
   TBranch        *b_VFE3_2;   //!                                                                                                                                                                         
   TBranch        *b_VFE3_3;   //!                                                                                                                                                                         
   TBranch        *b_VFE3_4;   //!                                                                                                                                                                         
   TBranch        *b_VFE4_0;   //!                                                                                                                                                                         
   TBranch        *b_VFE4_1;   //!                                                                                                                                                                         
   TBranch        *b_VFE4_2;   //!                                                                                                                                                                         
   TBranch        *b_VFE4_3;   //!                                                                                                                                                                         
   TBranch        *b_VFE4_4;   //!                                                                                                                                                                         
   TBranch        *b_VFE5_0;   //!                                                                                                                                                                         
   TBranch        *b_VFE5_1;   //!                                                                                                                                                                         
   TBranch        *b_VFE5_2;   //!                                                                                                                                                                         
   TBranch        *b_VFE5_3;   //!                                                                                                                                                                         
   TBranch        *b_VFE5_4;   //!                                                                                                                                                                         
   TBranch        *b_VFE7_0;   //!                                                                                                                                                                         
   TBranch        *b_VFE7_1;   //!                                                                                                                                                                         
   TBranch        *b_VFE7_2;   //!                                                                                                                                                                         
   TBranch        *b_VFE7_3;   //!                                                                                                                                                                         
   TBranch        *b_VFE7_4;   //!                                                                                                                                                                         
   TBranch        *b_VFE8_0;   //!                                                                                                                                                                         
   TBranch        *b_VFE8_1;   //!                                                                                                                                                                         
   TBranch        *b_VFE8_2;   //!                                                                                                                                                                         
   TBranch        *b_VFE8_3;   //!                                                                                                                                                                         
   TBranch        *b_VFE8_4;   //!                                                                                                                                                                         
   TBranch        *b_CLK;   //!                                                                                                                                                                            
   TBranch        *b_MCP1;   //!                                                                                                                                                                           
   TBranch        *b_MCP2;   //!                                                                                                                                                                           
   TBranch        *b_TRG;   //!                                                                                                                                                                            
   TBranch        *b_LED;   //!                                                                                                                                                                            
   TBranch        *b_CFD;   //!                                                                                                                                                                           
                                                                                                           
   TBranch        *b_n_channels;   //!                                                                                                                                                                     
   TBranch        *b_n_timetypes;   //!                                                                                                                                                                    
   TBranch        *b_b_charge;   //!                                                                                                                                                                       
   TBranch        *b_b_slope;   //!                                                                                                                                                                        
   TBranch        *b_b_rms;   //!                                                                                                                                                                          
   TBranch        *b_time;   //!                                                                                                                                                                           
   TBranch        *b_time_chi2;   //!                                                                                                                                                                      
   TBranch        *b_maximum;   //!                                                                                                                                                                        
   TBranch        *b_time_maximum;   //!                                                                                                                                                                   
   TBranch        *b_amp_max;   //!                                                                                                                                                                        
   TBranch        *b_time_max;   //!                                                                                                                                                                       
   TBranch        *b_chi2_max;   //!                                                                                                                                                                       
   TBranch        *b_charge_tot;   //!                                                                                                                                                                     
   TBranch        *b_charge_sig;   //!                                                                                                                                                                     
   TBranch        *b_fit_ampl;   //!                                                                                                                                                                       
   TBranch        *b_fit_time;   //!                                                                                                                                                                       
   TBranch        *b_fit_chi2;   //!                                                                                                                                                                   
   TBranch        *b_calibration;   //!    
   TBranch        *b_X;   //!                                                                                                                                                                              
   TBranch        *b_Y;   //! 


   MyAnalysis(TTree *tree=0);
   virtual ~MyAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MyAnalysis_cxx
MyAnalysis::MyAnalysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {


     std::cout << "tree" << std::endl;
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("vfe_ecal_tia_7262.root");
      if (!f || !f->IsOpen()) {

         f = new TFile("vfe_ecal_tia_7262.root");
      }
      f->GetObject("h4",tree);
      std::cout << "cout tree = " << tree <<  std::endl;
   }
   Init(tree);
}

MyAnalysis::~MyAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}


Int_t MyAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MyAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MyAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("index", &index, &b_index);
   fChain->SetBranchAddress("start_time", &start_time, &b_start_time);
   fChain->SetBranchAddress("time_stamp", &time_stamp, &b_time_stamp);
   fChain->SetBranchAddress("evt_flag", &evt_flag, &b_evt_flag);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("spill", &spill, &b_spill);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("VFE3_0", &VFE3_0, &b_VFE3_0);
   fChain->SetBranchAddress("VFE3_1", &VFE3_1, &b_VFE3_1);
   fChain->SetBranchAddress("VFE3_2", &VFE3_2, &b_VFE3_2);
   fChain->SetBranchAddress("VFE3_3", &VFE3_3, &b_VFE3_3);
   fChain->SetBranchAddress("VFE3_4", &VFE3_4, &b_VFE3_4);
   fChain->SetBranchAddress("VFE4_0", &VFE4_0, &b_VFE4_0);
   fChain->SetBranchAddress("VFE4_1", &VFE4_1, &b_VFE4_1);
   fChain->SetBranchAddress("VFE4_2", &VFE4_2, &b_VFE4_2);
   fChain->SetBranchAddress("VFE4_3", &VFE4_3, &b_VFE4_3);
   fChain->SetBranchAddress("VFE4_4", &VFE4_4, &b_VFE4_4);
   fChain->SetBranchAddress("VFE5_0", &VFE5_0, &b_VFE5_0);
   fChain->SetBranchAddress("VFE5_1", &VFE5_1, &b_VFE5_1);
   fChain->SetBranchAddress("VFE5_2", &VFE5_2, &b_VFE5_2);
   fChain->SetBranchAddress("VFE5_3", &VFE5_3, &b_VFE5_3);
   fChain->SetBranchAddress("VFE5_4", &VFE5_4, &b_VFE5_4);
   fChain->SetBranchAddress("VFE7_0", &VFE7_0, &b_VFE7_0);
   fChain->SetBranchAddress("VFE7_1", &VFE7_1, &b_VFE7_1);
   fChain->SetBranchAddress("VFE7_2", &VFE7_2, &b_VFE7_2);
   fChain->SetBranchAddress("VFE7_3", &VFE7_3, &b_VFE7_3);
   fChain->SetBranchAddress("VFE7_4", &VFE7_4, &b_VFE7_4);
   fChain->SetBranchAddress("VFE8_0", &VFE8_0, &b_VFE8_0);
   fChain->SetBranchAddress("VFE8_1", &VFE8_1, &b_VFE8_1);
   fChain->SetBranchAddress("VFE8_2", &VFE8_2, &b_VFE8_2);
   fChain->SetBranchAddress("VFE8_3", &VFE8_3, &b_VFE8_3);
   fChain->SetBranchAddress("VFE8_4", &VFE8_4, &b_VFE8_4);
   fChain->SetBranchAddress("CLK", &CLK, &b_CLK);
   fChain->SetBranchAddress("MCP1", &MCP1, &b_MCP1);
   fChain->SetBranchAddress("MCP2", &MCP2, &b_MCP2);
   fChain->SetBranchAddress("TRG", &TRG, &b_TRG);
   fChain->SetBranchAddress("LED", &LED, &b_LED);
   fChain->SetBranchAddress("CFD", &CFD, &b_CFD);
   fChain->SetBranchAddress("n_channels", &n_channels, &b_n_channels);
   fChain->SetBranchAddress("n_timetypes", &n_timetypes, &b_n_timetypes);
   fChain->SetBranchAddress("b_charge", b_charge, &b_b_charge);
   fChain->SetBranchAddress("b_slope", b_slope, &b_b_slope);
   fChain->SetBranchAddress("b_rms", b_rms, &b_b_rms);
   fChain->SetBranchAddress("time", time, &b_time);
   fChain->SetBranchAddress("time_chi2", time_chi2, &b_time_chi2);
   fChain->SetBranchAddress("maximum", maximum, &b_maximum);
   fChain->SetBranchAddress("time_maximum", time_maximum, &b_time_maximum);
   fChain->SetBranchAddress("amp_max", amp_max, &b_amp_max);
   fChain->SetBranchAddress("time_max", time_max, &b_time_max);
   fChain->SetBranchAddress("chi2_max", chi2_max, &b_chi2_max);
   fChain->SetBranchAddress("charge_tot", charge_tot, &b_charge_tot);
   fChain->SetBranchAddress("charge_sig", charge_sig, &b_charge_sig);
   fChain->SetBranchAddress("fit_ampl", fit_ampl, &b_fit_ampl);
   fChain->SetBranchAddress("fit_time", fit_time, &b_fit_time);
   fChain->SetBranchAddress("fit_chi2", fit_chi2, &b_fit_chi2);
   fChain->SetBranchAddress("calibration", calibration, &b_calibration);
   fChain->SetBranchAddress("X", X, &b_X);
   fChain->SetBranchAddress("Y", Y, &b_Y);


   Notify();
}

Bool_t MyAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MyAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MyAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MyAnalysis_cxx
