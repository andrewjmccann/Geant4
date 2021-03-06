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
// $Id: G4MPIrandomSeedGenerator.hh,v 1.1 2007/11/16 14:05:40 kmura Exp $
// $Name: geant4-09-01-patch-02 $
//
// ====================================================================
//   G4MPIrandomSeedGenerator.hh
//
//                                         2007 Q
// ====================================================================
#ifndef G4MPI_RANDOM_SEED_GENERATOR_H
#define G4MPI_RANDOM_SEED_GENERATOR_H

#include "G4VMPIseedGenerator.hh"

// ====================================================================
//
// class definition
//
// ====================================================================

class G4MPIrandomSeedGenerator : public G4VMPIseedGenerator {
protected:
  G4bool CheckDoubleCount();
  virtual void GenerateSeeds();

public:
  G4MPIrandomSeedGenerator();
  ~G4MPIrandomSeedGenerator();

};

#endif
