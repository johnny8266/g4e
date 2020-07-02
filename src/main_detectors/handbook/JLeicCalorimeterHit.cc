#include "JLeicCalorimeterHit.hh"

// Using G4ThreadLocal external JLeicCalorHitAllocator as was suggested in
//
G4ThreadLocal G4Allocator<JLeicCalorimeterHit>* JLeicCalorHitAllocator = nullptr;


JLeicCalorimeterHit::JLeicCalorimeterHit()
{
    fEdepAbs = 0.;
    fTrackLengthAbs = 0.;
    fEdepGap = 0.;
    fTrackLengthGap = 0.;
}

JLeicCalorimeterHit::~JLeicCalorimeterHit() = default;


/*
JLeicCalorHit::JLeicCalorHit(const JLeicCalorHit& right)
{
  EdepAbs = right.EdepAbs; TrackLengthAbs = right.TrackLengthAbs;
  EdepGap = right.EdepGap; TrackLengthGap = right.TrackLengthGap;
}
*/


const JLeicCalorimeterHit& JLeicCalorimeterHit::operator=(const JLeicCalorimeterHit& right)
{
    fEdepAbs = right.fEdepAbs;
    fTrackLengthAbs = right.fTrackLengthAbs;

    fEdepGap = right.fEdepGap;
    fTrackLengthGap = right.fTrackLengthGap;
  return *this;
}



void JLeicCalorimeterHit::Print()
{;}



