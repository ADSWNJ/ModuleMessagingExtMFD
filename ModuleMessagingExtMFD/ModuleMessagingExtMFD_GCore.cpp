// ==============================================================
//
//	ModuleMessagingExtMFD (Core Persistence)
//	===========================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "ModuleMessagingExtMFD_GCore.hpp"
#include "ModuleMessagingExtMFD_VCore.hpp"

ModuleMessagingExtMFD_GCore::ModuleMessagingExtMFD_GCore() {
  coreSimT = 0.0;
  return;
}

ModuleMessagingExtMFD_GCore::~ModuleMessagingExtMFD_GCore() {
  return;
}


void ModuleMessagingExtMFD_GCore::corePreStep(double simT,double simDT,double mjd) {
  if (coreSimT == 0) {
    coreSimT = simT;
    return;
  }
  if (coreSimT == simT) return;

  if (P.firstVC() == NULL) return; // No vessels interested in ModuleMessagingExtMFD yet

  coreSimDT = simT - coreSimT;
  coreSimT = simT;
  //sprintf(oapiDebugString(),"GCORE PRESTEP: %15.15f", coreSimDT);

  // Once per update - call vessel corePreSteps
  for (ModuleMessagingExtMFD_VCore* VC = (ModuleMessagingExtMFD_VCore*) P.firstVC(); VC != NULL; VC = (ModuleMessagingExtMFD_VCore*) P.nextVC()) {
    VC->corePreStep(coreSimT, coreSimDT, mjd);
  }

}
