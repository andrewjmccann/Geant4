/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CsSourceCapsule.h
 * @brief
 *
 * @date Mar 4, 2010
 *
 * @author hseywerd@nrcan.gc.ca
 **/

#ifndef CSSOURCECAPSULE_H_
#define CSSOURCECAPSULE_H_

#include "G4LogicalVolume.hh"

class CISensitiveMaterials;
class CIMaterials;

/**
 * @class CsSourceAssembly
 * @brief A logical volume representing a source assembly
 *
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 */
class CsSourceAssembly: public G4LogicalVolume  {
public:
	/**
	 * Create the PMT
	 * * @param name the name to assign to the device
	 */
	CsSourceAssembly(const G4String name, CISensitiveMaterials* pCISensitiveMaterials, const int type);

	/**
	 * Clean up
	 */
	~CsSourceAssembly();

	/// Return the positional offset of the source within the system
	inline const double GetSourceOffset() {
		return -1*m_HalfLength+2*m_PlugHalfLength+m_CapsuleHalfLength;
	}

private:

	/// Manage hits in materials
	CISensitiveMaterials* m_pCISensitiveMaterials;

	/// Defines what we implement in the capsule, 1 = full, 2 = no brass or lead.
	int m_iCapsuleType;

	/// How to show it
	G4VisAttributes* m_VisAttcapsule;

	/// Construction materials
	CIMaterials* m_Materials;


	/// Dimensions of enclosing volume (a brass cylinder) - outer radius
	static const G4double m_dOuterRadius;
	/// Dimensions of enclosing volume (a brass cylinder) - inner radius
	static const G4double m_dInnerRadius;
	/// Dimensions of enclosing volume (a brass cylinder) - length
	static const G4double m_HalfLength;

	/// Dimensions of source capsule itself - outer radius
	static const G4double m_dCapsuleRadius;
	/// Dimensions of source capsule itself - length
	static const G4double m_CapsuleHalfLength;

	///Dimensions of the lead source cylinder plug - radius
	static const G4double m_dPlugRadius;
	/// Dimensions of the lead source cylinder plug - length
	static const G4double m_PlugHalfLength;


  //Some useful string constants
  /// Indicates a logical volume
  static const G4String m_LogicalVolumeSuffix;
  /// Indicates a physical volume
  static const G4String m_PhysicalVolumeSuffix;
  /// Indicates an object representing a solid
  static const G4String m_SolidSuffix;

};

#endif /* CSSOURCECAPSULE_H_ */
