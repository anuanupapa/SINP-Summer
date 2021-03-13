#define bosonpt_cxx
#include "bosonpt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

using namespace std;

void bosonpt::Loop()
{
   if (fChain == 0) return;
   auto c = new TCanvas();
   auto h = new TH1F("h","ZBoson_Z_location",1200,-600,600);
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(nEle<2) continue;
      if(nEle<2) continue;
      int m=0,r=0;
      TLorentzVector v1,v2;
      float mag1;
      int qset=0;

      for(int i=0; i<nEle; ++i)
        {

	  if(fabs(eleSCEta->at(i))<1.479 && eleHoverE->at(i)<0.0414 && eleSigmaIEtaIEtaFull5x5->at(i)<0.00998 &&  eleMissHits->at(i)<=1 && eleConvVeto->at(i)==1 && elePt->at(i)>10 && eleCharge->at(i)!=qset)
            {
              if(m==0)
                {
                  v1.SetPtEtaPhiE(elePt->at(i),eleEta->at(i),elePhi->at(i),eleEn->at(i));
                  m=m+1;
                  qset=eleCharge->at(i);
                  r=r+1;
                }
              else {
                v2.SetPtEtaPhiE(elePt->at(i),eleEta->at(i),elePhi->at(i),eleEn->at(i));
                r=r+1;
                break;
              }
            }
	  else if(1.479 < abs(eleSCEta->at(i))  && abs(eleSCEta->at(i))< 2.4 && eleHoverE->at(i)<0.0641 &&  eleSigmaIEtaIEtaFull5x5->at(i)<0.0292 && eleMissHits->at(i)<=1 &&  eleConvVeto->at(i)==1 && elePt->at(i) && eleCharge->at(i)!=qset)
            {
              if(m==0)
                {
                  v1.SetPtEtaPhiE(elePt->at(i),eleEta->at(i),elePhi->at(i),eleEn->at(i));
                  r=r+1;
                  qset=eleCharge->at(i);
                  m=m+1;
                }
              else  {
                v2.SetPtEtaPhiE(elePt->at(i),eleEta->at(i),elePhi->at(i),eleEn->at(i));
                r=r+1;
                break;
              }
            }
	  
        }
      if(r==2){
	mag1 = (v1+v2).M();
	if(mag1>75 && mag1<105)
	  {
	    /*
	    Double_t y = v1.Py()+v2.Py();
	    Double_t x = (v1+v2).Px();
	    Double_t z = (v1+v2).Pz();
	    Double_t tot = pow(((x*x)+(y*y)+(z*z)),0.5);
	    */
	    Double_t tot = (v1+v2).Z();
	    h->Fill(tot);
	   
	  }
      }

   }
   h->Draw();
  c->Print("ZBoson_Z_location.pdf");
}
