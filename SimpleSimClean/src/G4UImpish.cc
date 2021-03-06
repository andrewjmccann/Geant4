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
// $Id: G4UImpish.cc,v 1.1 2007/11/16 14:05:41 kmura Exp $
// $Name: geant4-09-01-patch-02 $
//
// ====================================================================
//   G4UImpish.cc
//
//                                         2007 Q
// ====================================================================
#ifdef G4MPI_USE
#include "G4UImpish.hh"

// ====================================================================
//
// class description
//
// ====================================================================

//////////////////////
G4UImpish::G4UImpish()
  : G4VUIshell("")
//////////////////////
{
}

///////////////////////
G4UImpish::~G4UImpish()
///////////////////////
{
}

///////////////////////////////////////////////
G4String G4UImpish::GetCommandLine(const char*)
///////////////////////////////////////////////
{
  G4String newCommand;

  // recieve command string from master
  G4cout << "hoge hoge" << G4endl;

  return newCommand;
}

#endif
