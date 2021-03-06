#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TCut.h"
#include "TString.h"
#include "TF1.h"
#include "TPad.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLatex.h"
#include "TProfile2D.h"
#include "THStack.h"

const float LZ_MIN = -0.03;
const float LZ_MAX =  0.03;
const float LZ_INC = 0.001; //  101 pts

const float dKG_MIN =  -0.15;
const float dKG_MAX =   0.15;
const float dKG_INC =   0.01;    // x31 pts

const float dg1_MIN =  -0.10;
const float dg1_MAX =   0.10;
const float dg1_INC =   0.002;    // x101 pts

const double intLUMI = 1.;

//const double WJets_scale   = 37509.0* intLUMI/18353019;
double WJets_scale   = 3.32283007705589037e-05 * intLUMI;
double W4Jets_scale  = 214.0 * intLUMI/12842803;
double WW_scale      = 57.1097   * intLUMI/9450414;
double WZ_scale      = 32.3161  * intLUMI/10000267;

double ZJets_scale   = 3503.71  * intLUMI/30209426;
double ttbar_scale   = 225.197 * intLUMI/6893735;

double SToppS_scale  = 1.76 * intLUMI/ 139974;
double SToppT_scale  = 30.7 * intLUMI/1935066;
double SToppTW_scale = 11.1 * intLUMI/ 493458;
double STopS_scale   = 3.79 * intLUMI/ 259960;
double STopT_scale   = 56.4 * intLUMI/3758221;
double STopTW_scale  = 11.1 * intLUMI/ 497657;

double mc2data_scale;


bool domu=true;
float yRatioMin = 0.;
float yRatioMax = 2.6;

//TFile* sigLambdaZ;

////////// ALL input trees ///////////
TTree* treedata;
TTree* treeww;
TTree* treewz;
TTree* treewj;
TTree* treewjUp;
TTree* treewjDown;
TTree* treettb;
TTree* treeqcd;
TTree* treezj;
TTree* treests;
TTree* treestt;
TTree* treestw;
TTree* tree64;
TTree* tree65;
TTree* tree66;



////////// ALL histograms ///////////
TH1* th1data;
TH1* th1ww;
TH1* th1wz;
TH1* th1wjets;
TH1* systUp;
TH1* systDown;
TH1* th1Top;
TH1* th1qcd;
TH1* th1zjets;
TH1* th1stops;
TH1* th1stopt;
TH1* th1stoptw;
TH1* th1stopps;
TH1* th1stoppt;
TH1* th1stopptw;
TH1D *th1tot;
TH1D* th1totClone;
TH1* th1totempty;
TH1D* th1emptyclone;
TH1F* hhratio;
TH1F* hhratioUp;
TH1F* hhratioDown;
TH1* signalForDisplay;
TH1* signalRatioForDisplay;

bool saveDataCards_ = true;
//bool saveDataCards_ = false;
TF1 *gaus2;



