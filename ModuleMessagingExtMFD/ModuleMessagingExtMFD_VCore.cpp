// ==============================================================
//
//	ModuleMessagingExtMFD (Vessel Core Persistence)
//	==================================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "ModuleMessagingExtMFD_GCore.hpp"
#include "ModuleMessagingExtMFD_VCore.hpp"
#include "ParseFunctions.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

ModuleMessagingExtMFD_VCore::ModuleMessagingExtMFD_VCore(VESSEL *vin, ModuleMessagingExtMFD_GCore* gcin) {
	// Vessel core constructor
  GC = gcin;
	v = vin;

  return;
};

ModuleMessagingExtMFD_VCore::~ModuleMessagingExtMFD_VCore() {
  // Vessel core destructor
  // Need to tell LU that we no longer exist, else he'll access violate on v.getMass(), etc. 

}


void ModuleMessagingExtMFD_VCore::corePreStep(double SimT,double SimDT,double mjd) {

  return;
}