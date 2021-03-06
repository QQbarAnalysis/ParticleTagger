#define kaontagger_cxx
#include "kaontagger.h"
#include "TPad.h"
#include "TFile.h"

void kaontagger::Initialize() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetMarkerSize(0.1);


  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.33,1.667,2,2.5,3,4,5,6,7,8,9,10,13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  Float_t bins_costheta[200];
  bins_costheta[0]=0;
  for(int i=1;i<200;i++) bins_costheta[i]=bins_costheta[i-1]+1/200.;
  Int_t nbinnum_costheta=199;

  n_kaon=0;
  n_pion=0;
  n_proton=0;
  n_electron=0;
  n_muon=0;
  n_other=0;

  cont_pi=0;
  cont_p=0;
  cont_e=0;
  cont_mu=0;

  cont_DST_pi=0;
  cont_DST_p=0;
  cont_DST_e=0;
  cont_DST_mu=0;
  
  kaon_dEdx_truth = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_truth = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_truth = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  electron_dEdx_truth = new TH2F("electron_dEdx_truth","electron_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  muon_dEdx_truth = new TH2F("muon_dEdx_truth","muon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  other_dEdx_truth = new TH2F("other_dEdx_truth","other_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  //to fill with the new ID algorithm
  kaon_dEdx_id = new TH2F("kaon_dEdx_id","kaon_dEdx_id",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_id = new TH2F("proton_dEdx_id","proton_dEdx_id",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_id = new TH2F("pion_dEdx_id","pion_dEdx_id",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_good = new TH2F("kaon_dEdx_good","kaon_dEdx_good",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_good = new TH2F("proton_dEdx_good","proton_dEdx_good",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_good = new TH2F("pion_dEdx_good","pion_dEdx_good",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_bad = new TH2F("kaon_dEdx_bad","kaon_dEdx_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_bad = new TH2F("proton_dEdx_bad","proton_dEdx_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_bad = new TH2F("pion_dEdx_bad","pion_dEdx_bad",nbinnum_p,bins_p,nbinnumy,binsy);


  //to fill with the ID algorithm in the DST (dEdxID)
  kaon_dEdx_ID_DST_id = new TH2F("kaon_dEdx_ID_DST_id","kaon_dEdx_ID_DST_id",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_ID_DST_id = new TH2F("proton_dEdx_ID_DST_id","proton_dEdx_ID_DST_id",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_ID_DST_id = new TH2F("pion_dEdx_ID_DST_id","pion_dEdx_ID_DST_id",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_ID_DST_good = new TH2F("kaon_dEdx_ID_DST_good","kaon_dEdx_ID_DST_good",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_ID_DST_good = new TH2F("proton_dEdx_ID_DST_good","proton_dEdx_ID_DST_good",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_ID_DST_good = new TH2F("pion_dEdx_ID_DST_good","pion_dEdx_ID_DST_good",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_ID_DST_bad = new TH2F("kaon_dEdx_ID_DST_bad","kaon_dEdx_ID_DST_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_ID_DST_bad = new TH2F("proton_dEdx_ID_DST_bad","proton_dEdx_ID_DST_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_ID_DST_bad = new TH2F("pion_dEdx_ID_DST_bad","pion_dEdx_ID_DST_bad",nbinnum_p,bins_p,nbinnumy,binsy);


  kaon_likelihood_ID_DST_good = new TH1F("kaon_likelihood_ID_DST_good","kaon_likelihood_ID_DST_good",100,-100,100);
  proton_likelihood_ID_DST_good = new TH1F("proton_likelihood_ID_DST_good","proton_likelihood_ID_DST_good",100,-100,100);
  pion_likelihood_ID_DST_good = new TH1F("pion_likelihood_ID_DST_good","pion_likelihood_ID_DST_good",100,-100,100);

  kaon_likelihood_ID_DST_bad = new TH1F("kaon_likelihood_ID_DST_bad","kaon_likelihood_ID_DST_bad",100,-100,100);
  proton_likelihood_ID_DST_bad = new TH1F("proton_likelihood_ID_DST_bad","proton_likelihood_ID_DST_bad",100,-100,100);
  pion_likelihood_ID_DST_bad = new TH1F("pion_likelihood_ID_DST_bad","pion_likelihood_ID_DST_bad",100,-100,100);
  
  //-----------------
  binsy[0]=0.05;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;

  kaon_dEdx_corrected_truth = new TH2F("kaon_dEdx_corrected_truth","kaon_dEdx_corrected_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_corrected_truth = new TH2F("proton_dEdx_corrected_truth","proton_dEdx_corrected_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_corrected_truth = new TH2F("pion_dEdx_corrected_truth","pion_dEdx_corrected_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  

}

void kaontagger::Fill_histos_new_ID(int i, bool combined=false) {

  
      bool isproton = false;
      bool ispion = false;
      bool iselectron = false;
      bool iskaon = false;

      if(combined==true) {
	//proton
	if( (  momentum[i]<2 && type_algo3[i]==2212)  || (type_algo4[i]==2212 && momentum[i]>2 ) )  isproton=true;
	//pion
	if( (type_algo0[i]==211 ) || (momentum[i]>0.8 && type_algo4[i]==211)   ) ispion=true;
	//electron
	if( (type_algo0[i]==11 || type_algo0[i]==211) && dEdx[i]*1e6>0.22  )  iselectron=true;
	//kaon
	if( (momentum[i]>2 && type_algo4[i]==321 )  ||  (momentum[i]<2 && type_algo3[i]==321) ) iskaon=true;
	if(dEdx[i]*1e6>0.20 && momentum[i]<5 ) iskaon=false;
      } else {
	if( (momentum[i]>2 && type_algo4[i]==321 ) ) iskaon=true;
      }
	
    
      if(ispion==true || isproton==true || iselectron==true) iskaon=false;

      
      if(ispion) {
	pion_dEdx_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if(isproton) {
	proton_dEdx_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if( iskaon==true ) {
	kaon_dEdx_id->Fill(momentum[i],dEdx[i]*1e6);
	if(trueType[i]==2212) cont_p++;
	else if(trueType[i]==211) cont_pi++;
	else if(trueType[i]==11) cont_e++;
	else if(trueType[i]==13) cont_mu++;
      }
      
      if(isproton && trueType[i]==2212) proton_dEdx_good->Fill(momentum[i],dEdx[i]*1e6);
      if(isproton && trueType[i]!=2212) proton_dEdx_bad->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]==211) pion_dEdx_good->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]!=211) pion_dEdx_bad->Fill(momentum[i],dEdx[i]*1e6);

      if(iskaon && trueType[i]==321) kaon_dEdx_good->Fill(momentum[i],dEdx[i]*1e6);
      if(iskaon && trueType[i]!=321) kaon_dEdx_bad->Fill(momentum[i],dEdx[i]*1e6);

}


void kaontagger::Fill_histos_likelihood_DST_ID(int i) {

  //only for algo==0 (LikelihoodPID)
  bool isproton = false;
  bool ispion = false;
  bool iselectron = false;
  bool iskaon = false;
  
  if( type_algo0[i]==2212 )  isproton=true;
  if( type_algo0[i]==211  ) ispion=true;
  if( type_algo0[i]==11 )  iselectron=true;
  if( type_algo0[i]==321 ) iskaon=true;
  
  if(ispion==true || isproton==true || iselectron==true) iskaon=false;
  
  
  if(isproton && trueType[i]==2212) proton_likelihood_ID_DST_good->Fill(likelihood_algo0[i]);
  if(isproton && trueType[i]!=2212) proton_likelihood_ID_DST_bad->Fill(likelihood_algo0[i]);
  
  if(ispion && trueType[i]==211) pion_likelihood_ID_DST_good->Fill(likelihood_algo0[i]);
  if(ispion && trueType[i]!=211) pion_likelihood_ID_DST_bad->Fill(likelihood_algo0[i]);
  
  if(iskaon && trueType[i]==321) kaon_likelihood_ID_DST_good->Fill(likelihood_algo0[i]);
  if(iskaon && trueType[i]!=321) kaon_likelihood_ID_DST_bad->Fill(likelihood_algo0[i]);
  
}


void kaontagger::Fill_histos_DST_ID(int i,int algo) {

  
      bool isproton = false;
      bool ispion = false;
      bool iselectron = false;
      bool iskaon = false;

      //algorithms are
      //0 LikelihoodPID
      //1 LowMomentumID
      //2 BasicVariablePID
      //3 dEdxPID

      if(algo==0) {
	if( type_algo0[i]==2212 )  isproton=true;
	if( type_algo0[i]==211  ) ispion=true;
	if( type_algo0[i]==11 )  iselectron=true;
	if( type_algo0[i]==321 ) iskaon=true;
      }
      if(algo==1) {
	if( type_algo1[i]==2212 )  isproton=true;
	if( type_algo1[i]==211  ) ispion=true;
	if( type_algo1[i]==11 )  iselectron=true;
	if( type_algo1[i]==321 ) iskaon=true;
      }
      if(algo==2) {
	if( type_algo2[i]==2212 )  isproton=true;
	if( type_algo2[i]==211  ) ispion=true;
	if( type_algo2[i]==11 )  iselectron=true;
	if( type_algo2[i]==321 ) iskaon=true;
      }
      
      if(algo==3) {
	if( type_algo3[i]==2212 )  isproton=true;
	if( type_algo3[i]==211  ) ispion=true;
	if( type_algo3[i]==11 )  iselectron=true;
	if( type_algo3[i]==321 ) iskaon=true;
      }
   
      if(ispion==true || isproton==true || iselectron==true) iskaon=false;

      if(ispion) {
	pion_dEdx_ID_DST_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if(isproton) {
	proton_dEdx_ID_DST_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if( iskaon==true ) {
	kaon_dEdx_ID_DST_id->Fill(momentum[i],dEdx[i]*1e6);
	if(trueType[i]==2212) cont_DST_p++;
	else if(trueType[i]==211) cont_DST_pi++;
	else if(trueType[i]==11) cont_DST_e++;
	else if(trueType[i]==13) cont_DST_mu++;
      }
      
      if(isproton && trueType[i]==2212) proton_dEdx_ID_DST_good->Fill(momentum[i],dEdx[i]*1e6);
      if(isproton && trueType[i]!=2212) proton_dEdx_ID_DST_bad->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]==211) pion_dEdx_ID_DST_good->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]!=211) pion_dEdx_ID_DST_bad->Fill(momentum[i],dEdx[i]*1e6);

      if(iskaon && trueType[i]==321) kaon_dEdx_ID_DST_good->Fill(momentum[i],dEdx[i]*1e6);
      if(iskaon && trueType[i]!=321) kaon_dEdx_ID_DST_bad->Fill(momentum[i],dEdx[i]*1e6);

}

  
void kaontagger::Selection(bool secondary=false, int algo=3, bool combined=false)
{

  Initialize();
  if (fChain == 0) return;
   
  Long64_t nentries = fChain->GetEntriesFast();
  //  nentries=1000;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    for(int i=0;i<nParticles;i++) {

      bool selection= (vtxType[i]==2  && abs(costheta[i])<0.95);
      if (secondary==false) selection=true;
      if (selection == false) continue;


      if(trueType[i]==321) {
       	kaon_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
	kaon_dEdx_corrected_truth->Fill(momentum[i],dEdx[i]*1e6-0.019*std::log(momentum[i]));
       	n_kaon++;
      }
      if(trueType[i]==2212) {
       	proton_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
	proton_dEdx_corrected_truth->Fill(momentum[i],dEdx[i]*1e6-0.019*std::log(momentum[i]));
	n_proton++;
      }
      if(trueType[i]==211) {
       	pion_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
	pion_dEdx_corrected_truth->Fill(momentum[i],dEdx[i]*1e6-0.019*std::log(momentum[i]));
       	n_pion++;
      }
      if(trueType[i]==13) {
       	muon_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_muon++;
      }
      if(trueType[i]==11) {
       	electron_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_electron++;
      }
      if(trueType[i]==11) {
       	other_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_other++;
      }

      Fill_histos_DST_ID(i,algo);
      if(algo==0) Fill_histos_likelihood_DST_ID(i);
      Fill_histos_new_ID(i,combined);
	  
    }//for
    // }
    // if (Cut(ientry) < 0) continue;
  }

  std::cout<<"  "<<std::endl;
  std::cout<<"  ############### algorithm "<<algo<<" DST ###############  "<<std::endl;
  std::cout<<"Simulated kaons: "<<n_kaon<<", pions: "<<n_pion<<", protons: "<<n_proton<<", electrons: "<<n_electron<<", muons: "<<n_muon<<", other: "<<n_other<<std::endl;
  std::cout<<"Reco, kaons: "<<kaon_dEdx_ID_DST_id->GetEntries()<<", pions: "<<pion_dEdx_ID_DST_id->GetEntries()<<", protons: "<<proton_dEdx_ID_DST_id->GetEntries()<<std::endl;
  std::cout<<"Well Reco, kaons: "<<kaon_dEdx_ID_DST_good->GetEntries()<<", pions: "<<pion_dEdx_ID_DST_good->GetEntries()<<", protons: "<<proton_dEdx_ID_DST_good->GetEntries()<<std::endl;
  std::cout<<"Contamination in kaons id, pions:: "<<cont_DST_pi<<", protons: "<<cont_DST_p<<", electrons: "<<cont_DST_e<<", muons: "<<cont_DST_mu<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;
  std::cout<<"KAON ID: eff="<<kaon_dEdx_ID_DST_id->GetEntries()/n_kaon<<"  purity="<<kaon_dEdx_ID_DST_good->GetEntries()/kaon_dEdx_ID_DST_id->GetEntries()<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;

  std::cout<<"  "<<std::endl;
  if(combined==true) std::cout<<"  ############### KaonTagger IF combined with the old ones for pion and protons ###############  "<<std::endl;
  else std::cout<<"  ############### KaonTagger  ###############  "<<std::endl;
  std::cout<<"Simulated kaons: "<<n_kaon<<", pions: "<<n_pion<<", protons: "<<n_proton<<", electrons: "<<n_electron<<", muons: "<<n_muon<<", other: "<<n_other<<std::endl;
  std::cout<<"Reco, kaons: "<<kaon_dEdx_id->GetEntries()<<", pions: "<<pion_dEdx_id->GetEntries()<<", protons: "<<proton_dEdx_id->GetEntries()<<std::endl;
  std::cout<<"Well Reco, kaons: "<<kaon_dEdx_good->GetEntries()<<", pions: "<<pion_dEdx_good->GetEntries()<<", protons: "<<proton_dEdx_good->GetEntries()<<std::endl;
  std::cout<<"Contamination in kaons id, pions:: "<<cont_pi<<", protons: "<<cont_p<<", electrons: "<<cont_e<<", muons: "<<cont_mu<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;
  std::cout<<"KAON ID: eff ="<<kaon_dEdx_id->GetEntries()/n_kaon<<"  purity="<<kaon_dEdx_good->GetEntries()/kaon_dEdx_id->GetEntries()<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;

  //Plots(algo);
  //PlotsCorrected();
  PlotsProjection();
  //if(algo==0) PlotsLikelihood();
  //SimplePlot(algo);
}

void kaontagger::PlotsLikelihood() {

  TString title = "LikelihoodPID";

  gStyle->SetOptStat(0);
  
  TCanvas* c_Likelihood_truth = new TCanvas("c_Likelihood_new_vs_"+title,"c_Likelihood_new_vs_"+title,1800,600);
  c_Likelihood_truth->Divide(3,1);
  c_Likelihood_truth->cd(1);
  pion_likelihood_ID_DST_good->SetMarkerColor(4);
  pion_likelihood_ID_DST_good->SetLineColor(4);
  pion_likelihood_ID_DST_good->SetTitle("Well identified");
  pion_likelihood_ID_DST_good->GetXaxis()->SetTitle("likelihood value");
  pion_likelihood_ID_DST_good->Draw("");

  kaon_likelihood_ID_DST_good->SetMarkerColor(2);
  kaon_likelihood_ID_DST_good->SetLineColor(2);
  kaon_likelihood_ID_DST_good->Draw("same");

  proton_likelihood_ID_DST_good->SetMarkerColor(3);
  proton_likelihood_ID_DST_good->SetLineColor(3);
  proton_likelihood_ID_DST_good->Draw("same");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.85);
  leg->AddEntry(pion_likelihood_ID_DST_good,"pi","lp");
  leg->AddEntry(kaon_likelihood_ID_DST_good,"K","lp");
  leg->AddEntry(proton_likelihood_ID_DST_good,"p","lp");
  leg->Draw();


  c_Likelihood_truth->cd(2);
  kaon_likelihood_ID_DST_bad->SetMarkerColor(2);
  kaon_likelihood_ID_DST_bad->SetLineColor(2);
  kaon_likelihood_ID_DST_bad->SetTitle("Badly identified");
  kaon_likelihood_ID_DST_bad->GetXaxis()->SetTitle("likelihood value");
  kaon_likelihood_ID_DST_bad->SetLineStyle(2);
  kaon_likelihood_ID_DST_bad->Draw("");

  pion_likelihood_ID_DST_bad->SetMarkerColor(4);
  pion_likelihood_ID_DST_bad->SetLineColor(4);
  pion_likelihood_ID_DST_bad->SetLineStyle(2);
  pion_likelihood_ID_DST_bad->Draw("same");

  proton_likelihood_ID_DST_bad->SetMarkerColor(3);
  proton_likelihood_ID_DST_bad->SetLineColor(3);
  proton_likelihood_ID_DST_bad->SetLineStyle(2);
  proton_likelihood_ID_DST_bad->Draw("same");
  
  TLegend *leg2 = new TLegend(0.6,0.55,0.8,0.85);
  leg2->AddEntry(pion_likelihood_ID_DST_good,"pi","lp");
  leg2->AddEntry(kaon_likelihood_ID_DST_good,"K","lp");
  leg2->AddEntry(proton_likelihood_ID_DST_good,"p","lp");
  leg2->Draw();

  c_Likelihood_truth->cd(3);
  kaon_likelihood_ID_DST_bad->SetLineWidth(2);
  kaon_likelihood_ID_DST_good->SetLineWidth(2);
  kaon_likelihood_ID_DST_good->SetTitle("Kaons (normalized)");
  kaon_likelihood_ID_DST_good->GetXaxis()->SetTitle("likelihood value");
  kaon_likelihood_ID_DST_good->DrawNormalized("");
  kaon_likelihood_ID_DST_bad->DrawNormalized("same");

  TLegend *leg3 = new TLegend(0.6,0.55,0.8,0.85);
  leg3->AddEntry(kaon_likelihood_ID_DST_good,"K, well id","lp");
  leg3->AddEntry(kaon_likelihood_ID_DST_bad,"K, bad id","lp");
  leg3->Draw();

  
}


void kaontagger::PlotsProjection() {

  TString title = "Projection";

  gStyle->SetOptStat(0);
  
  TCanvas* c_dEdx_corrected_truth = new TCanvas("c_dEdx_"+title,"c_dEdx_"+title,1000,800);
  c_dEdx_corrected_truth->Divide(3,2);
  c_dEdx_corrected_truth->cd(1);
  gPad->SetLogx();

  pion_dEdx_corrected_truth->SetMarkerColor(4);
  pion_dEdx_corrected_truth->SetLineColor(4);
  pion_dEdx_corrected_truth->SetTitle("#frac{dE}{dx}");
  pion_dEdx_corrected_truth->GetYaxis()->SetTitle("dE/dx#times10^{-6}");
  pion_dEdx_corrected_truth->GetXaxis()->SetTitle("p");
  pion_dEdx_corrected_truth->Draw("");

  kaon_dEdx_corrected_truth->SetMarkerColor(2);
  kaon_dEdx_corrected_truth->SetLineColor(2);
  kaon_dEdx_corrected_truth->Draw("same");

  proton_dEdx_corrected_truth->SetMarkerColor(3);
  proton_dEdx_corrected_truth->SetLineColor(3);
  proton_dEdx_corrected_truth->Draw("same");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.85);
  leg->AddEntry(pion_dEdx_corrected_truth,"pi","lp");
  leg->AddEntry(kaon_dEdx_corrected_truth,"K","lp");
  leg->AddEntry(proton_dEdx_corrected_truth,"p","lp");
  leg->Draw();

  c_dEdx_corrected_truth->cd(2);
  TH1D * proj_pion_1 = pion_dEdx_corrected_truth->ProjectionY("proj_pion_1",11,12);
  TH1D * proj_kaon_1 = kaon_dEdx_corrected_truth->ProjectionY("proj_kaon_1",11,12);
  TH1D * proj_proton_1 = proton_dEdx_corrected_truth->ProjectionY("proj_proton_1",11,12);
  proj_pion_1->SetTitle(" momentum between (1.33,1.67) GeV");
  proj_pion_1->SetLineColor(4);
  proj_pion_1->Draw("histo");
  proj_kaon_1->SetLineColor(2);
  proj_kaon_1->Draw("histosame");
  proj_proton_1->SetLineColor(3);
  proj_proton_1->Draw("histosame");

  c_dEdx_corrected_truth->cd(3);
  TH1D * proj_pion_2 = pion_dEdx_corrected_truth->ProjectionY("proj_pion_2",14,15);
  TH1D * proj_kaon_2 = kaon_dEdx_corrected_truth->ProjectionY("proj_kaon_2",14,15);
  TH1D * proj_proton_2 = proton_dEdx_corrected_truth->ProjectionY("proj_proton_2",14,15);
  proj_pion_2->SetTitle(" momentum between (2,2.5) GeV");
  proj_pion_2->SetLineColor(4);
  proj_pion_2->Draw("histo");
  proj_kaon_2->SetLineColor(2);
  proj_kaon_2->Draw("histosame");
  proj_proton_2->SetLineColor(3);
  proj_proton_2->Draw("histosame");

  c_dEdx_corrected_truth->cd(4);
  TH1D * proj_pion_3 = pion_dEdx_corrected_truth->ProjectionY("proj_pion_3",18,19);
  TH1D * proj_kaon_3 = kaon_dEdx_corrected_truth->ProjectionY("proj_kaon_3",18,19);
  TH1D * proj_proton_3 = proton_dEdx_corrected_truth->ProjectionY("proj_proton_3",18,19);
  proj_pion_3->SetTitle(" momentum between (5,6) GeV");
  proj_pion_3->SetLineColor(4);
  proj_pion_3->Draw("histo");
  proj_kaon_3->SetLineColor(2);
  proj_kaon_3->Draw("histosame");
  proj_proton_3->SetLineColor(3);
  proj_proton_3->Draw("histosame");

  c_dEdx_corrected_truth->cd(5);
  TH1D * proj_pion_4 = pion_dEdx_corrected_truth->ProjectionY("proj_pion_4",23,24);
  TH1D * proj_kaon_4 = kaon_dEdx_corrected_truth->ProjectionY("proj_kaon_4",23,24);
  TH1D * proj_proton_4 = proton_dEdx_corrected_truth->ProjectionY("proj_proton_4",23,24);
  proj_pion_4->SetTitle(" momentum between (10,13.33) GeV");
  proj_pion_4->SetLineColor(4);
  proj_pion_4->Draw("histo");
  proj_kaon_4->SetLineColor(2);
  proj_kaon_4->Draw("histosame");
  proj_proton_4->SetLineColor(3);
  proj_proton_4->Draw("histosame");

  c_dEdx_corrected_truth->cd(6);
  TH1D * proj_pion_5 = pion_dEdx_corrected_truth->ProjectionY("proj_pion_5",26,27);
  TH1D * proj_kaon_5 = kaon_dEdx_corrected_truth->ProjectionY("proj_kaon_5",26,27);
  TH1D * proj_proton_5 = proton_dEdx_corrected_truth->ProjectionY("proj_proton_5",26,27);
  proj_pion_5->SetTitle(" momentum between (30,40) GeV");
  proj_pion_5->SetLineColor(4);
  proj_pion_5->Draw("histo");
  proj_kaon_5->SetLineColor(2);
  proj_kaon_5->Draw("histosame");
  proj_proton_5->SetLineColor(3);
  proj_proton_5->Draw("histosame");


  TCanvas* c_dEdx_corrected_truth2 = new TCanvas("c_dEdx_2_"+title,"c_dEdx_2_"+title,1000,800);
  c_dEdx_corrected_truth2->Divide(3,2);
  c_dEdx_corrected_truth2->cd(1);
  gPad->SetLogx();

  pion_dEdx_corrected_truth->SetMarkerColor(4);
  pion_dEdx_corrected_truth->SetLineColor(4);
  pion_dEdx_corrected_truth->SetTitle("#frac{dE}{dx}");
  pion_dEdx_corrected_truth->GetYaxis()->SetTitle("dE/dx#times10^{-6}");
  pion_dEdx_corrected_truth->GetXaxis()->SetTitle("p");
  pion_dEdx_corrected_truth->Draw("");

  kaon_dEdx_corrected_truth->SetMarkerColor(2);
  kaon_dEdx_corrected_truth->SetLineColor(2);
  kaon_dEdx_corrected_truth->Draw("same");

  proton_dEdx_corrected_truth->SetMarkerColor(3);
  proton_dEdx_corrected_truth->SetLineColor(3);
  proton_dEdx_corrected_truth->Draw("same");

  leg->Draw();

  c_dEdx_corrected_truth2->cd(2);

  TH1F *pull_pion_1 = new TH1F("pull_pion_1","pull_pion_1",30,-5,10);
  TH1F *pull_kaon_1 = new TH1F("pull_kaon_1","pull_kaon_1",30,-5,10);
  TH1F *pull_proton_1 = new TH1F("pull_proton_1","pull_proton_1",30,-5,10);
  for(int i=0; i<proj_kaon_1->GetNbinsX(); i++) {
    if(proj_pion_1->GetBinContent(i+1)>0)   pull_pion_1->Fill((proj_pion_1->GetBinCenter(i+1) - proj_kaon_1->GetMean()) / proj_kaon_1->GetRMS(), proj_pion_1->GetBinContent(i+1));
    if(proj_kaon_1->GetBinContent(i+1)>0)   pull_kaon_1->Fill((proj_kaon_1->GetBinCenter(i+1) - proj_kaon_1->GetMean()) / proj_kaon_1->GetRMS(), proj_kaon_1->GetBinContent(i+1) );
    if(proj_proton_1->GetBinContent(i+1)>0) pull_proton_1->Fill((proj_proton_1->GetBinCenter(i+1) - proj_kaon_1->GetMean()) / proj_kaon_1->GetRMS(), proj_proton_1->GetBinContent(i+1));
  }
  pull_pion_1->SetTitle(" momentum between (1.33,1.67) GeV");
  pull_pion_1->GetXaxis()->SetTitleOffset(1.4);
  pull_pion_1->GetXaxis()->SetTitle("#frac{dedx-<dedx>_{K}}{RMSdedx_{K}}");
  pull_pion_1->SetLineColor(4);
  pull_pion_1->Draw("histo");
  pull_kaon_1->SetLineColor(2);
  pull_kaon_1->Draw("histosame");
  pull_proton_1->SetLineColor(3);
  pull_proton_1->Draw("histosame");

  c_dEdx_corrected_truth2->cd(3);

  TH1F *pull_pion_2 = new TH1F("pull_pion_2","pull_pion_2",30,-5,10);
  TH1F *pull_kaon_2 = new TH1F("pull_kaon_2","pull_kaon_2",30,-5,10);
  TH1F *pull_proton_2 = new TH1F("pull_proton_2","pull_proton_2",30,-5,10);
  for(int i=0; i<proj_kaon_2->GetNbinsX(); i++) {
    if(proj_pion_2->GetBinContent(i+1)>0)   pull_pion_2->Fill((proj_pion_2->GetBinCenter(i+1) - proj_kaon_2->GetMean()) / proj_kaon_2->GetRMS(), proj_pion_2->GetBinContent(i+1));
    if(proj_kaon_2->GetBinContent(i+1)>0)   pull_kaon_2->Fill((proj_kaon_2->GetBinCenter(i+1) - proj_kaon_2->GetMean()) / proj_kaon_2->GetRMS(), proj_kaon_2->GetBinContent(i+1) );
    if(proj_proton_2->GetBinContent(i+1)>0) pull_proton_2->Fill((proj_proton_2->GetBinCenter(i+1) - proj_kaon_2->GetMean()) / proj_kaon_2->GetRMS(), proj_proton_2->GetBinContent(i+1));
  }
  pull_pion_2->SetTitle(" momentum between (2,2.5) GeV");
  pull_pion_2->GetXaxis()->SetTitleOffset(1.4);
  pull_pion_2->GetXaxis()->SetTitle("#frac{dedx-<dedx>_{K}}{RMSdedx_{K}}");
  pull_pion_2->SetLineColor(4);
  pull_pion_2->Draw("histo");
  pull_kaon_2->SetLineColor(2);
  pull_kaon_2->Draw("histosame");
  pull_proton_2->SetLineColor(3);
  pull_proton_2->Draw("histosame");

  c_dEdx_corrected_truth2->cd(4);

  TH1F *pull_pion_3 = new TH1F("pull_pion_3","pull_pion_3",30,-5,10);
  TH1F *pull_kaon_3 = new TH1F("pull_kaon_3","pull_kaon_3",30,-5,10);
  TH1F *pull_proton_3 = new TH1F("pull_proton_3","pull_proton_3",30,-5,10);
  for(int i=0; i<proj_kaon_3->GetNbinsX(); i++) {
    if(proj_pion_3->GetBinContent(i+1)>0)   pull_pion_3->Fill((proj_pion_3->GetBinCenter(i+1) - proj_kaon_3->GetMean()) / proj_kaon_3->GetRMS(), proj_pion_3->GetBinContent(i+1));
    if(proj_kaon_3->GetBinContent(i+1)>0)   pull_kaon_3->Fill((proj_kaon_3->GetBinCenter(i+1) - proj_kaon_3->GetMean()) / proj_kaon_3->GetRMS(), proj_kaon_3->GetBinContent(i+1) );
    if(proj_proton_3->GetBinContent(i+1)>0) pull_proton_3->Fill((proj_proton_3->GetBinCenter(i+1) - proj_kaon_3->GetMean()) / proj_kaon_3->GetRMS(), proj_proton_3->GetBinContent(i+1));
  }
  pull_pion_3->SetTitle(" momentum between (5,6) GeV");
  pull_pion_3->GetXaxis()->SetTitleOffset(1.4);
  pull_pion_3->GetXaxis()->SetTitle("#frac{dedx-<dedx>_{K}}{RMSdedx_{K}}");
  pull_pion_3->SetLineColor(4);
  pull_pion_3->Draw("histo");
  pull_kaon_3->SetLineColor(2);
  pull_kaon_3->Draw("histosame");
  pull_proton_3->SetLineColor(3);
  pull_proton_3->Draw("histosame");

  c_dEdx_corrected_truth2->cd(5);

  TH1F *pull_pion_4 = new TH1F("pull_pion_4","pull_pion_4",30,-5,10);
  TH1F *pull_kaon_4 = new TH1F("pull_kaon_4","pull_kaon_4",30,-5,10);
  TH1F *pull_proton_4 = new TH1F("pull_proton_4","pull_proton_4",30,-5,10);
  for(int i=0; i<proj_kaon_4->GetNbinsX(); i++) {
    if(proj_pion_4->GetBinContent(i+1)>0)   pull_pion_4->Fill((proj_pion_4->GetBinCenter(i+1) - proj_kaon_4->GetMean()) / proj_kaon_4->GetRMS(), proj_pion_4->GetBinContent(i+1));
    if(proj_kaon_4->GetBinContent(i+1)>0)   pull_kaon_4->Fill((proj_kaon_4->GetBinCenter(i+1) - proj_kaon_4->GetMean()) / proj_kaon_4->GetRMS(), proj_kaon_4->GetBinContent(i+1) );
    if(proj_proton_4->GetBinContent(i+1)>0) pull_proton_4->Fill((proj_proton_4->GetBinCenter(i+1) - proj_kaon_4->GetMean()) / proj_kaon_4->GetRMS(), proj_proton_4->GetBinContent(i+1));
  }
  pull_pion_4->SetTitle(" momentum between (10,13.33) GeV");
  pull_pion_4->GetXaxis()->SetTitleOffset(1.4);
  pull_pion_4->GetXaxis()->SetTitle("#frac{dedx-<dedx>_{K}}{RMSdedx_{K}}");
  pull_pion_4->SetLineColor(4);
  pull_pion_4->Draw("histo");
  pull_kaon_4->SetLineColor(2);
  pull_kaon_4->Draw("histosame");
  pull_proton_4->SetLineColor(3);
  pull_proton_4->Draw("histosame");

  c_dEdx_corrected_truth2->cd(6);

  TH1F *pull_pion_5 = new TH1F("pull_pion_5","pull_pion_5",30,-5,10);
  TH1F *pull_kaon_5 = new TH1F("pull_kaon_5","pull_kaon_5",30,-5,10);
  TH1F *pull_proton_5 = new TH1F("pull_proton_5","pull_proton_5",30,-5,10);
  for(int i=0; i<proj_kaon_5->GetNbinsX(); i++) {
    if(proj_pion_5->GetBinContent(i+1)>0)   pull_pion_5->Fill((proj_pion_5->GetBinCenter(i+1) - proj_kaon_5->GetMean()) / proj_kaon_5->GetRMS(), proj_pion_5->GetBinContent(i+1));
    if(proj_kaon_5->GetBinContent(i+1)>0)   pull_kaon_5->Fill((proj_kaon_5->GetBinCenter(i+1) - proj_kaon_5->GetMean()) / proj_kaon_5->GetRMS(), proj_kaon_5->GetBinContent(i+1) );
    if(proj_proton_5->GetBinContent(i+1)>0) pull_proton_5->Fill((proj_proton_5->GetBinCenter(i+1) - proj_kaon_5->GetMean()) / proj_kaon_5->GetRMS(), proj_proton_5->GetBinContent(i+1));
  }
  pull_pion_5->SetTitle(" momentum between (30,40) GeV");
  pull_pion_5->GetXaxis()->SetTitleOffset(1.4);
  pull_pion_5->GetXaxis()->SetTitle("#frac{dedx-<dedx>_{K}}{RMSdedx_{K}}");
  pull_pion_5->SetLineColor(4);
  pull_pion_5->Draw("histo");
  pull_kaon_5->SetLineColor(2);
  pull_kaon_5->Draw("histosame");
  pull_proton_5->SetLineColor(3);
  pull_proton_5->Draw("histosame");


  TCanvas* c_dEdx_corrected_truth3 = new TCanvas("c_dEdx_3_"+title,"c_dEdx_3_"+title,1400,600);
  c_dEdx_corrected_truth3->Divide(3,1);
  c_dEdx_corrected_truth3->cd(1);
  gPad->SetLogx();

  double x[5],y[5],ex[5],ey[5];
  x[0]=(1.3+1.67)/2.;
  x[1]=(2+2.5)/2.;
  x[2]=(5+6)/2.;
  x[3]=(10+13.33)/2.;
  x[4]=(30+40)/2.;
  ex[0]=-(1.3-1.67)/2.;
  ex[1]=-(2-2.5)/2.;
  ex[2]=-(5-6)/2.;
  ex[3]=-(10-13.33)/2.;
  ex[4]=-(30-40)/2.;

  y[0]=proj_pion_1->GetMean();  ey[0]=proj_pion_1->GetRMS();
  y[1]=proj_pion_2->GetMean();  ey[1]=proj_pion_2->GetRMS();
  y[2]=proj_pion_3->GetMean();  ey[2]=proj_pion_3->GetRMS();
  y[3]=proj_pion_4->GetMean();  ey[3]=proj_pion_4->GetRMS();
  y[4]=proj_pion_5->GetMean();  ey[4]=proj_pion_5->GetRMS();
  TGraphErrors * mean_pion = new TGraphErrors(5,x,y,ex,ey);
  
  mean_pion->SetTitle(" Average of the projection");
  mean_pion->GetXaxis()->SetTitle(" p ");
  mean_pion->GetYaxis()->SetTitle(" dEdx ");
  mean_pion->GetYaxis()->SetRangeUser(0.05,0.25);
  mean_pion->SetLineColor(4);
  mean_pion->SetMarkerColor(4);
  mean_pion->Draw("alp");

  y[0]=proj_kaon_1->GetMean();  ey[0]=proj_kaon_1->GetRMS();
  y[1]=proj_kaon_2->GetMean();  ey[1]=proj_kaon_2->GetRMS();
  y[2]=proj_kaon_3->GetMean();  ey[2]=proj_kaon_3->GetRMS();
  y[3]=proj_kaon_4->GetMean();  ey[3]=proj_kaon_4->GetRMS();
  y[4]=proj_kaon_5->GetMean();  ey[4]=proj_kaon_5->GetRMS();
  TGraphErrors * mean_kaon = new TGraphErrors(5,x,y,ex,ey);
  mean_kaon->SetLineColor(2);
  mean_kaon->SetMarkerColor(2);
  mean_kaon->Draw("lp");
   
  y[0]=proj_proton_1->GetMean();  ey[0]=proj_proton_1->GetRMS();
  y[1]=proj_proton_2->GetMean();  ey[1]=proj_proton_2->GetRMS();
  y[2]=proj_proton_3->GetMean();  ey[2]=proj_proton_3->GetRMS();
  y[3]=proj_proton_4->GetMean();  ey[3]=proj_proton_4->GetRMS();
  y[4]=proj_proton_5->GetMean();  ey[4]=proj_proton_5->GetRMS();
  TGraphErrors * mean_proton = new TGraphErrors(5,x,y,ex,ey);
  
  mean_proton->SetLineColor(3);
  mean_proton->SetMarkerColor(3);
  mean_proton->Draw("lp");

  c_dEdx_corrected_truth3->cd(2);
  gPad->SetLogx();

  ey[0]=0; ey[1]=0; ey[2]=0; ey[3]=0; ey[4]=0;
  y[0]=proj_pion_1->GetRMS();
  y[1]=proj_pion_2->GetRMS();
  y[2]=proj_pion_3->GetRMS();
  y[3]=proj_pion_4->GetRMS();
  y[4]=proj_pion_5->GetRMS();
  TGraphErrors * RMS_pion = new TGraphErrors(5,x,y,ex,ey);
  
  RMS_pion->SetTitle(" RMS of the projection");
  RMS_pion->GetXaxis()->SetTitle(" p ");
  RMS_pion->GetYaxis()->SetTitle(" dEdx ");
  RMS_pion->GetYaxis()->SetRangeUser(0.,0.025);
  RMS_pion->SetLineColor(4);
  RMS_pion->SetMarkerColor(4);
  RMS_pion->Draw("alp");

  y[0]=proj_kaon_1->GetRMS();
  y[1]=proj_kaon_2->GetRMS();
  y[2]=proj_kaon_3->GetRMS();
  y[3]=proj_kaon_4->GetRMS();
  y[4]=proj_kaon_5->GetRMS();
  TGraphErrors * RMS_kaon = new TGraphErrors(5,x,y,ex,ey);
  
  RMS_kaon->SetLineColor(2);
  RMS_kaon->SetMarkerColor(2);
  RMS_kaon->Draw("lp");

  y[0]=proj_proton_1->GetRMS();
  y[1]=proj_proton_2->GetRMS();
  y[2]=proj_proton_3->GetRMS();
  y[3]=proj_proton_4->GetRMS();
  y[4]=proj_proton_5->GetRMS();
  TGraphErrors * RMS_proton = new TGraphErrors(5,x,y,ex,ey);
  
  RMS_proton->SetLineColor(3);
  RMS_proton->SetMarkerColor(3);
  RMS_proton->Draw("lp");

  c_dEdx_corrected_truth3->cd(3);
  gPad->SetLogx();

  ey[0]=0; ey[1]=0; ey[2]=0; ey[3]=0; ey[4]=0;
  y[0]=100.*proj_pion_1->GetRMS()/proj_pion_1->GetMean();
  y[1]=100.*proj_pion_2->GetRMS()/proj_pion_2->GetMean();
  y[2]=100.*proj_pion_3->GetRMS()/proj_pion_3->GetMean();
  y[3]=100.*proj_pion_4->GetRMS()/proj_pion_4->GetMean();
  y[4]=100.*proj_pion_5->GetRMS()/proj_pion_5->GetMean();
  TGraphErrors * RMSnorm_pion = new TGraphErrors(5,x,y,ex,ey);
  
  RMSnorm_pion->SetTitle(" RMS of the projection");
  RMSnorm_pion->GetXaxis()->SetTitle(" p ");
  RMSnorm_pion->GetYaxis()->SetTitle(" % of averaged dEdx ");
  RMSnorm_pion->GetYaxis()->SetRangeUser(0,10);
  RMSnorm_pion->SetLineColor(4);
  RMSnorm_pion->SetMarkerColor(4);
  RMSnorm_pion->Draw("alp");

  y[0]=100.*proj_kaon_1->GetRMS()/proj_kaon_1->GetMean();
  y[1]=100.*proj_kaon_2->GetRMS()/proj_kaon_2->GetMean();
  y[2]=100.*proj_kaon_3->GetRMS()/proj_kaon_3->GetMean();
  y[3]=100.*proj_kaon_4->GetRMS()/proj_kaon_4->GetMean();
  y[4]=100.*proj_kaon_5->GetRMS()/proj_kaon_5->GetMean();
  TGraphErrors * RMSnorm_kaon = new TGraphErrors(5,x,y,ex,ey);
  
  RMSnorm_kaon->SetLineColor(2);
  RMSnorm_kaon->SetMarkerColor(2);
  RMSnorm_kaon->Draw("lp");

  y[0]=100.*proj_proton_1->GetRMS()/proj_proton_1->GetMean();
  y[1]=100.*proj_proton_2->GetRMS()/proj_proton_2->GetMean();
  y[2]=100.*proj_proton_3->GetRMS()/proj_proton_3->GetMean();
  y[3]=100.*proj_proton_4->GetRMS()/proj_proton_4->GetMean();
  y[4]=100.*proj_proton_5->GetRMS()/proj_proton_5->GetMean();
  TGraphErrors * RMSnorm_proton = new TGraphErrors(5,x,y,ex,ey);
  
  RMSnorm_proton->SetLineColor(3);
  RMSnorm_proton->SetMarkerColor(3);
  RMSnorm_proton->Draw("lp");

  TFile *file = new TFile("test.root","RECREATE");
  file->cd();
  mean_pion->SetName("mean_pion");
  mean_kaon->SetName("mean_kaon");
  mean_proton->SetName("mean_proton");
  mean_pion->Write();
  mean_kaon->Write();
  mean_proton->Write();

  RMSnorm_pion->SetName("RMSnorm_pion");
  RMSnorm_kaon->SetName("RMSnorm_kaon");
  RMSnorm_proton->SetName("RMSnorm_proton");
  RMSnorm_pion->Write();
  RMSnorm_kaon->Write();
  RMSnorm_proton->Write();

  proj_proton_1->Write();
  proj_proton_2->Write();
  proj_proton_3->Write();
  proj_proton_4->Write();
  proj_proton_5->Write();

  proj_kaon_1->Write();
  proj_kaon_2->Write();
  proj_kaon_3->Write();
  proj_kaon_4->Write();
  proj_kaon_5->Write();

  proj_pion_1->Write();
  proj_pion_2->Write();
  proj_pion_3->Write();
  proj_pion_4->Write();
  proj_pion_5->Write();

  
  file->Close();
  
}


void kaontagger::PlotsCorrected() {

  TString title = "Corrected";

  gStyle->SetOptStat(0);
  
  TCanvas* c_dEdx_corrected_truth = new TCanvas("c_dEdx_"+title,"c_dEdx_"+title,800,800);
  c_dEdx_corrected_truth->cd(1);
  gPad->SetLogx();

  pion_dEdx_corrected_truth->SetMarkerColor(4);
  pion_dEdx_corrected_truth->SetLineColor(4);
  pion_dEdx_corrected_truth->SetTitle("#frac{dE}{dx}= a #times log(p) + b");
  pion_dEdx_corrected_truth->GetYaxis()->SetTitle("dE/dx#times10^{-6}");
  pion_dEdx_corrected_truth->GetXaxis()->SetTitle("p");
  pion_dEdx_corrected_truth->Draw("");

  kaon_dEdx_corrected_truth->SetMarkerColor(2);
  kaon_dEdx_corrected_truth->SetLineColor(2);
  kaon_dEdx_corrected_truth->Draw("same");

  proton_dEdx_corrected_truth->SetMarkerColor(3);
  proton_dEdx_corrected_truth->SetLineColor(3);
  proton_dEdx_corrected_truth->Draw("same");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.85);
  leg->AddEntry(pion_dEdx_corrected_truth,"pi","lp");
  leg->AddEntry(kaon_dEdx_corrected_truth,"K","lp");
  leg->AddEntry(proton_dEdx_corrected_truth,"p","lp");
  leg->Draw();
    
}



void kaontagger::Plots(int algo) {

  TString title = "LikelihoodPID";
  if(algo==1) title = "LowMomMuID";
  if(algo==2) title = "BasicVariablePID";
  if(algo==3) title = "dEdxPID";

  gStyle->SetOptStat(0);
  
  TCanvas* c_dEdx_truth = new TCanvas("c_dEdx_new_vs_"+title,"c_dEdx_new_vs_"+title,2400,1200);
  c_dEdx_truth->Divide(4,2);
  c_dEdx_truth->cd(1);
  gPad->SetLogx();

  pion_dEdx_truth->SetMarkerColor(4);
  pion_dEdx_truth->SetLineColor(4);
  pion_dEdx_truth->SetTitle("Truth");
  pion_dEdx_truth->Draw("");

  other_dEdx_truth->SetMarkerColor(6);
  other_dEdx_truth->SetLineColor(6);
  other_dEdx_truth->Draw("same");

  kaon_dEdx_truth->SetMarkerColor(2);
  kaon_dEdx_truth->SetLineColor(2);
  kaon_dEdx_truth->Draw("same");

   proton_dEdx_truth->SetMarkerColor(3);
  proton_dEdx_truth->SetLineColor(3);
  proton_dEdx_truth->Draw("same");

  electron_dEdx_truth->SetMarkerColor(1);
  electron_dEdx_truth->SetLineColor(1);
  electron_dEdx_truth->Draw("same");

  muon_dEdx_truth->SetMarkerColor(5);
  muon_dEdx_truth->SetLineColor(5);
  muon_dEdx_truth->Draw("same");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.85);
  leg->AddEntry(electron_dEdx_truth,"e","lp");
  leg->AddEntry(pion_dEdx_truth,"pi","lp");
  leg->AddEntry(kaon_dEdx_truth,"K","lp");
  leg->AddEntry(proton_dEdx_truth,"p","lp");
  leg->AddEntry(muon_dEdx_truth,"mu","lp");
  //  leg->AddEntry(other_dEdx_truth,"other","lp");
  leg->Draw();


  c_dEdx_truth->cd(2);
  gPad->SetLogx();
  
  pion_dEdx_id->SetMarkerColor(4);
  pion_dEdx_id->SetLineColor(4);
  pion_dEdx_id->SetTitle("ID-optimized");
  pion_dEdx_id->Draw("");

  kaon_dEdx_id->SetMarkerColor(2);
  kaon_dEdx_id->SetLineColor(2);
  kaon_dEdx_id->Draw("same");

  proton_dEdx_id->SetMarkerColor(3);
  proton_dEdx_id->SetLineColor(3);
  proton_dEdx_id->Draw("same");

  TLegend *leg2 = new TLegend(0.6,0.55,0.8,0.85);
  leg2->AddEntry(pion_dEdx_truth,"pi","lp");
  leg2->AddEntry(kaon_dEdx_truth,"K","lp");
  leg2->AddEntry(proton_dEdx_truth,"p","lp");
  leg2->Draw();

  c_dEdx_truth->cd(3);
  gPad->SetLogx();
  
  pion_dEdx_good->SetMarkerColor(4);
  pion_dEdx_good->SetLineColor(4);
  pion_dEdx_good->SetTitle("Well Id (ID-optimized)");
  pion_dEdx_good->Draw("");

  kaon_dEdx_good->SetMarkerColor(2);
  kaon_dEdx_good->SetLineColor(2);
  kaon_dEdx_good->Draw("same");

  proton_dEdx_good->SetMarkerColor(3);
  proton_dEdx_good->SetLineColor(3);
  proton_dEdx_good->Draw("same");

  leg2->Draw();

  c_dEdx_truth->cd(4);
  gPad->SetLogx();
  
  pion_dEdx_bad->SetMarkerColor(4);
  pion_dEdx_bad->SetLineColor(4);
  pion_dEdx_bad->SetTitle("Badly Id (ID-optimized)");
  pion_dEdx_bad->Draw("");

  kaon_dEdx_bad->SetMarkerColor(2);
  kaon_dEdx_bad->SetLineColor(2);
  kaon_dEdx_bad->Draw("same");

  proton_dEdx_bad->SetMarkerColor(3);
  proton_dEdx_bad->SetLineColor(3);
  proton_dEdx_bad->Draw("same");
  leg2->Draw();


  c_dEdx_truth->cd(5);
  gPad->SetLogx();
  pion_dEdx_truth->Draw("");
  other_dEdx_truth->Draw("same");
  kaon_dEdx_truth->Draw("same");
  proton_dEdx_truth->Draw("same");
  electron_dEdx_truth->Draw("same");
  muon_dEdx_truth->Draw("same");

 
  leg->Draw();
  c_dEdx_truth->cd(6);
  gPad->SetLogx();
  
  pion_dEdx_ID_DST_id->SetMarkerColor(4);
  pion_dEdx_ID_DST_id->SetLineColor(4);
  pion_dEdx_ID_DST_id->SetTitle(title);
  pion_dEdx_ID_DST_id->Draw("");

  kaon_dEdx_ID_DST_id->SetMarkerColor(2);
  kaon_dEdx_ID_DST_id->SetLineColor(2);
  kaon_dEdx_ID_DST_id->Draw("same");

  proton_dEdx_ID_DST_id->SetMarkerColor(3);
  proton_dEdx_ID_DST_id->SetLineColor(3);
  proton_dEdx_ID_DST_id->Draw("same");

  leg2->Draw();

  c_dEdx_truth->cd(7);
  gPad->SetLogx();
  
  pion_dEdx_ID_DST_good->SetMarkerColor(4);
  pion_dEdx_ID_DST_good->SetLineColor(4);
  pion_dEdx_ID_DST_good->SetTitle("Well Id "+title);
  pion_dEdx_ID_DST_good->Draw("");

  kaon_dEdx_ID_DST_good->SetMarkerColor(2);
  kaon_dEdx_ID_DST_good->SetLineColor(2);
  kaon_dEdx_ID_DST_good->Draw("same");

  proton_dEdx_ID_DST_good->SetMarkerColor(3);
  proton_dEdx_ID_DST_good->SetLineColor(3);
  proton_dEdx_ID_DST_good->Draw("same");

  leg2->Draw();

  c_dEdx_truth->cd(8);
  gPad->SetLogx();
  
  pion_dEdx_ID_DST_bad->SetMarkerColor(4);
  pion_dEdx_ID_DST_bad->SetLineColor(4);
  pion_dEdx_ID_DST_bad->SetTitle("Badly Id "+title);
  pion_dEdx_ID_DST_bad->Draw("");

  kaon_dEdx_ID_DST_bad->SetMarkerColor(2);
  kaon_dEdx_ID_DST_bad->SetLineColor(2);
  kaon_dEdx_ID_DST_bad->Draw("same");

  proton_dEdx_ID_DST_bad->SetMarkerColor(3);
  proton_dEdx_ID_DST_bad->SetLineColor(3);
  proton_dEdx_ID_DST_bad->Draw("same");


  leg2->Draw();
  //c_dEdx_truth->Print("plots_secondary/c_dEdx_new_vs_"+title+".png");
  
}



void kaontagger::SimplePlot(int algo) {
  
  TString title = "LikelihoodPID";
  if(algo==1) title = "LowMomMuID";
  if(algo==2) title = "BasicVariablePID";
  if(algo==3) title = "dEdxPID";
  
  gStyle->SetOptStat(0);
  TCanvas* c_dEdx = new TCanvas("c_dEdx_"+title,"c_dEdx_"+title,800,800);
  c_dEdx->cd(1);
  gPad->SetLogx();


  kaon_dEdx_truth->SetMarkerColor(2);
  kaon_dEdx_truth->SetLineColor(2);
  kaon_dEdx_truth->Draw("");
  
  kaon_dEdx_ID_DST_id->SetMarkerColor(3);
  kaon_dEdx_ID_DST_id->SetLineColor(3);
  kaon_dEdx_ID_DST_id->Draw("same");

  kaon_dEdx_id->SetMarkerColor(1);
  kaon_dEdx_id->SetLineColor(1);
  kaon_dEdx_id->Draw("same");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.85);
  leg->AddEntry(kaon_dEdx_truth,"K","lp");
  leg->AddEntry(kaon_dEdx_ID_DST_id,"K,"+title,"lp");
  leg->AddEntry(kaon_dEdx_id,"K, new ID","lp");
  leg->Draw();
 // c_dEdx->Print("plots_secondary/c_dEdx_"+title+".png");
}
