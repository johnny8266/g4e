//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: JLeicTrackingAction.hh 66587 2012-12-21 11:06:44Z ihrivnac $
//
/// \file electromagnetic/VertexEIC/include/JLeicTrackingAction.hh
/// \brief Definition of the JLeicTrackingAction class
//
#ifndef JLeicTrackingAction_h
#define JLeicTrackingAction_h

#include <unordered_map>

#include <G4UserTrackingAction.hh>
#include <G4GenericMessenger.hh>


class JLeicTrackingAction : public G4UserTrackingAction
{

public:
    JLeicTrackingAction();

    ~JLeicTrackingAction() override = default;

    void PreUserTrackingAction(const G4Track *) override;
    void PostUserTrackingAction(const G4Track *) override;

private:
    std::unordered_map<std::uint64_t, std::uint64_t> mTrackLevelsById;

    int mTrackKillAncestryLevel = 0;   // -1 - don't kill tracks based on Ancestry Level
    static G4GenericMessenger *mMessenger;
};

#endif

