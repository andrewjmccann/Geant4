///***************************************************************************


/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2009.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIPhysicsList.h
 * @brief Build all the physics processes
 *
 * @date 2009-11-14
 *
 * @author hseywerd@nrcan.gc.ca
 **/

#ifndef CIPhysicsList_H_
#define CIPhysicsList_H_
#include "G4VModularPhysicsList.hh"
#include "G4EmConfigurator.hh"

class G4DecayPhysics;
class G4RadioactiveDecayPhysics;
class G4EmStandardPhysics;


class CIPhysicsListMessenger;

class CIPhysicsList : public G4VModularPhysicsList{
public:
	CIPhysicsList();
	virtual ~CIPhysicsList();
	void ConstructParticle();
	void ConstructProcess();
	void ConstructGeneral();
	void SetCuts();
	/**
	 * Sets parameters for the optical processes to be invoked
	 * @param newValue
	 */
	inline void SetOpticalProcesses(const G4bool newValue) {
		m_bUseOptical = newValue;
	}
	;
	/**
	 * Sets parameters to invoke G4LECS package
	 * @param newValue  if true G4LECS will be used.
	 */
	inline void SetG4LECS(const G4bool newValue) {
		m_bUseG4LECS = newValue;
	}
	;
	void AddPhysicsList(const G4String& name);

private:
//	/*
//	 * Build processes for transportation
//	 */
//	void AddTransportation();
	/**
	 * Build electromagnetic processes
	 */
	void ConstructEM();

	/// Pointer to the messenger for UI interaction
	CIPhysicsListMessenger* m_pMessenger;

	/// General decay processes
	G4DecayPhysics* m_pDecayPhysics;
	/// For radioactive decay
	G4RadioactiveDecayPhysics* m_pRadioactiveDecayPhysics;
	/// Electromagnetic processes
	G4VPhysicsConstructor* m_EMPhysicsList;
  /// To set up different models for EM physics
  G4EmConfigurator m_EMConfigurator;

  /// If true G4LECS package will be used.
	G4bool m_bUseG4LECS;
	/// If true optical processes will be simulated
	G4bool m_bUseOptical;
	/// If true will simulate point source rather than use particle gun
	G4bool m_bUsePointSource;

 static const G4String m_strParallelWorldName;
  G4double fCutForGamma;
  G4double fCutForElectron;
  G4double fCutForPositron;

  G4bool   fHelIsRegisted;
  G4bool   fBicIsRegisted;
  G4bool   fBiciIsRegisted;
    
  G4String                             fEmName;
  G4VPhysicsConstructor*               fEmPhysicsList;

};

#endif /* CIPhysicsList_H_ */
