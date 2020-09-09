/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CIPrimaryGeneratorAction.h
 * @brief Generate the primary particle
 **/
#ifndef CIPrimaryGeneratorAction_h
#define CIPrimaryGeneratorAction_h
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Types.hh"
#include "G4ThreeVector.hh"


class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;
class CIPrimaryGeneratorMessenger;
#include "CIRootRunHeader.h"

/**
 * @brief Action class for primary vertex/particle generation.
 *
 * Implements GeneratePrimaries() which is invoked from G4RunManager during the event loop
 * Generates a gamma with setable energy, and initial vertex at the origin, and moving in +z direction
 *
 * If G4GPS is used to generate the primary gammas the following should be cards should be placed
 * in the user macro file:
 * - /ComptonImager/PrimaryGenerator/GenerateByGPS
 * - /gps/particle gamma
 * - /gps/pos/type Point
 * - /gps/pos/centre 0., 0., -5. m
 * - /gps/energy 662 keV
 * - /gps/ang/type iso
 * This will generate an isotropic gamma field with an origin at (0,0,-5), with an energy of 662keV.
 *
 *
 @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */
class CIPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    /**
     * Construct the generator
     */
    CIPrimaryGeneratorAction ();

    ~CIPrimaryGeneratorAction();

    /**
     * @brief Generate the primary particle, i.e. the gamma, for the event. invoked from G4RunManager during the event loop
     *
     * Invoked from G4RunManager during the event loop.
     * Generates a single gamma of the preset energy value going along the z axis.
     * @param event pointer to the event
     */
    void GeneratePrimaries (G4Event* event);

    /**
     * Set the energy of the incoming gamma in this event
     * @param energy energy of the incoming gamma - for G4ParticleGun
     */
    inline void SetPrimaryEnergy (const G4double energy) {m_dGammaEnergy = energy;};
    /**
     * Get the energy of the incoming gamma in this event
     * @return energy of the incoming gamma
     */
    inline double GetPrimaryEnergy() const {return m_dGammaEnergy;};

    /// Enable generation of NORM background
    inline void SetNORMGeneration (const bool generate) {m_bGenerateNORM = generate;};

		/// Enable generation by G4GPS
    inline void SetG4GPSPointSourceGeneration (const bool generate) {m_bGenerateG4GPS = generate;};

    /// Return the energy of the source - first source
    G4double GetESource1() const;
    /// Return the energy of the source - second source -- not implemented
    G4double GetESource2()  const {return -1.0;}
    /// Return the intensity of the source - first source
    G4double GetISource1()  const {return 1.0;}
    /// Return the intensity of the source - second source -- not implemented
    G4double GetISource2()  const {return -1.0;}
    /// Return the type of the source -- for now just the simplest thing
    CIRootRunHeader::STYPE GetSourceType() const {return CIRootRunHeader::STYPE_MONO;}

    G4ThreeVector GetSource1Postion() const;

  private:
    /// The particle gun
    G4ParticleGun*                m_pParticleGun;

    /// Gamma initial energy (keV) for G4ParticleGun only
    G4double m_dGammaEnergy;

    /// Primary vertex position -- for G4ParticleGun only
    G4ThreeVector m_PrimaryVertexPos;

    /// If true generate Naturally Occuring Radioactive Material Background distributions (NORM)
    G4bool m_bGenerateNORM;

    /// If true generate primary with point source via G4GPS
    G4bool m_bGenerateG4GPS;

    /// A G4GPS source for particles,
    G4GeneralParticleSource*			m_pG4GPS;

    /// Pointer to the UI messenger
    CIPrimaryGeneratorMessenger* m_pCIPrimaryGeneratorMessenger;
};

#endif
