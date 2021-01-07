#include <ROOT/RDataFrame.hxx>
#include <iostream>
using namespace std;
//using namespace ROOT::Experimental;

void data_frame_test()
{

  //  TFile *file = TFile::Open("../build/g4e_output_3000events.root");
  //  TTree *events = (TTree *) file->Get("events");

  //  ROOT::RDataFrame TDF("events", "../build/g4e_output_3000events.root");
  ROOT::RDataFrame TDF("DVCS", "result_foam.root", {"Q2"});

  auto cutQ2 = [](double Q2) { return Q2 < 5.; };
  
  auto entries2 = TDF.Filter("Q2 < 10.").Count();
  cout << *entries2 << endl;
  
  //  auto h = TDF.Histo1D("Q2");
  auto hist = TDF.Filter(cutQ2).Histo1D();
  hist->DrawCopy();
}
