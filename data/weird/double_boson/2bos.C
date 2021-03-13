#define 2bos_cxx
#include "2bos.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void 2bos::Loop()
{
  if (fChain == 0) return;
  auto h1 = new TH1F("h","Z_Boson_di",200,0,200);
  Long64_t nentries = fChain->GetEntriesFast();
  auto t = new TCanvas();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    Float_t mag=0;
    Float_t mag1=0;
    Float_t mag2=0;
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(nMu>3)
      {
        Int_t q1=0;
        TLorentzVector v1,v2,v3,v4;
        Int_t c1=0;
        Int_t u=0;
        for(u=0; u<nMu; ++u)
          {
            if(muPt->at(u)>25)
              {
                c1=c1+1;
                v1.SetPtEtaPhiE(muPt->at(u),muEta->at(u),muPhi->at(u),muEn->at(u));
                q1 = muCharge->at(u);
                break;
              }
          }
        Int_t p;
        for(int i=u; i<nMu; ++i)
          {
            if(muCharge->at(i)!=q1 && muPt->at(i)>25)
              {
                v2.SetPtEtaPhiE(muPt->at(i),muEta->at(i),muPhi->at(i),muEn->at(i));
                c1=c1+1;
                p=i;
                break;
              }
          }
        if(c1==2)
          {
            mag1=(v1+v2).M();
          }

        Int_t c2=0;
        Int_t q2=0;
        Int_t w=0;
        if(mag1>90 && mag1<95)
          {
            for(int j=0; j<nEle; ++j)
              {
                if(elePt->at(j)>25)
                  {
                    c2=c2+1;
                    v3.SetPtEtaPhiE(muPt->at(j),muEta->at(j),muPhi->at(j),muEn->at(j));
                    q2=muCharge->at(j);
                    w=j;
                    break;
                  }
              }
            for(int t=w; t<nEle; ++t)
              {
                if(eleCharge->at(t)!=q2 && muPt->at(t)>25)
                  {
                    c2=c2+1;
                    v4.SetPtEtaPhiE(muPt->at(t),muEta->at(t),muPhi->at(t),muEn->at(t));
                    break;
                  }
              }
            if(c2==2)
              {
                mag2=(v3+v4).M();
              }
          }
        if(mag2>90 && mag2<95)
          {
            mag=(v1+v2+v3+v4).M();
            h1->Fill(mag);
          }
      }
  }
  h1->Draw();
  t->Print("diboson_only_muon.pdf");
}