void InstantiateTrees() {

  ////////// ALL input files ///////////
  TFile* fin2;
  TFile* wwShape_file;
  TFile* wzShape_file;
  TFile* wjetsShape_file;
  TFile* wjetsShapeUp_file;
  TFile* wjetsShapeDown_file;
  TFile* ttbar_file;
  TFile* qcd_file1;
  TFile* zjets_file;
  TFile* stops_file;
  TFile* stopt_file;
  TFile* stoptW_file;
  TFile* stopps_file;
  TFile* stoppt_file;
  TFile* stopptW_file;

 if (domu) {
    fin2            = new TFile("InData/RD_WmunuJets_DataAll_GoldenJSON_19p3invfb.root", "read");
    wwShape_file    = new TFile("InData/RD_mu_WW_CMSSW532.root", "READ");
    wzShape_file    = new TFile("InData/RD_mu_WZ_CMSSW532.root", "READ");
    wjetsShape_file = new TFile("InData/RD_mu_WpJ_CMSSW532.root", "READ");
    wjetsShapeUp_file = new TFile("InData/RD_mu_WpJscaleup_CMSSW532.root", "READ");
    wjetsShapeDown_file = new TFile("InData/RD_mu_WpJscaledown_CMSSW532.root", "READ");
    ttbar_file      = new TFile("InData/RD_mu_TTbar_CMSSW532.root", "READ");
    qcd_file1       = new TFile("InData/RD_mu_WpJ_CMSSW532.root", "READ");
    zjets_file      = new TFile("InData/RD_mu_ZpJ_CMSSW532.root", "READ");
    stops_file      = new TFile("InData/RD_mu_STopS_T_CMSSW532.root", "READ");
    stopt_file      = new TFile("InData/RD_mu_STopT_T_CMSSW532.root", "READ");
    stoptW_file     = new TFile("InData/RD_mu_STopTW_T_CMSSW532.root", "READ");
    stopps_file =  new TFile("InData/RD_mu_STopS_Tbar_CMSSW532.root", "READ");
    stoppt_file =  new TFile("InData/RD_mu_STopT_Tbar_CMSSW532.root", "READ");
    stopptW_file =  new TFile("InData/RD_mu_STopTW_Tbar_CMSSW532.root", "READ");
  } else { // electrons

   fin2            = new TFile("InData/RD_WenuJets_DataAllSingleElectronTrigger_GoldenJSON_19p2invfb.root", "READ");
    wwShape_file    = new TFile("InData/RD_el_WW_CMSSW532.root", "READ");
    wzShape_file    = new TFile("InData/RD_el_WZ_CMSSW532.root", "READ");
    wjetsShape_file = new TFile("InData/RD_el_WpJ_CMSSW532.root", "READ");
    wjetsShapeUp_file = new TFile("InData/RD_el_WpJscaleup_CMSSW532.root", "READ");
    wjetsShapeDown_file = new TFile("InData/RD_el_WpJscaledown_CMSSW532.root", "READ");
    ttbar_file      = new TFile("InData/RD_el_TTbar_CMSSW532.root", "READ");
    qcd_file1       = new TFile("InQCD/RDQCD_WenuJets_Isog0p3NoElMVA_19p2invfb.root", "READ");
    zjets_file      = new TFile("InData/RD_el_ZpJ_CMSSW532.root", "READ");
    stops_file      = new TFile("InData/RD_el_STopS_T_CMSSW532.root", "READ");
    stopt_file      = new TFile("InData/RD_el_STopT_T_CMSSW532.root", "READ");
    stoptW_file     = new TFile("InData/RD_el_STopTW_T_CMSSW532.root", "READ");
    stopps_file =  new TFile("InData/RD_el_STopS_Tbar_CMSSW532.root", "READ");
    stoppt_file =  new TFile("InData/RD_el_STopT_Tbar_CMSSW532.root", "READ");
    stopptW_file =  new TFile("InData/RD_el_STopTW_Tbar_CMSSW532.root", "READ");
 }


  treedata = (TTree*) fin2->Get("WJet");
  double nData = treedata->GetEntries();
  std::cout << "ndata =" << nData <<std::endl;

  //// ------------ Get all trees
  treeww    = (TTree*)    wwShape_file->Get("WJet");
  treewz    = (TTree*)    wzShape_file->Get("WJet");
  treewj    = (TTree*)    wjetsShape_file->Get("WJet");
  treewjUp  = (TTree*)    wjetsShapeUp_file->Get("WJet");
  treewjDown = (TTree*)    wjetsShapeDown_file->Get("WJet");
  treettb   = (TTree*)    ttbar_file->Get("WJet");
  treeqcd   = (TTree*)    qcd_file1->Get("WJet");
  treezj    = (TTree*)    zjets_file->Get("WJet");
  treests   = (TTree*)    stops_file->Get("WJet");
  treestt   = (TTree*)    stopt_file->Get("WJet");
  treestw   = (TTree*)    stoptW_file->Get("WJet");
  tree64    = (TTree*)    stopps_file->Get("WJet");
  tree65    = (TTree*)    stoppt_file->Get("WJet");
  tree66    = (TTree*)    stopptW_file->Get("WJet");

  //// ------------ Create a tree branch for dijet pt
  const char* dijetPt = "sqrt(JetPFCor_Pt[0]*JetPFCor_Pt[0]+JetPFCor_Pt[1]*JetPFCor_Pt[1]+2*JetPFCor_Pt[0]*JetPFCor_Pt[1]*cos(JetPFCor_Phi[0]-JetPFCor_Phi[1]))";
  treedata->SetAlias("dijetPt", dijetPt);
  treeww->SetAlias("dijetPt", dijetPt);
  treewz->SetAlias("dijetPt", dijetPt);
  treewj->SetAlias("dijetPt", dijetPt);
  treewjUp->SetAlias("dijetPt", dijetPt);
  treewjDown->SetAlias("dijetPt", dijetPt);
  treettb->SetAlias("dijetPt", dijetPt);
  treeqcd->SetAlias("dijetPt", dijetPt);
  treezj->SetAlias("dijetPt", dijetPt);
  treests->SetAlias("dijetPt", dijetPt);
  treestt->SetAlias("dijetPt", dijetPt);
  treestw->SetAlias("dijetPt", dijetPt);
  tree64->SetAlias("dijetPt", dijetPt);
  tree65->SetAlias("dijetPt", dijetPt);
  tree66->SetAlias("dijetPt", dijetPt);
}







