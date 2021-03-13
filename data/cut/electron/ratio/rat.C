#define rat_cxx
#include "rat.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void rat::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   auto t=new TCanvas();

   auto h1 = new TH1F("h1","Histo_cut_ele_pos;Invariant in GeV;Number of such events",210,-10,200);
   auto h2 = new TH1F("h2","Ratio",210,-10,200);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;                                                                                                                                                                                                       
     if(nEle<2) continue;

     TLorentzVector v1,v2,v3,v4;
     float mag1,mag2;


     Int_t tag;
     int c=0;
     if(nEle<2) continue;
     for(int i=0; i<nEle; ++i)
       {
	 if(rat::test(i)==true && elePt->at(i)>15)
	   {
	     tag=i;
	     c=c+1;
	     break;
	   }
       }
     for(int k=0; k<nEle; ++k)
       {
	 if(rat::test(k)==true && eleCharge->at(tag)!=eleCharge->at(k))
	   {
	     v1.SetPtEtaPhiE(elePt->at(k),eleEta->at(k),elePhi->at(k),eleEn->at(k));
	     v2.SetPtEtaPhiE(elePt->at(tag),eleEta->at(tag),elePhi->at(tag),eleEn->at(tag));
	     c=c+1;
	     break;
	   }
       }
     if(c==2)
       {
	 mag1=(v1+v2).M();
	 h1->Fill(mag1);
       }
     
 
 	 v3.SetPtEtaPhiE(elePt->at(0),eleEta->at(0),elePhi->at(0),eleEn->at(0));
	 v4.SetPtEtaPhiE(elePt->at(1),eleEta->at(1),elePhi->at(1),eleEn->at(1));
	 mag2=(v3+v4).M();
	 h2->Fill(mag2);
      
   }
   
   auto h3=new TH1F(*h2);
   h3->Divide(h1);
   h3->Draw();
   t->Print("Ratio_no_cut_vs_cut.pdf");
}

