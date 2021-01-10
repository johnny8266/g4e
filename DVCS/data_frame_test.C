#include <ROOT/RDataFrame.hxx>
#include <iostream>

using namespace std;
using vectorD = vector<double>;

void data_frame_test()
{
  ROOT::RDataFrame TDF("events", "../build/g4e_output_3000events.root");
 
  //  auto cutQ2 = [](double Q2) { return Q2 < 5.; };
  auto cutQ2 = [](ULong64_t event_id) { return event_id > 5.; };
  auto n_cut = [](const vectorD &hit_x) { return hit_x.size() > 1000; };

  auto nentries = TDF.Filter(n_cut, {"hit_x"}).Count();
  cout << *nentries << " passed all filters" << endl;
  
  auto entries2 = TDF.Filter("event_id > 10.").Count();
  cout << *entries2 << " event_id > 10" << endl;
  
  //  auto h = TDF.Histo1D("Q2");
  auto hist = TDF.Filter(cutQ2).Histo1D();
  hist->DrawCopy();
}
