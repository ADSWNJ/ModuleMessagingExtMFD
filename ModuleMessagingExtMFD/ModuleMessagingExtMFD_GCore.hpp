// ==============================================================
//
//	ModuleMessagingExtMFD (Global Core Header)
//	=============================
//
//	Copyright (C) 2016-2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include <list>
#include <string>
#include "windows.h"
#include "orbitersdk.h"
#include "ModuleMessagingExtMFD_Buttons.hpp"
#include "MFDPersist.hpp"
#include "MMExt2_Advanced.hpp"

using namespace std;

#ifndef _MMExt2MFD_GCORE_H
#define _MMExt2MFD_GCORE_H


//+++++
// Global Persistence core. One of these is instantiated for the whole orbiter session, on the first launch of this MFD type
//+++++

class ModuleMessagingExtMFD_GCore {
  public:
    void corePreStep(double SimT,double SimDT,double mjd);

    // Global references ... instantiation and a link to the persistence library (running the linked lists)
    ModuleMessagingExtMFD_GCore();
    ~ModuleMessagingExtMFD_GCore();
    MFDPersist P;

    MMExt2::Advanced mm;
    vector<string> mmDumpVesTyp;
    vector<string> mmDumpModVar;
    vector<string> mmActL1;
    vector<string> mmActL2;
    string mmVer;
    bool coreFound; 
    unsigned int ofsV;
    unsigned int ofsA;
private:
    double coreSimT;
};


#endif // _MMExt2MFD_GCORE_H