#define cut_study_cxx
#include "cut_study.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void cut_study::Loop()
{
   if (fChain == 0) return;
   auto t = new TCanvas();
   t->Divide(1,2,0,0);
   Long64_t nentries = fChain->GetEntriesFast();
   auto h1 = new TH1F("h1","barrel",100,0,0.1);
   auto h2 = new TH1F("h2","endcap",100,0,0.1);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     if(nEle>1)
       {
	 for (Int_t i=0; i<nEle; ++i)
	   {
	     if(cut_study::test(i)==true)
	       {
	
		 if(fabs(eleSCEta->at(i))<1.479)
		   {
		     h1->Fill(eleSigmaIEtaIEtaFull5x5->at(i));
		   }
		 if(abs(eleSCEta->at(i))>1.479 && abs(eleSCEta->at(i))<2.4)
		   {
		     h2->Fill(eleSigmaIEtaIEtaFull5x5->at(i));
		   }
	       }
	   }
       }
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
   }
   t->cd(1);
   h1->Draw();
   
   t->cd(2);
   h2->Draw();


   t->Print("eleSigmaIEtaIEtaFull5x5_tightelectrons.pdf");

}
