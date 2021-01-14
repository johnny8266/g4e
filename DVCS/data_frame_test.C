#include <ROOT/RDataFrame.hxx>
#include <iostream>

using namespace std;
using vectorD = vector<double>;
using FourVector = ROOT::Math::XYZTVector;
using FourVectorVec = vector<FourVector>;
using FourVectorRVec = ROOT::VecOps::RVec<FourVector>;

void data_frame_test()
{
  //  ROOT::RDataFrame TDF("events", "../build/g4e_output_10k_events_crossing_angle.root", {"event_id"});
  ROOT::RDataFrame TDF("events", "../build/g4e_output_50events_for_test.root", {"event_id"});
  ROOT::RDataFrame TDF_vol_name("events", "../build/g4e_output_50events_for_test.root", {"hit_vol_name"});
  
  //  auto cutQ2 = [](double Q2) { return Q2 < 5.; };
  auto cutQ2 = [](ULong64_t event_id) { return event_id > 5.; };
  auto n_cut = [](const vectorD &hit_x) { return hit_x.size() > 1000; };
  auto cut_vol_name = [](vector<string> &hit_vol_name){return 0;};
        
   
  auto nentries = TDF.Filter(n_cut, {"hit_x"}).Count();
  cout << *nentries << " passed all filters" << endl;
  
  auto entries2 = TDF.Filter("hit_id > 0").Count();
  cout << *entries2 << " event_id > 10" << endl;
  
  //  auto entries3 = TDF_vol_name.Filter("hit_vol_name == ffi_RPOT_D2_lay_Phys_3").Count();
  //  cout << *entries3 << endl;

  
  /*

  auto getPt = [](const FourVectorRVec &tracks)
    {
     return ROOT::VecOps::Map(tracks, [](const FourVector& v){return v.Pt();});
    };

  auto augmented_d = TDF.Define("tracks_n", [](const FourVectorRVec &tracks) { return (int)tracks.size(); })
    .Filter([](int tracks_n) { return tracks_n > 2; }, {"tracks_n"})
    .Define("tracks_pts", getPt);

  auto trN = augmented_d.Histo1D({"", "", 40, -.5, 39.5}, "tracks_n");
  auto trPts = augmented_d.Histo1D("tracks_pts");

  //  auto c1 = new TCanvas();
  //  trN->DrawCopy();
   
  //  auto c2 = new TCanvas();
  //  trPts->DrawCopy();
  */


  //  auto hist = TDF.Filter(cutQ2).Histo1D();
  //  hist->DrawCopy();
}