void ScaleHistos(int channel)
{
  double WJets_norm = 1.;
  double VV_norm = 1.;
  double Top_norm = 1.;

  /*
  if(channel==0) {
    WJets_norm = 1.0055;
    VV_norm = 1.1144;
    Top_norm = 0.99664;
  }
  if(channel==1) {
    WJets_norm = 1.1107;
    VV_norm = 1.3919;
    Top_norm = 0.9825;
  }
  if(channel==2) {
    WJets_norm = 1.1271;
    VV_norm = 1.2530;
    Top_norm = 1.013;
  }
  if(channel==3) {
    WJets_norm = 1.0984;
    VV_norm = 1.3804;
    Top_norm = 1.0267;
  }
  */

  WJets_scale   *= WJets_norm;
  WW_scale      *= VV_norm;
  WZ_scale      *= VV_norm;
  ttbar_scale   *= Top_norm;
  SToppS_scale  *= Top_norm;
  SToppT_scale  *= Top_norm;
  SToppTW_scale *= Top_norm;
  STopS_scale   *= Top_norm;
  STopT_scale   *= Top_norm;
  STopTW_scale  *= Top_norm;

  th1Top->Scale(ttbar_scale);
  th1Top->SetFillColor(kGreen+2);
  th1Top->SetLineColor(kGreen+2);
  th1Top->SetLineWidth(0);
  th1stops->Scale(STopS_scale);
  th1stops->SetFillColor(7);
  th1stops->SetLineWidth(2);
  th1stopt->Scale(STopT_scale);
  th1stopt->SetFillColor(13);
  th1stopt->SetLineWidth(2);
  th1stoptw->Scale(STopTW_scale);
  th1stoptw->SetFillColor(9);
  th1stoptw->SetLineWidth(2);
  th1wjets->Scale(WJets_scale);
  th1wjets->SetFillColor(kRed);
  th1wjets->SetLineColor(kRed);
  th1wjets->SetLineWidth(0);
  th1ww->Scale(WW_scale);
  th1ww->SetFillColor(kAzure+8);
  th1ww->SetLineColor(kAzure+8);
  th1ww->SetLineWidth(0);
  th1wz->Scale(WZ_scale);
  th1wz->SetFillColor(11);
  th1wz->SetLineWidth(0);
  // th1qcd->Scale(QCD_scale);
  
  th1qcd->SetFillColor(kGray+1);
  th1qcd->SetLineColor(kGray+1);
  th1qcd->SetLineWidth(0);
  th1zjets->Scale(ZJets_scale);
  th1zjets->SetFillColor(kYellow);
  th1zjets->SetLineColor(kYellow);
  th1zjets->SetLineWidth(0);
  std::cout << " qcd " << th1qcd->Integral()   << std::endl;
  std::cout << "tt "   << th1Top->Integral()   << std::endl;
  std::cout << "ww "   << th1ww->Integral()    << std::endl;
  std::cout << "wz "   << th1wz->Integral()    << std::endl;
  std::cout << "z "    << th1zjets->Integral() << std::endl;
  
  double den_qcd = 
    th1Top->Integral()+
    th1stops->Integral()+
    th1stopt->Integral()+
    th1stoptw->Integral()+
    th1wjets->Integral()+
    th1ww->Integral()+
    th1wz->Integral()+
    th1zjets->Integral();

  double qcd_scale;

  if (domu)
    qcd_scale = 0.0 ;//muon
  else
    qcd_scale = 0.03; //electron
  if(channel==3) qcd_scale = 0.0; //electron boosted 


  std::cout << " qcd_scale  " << qcd_scale <<std::endl;
  th1qcd->Scale(qcd_scale*den_qcd/th1qcd->Integral()); 

  double den = 
    th1Top->Integral()+
    th1stops->Integral()+
    th1stopt->Integral()+
    th1stoptw->Integral()+
    th1wjets->Integral()+
    th1ww->Integral()+
    th1wz->Integral()+
    th1zjets->Integral()+
    th1qcd->Integral();

  std::cout << "den = " <<den <<std::endl;
  std::cout <<" data " <<  th1data->Integral() << std::endl;

  mc2data_scale = th1data->Integral()/den;

  th1qcd->Scale   (mc2data_scale); std::cout <<"qcd "   << th1qcd->Integral()   << std::endl;
  th1Top->Scale   (mc2data_scale); std::cout <<"tt "    << th1Top->Integral()   << std::endl;
  th1stops->Scale (mc2data_scale); std::cout <<"stops " << th1stops->Integral() << std::endl;
  th1stopt->Scale (mc2data_scale); std::cout <<"stopt " << th1stopt->Integral() << std::endl;
  th1stoptw->Scale(mc2data_scale); std::cout <<"stoptw "<< th1stoptw->Integral()<< std::endl;
  th1wjets->Scale (mc2data_scale); std::cout <<"wjets " << th1wjets->Integral() << std::endl;
  th1ww->Scale    (mc2data_scale); std::cout <<"ww "    << th1ww->Integral()    << std::endl;
  th1wz->Scale    (mc2data_scale); std::cout << "wz "   << th1wz->Integral()    << std::endl;
  th1zjets->Scale (mc2data_scale); std::cout << "z "    << th1zjets->Integral() << std::endl;

  double den2 =
    th1Top->Integral()+
    th1stops->Integral()+
    th1stopt->Integral()+
    th1stoptw->Integral()+
    th1wjets->Integral()+
    th1ww->Integral()+
    th1wz->Integral()+
    th1zjets->Integral()+
    th1qcd->Integral();

  std::cout << "den2 " << den2 << std::endl;

  th1Top->Add(th1stoptw,1);
  th1Top->Add(th1stopt,1);
  th1Top->Add(th1stops,1);
  th1ww->Add(th1wz,1);
}


void AddOverflowBin(TH1* hist) {
  int nBinsTot = hist->GetNbinsX();
  double lastbin = hist->GetBinContent(nBinsTot);
  double overflow = hist->GetBinContent(nBinsTot+1);
  hist->SetBinContent(nBinsTot, lastbin+overflow);
  hist->SetBinError(nBinsTot, sqrt(lastbin+overflow));
}



void AddOverflowBin(TH1* hist, TF1 *f, double dm_max) {
  int nBinsTot = hist->GetNbinsX();
  double lastbin = hist->GetBinContent(nBinsTot);
  double overflow = f->Integral(dm_max, dm_max + 400.);
  hist->SetBinContent(nBinsTot, lastbin+overflow);
  hist->SetBinError(nBinsTot, sqrt(lastbin+overflow));
}


  // Sum all the backgrounds
void SumAllBackgrounds() {

  //-------- First add overflow bin ----------------
  AddOverflowBin(th1ww);
  AddOverflowBin(th1wjets);
  AddOverflowBin(th1zjets);
  AddOverflowBin(th1Top);
  AddOverflowBin(th1qcd);
  AddOverflowBin(th1data);

  //-------- Now sum of all bkg histograms ----------
  th1tot = (TH1D*)th1wjets->Clone("th1tot");
  th1tot->Reset();
  th1tot->Add(th1ww,1);
  th1tot->Add(th1qcd,1);
  th1tot->Add(th1Top,1);
  th1tot->Add(th1wjets,1);
  th1tot->Add(th1zjets,1);
  th1tot->SetFillStyle(3001);
  th1tot->SetFillColor(1);
  th1tot->SetLineColor(1);
  th1tot->SetMarkerStyle(0);
  th1tot->SetMinimum(0.0);


  //-------- Needed for plotting ----------
  th1totClone = ( TH1D*) th1tot->Clone("th1totClone");
  th1totClone->SetMarkerStyle(0);
  th1totClone->SetFillStyle(3003);
  th1totClone->SetFillColor(11);
  th1totClone->SetLineColor(0);

  double binErr(0.0);
  for(int i=0; i<th1totClone->GetNbinsX(); ++i) {
    binErr = sqrt((th1ww->GetBinError(i))**2 +
		  (th1qcd->GetBinError(i))**2 +
		  (th1Top->GetBinError(i))**2 +
		  (th1wjets->GetBinError(i))**2 +
		  (th1zjets->GetBinError(i))**2);
    th1totClone->SetBinError(i, binErr);
  }
  

  //-------- Ratio histogram ----------
  hhratio    = (TH1F*) th1data->Clone("hhratio")  ;
  hhratio->Sumw2();
  hhratio->SetMarkerSize(1.25);
  hhratio->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
  hhratio->Divide(th1tot);
  double binError(0.0), mcbinentry(0.0), mcerror(0.0);
  for(int i=0; i<hhratio->GetNbinsX(); ++i) {
    binError = hhratio->GetBinError(i);
    mcerror = th1tot->GetBinError(i);
    mcbinentry = th1tot->GetBinContent(i);
    if(mcbinentry>0.) mcerror /= mcbinentry;
    else mcerror = 0.0;
    binError = sqrt(binError**2 + mcerror**2);
    hhratio->SetBinError(i, binError);
    if(th1data->GetBinContent(i)<0.1) hhratio->SetBinError(i,0.0);
  }
}





