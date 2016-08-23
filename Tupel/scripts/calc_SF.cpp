 #include "TStyle.h"
 #include "TFile.h"
 #include "TTree.h"
 #include "TH2.h"
 #include "TLegend.h"
 #include "TCanvas.h"
 #include "TROOT.h"
 #include "TAxis.h"
 #include <vector>
 #include <iostream>
 #include <sstream>
 #include <iomanip>
 #include <math.h>

void ratio_lat()  {
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1);

  double bincontnt = 0.0;
  double xcenter = 0.0;
  double ycenter =0.0;
  int d=10;

  TCanvas *C1 = new TCanvas("MyC1","Ratio canvas",10,10,800,800);
//  TFile *f1       = new TFile("/user/mgul/root_files_muon/ttbar_isElec_0.root");
//  TFile *f1       = new TFile("testoutput_0000_1.root");
  TFile *f1       = new TFile("root_files/ttbar_isElec_1.root");

  TString channel = "mu";
  TString sig = "ttbar";
   
  TH2D *h3     = (TH2D*)f1->Get("eljets_2btag/metptshapes_exp");
  TH1D *hn     = (TH1D*)f1->Get("eljets_2btag/MET_E");
//  TH2D *h3     = (TH2D*)f1->Get("eljets_2btag/ncjetshapes_exp");
//  TH1D *hn     = (TH1D*)f1->Get("eljets_2btag/n_cjets_aft");

//   TH1D *h1  = new TH1D("h1", "h1", 5, 1, 6);
//   TH1D *h2  = new TH1D("h2", "h2", 5, 1, 6);
   TH1D *h1  = new TH1D("h1", "h1", 100, 0., 200.);
   TH1D *h2  = new TH1D("h2", "h2", 100, 0., 200.);


   //   TH1D *h1  = new TH1D("h1", "h1", 5, 1., 6.);
   //   TH1D *h2  = new TH1D("h2", "h2", 5, 1., 6.);

  cout<<"No of bins h3:  "<<h3->GetXaxis()->GetNbins()<<endl;
  cout<<"xmin xmax h3:  "<<h3->GetXaxis()->GetXmin()<<",   "<<h3->GetXaxis()->GetXmax()<<endl;
  cout<<"No of bins hn:  "<<hn->GetXaxis()->GetNbins()<<endl;
  cout<<"xmin xmax h3:  "<<hn->GetXaxis()->GetXmin()<<",   "<<hn->GetXaxis()->GetXmax()<<endl;


   double bin_content_u, bin_content_d;
   int ibin_d, ibin_u;
   std::cout<< "NBinsX : " << h3->GetXaxis()->GetNbins()<< "Y Bins : "<< h3->GetYaxis()->GetNbins()  << std::endl;
   std::cout<< "BinsX contents h3: " << h3->GetBinContent(5) << std::endl;
   std::cout<< "BinsX contents hn: " << hn->GetBinContent(5) << std::endl;

   //      for (int j=1; j<h3->GetYaxis()->GetNbins(); j=j+2)
   //	{
   for (int i=0;i<=h3->GetXaxis()->GetNbins();i++) 
     {
       ibin_d = h3->GetBin(i,5);
       ibin_u = h3->GetBin(i,6);
       bin_content_d = h3->GetBinContent(ibin_d);
       bin_content_u = h3->GetBinContent(ibin_u);
       
       	      std::cout << "i: " << i << " ibin down: " << ibin_d << " ibin up : " << ibin_u<< " down : " << bin_content_d 
       			<< " up : " << bin_content_u << " nominal : " << hn->GetBinContent(i) <<std::endl;
       h1->SetBinContent(i,bin_content_u);
       h2->SetBinContent(i,bin_content_d);

     }
   
   

   /*
     h1->Scale(1/h1->Integral());
     h2->Scale(1/h2->Integral());
     hn->Scale(1/hn->Integral());
   */
   h1->SetLineColor(kRed);
   h2->SetLineColor(kBlue);
   hn->SetLineColor(kGreen);
   
   hn->Draw("hist");
   h1->Draw("hist sames");
   h2->Draw("hist sames");
   
   //   std::cout << "systematics : "<< 0.5 * 100 *  ( (h1->Integral() - h2->Integral() )/hn->Integral())<<std::endl;
   std::cout << "systematics : "<< 0.5 * 100 *  ( (h1->GetSumOfWeights() - h2->GetSumOfWeights() )/hn->GetSumOfWeights())<<std::endl;
   //      string s1 = "Results/Files_23July/"+obs+".png";
   //      c1->SaveAs(s1.c_str());
   
   //	}
   
   TLegend *leg = new TLegend(0.65,0.6541451,0.8429648,0.8873057,NULL,"brNDC");
   //TLegend *leg = new TLegend(0.7324121,0.6541451,0.8429648,0.8873057,NULL,"brNDC");                              
   //TLegend *leg = new TLegend(0.7236181,0.5947446,0.8228643,0.8797187,NULL,"brNDC");                              
   leg->SetFillColor(0);
   leg->SetBorderSize(0);
   leg->SetTextFont(42);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   
   leg->AddEntry(hn,"Nominal","l");
   leg->AddEntry(h1,"Up","l");//"lpe");                                                            
   leg->AddEntry(h2,"Dn","l");//"lpe");                                                            
   leg->Draw();

   TLatex * tex2 = new TLatex(0.12,0.76,channel);
   tex2->SetNDC();
   tex2->SetTextAlign(61);
   tex2->SetTextFont(42);
   tex2->SetTextSize(0.058);
   tex2->SetLineWidth(2);
   //   tex2->Draw();

   TLatex * tex3 = new TLatex(0.12,0.83,""+sig+" file" );
   tex3->SetNDC();
   tex3->SetTextAlign(61);
   tex3->SetTextFont(42);
   tex3->SetTextSize(0.058);
   tex3->SetLineWidth(2);

   C1->SaveAs("sys_13tev/" +sig+ "_" +channel+ ".png");
   
}
