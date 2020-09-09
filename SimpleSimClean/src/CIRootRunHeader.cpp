/***************************************************************************
*   Copyright (C) Minister of Natural Resources Canada 2008.               *
*   hseywerd@nrcan.gc.ca                                                   *
*                                                                          *
***************************************************************************/
/**
 * @file CIRootRunHeader.cpp
 * @brief Data for run information to store with root
 * @author Henry Seywerd hseywerd@nrcan.gc.ca
 **/
#include "CIRootRunHeader.h"


#if !defined(__CINT__)
ClassImp (CIRootRunHeader);
#endif

CIRootRunHeader::CIRootRunHeader() :
		m_iRunNumber(-1), m_iRankNumber(-1), m_RunDataType(RTYPE_OTHER), m_dSourcePosX(0), m_dSourcePosY(0), m_dSourcePosZ(0),
    m_dESource1(0), m_dESource2(0), m_dISource1(0), m_dISource2(0), m_strMaterialScatter(""), m_strMaterialAbsorber(""),
    m_SmearType(SMEAR_OTHER), m_dSmearFactorAbsorber(0), m_dSmearFactorScatter(0)
{


}


CIRootRunHeader::CIRootRunHeader(const int iRunNum, const int iRank) :
		m_iRunNumber(iRunNum), m_iRankNumber(iRank), m_RunDataType(RTYPE_OTHER), m_dSourcePosX(0), m_dSourcePosY(0), m_dSourcePosZ(0),
    m_dESource1(0), m_dESource2(0), m_dISource1(0), m_dISource2(0), m_strMaterialScatter(""), m_strMaterialAbsorber(""),
    m_SmearType(SMEAR_OTHER), m_dSmearFactorAbsorber(0), m_dSmearFactorScatter(0)

{
}

//-----------------------------------------------------------------------------
CIRootRunHeader::~CIRootRunHeader()
{
}