TLegend* GetLegend(int channel)
{
  // float  legX0=0.5, legX1=0.89, legY0=0.41, legY1=0.86;
  float  legX0=0.6, legX1=0.93, legY0=0.45, legY1=0.88;
  if(channel > 1) { legX0=0.6; legY0=0.48; }
  TLegend * Leg = new TLegend( legX0, legY0, legX1, legY1);
  Leg->SetFillColor(0);
  Leg->SetFillStyle(0);
  Leg->SetTextSize(0.05);
  Leg->AddEntry(th1data,  "Data",  "PLE");
  Leg->AddEntry(th1ww,  "WW+WZ ",  "f");
  Leg->AddEntry(th1wjets,  "W+jets",  "f");
  Leg->AddEntry(th1Top,  "top",  "f");
  if(channel != 2) Leg->AddEntry(th1qcd,  "Multijet",  "f");
  Leg->AddEntry(th1zjets,  "Z+Jets",  "f");
  Leg->AddEntry(th1tot,  "MC error",  "f");
  Leg->AddEntry(systUp,  "Shape error",  "f");
  Leg->AddEntry(signalForDisplay,  "#lambda_{Z}=0.03",  "l");
  Leg->SetFillColor(0);

  return Leg;
}


void SetupEmptyHistogram(int bins, double dm_min, double dm_max, char* xtitle)
//void SetupEmptyHistogram(int bins, double* ptbins, char* xtitle)
{
  //th1totempty = new TH1D("th1totempty", "th1totempty", bins, ptbins); // dm_min, dm_max);
  th1totempty = new TH1D("th1totempty", "th1totempty", bins,dm_min, dm_max);
  char tmpc[100];    sprintf(tmpc,"Events / %d GeV", (int) (dm_max-dm_min)/bins);
  th1totempty->SetYTitle(tmpc);
  th1totempty->GetYaxis()->SetTitleOffset(1);
  th1totempty->GetYaxis()->SetLabelOffset(0.01);
  th1totempty->GetYaxis()->SetLabelSize(0.08);
  th1totempty->GetYaxis()->SetTitleSize(0.08);

  int maxbin = th1data->GetMaximumBin();
  float maxval = th1data->GetBinContent(maxbin);
  std::cout << "maxval " <<maxval <<std::endl;
  th1totempty->SetMaximum(1.2*maxval);
  th1totempty->SetMinimum(0.0);


  //th1emptyclone = new TH1D("th1emptyclone", "th1emptyclone", bins, ptbins); // dm_min, dm_max);
  th1emptyclone = new TH1D("th1emptyclone", "th1emptyclone", bins, dm_min, dm_max);
  th1emptyclone->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
  th1emptyclone->GetXaxis()->SetTitle(xtitle);
  th1emptyclone->GetXaxis()->SetTitleOffset(0.9);
  th1emptyclone->GetXaxis()->SetTitleSize(0.15);
  th1emptyclone->GetXaxis()->SetLabelSize(0.15);
  th1emptyclone->SetYTitle("Data/MC  ");
  th1emptyclone->GetYaxis()->SetTitleSize(0.2);
  th1emptyclone->GetXaxis()->SetNdivisions(505);
  th1emptyclone->GetYaxis()->SetNdivisions(505);
  th1emptyclone->GetYaxis()->SetTitleOffset(0.3);
  th1emptyclone->GetYaxis()->CenterTitle(true);
  th1emptyclone->GetYaxis()->SetLabelSize(0.2);
  th1emptyclone->GetXaxis()->SetLabelSize(0.2);
  th1emptyclone->GetXaxis()->SetTitleSize(0.2);
  th1emptyclone->GetYaxis()->SetMoreLogLabels();
  th1emptyclone->GetYaxis()->SetNoExponent();
}


//------- Get signal histogram -------

