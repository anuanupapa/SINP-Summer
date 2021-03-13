#define rat_cxx
#include "rat.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLorentzVector.h>
void rat::Loop()
{
   if (fChain == 0) return;
   auto c = new TCanvas();
   auto f = new TF1("f1","[0]",0,150);
   Long64_t nentries = fChain->GetEntriesFast();
   auto h1 = new TH1F("h1","ratio",150,0,150);
   auto h2 = new TH1F("h2","muon",150,0,150);
   Long64_t nbytes = 0, nb = 0;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     TLorentzVector v1,v2,v3,v4;
     Float_t mag1,mag2;
     // if (Cut(ientry) < 0) continue;                            
     if(nMu>=2)
       {
	   v1.SetPtEtaPhiE(muPt->at(0),muEta->at(0),muPhi->at(0),muEn->at(0));
	   v2.SetPtEtaPhiE(muPt->at(1),muEta->at(1),muPhi->at(1),muEn->at(1));
	   mag1 = (v1+v2).M();
	   h1->Fill(mag1);
       }
     if(nEle>=2)
       {
	   v3.SetPtEtaPhiE(elePt->at(0),eleEta->at(0),elePhi->at(0),eleEn->at(0));
	   v4.SetPtEtaPhiE(elePt->at(1),eleEta->at(1),elePhi->at(1),eleEn->at(1));
	   mag2 = (v3+v4).M();
	   h2->Fill(mag2);
       }
   }
   auto h3 = new TH1F(*h1);
   h3->Divide(h2);
   h3->Draw();
   h3->Fit("f1","","",80,100);
   f->Draw("Same");
   c->Print("Ratio_between_mu_ele_ZBoson.pdf");
}
