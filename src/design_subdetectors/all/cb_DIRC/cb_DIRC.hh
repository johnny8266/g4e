//
// Created by yulia on 6/7/19.
//

#ifndef G4E_CB_DIRC_HH
#define G4E_CB_DIRC_HH

#include <G4PVDivision.hh>
#include <G4PhysicalConstants.hh>
#include "G4RotationMatrix.hh"
#include "G4Material.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include <spdlog/spdlog.h>

#include "../../../design_main/jleic/JLeicDetectorConfig.hh"

struct cb_DIRC_Config
{

    G4double RIn;
    G4double ROut;
    G4double SizeZ;

};

class cb_DIRC_Design
{
public:
    inline void Construct(cb_DIRC_Config cfg, G4Material *worldMaterial, G4VPhysicalVolume *motherVolume)
    {
        ConstructionConfig = cfg;

        Solid = new G4Tubs("cb_DIRC_GVol_Solid", cfg.RIn, cfg.ROut, cfg.SizeZ / 2., 0., 360 * deg);
        Logic = new G4LogicalVolume(Solid, worldMaterial, "cb_DIRC_GVol_Logic");
        Phys = new G4PVPlacement(nullptr, G4ThreeVector(), "DIRC", Logic, motherVolume, false, 0);

        // cb_DIRC_GVol_Logic->SetVisAttributes(G4VisAttributes::Invisible);
        G4VisAttributes *visAttr = new G4VisAttributes(G4Color(0.1, 0, 1., 0.1));
        visAttr->SetLineWidth(1);
        visAttr->SetForceSolid(false);
        Logic->SetVisAttributes(visAttr);

    }

    G4Tubs *Solid;      //pointer to the solid
    G4LogicalVolume *Logic;    //pointer to the logical
    G4VPhysicalVolume *Phys;  //pointer to the physical
    G4UniformMagField *MagneticField;      //pointer to the magnetic field

    /// Parameters that was used in the moment of construction
    cb_DIRC_Config ConstructionConfig;

    inline void ConstructBars()
    {
        auto cfg = ConstructionConfig;

        printf("CB_DIRC:: \n");
        cb_DIRC_bars_DZ = cfg.SizeZ;
        cb_DIRC_bars_DY = 42. * cm;
        cb_DIRC_bars_DX = 1.7 * cm;
        //   dR =  cb_DIRC_GVol_RIn+3.*cm;
        double dR = 83.65 * cm;

        double myL = 2 * pi * dR;
        int NUM = myL / cb_DIRC_bars_DY;

        /*     for(int i=0;i<2; i++){
          double LN = cb_DIRC_bars_DY * NUM;
          double LN1 = cb_DIRC_bars_DY * (NUM+1+i);
        printf("cb_DIRC_bars:: LN= Orig NUM=%d\n",NUM);
        if (LN/LN1>0.8) NUM=NUM+1;
        printf("cb_DIRC_bars:: LN=%f, LN1=%f  delenie=%f NUM=%d \n",LN,LN1,LN/LN1,NUM);
        }
        */
        cb_DIRC_bars_deltaphi = 2 * 3.1415926 / NUM;

        cb_DIRC_bars_Material = G4Material::GetMaterial("quartz");

        cb_DIRC_bars_Solid = new G4Box("cb_DIRC_bars_Solid", cb_DIRC_bars_DX / 2., cb_DIRC_bars_DY / 2., cb_DIRC_bars_DZ / 2.);

        cb_DIRC_bars_Logic = new G4LogicalVolume(cb_DIRC_bars_Solid, cb_DIRC_bars_Material, "cb_DIRC_bars_Logic");

        attr_cb_DIRC_bars = new G4VisAttributes(G4Color(0., 1., 0., 1.0));
        attr_cb_DIRC_bars->SetForceSolid(true);
        cb_DIRC_bars_Logic->SetVisAttributes(attr_cb_DIRC_bars);

        for (int ia = 0; ia < NUM; ia++) {
            // for (int ia = 0; ia < 1; ia++) {
            //for (int ia=0;ia<1;ia++) {
            printf("cb_DIRC_bars:: la =%d NUM=%d, dR=%f cb_DIRC_bars_deltaphi=%f  \n", ia, NUM, dR, cb_DIRC_bars_deltaphi);

            double phi = (ia * (cb_DIRC_bars_deltaphi));
            double x = -dR * cos(phi);
            double y = -dR * sin(phi);
            G4RotationMatrix rm_dirc;
            rm_dirc.rotateZ(cb_DIRC_bars_deltaphi * ia);
            //	rm[lay][ia].rotateZ(cb_DIRC_bars_deltashi);

            printf("cb_DIRC_bars::   %d x=%f  y=%f  \n", ia, x, y);
            auto name = fmt::format("cb_DIRC_bars_Phys_{}", ia);
            cb_DIRC_bars_Phys = new G4PVPlacement(G4Transform3D(rm_dirc, G4ThreeVector(x, y, 0)), name, cb_DIRC_bars_Logic, Phys, false, 0);
        }
    }

private:

    //--------------DIRC bars detector----------------------

    G4double cb_DIRC_bars_RIn;
    G4double cb_DIRC_bars_ROut;
    G4double cb_DIRC_bars_DZ;
    G4double cb_DIRC_bars_DY;
    G4double cb_DIRC_bars_DX;
    G4double cb_DIRC_bars_deltaphi;

    G4Material *cb_DIRC_bars_Material;
    G4VisAttributes *attr_cb_DIRC_bars;
    // G4Tubs*            cb_DIRC_bars_Solid;    //pointer to the solid World
    G4Box *cb_DIRC_bars_Solid;    //pointer to the solid World
    G4LogicalVolume *cb_DIRC_bars_Logic;    //pointer to the logical World
    G4VPhysicalVolume *cb_DIRC_bars_Phys;    //pointer to the physical World
    //*************************************************************

};

#endif //G4E_CB_DIRC_HH