TCut
GetSigRatioFunction(float lambdaZ, float dkappaGamma, float deltaG1,const char *obsrvbl)
{
  //printf("%g\t%g\t%g\r",lambdaZ,dkappaGamma,deltaG1);

  TFile f("ATGC_shape_coefficients.root");
  TProfile2D* p0_prof; 
  TProfile2D* p1_prof; 
  TProfile2D* p2_prof; 
  TProfile2D* p3_prof; 
  TProfile2D* p4_prof; 
  TProfile2D* p5_prof; 
  TProfile2D* p6_prof; 
  float var1, var2;

  if(fabs(deltaG1)<0.000001) {
    p0_prof = (TProfile2D*) f.Get("p0_lambda_dkg");
    p1_prof = (TProfile2D*) f.Get("p1_lambda_dkg");
    p2_prof = (TProfile2D*) f.Get("p2_lambda_dkg");
    p3_prof = (TProfile2D*) f.Get("p3_lambda_dkg");
    p4_prof = (TProfile2D*) f.Get("p4_lambda_dkg");
    p5_prof = (TProfile2D*) f.Get("p5_lambda_dkg");
    p6_prof = (TProfile2D*) f.Get("p6_lambda_dkg");
    var1 = lambdaZ; 
    var2 = dkappaGamma; 
    //printf("Looking up coefficients for lambdaZ=%g, dkappaGamma=%g\n",var1,var2);
  }
  else if(fabs(dkappaGamma)<0.000001) { 
    p0_prof = (TProfile2D*) f.Get("p0_lambda_dg1");
    p1_prof = (TProfile2D*) f.Get("p1_lambda_dg1");
    p2_prof = (TProfile2D*) f.Get("p2_lambda_dg1");
    p3_prof = (TProfile2D*) f.Get("p3_lambda_dg1");
    p4_prof = (TProfile2D*) f.Get("p4_lambda_dg1");
    p5_prof = (TProfile2D*) f.Get("p5_lambda_dg1");
    p6_prof = (TProfile2D*) f.Get("p6_lambda_dg1");
    var1 = lambdaZ; 
    var2 = deltaG1;
    //printf("Looking up coefficients for lambdaZ=%g, deltaG1=%g\n",var1,var2);
  }
  else if(fabs(lambdaZ)<0.000001) {
    p0_prof = (TProfile2D*) f.Get("p0_dkg_dg1");
    p1_prof = (TProfile2D*) f.Get("p1_dkg_dg1");
    p2_prof = (TProfile2D*) f.Get("p2_dkg_dg1");
    p3_prof = (TProfile2D*) f.Get("p3_dkg_dg1");
    p4_prof = (TProfile2D*) f.Get("p4_dkg_dg1");
    p5_prof = (TProfile2D*) f.Get("p5_dkg_dg1");
    p6_prof = (TProfile2D*) f.Get("p6_dkg_dg1");
    var1 = dkappaGamma; 
    var2 = deltaG1;
    printf("Looking up coefficients for dkappaGamma=%g, deltaG1=%g\n",var1,var2);
  }
  else {
    assert(0);
  }

  TCut sigratio(
    TString::Format("(%g-1.0+",p0_prof->Interpolate(var1,var2))+
    TString::Format("%s*(%g+",obsrvbl,p1_prof->Interpolate(var1,var2))+
    TString::Format("%s*(%g+",obsrvbl,p2_prof->Interpolate(var1,var2))+
    TString::Format("%s*(%g+",obsrvbl,p3_prof->Interpolate(var1,var2))+
    TString::Format("%s*(%g+",obsrvbl,p4_prof->Interpolate(var1,var2))+
    TString::Format("%s*(%g+",obsrvbl,p5_prof->Interpolate(var1,var2))+
    TString::Format("%s*%g))))))",obsrvbl,p6_prof->Interpolate(var1,var2))
    );

  return sigratio;
}


void cmspre()
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.05);

  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.85,0.93,"#sqrt{s} = 8 TeV");
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.65,0.93,Form("#scale[0.5]{#lower[-0.15]{#it{#int}}}#it{L} dt = %0.1f#kern[0.2]{fb}^{-1}", 19.3));
  latex.SetTextAlign(11); // align left
//  latex.DrawLatex(0.15,0.93,"CMS,  #sqrt{s} = 7 TeV");//preliminary 2011");
  latex.DrawLatex(0.15,0.93,"CMS");

}

const double ptbins_boosted[15] = {
  200,225,250,275,300,325,350,375,400,425,450,500,550,625,925
};

