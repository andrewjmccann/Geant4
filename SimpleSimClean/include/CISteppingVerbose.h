/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/
/**
 * @file CISteppingVerbose.h
 * @brief 
 *
 * @date Aug 6, 2009
 *
 * @author hseywerd@nrcan.gc.ca
 **/

#ifndef CISTEPPINGVERBOSE_H_
#define CISTEPPINGVERBOSE_H_

/**
 * @class CISteppingVerbose
 * @brief 
 *
 *
 * @author hseywerd
 *
 */
#include "G4SteppingVerbose.hh"

class CISteppingVerbose : public G4SteppingVerbose {
public:
	CISteppingVerbose();
	virtual ~CISteppingVerbose();

	void StepInfo();
	void TrackingStarted();
	void ComptonInfo();
};

#endif /* CISTEPPINGVERBOSE_H_ */
