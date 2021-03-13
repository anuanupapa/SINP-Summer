#define Reader2_cxx
#include "Reader2.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include<fstream>
void Reader2::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Reader2.C
//      root> Reader2 t
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
   Int_t c=0; 
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	if (nEle==1){c=c+1;}
   	else if(nEle==2){c=c+2;}
	else if(nEle==3){c=c+3;}
	else if(nEle==4){c=c+4;}
	else if(nEle==5){c=c+5;}
	else if(nEle==6){c=c+6;}
	else if(nEle==7){c=c+7;}
	else if(nEle==8){c=c+8;}
	}
	cout<<c<<endl;
}
