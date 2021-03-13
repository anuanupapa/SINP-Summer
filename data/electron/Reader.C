#define Reader_cxx
#include "Reader.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Reader::Loop()
{

   if (fChain == 0) return;
   Int_t pos=0 ,ele=0;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; nentries/2;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

	for (vector<int>::iterator it=eleCharge->begin(); it!=eleCharge->end(); ++it)
	{
		cout<<*it<<" | ";
		if (*it==-1){ele=ele+1;}
		else {pos=pos+1;}
//		v.push_back(*it);
	}
//	for (vector<float>::iterator it=v.begin(); it!=v.end(); ++it)
//	{
//		cout<<*it<<" | ";
//	}
	cout<<endl;
	}
	cout<<"pos="<<pos<<" ele="<<ele<<endl;
}
