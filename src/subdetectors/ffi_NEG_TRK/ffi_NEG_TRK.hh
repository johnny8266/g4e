//
// Created by yulia on 9/18/19.
//

#ifndef G4E_FFI_NEG_TRK_HH
#define G4E_FFI_NEG_TRK_HH



#include <G4PVDivision.hh>
#include "G4RotationMatrix.hh"
#include "G4Material.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

#include "JLeicDetectorConfig.hh"

struct ffi_NEG_TRK_Config {
// define here Global volume parameters
  //  double Rin = 0 * cm;
  //  double ROut;
    double SizeX=200 *cm;
    double SizeY=100*cm; 
    double SizeZ = 30 * cm;
    double Zpos;
    double Xpos;
   double Angle =-90*deg;
   G4RotationMatrix rot_matx;


    int Nlayers=1;
    double lay_Zshift=1.*cm;


};


class ffi_NEG_TRK_Design {
public:
    inline void Construct(ffi_NEG_TRK_Config cfg, G4Material *worldMaterial, G4VPhysicalVolume *motherVolume) {
        printf("Begin ffi_NEG_TRK volume \n");

        ConstructionConfig = cfg;
        // create  a global volume for your detectors

	//       Solid = new G4Tubs("ffi_NEG_TRK_GVol_Solid",cfg.RIn, cfg.ROut,
	//                  cfg.SizeZ / 2., 0., 360 * deg);
        Solid = new G4Box("ffi_NEG_TRK_GVol_Solid",cfg.SizeX /2., cfg.SizeY/2., cfg.SizeZ / 2.);

 
        Logic = new G4LogicalVolume(Solid, worldMaterial, "ffi_NEG_TRK_GVol_Logic");

        // ci_GEM_GVol_PosZ= SizeZ/2-abs(World_ShiftVTX)+ci_GEM_GVol_SizeZ-5*cm;   // --- need to find out why this 5 cm are needed
        Phys = new G4PVPlacement(G4Transform3D(cfg.rot_matx, G4ThreeVector(cfg.Xpos, 0, cfg.Zpos)), "ffi_NEG_TRK_GVol_Phys", Logic,
                                 motherVolume, false, 0);

        //  G4VisAttributes* vgemff= new G4VisAttributes(G4Color(0.8,0.4,0.3,0.8));
        G4VisAttributes *attr_fi_D1A_GVol = new G4VisAttributes(G4Color(0.3, 0, 3., 0.1));
        attr_fi_D1A_GVol->SetLineWidth(1);
        attr_fi_D1A_GVol->SetForceSolid(true);
        Logic->SetVisAttributes(attr_fi_D1A_GVol);


    };

    inline void ConstructDetectors() {
        printf("Begin ffi_NEG_TRK detector volumes \n");
        auto cfg = ConstructionConfig;

        // construct here your detectors

        // ---------------------------------------------------------------------------
        //                     D1 tracking  all
        // ---------------------------------------------------------------------------
	//    ffi_NEG_TRK_lay_RIn = 10 * cm;
	//    ffi_NEG_TRK_lay_ROut = cfg.ROut - 5 * cm;
        ffi_NEG_TRK_lay_SizeZ = 1 * cm;
        //   ffi_NEG_TRK_lay_Material = fMat->GetMaterial("Ar10CO2");  //----   !!!!! ----
        ffi_NEG_TRK_lay_Material =G4Material::GetMaterial("G4_Galactic");
	//       lay_Solid = new G4Tubs("ffi_NEG_TRK_lay_Solid", ffi_NEG_TRK_lay_RIn, ffi_NEG_TRK_lay_ROut,
        //                              ffi_NEG_TRK_lay_SizeZ / 2., 0., 360 * deg);
        lay_Solid = new G4Box("ffi_NEG_TRK_lay_Solid",cfg.SizeX /2.-1*mm, cfg.SizeY/2.-1*mm ,
                                      ffi_NEG_TRK_lay_SizeZ / 2.);
        lay_Logic = new G4LogicalVolume(lay_Solid, ffi_NEG_TRK_lay_Material, "ffi_NEG_TRK_lay_Logic");



        int ffsi_counter = 0;
        for (int fflay = 0; fflay < cfg.Nlayers; fflay++) {
            double Z = -cfg.SizeZ / 2 + (fflay + 1) * ffi_NEG_TRK_lay_SizeZ / 2 + (fflay + 1) * cfg.lay_Zshift;
            lay_Phys = new G4PVPlacement(0, G4ThreeVector(0, 0, Z),
                                                "ffi_NEG_TRK_lay_Phys", lay_Logic,
                                                Phys, false, ffsi_counter);
            ffsi_counter++;
            attr_fi_NEG_TRK_lay = new G4VisAttributes(G4Color(0.8, 0.4 + 0.1 * fflay, 0.3, 1.));
            attr_fi_NEG_TRK_lay->SetLineWidth(1);
            attr_fi_NEG_TRK_lay->SetForceSolid(true);
            lay_Logic->SetVisAttributes(attr_fi_NEG_TRK_lay);
        }

    };

  //    G4Tubs *Solid;      //pointer to the solid
     G4Box *Solid;      //pointer to the solid
    G4LogicalVolume *Logic;    //pointer to the logical
    G4VPhysicalVolume *Phys;  //pointer to the physical

    /// Parameters that was used in the moment of construction
    ffi_NEG_TRK_Config  ConstructionConfig;
  //   G4Tubs *lay_Solid;    //pointer to the solid  FARFORWD
    G4Box *lay_Solid;    //pointer to the solid  FARFORWD
    G4LogicalVolume *lay_Logic;    //pointer to the logical FARFORWD
    G4VPhysicalVolume *lay_Phys;    //pointer to the physical FARFORWD

     G4double ffi_NEG_TRK_lay_RIn;
    G4double ffi_NEG_TRK_lay_ROut;
    G4double ffi_NEG_TRK_lay_SizeZ;

private:

    // define here local variables and parameter of detectors

    G4Material *ffi_NEG_TRK_lay_Material;
    G4VisAttributes* attr_fi_NEG_TRK_lay;


};



#endif //G4E_FFI_NEG_TRK_HH
