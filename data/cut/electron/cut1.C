#define cut1_cxx
#include "cut1.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void cut1::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  auto t=new TCanvas();
  auto h1 = new TH1F("h1","Histo_cut_ele_pos;Invariant in GeV;Number of such events",210,-10,200);
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;                                                                                                                                                                                                                                                        \
                                                                                                                                                                                                                                                                                              
    if(nEle<2) continue;
    int m=0,r=0;
    TLorentzVector v1,v2;
    float mag1;
    int qset=0;

    for(int i=0; i<nEle; ++i)
      {

        if(fabs(eleSCEta->at(i))<1.479 && eleHoverE->at(i)<0.0414 && eleSigmaIEtaIEtaFull5x5->at(i)<0.00998 &&  eleMissHits->at(i)<=1 && eleConvVeto->at(i)==1 && elePt->at(i)>10 && fabs(eleEoverPInv->at(i))<0.0129 && fabs(eledEtaAtVtx->at(i))<0.00308 && fabs(eledPhiAtVtx->at(i))<0.0816 && eleCharge->at(i)!=qset)
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
        else if(1.479 < abs(eleSCEta->at(i))  && abs(eleSCEta->at(i))< 2.4 && eleHoverE->at(i)<0.0641 &&  eleSigmaIEtaIEtaFull5x5->at(i)<0.0292 && eleMissHits->at(i)<=1 &&  eleConvVeto->at(i)==1 && elePt->at(i) && fabs(eleEoverPInv->at(i))<0.0129 && fabs(eledEtaAtVtx->at(i))<0.00605 && fabs(eledPhiAtVtx->at(i))<0.0394 && eleCharge->at(i)!=qset)
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
      mag1=(v1+v2).M();
      h1->Fill(mag1);
    }

  }
  h1->Draw();
  t->Print("ZBosons_cut_pos_ele_allcuts.pdf");

}