//////---------- channel: 0==muon dijet, 1== electron dijet
/////                     2==muon  boosted,   3== electron boosted
void makeATGCLimitDataCards(int channel) {


//   const Int_t bins = 8; 
//   const Float_t dm_min = 200.; 
//   const Float_t dm_max = 600.;

  Int_t bins = 7; 
  Float_t dm_min = 100.; 
  Float_t dm_max = 275.;
  if(channel>1) { bins = 12; dm_min = 200.; dm_max = 500; }


  domu = true;
  if(channel==1 || channel==3) domu = false;

 
  TString outfile = (domu?TString("mu_"):TString("el_"))+ 
    (channel<2?TString("dijet"):TString("boosted"));
  TFile* outputForLimit = TFile::Open(outfile+".root", "recreate");




  TString cutsDijet("(W_pt<200.) && (dijetPt>70.) && (abs(JetPFCor_Eta[0])<2.4) && (abs(JetPFCor_Eta[1])<2.4) && (abs(JetPFCor_Eta[0]-JetPFCor_Eta[1])<1.5) &&(abs(JetPFCor_dphiMET[0])>0.4) &&(W_mt>30.) &&(JetPFCor_Pt[0]>40.) &&(JetPFCor_Pt[1]>35.) &&(JetPFCor_Pt[2]<30.) &&(JetPFCor_bDiscriminatorCSV[0]<0.244) &&(JetPFCor_bDiscriminatorCSV[1]<0.244) && (Mass2j_PFCor>70. && Mass2j_PFCor<100.)");



  TString cutsMerged("(W_pt>200.) && (GroomedJet_CA8_pt[0]>200.) &&(abs(GroomedJet_CA8_eta[0])<2.4) &&(JetPFCor_bDiscriminatorCSV[0]<0.244) &&(GroomedJet_numberbjets <1)&&(ggdboostedWevt==1) && (GroomedJet_CA8_tau2tau1[0]<0.55) && (GroomedJet_CA8_mass[0]>70. && GroomedJet_CA8_mass[0]<100.)");


  TString lepton_cut = "(event_met_pfmet >30) && (W_electron_pt>35.) &&";
  if(channel==0) lepton_cut = "(event_met_pfmet >25) &&(abs(W_muon_eta)<2.1) && (W_muon_pt>25.) &&";
  if(channel==1) lepton_cut = "(event_met_pfmet >30) && (W_electron_pt>30.) &&";
  if(channel==2) lepton_cut = "(event_met_pfmet >50) &&(abs(W_muon_eta)<2.1) && (W_muon_pt>30.) &&";
  if(channel==3) lepton_cut = "(event_met_pfmet >70) && (W_electron_pt>35.) &&";


  TString jet_cut = cutsDijet;
  if(channel>1) jet_cut = cutsMerged;

  TCut the_cut( TString("(effwt*puwt)*(") + lepton_cut + jet_cut + TString(")") );

  char* observable = "dijetPt";
  char* xtitle = "p_{T}^{jj} [GeV]"; 
  if(channel>1) { 
    observable = "GroomedJet_CA8_pt[0]";
    xtitle = "p_{T}^{j} [GeV]";
  }

  InstantiateTrees();



  //th1data  = new TH1D("th1data",  "th1data",  bins, ptbins_boosted); // bins, dm_min, dm_max);
  th1data  = new TH1D("th1data",  "th1data",  bins, dm_min, dm_max);
  th1data->Sumw2();
  th1data->SetMarkerStyle(20);
  th1data->SetMarkerSize(1.25);
  th1data->SetLineWidth(2);
  th1data->SetMinimum(0.0);
  treedata->Draw(TString(observable)+TString(">>th1data"), the_cut, "goff");

  // ------- Get WW/WZ ------- 
    th1ww = new TH1D("th1ww", "th1ww", bins, dm_min, dm_max);
    th1wz = new TH1D("th1wz", "th1wz", bins, dm_min, dm_max);
    th1ww->Sumw2();
    th1wz->Sumw2();
    treeww->Draw(TString(observable)+TString(">>th1ww"), the_cut, "goff");
    treewz->Draw(TString(observable)+TString(">>th1wz"), the_cut, "goff");

    // ------- Get WJets ------- 
    th1wjets  = new TH1D("th1wjets",  "th1wjets", bins, dm_min, dm_max);
    th1wjets->Sumw2();
    treewj->Draw(TString(observable)+TString(">>th1wjets"), the_cut, "goff");


    // ------- Get ttbar ------- 
    th1Top = new TH1D("th1Top", "th1Top", bins, dm_min, dm_max);
    th1Top->Sumw2();
    treettb->Draw(TString(observable)+TString(">>th1Top"), the_cut, "goff");

    // ------- Get QCD ------- 
    th1qcd = new TH1D("th1qcd", "th1qcd", bins, dm_min, dm_max);
    th1qcd->Sumw2();
    treeqcd->Draw(TString(observable)+TString(">>th1qcd"), the_cut, "goff");

    // ------- Get Z+Jets ------- 
    th1zjets = new TH1D("th1zjets", "th1zjets", bins, dm_min, dm_max);
    th1zjets->Sumw2();
    treezj->Draw(TString(observable)+TString(">>th1zjets"), the_cut, "goff");


    // ------- Get Single top ------- 
    th1stops = new TH1D("th1stops", "th1stops", bins, dm_min, dm_max);
    th1stopt = new TH1D("th1stopt", "th1stopt", bins, dm_min, dm_max);
    th1stoptw = new TH1D("th1stoptw", "th1stoptw", bins, dm_min, dm_max);
    th1stops->Sumw2();
    th1stopt->Sumw2();
    th1stoptw->Sumw2();

    treests->Draw(TString(observable)+TString(">>th1stops"), the_cut, "goff");
    treestt->Draw(TString(observable)+TString(">>th1stopt"), the_cut, "goff");
    treestw->Draw(TString(observable)+TString(">>th1stoptw"), the_cut, "goff");
 
    th1stopps = new TH1D("th1stopps", "th1stopps", bins, dm_min, dm_max);
    th1stoppt = new TH1D("th1stoppt", "th1stoppt", bins, dm_min, dm_max);
    th1stopptw = new TH1D("th1stopptw", "th1stopptw", bins, dm_min, dm_max);
    th1stopps->Sumw2();
    th1stoppt->Sumw2();
    th1stopptw->Sumw2();
    tree64->Draw(TString(observable)+TString(">>th1stopps"), the_cut, "goff");
    tree65->Draw(TString(observable)+TString(">>th1stoppt"), the_cut, "goff");
    tree66->Draw(TString(observable)+TString(">>th1stopptw"), the_cut, "goff");


    // ---- Scale the histos ---- 
    ScaleHistos(channel);
    
    // ---- Make smooth diboson shape ----------
    TH1D* th1wwclone = (TH1D *)th1ww->Clone("th1wwclone");
    float tmin = 200.0;
    if(channel>1) tmin = 300.0;
    gaus2 = new TF1("gaus2","gaus", tmin, 1000000000.);
    th1wwclone->Fit(gaus2,"I0","");
    
    // ---- Empty histograms for display/plotting ---- 
    SetupEmptyHistogram(bins, dm_min, dm_max, xtitle);
    //SetupEmptyHistogram(bins, ptbins_boosted, xtitle);

    // ---- Sum all backgrounds ----------
    TH1D* th1ww_no_overflow = (TH1D *)th1ww->Clone("th1ww_no_overflow");
    SumAllBackgrounds();


    // ---- Get signal histogram ----------
    TCut sigratio= GetSigRatioFunction(0.03, 0.0, 0.0,observable);

    TCut newcut = the_cut*sigratio;

    TH1D *signalForDisplay = new TH1D("signalForDisplay","signalForDisplay",bins,dm_min,dm_max);

    TString drawstr = TString(observable)+TString(">>signalForDisplay");

#if 1
    cout <<
      TString("wwtree->Draw(\"")+drawstr+TString("\", \"")+
      TString((const char*)newcut)+TString("\", \"goff\")") << endl;
#endif

    treeww->Draw(drawstr, newcut, "goff");

    cout << "signalForDisplay nentries = " << signalForDisplay->GetEntries() << endl;

    // ----- need to subtract the diboson contribution 
    signalForDisplay->SetLineWidth(2);
    signalForDisplay->SetLineColor(1);
    signalForDisplay->SetFillColor(0);

    signalForDisplay->Scale(mc2data_scale*WW_scale);

    //-------- Add overflow bin ----------------
    AddOverflowBin(signalForDisplay);


    // ---- Compose the stack ----------
    THStack* hs = new THStack("hs","MC contribution");
    hs->Add(th1zjets);
    hs->Add(th1qcd);
    hs->Add(th1Top);
    hs->Add(th1wjets);
    hs->Add(th1ww);
    hs->Add(signalForDisplay);



    // ---- Stack for shape systematics Up ----------
    TF1* formScaleUp = new TF1("formScaleUp", "1.0+0.4*log(x/5)", dm_min, dm_max);
    TF1* formScaleDown = new TF1("formScaleDown", "1.0-0.2*log(x/5)", dm_min, dm_max);
    systUp = (TH1D*) th1wjets->Clone("systUp");
    systUp->Multiply(formScaleUp);
    systUp->Add(th1zjets);
    systUp->Add(th1qcd);
    systUp->Add(th1Top);
    systUp->Add(th1ww);
    systUp->SetFillColor(0);
    systUp->SetLineStyle(2);
    systUp->SetLineColor(2);
    systUp->SetLineWidth(3);
    hhratioUp    = (TH1F*) th1data->Clone("hhratioUp")  ;
    hhratioUp->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
    hhratioUp->Divide(systUp);
    hhratioUp->SetLineStyle(2);
    hhratioUp->SetLineColor(2);
    hhratioUp->SetLineWidth(3);


    // ---- Stack for shape systematics Down ----------
    systDown = (TH1D*) th1wjets->Clone("systDown");
    systDown->Multiply(formScaleDown);
    systDown->Add(th1zjets);
    systDown->Add(th1qcd);
    systDown->Add(th1Top);
    systDown->Add(th1ww);
    systDown->SetFillColor(0);
    systDown->SetLineWidth(3);
    systDown->SetLineStyle(2);
    systDown->SetLineColor(2);
    hhratioDown    = (TH1F*) th1data->Clone("hhratioDown")  ;
    hhratioDown->GetYaxis()->SetRangeUser(yRatioMin, yRatioMax);
    hhratioDown->Divide(systDown);
    hhratioDown->SetLineStyle(2);
    hhratioDown->SetLineColor(2);
    hhratioDown->SetLineWidth(3);


    /////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////


    // ------- Setup the canvas ------- 
    gStyle->SetOptStat(0);
    // gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadLeftMargin(0.15);
    // gStyle->SetPadRightMargin(0.2);
    gStyle->SetPadBottomMargin(0.3);
    // gStyle->SetErrorX(0.5);

    TCanvas* c1 = new TCanvas("dijetPt", "", 10,10, 500, 500);
    TPad *d1, *d2;
    c1->Divide(1,2,0,0);
    d1 = (TPad*)c1->GetPad(1);
    d1->SetPad(0.01,0.30,0.95,0.99);
    d2 = (TPad*)c1->GetPad(2);
    d2->SetPad(0.01,0.02,0.95,0.30);

    d1->cd();
    gPad->SetBottomMargin(0.005);
    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.04);
    // gPad->SetLeftMargin(0.14);


    // Draw it all
    double ymax= 5000000.;
    double ymin= 7.0;
    if(channel>1) { 
      ymax= 30000.;
      ymin= 7.0;
    }

    th1totempty->GetYaxis()->SetRangeUser(ymin, ymax);
    th1data->GetYaxis()->SetRangeUser(ymin, ymax);
    th1totempty->Draw();
    th1data->Draw("esame");
    hs->Draw("samehist");
   for (int i=1;i<=th1tot->GetNbinsX();i++)
      {
	 double val = th1tot->GetBinContent(i);
	 double err = fabs(th1tot->GetBinError(i));
	 TBox *b = new TBox(th1tot->GetBinLowEdge(i),
			    val-err,th1tot->GetBinLowEdge(i+1),val+err);
	 b->SetLineColor(1);
	 b->SetFillColor(1);
	 b->SetFillStyle(3001);
	 b->SetLineStyle(3001);	 
	 b->Draw();
      }
    th1data->Draw("esame");
    cmspre(); 
    // Set up the legend
    TLegend* Leg = GetLegend(channel);   
    Leg->Draw();  
    d1->SetLogy();
    gPad->RedrawAxis();


    d2->cd();
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.04);
    gPad->SetFrameBorderSize(0);
    gPad->SetTickx();

    th1emptyclone->Draw();
    hhratio->Draw("esame");
    hhratioUp->Draw("hist lsame");
    hhratioDown->Draw("hist lsame");
    TLine *line; line = new TLine(dm_min,1.0,dm_max,1.0);
    line->SetLineStyle(1);
    line->SetLineWidth(1);
    line->SetLineColor(1);
    line->Draw();
    c1->Print(TString("OutDir/")+outfile+TString("_dijetPt.png"));
    //gPad->WaitPrimitive();
    c1->Modified();
    c1->Update();
    c1->SaveAs(TString("OutDir/")+outfile+TString("_dijetPt.pdf")); 
    c1->SaveAs(TString("OutDir/")+outfile+TString("_dijetPt.root")); 

   

    ///// -------------------------------//////

    if(saveDataCards_) {
      outputForLimit->cd();
      th1data->SetName("data_obs");
      th1data->Write("data_obs");
      th1tot->SetName("background");
      th1tot->Write("background");
      th1ww->SetName("diboson");
      th1ww->Write("diboson");
      th1ww_no_overflow->Write("th1ww_no_overflow");
      char* tempname = "background_backshapeUp";
      if(channel==0) tempname = "background_mudijet_backshapeUp";
      if(channel==1) tempname = "background_eldijet_backshapeUp";
      if(channel==2) tempname = "background_muboosted_backshapeUp";
      if(channel==3) tempname = "background_elboosted_backshapeUp";
      systUp->SetName(tempname);
      systUp->Write(tempname);
      tempname = "background_backshapeDown";
      if(channel==0) tempname = "background_mudijet_backshapeDown";
      if(channel==1) tempname = "background_eldijet_backshapeDown";
      if(channel==2) tempname = "background_muboosted_backshapeDown";
      if(channel==3) tempname = "background_elboosted_backshapeDown";
      systDown->SetName(tempname);
      systDown->Write(tempname);


//       char mysighistname[100];
//       for (float m=-0.1; m<0.1005; m += 0.005) {
// 	for (float n=0.3; n>-0.302; n -= 0.02) {
// 	  for (float q=0.6; q>-0.605; q -= 0.05) {
// 	  // if( fabs(m) > 0.1 && fabs(n) > 0.2) continue;
// 	  sprintf(mysighistname, 
// 		  "signal_lambdaZ_%0.3f_deltaKappaGamma_%0.3f_deltaG1_%0.3f", 
// 		  m+0.00001, n+0.00001, q+0.00001);
// 	  TH1D* stackhist = GetSignalHistogram(m+0.00001, n+0.00001, 
// 					       q+0.00001, mysighistname,th1wwclone);
// 	  outputForLimit->cd();
// 	  stackhist->Write(); 
// 	  delete stackhist;
// 	  }
// 	}
//       }


      char mysighistname[100];

      //for (float m=-0.05; m<0.051; m += 0.001) {
      for (float m=LZ_MIN; m<LZ_MAX+LZ_INC; m += LZ_INC) {
	for (float n=dKG_MAX; n>=dKG_MIN; n -= dKG_INC) {
	  sprintf(mysighistname, 
		  "signal_lambdaZ_%0.3f_deltaKappaGamma_%0.3f", 
		  m+0.00001, n+0.00001);

	  // ---- Get signal histogram ----------
	  TCut sigratio= GetSigRatioFunction(m, n, 0.0,observable);

	  TCut newcut = the_cut*sigratio;

	  TH1D *stackhist = new TH1D(mysighistname,mysighistname,bins,dm_min,dm_max);
	  //TH1D *stackhist = new TH1D(mysighistname,mysighistname,55,-1,10);

	  stackhist->Sumw2();

	  TString drawstr = TString(observable)+Form(">>%s",mysighistname);
	  //TString drawstr = TString(sigratio)+Form(">>%s",mysighistname);

#if 1
	  cout <<
	    TString("wwtree->Draw(\"")+drawstr+TString("\", \"")+
	    TString((const char*)newcut)+TString("\", \"goff\")") << endl;
#endif

	  treeww->Draw(drawstr, newcut, "goff");
	  //treeww->Draw(drawstr, the_cut, "goff");

	  cout << TString(mysighistname)<< " nentries = " << stackhist->GetEntries() << endl;

	  stackhist->SetLineWidth(2);
	  stackhist->SetLineColor(1);
	  stackhist->SetFillColor(0);

	  stackhist->Scale(mc2data_scale*WW_scale);

	  //-------- Add overflow bin ----------------
	  AddOverflowBin(stackhist);
	  outputForLimit->cd();
	  stackhist->Write(); 
	  delete stackhist;
	}
      }
 


      //for (float m=-0.05; m<0.051; m += 0.001) {
      for (float m=LZ_MIN; m<LZ_MAX+LZ_INC; m +=LZ_INC) {
	for (float n=dg1_MAX; n>=dg1_MIN; n -= dg1_INC) {
	  sprintf(mysighistname, 
		  "signal_lambdaZ_%0.3f_deltaG1_%0.3f", 
		  m+0.00001, n+0.00001);

	  // ---- Get signal histogram ----------
	  TCut sigratio= GetSigRatioFunction(m, 0.0, n, observable);

	  TCut newcut = the_cut*sigratio;

	  TH1D *stackhist = new TH1D(mysighistname,mysighistname,bins,dm_min,dm_max);
	  //TH1D *stackhist = new TH1D(mysighistname,mysighistname,55,-1,10);

	  stackhist->Sumw2();

	  TString drawstr = TString(observable)+Form(">>%s",mysighistname);
	  //TString drawstr = TString(sigratio)+Form(">>%s",mysighistname);

#if 1
	  cout <<
	    TString("wwtree->Draw(\"")+drawstr+TString("\", \"")+
	    TString((const char*)newcut)+TString("\", \"goff\")") << endl;
#endif

	  treeww->Draw(drawstr, newcut, "goff");
	  //treeww->Draw(drawstr, the_cut, "goff");

	  cout << TString(mysighistname)<< " nentries = " << stackhist->GetEntries() << endl;

	  stackhist->SetLineWidth(2);
	  stackhist->SetLineColor(1);
	  stackhist->SetFillColor(0);

	  stackhist->Scale(mc2data_scale*WW_scale);

	  //-------- Add overflow bin ----------------
	  AddOverflowBin(stackhist);

	  outputForLimit->cd();
	  stackhist->Write(); 
	  delete stackhist;
	}
      }
 

      for (float m=dKG_MAX; m>=dKG_MIN; m -= dKG_INC) {
	for (float n=dg1_MAX; n>=dg1_MIN; n -= dg1_INC) {
	  sprintf(mysighistname, 
		  "signal_deltaKappaGamma_%0.3f_deltaG1_%0.3f", 
		  m+0.00001, n+0.00001);

	  // ---- Get signal histogram ----------
	  TCut sigratio= GetSigRatioFunction(0.0, m, n, observable);

	  TCut newcut = the_cut*sigratio;

	  TH1D *stackhist = new TH1D(mysighistname,mysighistname,bins,dm_min,dm_max);
	  //TH1D *stackhist = new TH1D(mysighistname,mysighistname,55,-1,10);

	  stackhist->Sumw2();

	  TString drawstr = TString(observable)+Form(">>%s",mysighistname);
	  //TString drawstr = TString(sigratio)+Form(">>%s",mysighistname);

#if 1
	  cout <<
	    TString("wwtree->Draw(\"")+drawstr+TString("\", \"")+
	    TString((const char*)newcut)+TString("\", \"goff\")") << endl;
#endif

	  treeww->Draw(drawstr, newcut, "goff");
	  //treeww->Draw(drawstr, the_cut, "goff");

	  cout << TString(mysighistname)<< " nentries = " << stackhist->GetEntries() << endl;

	  stackhist->SetLineWidth(2);
	  stackhist->SetLineColor(1);
	  stackhist->SetFillColor(0);

	  stackhist->Scale(mc2data_scale*WW_scale);

	  //-------- Add overflow bin ----------------
	  AddOverflowBin(stackhist);

	  outputForLimit->cd();
	  stackhist->Write(); 
	  delete stackhist;
	}
      }
 


      outputForLimit->Close();

    } ///// close if saveDataCards_

    delete th1wwclone;
}


void makeATGCLimitDataCards(void)
{
  //makeATGCLimitDataCards(2);
  makeATGCLimitDataCards(3);
}

