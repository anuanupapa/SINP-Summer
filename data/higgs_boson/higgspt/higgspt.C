#define higgspt_cxx
#include "higgspt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>

void higgspt::Loop()
{
  if (fChain == 0) return;
  auto h = new TH1F("h","higgsboson_3_mom",1100,0,1100);
  Long64_t nentries = fChain->GetEntriesFast();
  auto t = new TCanvas();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    float mag;
    float mag1,mag2;
    Int_t q=0;
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;                                                                                                                                                                                                                                                                                                                              
    if(nMu<4) continue;
      
	Int_t u;
	TLorentzVector v1,v2,v3,v4;
	int c1=0;
	for(u=0; u<nMu; ++u)
	  {
	    if(muEn->at(u)>30)
	      {
		v1.SetPtEtaPhiE(muPt->at(0),muEta->at(0),muPhi->at(0),muEn->at(0));
		q = muCharge->at(u);
	      }
	  }
	for(int i=1; i<nMu; ++i)
	  {
	    if(muCharge->at(i)==q && muEn->at(i)>30)
	      {
		v2.SetPtEtaPhiE(muPt->at(i),muEta->at(i),muPhi->at(i),muEn->at(i));
		c1=c1+1;
		break;
	      }
	  }

	int w=0;
	for(int i=0; i<nMu; ++i )
	  {
	    if(q!=muCharge->at(i) && w==0 && muEn->at(i)>30)
	      {
		w=1;
		v3.SetPtEtaPhiE(muPt->at(i),muEta->at(i),muPhi->at(i),muEn->at(i));
		c1=c1+1;
	      }
	    if(q!=muCharge->at(i) && w==1 && muEn->at(i)>30)
	      {
		w=w+1;
		c1=c1+1;
		v4.SetPtEtaPhiE(muPt->at(i),muEta->at(i),muPhi->at(i),muEn->at(i));
		break;
	      }
	  }
	/*if(c1==3)
	  {
	    mag=(v1+v2+v3+v4).M();
	    h->Fill(mag);
	    }*/
	if(c1==3)
	  {
	    Double_t z = (v1+v2+v3+v4).Pz();
	    Double_t y = (v1+v2+v3+v4).Py();
	    Double_t x = (v1+v2+v3+v4).Px();
	    Double_t tot = pow(((x*x)+(y*y)+(z*z)),0.5);
	    h->Fill(tot);
	  }
	
  }
  h->Draw();
  t->Print("HiggsBoson_3mom.pdf");
}


