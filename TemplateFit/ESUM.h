//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Aug 25 11:10:47 2017 by ROOT version 6.06/08
// from TTree template_tree/template_tree
// found on file: template_recos_C3_100.root
//////////////////////////////////////////////////////////

#ifndef ESUM_h
#define ESUM_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ESUM {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         hodo_X[2];
   Float_t         hodo_Y[2];
   Float_t         WC_X;
   Float_t         WC_Y;
   Float_t         temp_amp[25];
   Float_t         temp_time[25];
   Float_t         max_time[25];
   Float_t         digiMax[25];
   Float_t         EA_X;
   Float_t         EA_Y;
   UInt_t          run;
   UInt_t          spill;
   UInt_t          event;

   // List of branches
   TBranch        *b_hodo_X;   //!
   TBranch        *b_hodo_Y;   //!
   TBranch        *b_WC_X;   //!
   TBranch        *b_WC_Y;   //!
   TBranch        *b_temp_amp;   //!
   TBranch        *b_temp_time;   //!
   TBranch        *b_max_time;   //!
   TBranch        *b_digiMax;   //!
   TBranch        *b_EA_X;   //!
   TBranch        *b_EA_Y;   //!
   TBranch        *b_run;   //!
   TBranch        *b_spill;   //!
   TBranch        *b_event;   //!

   ESUM(TTree *tree=0);
   virtual ~ESUM();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ESUM_cxx
ESUM::ESUM(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("template_recos_C3_50.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("template_recos_C3_50.root");
      }
      f->GetObject("template_tree",tree);

   }
   Init(tree);
}

ESUM::~ESUM()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ESUM::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ESUM::LoadTree(Long64_t entry)
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

void ESUM::Init(TTree *tree)
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

   fChain->SetBranchAddress("hodo_X", hodo_X, &b_hodo_X);
   fChain->SetBranchAddress("hodo_Y", hodo_Y, &b_hodo_Y);
   fChain->SetBranchAddress("WC_X", &WC_X, &b_WC_X);
   fChain->SetBranchAddress("WC_Y", &WC_Y, &b_WC_Y);
   fChain->SetBranchAddress("temp_amp", temp_amp, &b_temp_amp);
   fChain->SetBranchAddress("temp_time", temp_time, &b_temp_time);
   fChain->SetBranchAddress("max_time", max_time, &b_max_time);
   fChain->SetBranchAddress("digiMax", digiMax, &b_digiMax);
   fChain->SetBranchAddress("EA_X", &EA_X, &b_EA_X);
   fChain->SetBranchAddress("EA_Y", &EA_Y, &b_EA_Y);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("spill", &spill, &b_spill);
   fChain->SetBranchAddress("event", &event, &b_event);
   Notify();
}

Bool_t ESUM::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ESUM::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ESUM::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ESUM_cxx
