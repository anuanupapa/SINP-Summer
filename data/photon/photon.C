#define photon_cxx
#include "photon.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
float c=3*pow(10,8);
void photon::Loop()
{
//   In a ROOT session, you can do:
//      root> .L photon.C
//      root> photon t
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

   Long64_t nentries = fChain->GetEntriesFast();
   auto h= new TH1F("h","Individual Photons",500,0,500);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb; 
     // if (Cut(ientry) < 0) continue;
      Float_t mag;
      if(nPho<1) continue;
      for(int i=0; i<nPho; ++i)
	{
	  Float_t Pt = float(phoEt->at(i))/c;
	  TLorentzVector v;
	  v.SetPtEtaPhiE(Pt,phoEta->at(i),phoPhi->at(i),phoE->at(i));
	  mag=v.M();
	  h->Fill(mag);
	}
   }
   h->Draw();
}
