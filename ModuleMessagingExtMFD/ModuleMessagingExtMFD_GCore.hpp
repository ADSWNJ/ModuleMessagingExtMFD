// ==============================================================
//
//	ModuleMessagingExtMFD (Global Core Header)
//	=============================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
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
#include <EnjoLib/ModuleMessagingExtBase.hpp>
#include <EnjoLib/ModuleMessagingExtPut.hpp>
#include <EnjoLib/ModuleMessagingExt.hpp>
using namespace std;

#ifndef _SCRAM_ATT_GCORE_H
#define _SCRAM_ATT_GCORE_H


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


  private:
    double coreSimT;
    double coreSimDT;
};


#endif // _SCRAM_ATT_GCORE_H