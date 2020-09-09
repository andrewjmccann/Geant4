/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CIDetectorConstruction.h
 * @brief Abstract base class for all CIDetectorConstruction objects
 *
 * Provides a defined interface for other parts of the program from which detector characteristics may be inquired.
 *
 * @date 2010-02-20
 *
 * @author hseywerd@nrcan.gc.ca
 **/

#ifndef CIDETECTORCONSTRUCTION_H_
#define CIDETECTORCONSTRUCTION_H_


#include "G4VUserDetectorConstruction.hh"
#include "CIRootRunHeader.h"

class CIDetectorConstruction : public G4VUserDetectorConstruction {
public:
	CIDetectorConstruction() : m_bApplySmear(false), m_dSmearFactorScat(0.0), m_dSmearFactorAbs(0.0) {};
	virtual ~CIDetectorConstruction() {};
	/// Return the smear factor used for the absorber detector
	virtual double GetSmearFactorA() const {return m_dSmearFactorAbs;}
	/// Return the smear factor used for the scatter detector
	virtual double GetSmearFactorS() const {return m_dSmearFactorScat;}
  /// Return the material used in the absorber detector
	virtual std::string GetMaterialAbsorber() const = 0;
	/// Return the material used in the scatter detector
	virtual std::string  GetMaterialScatter() const = 0;
	/// Get the smearing method used
	virtual CIRootRunHeader::SMEAR GetSmearType() const  = 0;

  inline virtual void SetApplySmear (const bool flag)            { m_bApplySmear = flag;}
  inline virtual void SetSmearValueScat (const double value)     { m_dSmearFactorScat = value;}
  inline virtual void SetSmearValueAbs (const double value)      { m_dSmearFactorAbs = value; G4cout<<"Set smear abs to "<< m_dSmearFactorAbs<<G4endl;}

protected:
  bool   m_bApplySmear;
  double m_dSmearFactorScat;
  double m_dSmearFactorAbs;
};

#endif /* CIDETECTORCONSTRUCTION_H_ */




