// ==============================================================
//
//	ModuleMessagingExtMFD (Vessel Core Header)
//	=============================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "windows.h"
#include "orbitersdk.h"
#include "ModuleMessagingExtMFD_Buttons.hpp"
#include "MFDPersist.hpp"
#include "ModuleMessagingExtMFD_GCore.hpp"
#include "ModuleMessagingExtMFD_AP.hpp"
#include <list>
#include <string>
#include <vector>
using namespace std;

#ifndef _SCRAM_ATT_VCORE_H
#define _SCRAM_ATT_VCORE_H

//+++++
// Vessel Persistence core. One of these is instantiated per Vessel flown with this MFD up.
//+++++

class ModuleMessagingExtMFD_VCore {
  public:
    void corePreStep(double SimT,double SimDT,double mjd);

    // Core references ... instantiation, vessel reference and GC.
    ModuleMessagingExtMFD_VCore(VESSEL *vin, ModuleMessagingExtMFD_GCore* gcin);
    ~ModuleMessagingExtMFD_VCore();
    ModuleMessagingExtMFD_GCore* GC;


		// Add Vessel data here
    VESSEL *v;
    int vix; // Vessel index in LU

    class ModuleMessagingExtMFD_AP ap;

    int apState;    //  0 = inactive, 1 = Ready (armed), 2 = Point, 3 = Burn


  private:
};


#endif // _SCRAM_ATT_VCORE_H




