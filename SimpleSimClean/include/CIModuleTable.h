/***************************************************************************
 *   Copyright (C) Minister of Natural Resources Canada 2008.              *
 *   hseywerd@nrcan.gc.ca                                                  *
 *                                                                         *
 ***************************************************************************/

/**
 * @file CIModuleTable.h
 * @brief Define a class to map module identifier strings to a module ID code
 **/

#ifndef CIModuleTable_H_
#define CIModuleTable_H_

#include <string>
#include <map>
/**
 * @class CIModuleTable
 * @brief Define a class to map module identifier strings to a module ID code
 *
 * This is a wrapper for an implementation based on the not so c++ standard library map class
 */
class G4VPhysicalVolume;
class CIModuleTable {
public:
	typedef std::map<std::string, int> M;
	typedef std::pair<const std::string, const int> P;
	/// Enumerates the different detector parts
	typedef enum {
		/// Module is in the scatter detector
		SUBDET_SCATTER,
		/// Module is in the absorber detector
		SUBDET_ABSORBER,
		/// Module is something else
		SUBDET_OTHER
	} SUBDET;

	/**
	 * Constructs the module ID class implementing the
	 */
	CIModuleTable();

	/**
	 * Destructor
	 */
	virtual ~CIModuleTable();

	/**
	 * Inserts a module into the table
	 * @param moduleName the name of the module
	 * @param moduleID identification number of the module
	 * @param iLayer the layer of the subdetector
	 * @param activePosition the position of the active centre of the cell.
	 * @param subDetector which subdetector this module corresponds to
	 */
	inline void InsertModule(const int moduleID, const int iLayer, const G4ThreeVector activePosition, const SUBDET subDetector, G4VPhysicalVolume* pVol) {
		P p(pVol->GetName(), moduleID);
		m_ModuleMap.insert(p);
		m_Layer.insert(m_Layer.end(), iLayer);
		m_ActiveCentre.insert( m_ActiveCentre.end(), activePosition);
		m_SubDetectorType.insert(m_SubDetectorType.end(), subDetector);
		m_PhysVol.insert(m_PhysVol.end(), pVol);
		G4cout<<"inserted module "<< pVol->GetName() <<" with ID "<< moduleID<< " and center " << activePosition << G4endl;
		G4cout << "module size is " <<  m_ModuleMap.size() << G4endl;

	}

	/**
	 * Deletes a module from the table
	 * @param moduleName the name of the module to delete
	 */
	inline void DeleteModule(const std::string moduleName) {
		const int id = GetModuleID(moduleName);
		m_ModuleMap.erase(moduleName);
		m_Layer.erase(m_Layer.begin()+id);
		m_ActiveCentre.erase(m_ActiveCentre.begin()+id);
		m_SubDetectorType.erase(m_SubDetectorType.begin()+id);
		m_PhysVol.erase(m_PhysVol.begin()+id);

	}

	/**
	 * Finds a name from the table, given the ID
	 * @param moduleID the ID of the module
	 * @return the string giving the module name, null string if not found
	 */
	inline std::string GetModuleName(const int moduleID) {
		for (M::const_iterator p = m_ModuleMap.begin(); p != m_ModuleMap.end(); ++p) {
			if (p->second == moduleID) {
				//G4cout<<"Return module by ID "<< p->first<<" with ID "<< moduleID<<G4endl;
				return p->first;
			}
		}
		return "";
	}

	const inline G4ThreeVector& GetActivePosition(const int moduleID) const {return m_ActiveCentre[moduleID];};

	/**
	 * Finds a module from the table
	 * @param moduleName the name of the module
	 * @return the id of the module, -1 if not found
	 */
	inline int GetModuleID(const std::string moduleName) {
		//G4cout<<"Return module from name "<< moduleName<<" with ID "<< m_ModuleMap[moduleName]<<G4endl;
		for (M::const_iterator p = m_ModuleMap.begin(); p != m_ModuleMap.end(); ++p) {
			if (p->first == moduleName) {
				return p->second;
			}
		}
		return -1;

	}

	/**
	 * Get the number of modules handled
	 * @return the number of modules
	 */
	inline int GetMaxModules() const {
		return m_ModuleMap.size();
	}

	/**
	 * Get the subdetector in which this module lies
	 * @param moduleID the id of the module in question
	 * @return the subdetector identifier
	 */
	const inline SUBDET GetSubDetector(const int moduleID) const {
		return m_SubDetectorType[moduleID];
	}

	const inline int GetLayer(const int moduleID) const {
		return m_Layer[moduleID];
	}

	/// Get the base name for scatter cells
	static inline G4String GetScatterCellName() {return m_strScatterCellName;}

	/// Get the base name for absorber cells
	static inline G4String GetAbsorberCellName() {return m_strAbsorberCellName;}

	/**
	 * Determine if the point is within the scatter detector
	 * @param pos point to check
	 * @return true if inside, else false
	 */
	G4bool IsPointInScatDet(const G4ThreeVector pos) const;

	/**
	 * Determine if the point is within the absorber detector
	 * @param pos point to check
	 * @return true if inside, else false
	 */
	G4bool IsPointInAbsDet(const G4ThreeVector pos) const;


	const G4VPhysicalVolume* GetPVol(const int moduleID) const {
		return m_PhysVol[moduleID];
	}


	/**
	 * Return the module physical volume in which the given optical hit position is located
	 *
	 * Depends on a particular module heirarchy, (element->SiPM->Module)
	 * @param pos the position
	 * @return the physical volume
	 */
	const G4VPhysicalVolume* GetModulePhysForOpticalHit(const G4ThreeVector pos);

	/**
	 * Return the module physical volume in which the given optical hit position is located
	 *
	 * Depends on a particular module heirarchy, (element->SiPM->Module)
	 * @param pos the position
	 * @return the physical volume
	 */
	const G4VPhysicalVolume* GetModulePhysForScintiHit(const G4ThreeVector pos);



private:

	/// The map storing the module name id relationship.
	M m_ModuleMap;
	/// The layer of the subdetector
	std::vector<int> m_Layer;
	/// The centres of the cells.
	std::vector<G4ThreeVector> m_ActiveCentre;
	/// The type of detector to which the cell belongs
	std::vector<SUBDET> m_SubDetectorType;

	// Names for scatter and absorber cells
  /// Base name for the scatter detector
  static const G4String m_strScatterCellName;
  /// Base name for the absorber detector
  static const G4String m_strAbsorberCellName;
  /// The physical volume representing the cell
  std::vector<G4VPhysicalVolume*> m_PhysVol;
};

#endif /* CIModuleTable_H_ */
