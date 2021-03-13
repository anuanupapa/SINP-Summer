#define each_cxx
#include "each.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void each::Loop()
{
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  auto t=new TCanvas();
  auto h1 = new TH1F("h1",";Invariant in GeV;Number of such events",210,-10,200);
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if(nEle<2) continue;
    int m=0,r=0;
    TLorentzVector v1,v2;
    float mag1;
    int qset=0;

    for(Int_t i=0; i<nEle; ++i)
      {

        if(each::test(i)==true && eleCharge->at(i)!=qset)
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
        else if(each::test(i)==true && eleCharge->at(i)!=qset)
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
  /*    Double_t mybw(Double_t* x, Double_t* par) ;
    int   division = h1->GetNbinsX();
    float massMIN = h1->GetBinLowEdge(1);
    float massMAX = h1->GetBinLowEdge(division+1);
    //  float BIN_SIZE = h->GetBinWidth(1);
    
    TF1 *func = new TF1("mybw",mybw,massMIN, massMAX,3);
    func->SetParameter(0,300.0);   func->SetParName(0,"const");
    func->SetParameter(2,-90.0);     func->SetParName(1,"sigma");
    func->SetParameter(1,4.0);    func->SetParName(2,"mean");
    
    h1->Fit(func);
    func->Draw("Same");*/
  t->Print("ZBosons_eledPhiAtVtx.pdf");

}
Double_t mybw(Double_t* x, Double_t* par)
{
    Double_t arg1 = 14.0/22.0;
    Double_t arg2 = par[1]*par[1]*par[2]*par[2];
    Double_t arg3 = ((x[0]*x[0]) - (par[2]*par[2]))*((x[0]*x[0]) - (par[2]*par[2]));
    Double_t arg4 = x[0]*x[0]*x[0]*x[0]*((par[1]*par[1])/(par[2]*par[2]));
    return par[0]*arg1*arg2/(arg3 + arg4);
}

