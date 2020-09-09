/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIRootRunHeader.h
 * @brief Data for run information to store with root
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#ifndef CIRootRunHeader_h
#define CIRootRunHeader_h

#include "TROOT.h"



/**
 * @class CIRootRunHeader
 * @brief Data for run information to store with root
 *
 * Processing classes intended for integration with root:
 * 1) Ensure that each such class has the following lines in the header and the implementation files:
 * Header - within the class declaration, where CIRootRunHeader is replaced with the class name
 * ClassDef (CIRootRunHeader, 1);
 * Implementation - in the file body, where CIRootRunHeader is replaced with the class name
 * \#if !defined(__CINT__)
 * ClassImp(CIRootRunHeader);
 * \#endif
 * 2) Process the header files with rootcint
 * rootcint eventdict.cpp -c CIRootRunHeader.h ...
 * where CIRootRunHeader.h is the list of all the header files of the classes which are going to be saved
 * The output is eventdict.cpp and eventdict.h, these are not to be edited
 * 3)
 * @author Henry Seywerd <hseywerd@nrcan.gc.ca>
 *
 **/

class CIRootRunHeader : public TObject
{
  public:
  	/// Run data types
  	typedef enum {
  		/// Monte Carlo data
  		RTYPE_MC,
  		/// Real data
  		RTYPE_REAL,
  		/// Something else, whatever that may be
  		RTYPE_OTHER
  	} RTYPE;

  	/// Defines different possible source configurations (if known)
  	typedef enum {
  		/// Mono-energetic source (MC)
  		STYPE_MONO,
  		/// Mono-energetic source with NORM (MC)
  		STYPE_MONO_NORM,
  		/// Two energy peak sources (MC)
  		STYPE_DUAL,
  		/// Dual peak with NORM (MC)
  		STYPE_DUAL_NORM,
  		/// Complex energy spectrum sources (MC)
  		STYPE_COMPLEX,
  		/// Real mono-peaked source with whatever real background may be around
  		STYPE_REAL_MONO,
  		/// Real dual-peaked
  		STYPE_REAL_DUAL,
  		/// Real complex spectrum
  		STYPE_REAL_COMPLEX
  	} STYPE;

  	/// Defines smearing algorithms, also see m_dSmearFactor;
  	typedef enum {
  		/// Use pure Geant results for smearing - no magic factors
  		SMEAR_GEANT_DEFAULT,
  		/// Smear with a numberical factor (FWHM % of energy), gaussian shape
  		SMEAR_SINGLE_GAUSS,
  		/// Other - default
  		SMEAR_OTHER
  	} SMEAR;

    CIRootRunHeader();

    CIRootRunHeader(const int iRunNum, const int iRank);

    ~CIRootRunHeader();

    inline void SetRunNumber(const int N) {m_iRunNumber = N;};
    inline int GetRunNumber() { return m_iRunNumber;};

    inline void SetRank(const int N) {m_iRankNumber = N;};

    inline void GetSourcePos(double& dX, double& dY, double& dZ) {dX = m_dSourcePosX;  dY = m_dSourcePosY; dZ = m_dSourcePosZ;}
    inline void SetSourcePos(const double dX, const double dY, const double dZ) {m_dSourcePosX = dX; m_dSourcePosY = dY; m_dSourcePosZ = dZ;}

    inline double GetESource1() const { return m_dESource1;}
    inline void SetESource1(const double E) {this->m_dESource1 = E;}

    inline double GetESource2() const { return m_dESource2;}
    inline void SetESource2(const double E) {this->m_dESource2 = E;}

    inline double GetISource1() const { return m_dISource1;}
    inline void SetISource1(const double I) {this->m_dISource1 = I;}

    inline double GetISource2() const { return m_dISource2;}
    inline void SetISource2(const double I) {this->m_dISource2 = I;}

    inline double GetSmearFactorA() const { return m_dSmearFactorAbsorber;}
    inline void SetSmearFactorA(const double S) {this->m_dSmearFactorAbsorber = S;}

    inline double GetSmearFactorS() const { return m_dSmearFactorScatter;}
    inline void SetSmearFactorS(const double S) {this->m_dSmearFactorScatter = S;}

    inline std::string  GetMaterialAbsorber() const { return m_strMaterialAbsorber;}
    inline void SetMaterialAbsorber(const std::string mat) {this->m_strMaterialAbsorber = mat;}

    inline std::string  GetMaterialScatter() const { return m_strMaterialScatter;}
    inline void SetMaterialScatter(const std::string mat) {this->m_strMaterialScatter = mat;}

    inline RTYPE GetRunDataType() const { return m_RunDataType;}
    inline void SetRunDataType(const RTYPE type) {this->m_RunDataType = type;}

    inline SMEAR GetSmearType() const { return m_SmearType;}
    inline void SetSmearType(const SMEAR type) {this->m_SmearType = type;}

    inline STYPE GetSourceType() const { return m_SourceType;}
    inline void SetSourceType(const STYPE type) {this->m_SourceType = type;}


  private:
    /// The run number
    int m_iRunNumber;
    /// The rank, i.e. which process of a multiprocessor run
    int m_iRankNumber;
    /// The data type in this file
    RTYPE m_RunDataType;
    /// Source position x (cm)
    double m_dSourcePosX;
    /// Source position y (cm)
    double m_dSourcePosY;
    /// Source position z (cm)
    double m_dSourcePosZ;
    /// Source type
    STYPE m_SourceType;
  	/// Energy of source (1st peak) 0 if unknown (keV)
  	double m_dESource1;
  	/// Energy of source (2nd peak) 0 if not present or unknown (keV)
  	double m_dESource2;
  	/// Source intensity (cps) (1st peak)
  	double m_dISource1;
  	/// Source intensity (cps) (2nd peak)
  	double m_dISource2;
  	/// Material for scatter detector
  	std::string m_strMaterialScatter;
  	/// Material for absorber detector
  	std::string m_strMaterialAbsorber;
  	/// Smearing method
  	SMEAR m_SmearType;
  	/// Smearing factor for Absorber
  	double m_dSmearFactorAbsorber;
  	/// Smearing factor for Scatter
  	double m_dSmearFactorScatter;


    ClassDef (CIRootRunHeader, 5)

};

#endif

