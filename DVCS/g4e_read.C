// =================================================================================
//
// (!!!) THIS EVENT LOOP METHOD IS SLOW IN ROOT INTERPRETTER
// It is only for a showcase

// Event loop (use pool or fancier TDataFrame for multithreaded processing, )
// Here is the examples of multicore usage:
// https://root.cern.ch/root/html608/dir_b2d2b4e27d077f7d4f8f12bfa35378a6.html
// And here is the TDataFrame
// https://root.cern.ch/doc/v610/classROOT_1_1Experimental_1_1TDataFrame.html

// Now we try to keep things simple for this example:

// =================================================================================
#include <ROOT/RDataFrame.hxx>
//using namespace ROOT::Experimental;

void g4e_read()
{

  //  TFile *file = TFile::Open("../build/g4e_output_10k_events.root");
  TFile *file = TFile::Open("../build/g4e_output_10k_events_crossing_angle.root");
  TTree *events = (TTree *) file->Get("events");

  TTreeReader fReader("events", file);

  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<ULong64_t>     event_id = {fReader, "event_id"};

  // Hits collections
  TTreeReaderValue<ULong64_t>     hit_count = {fReader, "hit_count"};
  TTreeReaderArray<unsigned long> hit_id = {fReader, "hit_id"};
  TTreeReaderArray<unsigned long> hit_trk_id = {fReader, "hit_trk_id"};
  TTreeReaderArray<unsigned long> hit_ptr_id = {fReader, "hit_ptr_id"};
  TTreeReaderArray<unsigned long> hit_parent_trk_id = {fReader, "hit_parent_trk_id"};  // PDG code of that particle
  TTreeReaderArray<string>        hit_vol_name = {fReader, "hit_vol_name"};
  TTreeReaderArray<double>        hit_x = {fReader, "hit_x"};
  TTreeReaderArray<double>        hit_y = {fReader, "hit_y"};
  TTreeReaderArray<double>        hit_z = {fReader, "hit_z"};
  TTreeReaderArray<double>        hit_e_loss = {fReader, "hit_e_loss"};

  // Tracks data
  TTreeReaderValue<ULong64_t>     trk_count = {fReader, "trk_count"};
  TTreeReaderArray<unsigned long> trk_id = {fReader, "trk_id"};
  TTreeReaderArray<long>          trk_pdg = {fReader, "trk_pdg"};
  TTreeReaderArray<unsigned long> trk_parent_id = {fReader, "trk_parent_id"};
  TTreeReaderArray<long>          trk_create_proc = {fReader, "trk_create_proc"};
  TTreeReaderArray<unsigned long> trk_level = {fReader, "trk_level"};
  TTreeReaderArray<double>        trk_vtx_x = {fReader, "trk_vtx_x"};
  TTreeReaderArray<double>        trk_vtx_y = {fReader, "trk_vtx_y"};
  TTreeReaderArray<double>        trk_vtx_z = {fReader, "trk_vtx_z"};
  TTreeReaderArray<double>        trk_vtx_dir_x = {fReader, "trk_vtx_dir_x"};
  TTreeReaderArray<double>        trk_vtx_dir_y = {fReader, "trk_vtx_dir_y"};
  TTreeReaderArray<double>        trk_vtx_dir_z = {fReader, "trk_vtx_dir_z"};
  TTreeReaderArray<double>        trk_mom = {fReader, "trk_mom"};

  // 'Copy' of generated particle data
  TTreeReaderValue<ULong64_t>     gen_prt_count = {fReader, "gen_prt_count"};
  TTreeReaderArray<unsigned long> gen_prt_id = {fReader, "gen_prt_id"};
  TTreeReaderArray<unsigned long> gen_prt_vtx_id = {fReader, "gen_prt_vtx_id"};
  TTreeReaderArray<unsigned long> gen_prt_pdg = {fReader, "gen_prt_pdg"};
  TTreeReaderArray<unsigned long> gen_prt_trk_id = {fReader, "gen_prt_trk_id"};
  TTreeReaderArray<double>        gen_prt_charge = {fReader, "gen_prt_charge"};
  TTreeReaderArray<double>        gen_prt_dir_x = {fReader, "gen_prt_dir_x"};
  TTreeReaderArray<double>        gen_prt_dir_y = {fReader, "gen_prt_dir_y"};
  TTreeReaderArray<double>        gen_prt_dir_z = {fReader, "gen_prt_dir_z"};
  TTreeReaderArray<double>        gen_prt_tot_mom = {fReader, "gen_prt_tot_mom"};
  TTreeReaderArray<double>        gen_prt_tot_e = {fReader, "gen_prt_tot_e"};
  TTreeReaderArray<double>        gen_prt_time = {fReader, "gen_prt_time"};
  TTreeReaderArray<double>        gen_prt_polariz_x = {fReader, "gen_prt_polariz_x"};
  TTreeReaderArray<double>        gen_prt_polariz_y = {fReader, "gen_prt_polariz_y"};
  TTreeReaderArray<double>        gen_prt_polariz_z = {fReader, "gen_prt_polariz_z"};
  TTreeReaderValue<ULong64_t>     gen_vtx_count = {fReader, "gen_vtx_count"};
  TTreeReaderArray<unsigned long> gen_vtx_id = {fReader, "gen_vtx_id"};
  TTreeReaderArray<unsigned long> gen_vtx_part_count = {fReader, "gen_vtx_part_count"};
  TTreeReaderArray<double>        gen_vtx_x = {fReader, "gen_vtx_x"};
  TTreeReaderArray<double>        gen_vtx_y = {fReader, "gen_vtx_y"};
  TTreeReaderArray<double>        gen_vtx_z = {fReader, "gen_vtx_z"};
  TTreeReaderArray<double>        gen_vtx_time = {fReader, "gen_vtx_time"};
  TTreeReaderArray<double>        gen_vtx_weight = {fReader, "gen_vtx_weight"};

  double mass_electron = 0.00051099895;
  double mass_proton = 0.0938271998;

  TFile save_pic("plots.root", "RECREATE");
  
  // =================================
  // Histgram
  // =================================
  auto electron_DPx_primary_recontruct = new TH1F("electron_DPx_primary_recontruct", "electron_DPx_primary_recontruct", 200, -0.1, 0.1);
  auto electron_DPz_primary_recontruct = new TH1F("electron_DPz_primary_recontruct", "electron_DPz_primary_recontruct", 200, -0.1, 0.1);
  auto photon_DPx_primary_recontruct = new TH1F("photon_DPx_primary_recontruct", "photon_DPx_primary_recontruct", 200, -0.1, 0.1);
  auto photon_DPy_primary_recontruct = new TH1F("photon_DPy_primary_recontruct", "photon_DPy_primary_recontruct", 200, -0.1, 0.1);
  auto photon_DPz_primary_recontruct = new TH1F("photon_DPz_primary_recontruct", "photon_DPz_primary_recontruct", 200, -0.1, 0.1);
  auto proton_DPx_primary_recontruct = new TH1F("proton_DPx_primary_recontruct", "proton_DPx_primary_recontruct", 200, -0.1, 0.1);
  auto proton_DPy_primary_recontruct = new TH1F("proton_DPy_primary_recontruct", "proton_DPy_primary_recontruct", 200, -0.1, 0.1);
  auto proton_DPz_primary_recontruct = new TH1F("proton_DPz_primary_recontruct", "proton_DPz_primary_recontruct", 200, -0.1, 0.1);
  //  auto h1_el_e_tot = new TH1D("rec_el_e_tot", "Energy of the recoil electron", 150, 0., 15.);
  auto h_x_hits_RPOT = new TH1F("h_x_hits_RPOT", "X hits in RPOT", 150, 700, 1000);
  auto h_y_hits_RPOT = new TH1F("h_y_hits_RPOT", "Y hits in RPOT", 40, -40, 40);
  auto h_z_hits_RPOT = new TH1F("h_z_hits_RPOT", "Z hits in RPOT", 55, 26090, 26200);
  auto h1_eloss_proton_RPOT = new TH1F("h1_eloss_proton_RPOT", "h1_eloss_proton_RPOT", 80, 0., 0.8);

  //  auto h2_xy_hits_elcap = new TH2I("xy_hits_elcap", "X,Y hits in Electron Endcap EMCAL", 200, -1500, 1500, 200, -1500, 1500);
  auto h2_eloss_proton_RPOT = new TH2F("h2_eloss_proton_RPOT", "h2_eloss_proton_RPOT", 4, 0, 4, 80, 0., 0.8);
  
  auto h3_xyz_hits_RPOT = new TH3F("h3_xyz_hits_RPOT", "X,Y,Z hits in RPOT", 150, 700, 1000, 40, -40, 40, 55, 26090, 26200);

  
  size_t events_numer = 0;

  //===============================================
  // Loop the Event
  //===============================================
  
  while (fReader.Next())
    {
      if(++events_numer > 7000)
	break;
      
      if(events_numer%100 == 0)
	cout << "Read " << events_numer << " th events..." << endl;
      
      std::unordered_set<uint64_t> track_ids_in_ecap_emcal;  // Get tracks information that have hits in ion EMCAL
      std::unordered_set<uint64_t> track_ids_in_ffi_RPOTS;  // Get tracks information that have hits in Roman Pots(FarForward ion direction area)
      
    
      // Read basic values
      auto hits_count = static_cast<size_t>(*hit_count.Get());         // Number of hits
      auto tracks_count = static_cast<size_t>(*trk_count.Get());       // Number of tracks
      //      cout << "This event has: " << tracks_count << " tracks || " << hits_count << " hits." << endl;

      
      // =============================
      // Primary Proton event
      // =============================
	      
      for(size_t i = 0 ; i < hits_count ; i++)
	{
	  // This is is of a track that made this hit
	  uint64_t hit_track_id = static_cast<uint64_t>(hit_trk_id[i]);
	  uint64_t hit_parent_track_id = static_cast<uint64_t>(hit_parent_trk_id[i]);
	  
	  // This is a volume name of a hit
	  std::string vol_name = static_cast<std::string>(hit_vol_name[i]);
		  
	  double x = hit_x[i], y = hit_y[i], z = hit_z[i];
	  double e_loss = hit_e_loss[i];
            
        
	  // Check that the name starts with "ci_EMCAL"
	  //	  if(vol_name.rfind("ci_EMCAL", 0) == 0)
	  if( (vol_name.rfind("cb_", 0) == 0) || (vol_name.rfind("ce_", 0) == 0) )
	    {
	      track_ids_in_ecap_emcal.insert(hit_track_id);
	      //	      cout << i << " || ";
	      //	      cout << hit_track_id << " || " << hit_parent_track_id <<  endl;
	      //	      h2_xy_hits_elcap->Fill(x, y);
	    }
		  
	  if(vol_name.rfind("ffi_RPOT_D2_lay_Phys_0", 0) == 0)
	    h2_eloss_proton_RPOT->Fill(0., (hit_e_loss[i] * 1000.));

	  if(vol_name.rfind("ffi_RPOT_D2_lay_Phys_1", 0) == 0)
	    h2_eloss_proton_RPOT->Fill(1., (hit_e_loss[i] * 1000.));

	  if(vol_name.rfind("ffi_RPOT_D2_lay_Phys_2", 0) == 0)
	    h2_eloss_proton_RPOT->Fill(2., (hit_e_loss[i] * 1000.));

	  if(vol_name.rfind("ffi_RPOT_D2_lay_Phys_3", 0) == 0)
	    h2_eloss_proton_RPOT->Fill(3., (hit_e_loss[i] * 1000.));

	  //	  if(vol_name.rfind("ffi_RPOT_D2_lay", 0) == 0)
	  if(vol_name.rfind("ffi", 0) == 0)
	    {
	      track_ids_in_ffi_RPOTS.insert(hit_track_id);
	      if(hit_trk_id[i] == 3)
		{
		  h_x_hits_RPOT->Fill(x);
		  h_y_hits_RPOT->Fill(y);
		  h_z_hits_RPOT->Fill(z);
		  h3_xyz_hits_RPOT->Fill(x, y, z);
		  h1_eloss_proton_RPOT->Fill( (hit_e_loss[i] * 1000.) );
		}
	      //	      cout << hit_trk_id[i] << "        " << hit_ptr_id[i] << "        " << hit_parent_trk_id[i] << "        " << vol_name << "        " << x << "  " << y << "  " <<  z << endl;
	    }
	    
	}
      
      // =============================
      // Iterate over tracks
      // =============================
      
      double px, py, pz, epx0, epy0, epz0, gpx0, gpy0, gpz0, ppx0, ppy0, ppz0;
      TLorentzVector lv;
      
      epx0 = gen_prt_dir_x[0] * gen_prt_tot_mom[0];
      epy0 = gen_prt_dir_y[0] * gen_prt_tot_mom[0];
      epz0 = gen_prt_dir_z[0] * gen_prt_tot_mom[0];
      
      gpx0 = gen_prt_dir_x[1] * gen_prt_tot_mom[1];
      gpy0 = gen_prt_dir_y[1] * gen_prt_tot_mom[1];
      gpz0 = gen_prt_dir_z[1] * gen_prt_tot_mom[1];

      ppx0 = gen_prt_dir_x[2] * gen_prt_tot_mom[2];
      ppy0 = gen_prt_dir_y[2] * gen_prt_tot_mom[2];
      ppz0 = gen_prt_dir_z[2] * gen_prt_tot_mom[2];
      	    
      //      cout << px0 << " " << py0 << " " << pz0 << endl;

      for(size_t i = 0 ; i < tracks_count ; i++)
	{
	  //	  if(trk_pdg[i] != 11) continue;       // Take only electrons for now
	  //	  if(trk_pdg[i] != 22) continue;       // Take only photons for now
	  if(trk_parent_id[i] != 0) continue;  // Take only particles from a generator

	  // Check track has hits in far ion region
	  if( track_ids_in_ffi_RPOTS.count( trk_id[i]) )
	    {
	      px = trk_vtx_dir_x[i] * trk_mom[i];
	      py = trk_vtx_dir_y[i] * trk_mom[i];
	      pz = trk_vtx_dir_z[i] * trk_mom[i];

	      lv.SetXYZM(px, py, pz, mass_proton);

	      proton_DPx_primary_recontruct->Fill(ppx0 - lv.Px());
	      proton_DPy_primary_recontruct->Fill(ppy0 - lv.Py());
	      proton_DPz_primary_recontruct->Fill(ppz0 - lv.Pz());
	    }
		    
	  
	  // Check track has hits in eletron or inner barrel region
	  if( track_ids_in_ecap_emcal.count( trk_id[i]) )
	    {
	      //continue;
	      //	      cout << "track in the ce_EMCAL, particle: " << trk_pdg[i] << endl;
	      // Construct TLorenz vector
	      px = trk_vtx_dir_x[i] * trk_mom[i];
	      py = trk_vtx_dir_y[i] * trk_mom[i];
	      pz = trk_vtx_dir_z[i] * trk_mom[i];

	      lv.SetXYZM(px, py, pz, mass_electron);
	      //	      h1_el_e_tot->Fill(lv.Energy());

	      if(trk_pdg[i] == 11)
		{
		  electron_DPx_primary_recontruct->Fill(epx0 - (lv.Px()));
		  electron_DPz_primary_recontruct->Fill(epz0 - (lv.Pz()));
		}
	      if(trk_pdg[i] == 22)
		{
		  photon_DPx_primary_recontruct->Fill(gpx0 - (lv.Px()));
		  photon_DPy_primary_recontruct->Fill(gpy0 - (lv.Py()));
		  photon_DPz_primary_recontruct->Fill(gpz0 - (lv.Pz()));
		}
	      
	      //	      cout << epx0 - (lv.Px()) << "  " << epy0 - (lv.Py()) << "  " << epz0 - (lv.Pz()) << "  ";
	      //	      cout << trk_id[i] << endl;
	    }
	}
    }


  
  // ======================================
  // Draw the Results
  // ======================================
  
  auto c1 = new TCanvas("c1","The Canvas Title",800,800);
  h2_eloss_proton_RPOT->GetXaxis()->SetNdivisions(4, kTRUE);
  h2_eloss_proton_RPOT->Draw("colorz");

  h1_eloss_proton_RPOT->GetXaxis()->SetTitle("[MeV]");
  h1_eloss_proton_RPOT->Draw();

  h_x_hits_RPOT->Draw();

  h_y_hits_RPOT->Draw();
  
  h_z_hits_RPOT->Draw();

  h3_xyz_hits_RPOT->GetXaxis()->SetTitle("X");
  h3_xyz_hits_RPOT->GetXaxis()->CenterTitle();
  h3_xyz_hits_RPOT->GetYaxis()->SetTitle("Y");
  h3_xyz_hits_RPOT->GetYaxis()->CenterTitle();
  h3_xyz_hits_RPOT->GetZaxis()->SetTitle("Z");
  h3_xyz_hits_RPOT->GetZaxis()->CenterTitle();
  //  h3_xyz_hits_RPOT->Draw("box");

  
  auto c2 = new TCanvas("c2","The Canvas Title", 1200, 800);
  c2->Divide(3,2);
  c2->cd(1);
  photon_DPx_primary_recontruct->GetXaxis()->SetTitle("PX0 - PX1");
  //  photon_DPx_primary_recontruct->Draw();
  c2->cd(2);
  photon_DPy_primary_recontruct->GetXaxis()->SetTitle("PY0 - PY1");
  //  photon_DPy_primary_recontruct->Draw();
  c2->cd(3);
  photon_DPz_primary_recontruct->GetXaxis()->SetTitle("PZ0 - PZ1");
  //  photon_DPz_primary_recontruct->Draw();
  c2->cd(4);
  electron_DPx_primary_recontruct->GetXaxis()->SetTitle("PX0 - PX1");
  //  electron_DPx_primary_recontruct->Draw();
  c2->cd(6);
  electron_DPz_primary_recontruct->GetXaxis()->SetTitle("PZ0 - PZ1");
  electron_DPz_primary_recontruct->Draw();

  
  auto c3 = new TCanvas("c3","The Canvas Title", 1200, 400);
  c3->Divide(3, 1);
  c3->cd(1);
  proton_DPx_primary_recontruct->Draw();
  c3->cd(2);
  proton_DPy_primary_recontruct->Draw();
  c3->cd(3);
  proton_DPz_primary_recontruct->Draw();
    
  
  save_pic.Write();
  save_pic.Close();
}
