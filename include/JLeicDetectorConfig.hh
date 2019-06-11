//
// Created by yulia on 6/6/19.
//

#ifndef G4E_JLeicDetectorParameters_HH
#define G4E_JLeicDetectorParameters_HH

#include "cb_Solenoid/cb_Solenoid.hh"

#include "cb_VTX/cb_VTX.hh"
#include "cb_CTD/cb_CTD.hh"
#include "cb_DIRC/cb_DIRC.hh"
#include "cb_EMCAL/cb_EMCAL.hh"
#include "cb_HCAL/cb_HCAL.hh"


#include "ce_MRICH/ce_MRICH.hh"

#include "ffe_CPOL/ffe_CPOL.hh"


struct JLeicDetectorConfig {

    struct World_Config {
        double ShiftVTX = 40. * cm;
        double SizeR = 10000. * cm;
        double SizeZ = 20000. * cm;
    } World;

    struct ci_Endcap_Config {
        double RIn = 20. * cm;
        double ROut = NAN;
        double SizeZ = 250 * cm;
        double ShiftZ = 0. * cm;
        double PosX = 0. * cm;
        double PosZ = 0. * cm;
    } ci_Endcap;

    struct ce_Endcap_Config {
        double RIn = 20 * cm;
        double SizeZ = 60 * cm;
        double PosZ = NAN;
        double ROut = NAN;
    } ce_Endcap;


    //------------ BAREL-----
    cb_Solenoid_Config cb_Solenoid;

    cb_VTX_Config   cb_VTX;
    cb_CTD_Config   cb_CTD;
    cb_DIRC_Config  cb_DIRC;
    cb_EMCAL_Config cb_EMCAL;
    cb_HCAL_Config  cb_HCAL;
    //------------E-ENDCAP-----

    ce_MRICH_Config  ce_MRICH;

    //------------Far-Forward-Electron-----
    ffe_CPOL_Config ffe_CPOL;

    //------------H-ENDCAP-----

    //------------Far-Forward-Ion-----


} ;

#endif //G4E_JLeicDetectorParameters_HH
