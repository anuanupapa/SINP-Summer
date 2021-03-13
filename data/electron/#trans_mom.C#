#define trans_mom_cxx
#include "trans_mom.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void trans_mom::Loop()
{
   if (fChain == 0) return;
   
   Long64_t nentries = fChain->GetEntriesFast();
   
   //TLorentzVector v1,v2,v3;
   //float mag = 0;
   auto c = new TCanvas();
   auto h = new TH1F("h","Z Boson using electrons;Energy GeV;Number of collisions",160,-10,150);
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if (nEle < 2) continue;
     cout<<"Event No.: "<<jentry<<endl;;     
     TLorentzVector v1,v2 ;
     float mag = 0;
    
     v1.SetPtEtaPhiE(elePt->at(0),eleEta->at(0),elePhi->at(0),eleEn->at(0));
     v2.SetPtEtaPhiE(elePt->at(1),eleEta->at(1),elePhi->at(1),eleEn->at(1));
     
     mag = (v1+v2).M();
     h->Fill(mag);
     //     file2<<mag<<endl;
     //     cout<<mag<<endl;
     //     file<<endl;
 
     //     }
   }
   h->Draw();
c->Print("c.pdf");
}
