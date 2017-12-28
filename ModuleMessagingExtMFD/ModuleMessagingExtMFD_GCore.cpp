// ==============================================================
//
//	ModuleMessagingExtMFD (Core Persistence)
//	========================================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "ModuleMessagingExtMFD_GCore.hpp"
#include "ModuleMessagingExtMFD_VCore.hpp"

ModuleMessagingExtMFD_GCore::ModuleMessagingExtMFD_GCore() : mm("MMExtMFD") {
  string ver;
  mmVer = "";
  coreFound = mm.GetVersion(&ver);
  if (coreFound) mmVer = string() + "Using: " + ver;
  return;
}

ModuleMessagingExtMFD_GCore::~ModuleMessagingExtMFD_GCore() {
  return;
}


void ModuleMessagingExtMFD_GCore::corePreStep(double simT,double simDT,double mjd) {
  if (coreSimT == 0.0) {
    coreSimT = -3.0;
  }

  if (simT - coreSimT > 2.0) {
    coreSimT = simT;
    int ix = 0;
    char typ;
    string mod;
    string var;
    string vesName;
    VESSEL *ves;
    string msg;
    list<string> mmListVes;
    list<string> mmListModVarTyp;
    int siz;
    while (mm.Find("*", "*", &ix, &typ, &mod, &var, &ves, false, NULL)) {
      msg = string() + ves->GetName() + " (" + typ + ")";
      mmListVes.push_back(msg.c_str());
      mmListModVarTyp.push_back(mod + ":" + var);
    }
    siz = mmListVes.size();
    mmDumpVes.resize(mmListVes.size());
    mmDumpModVarTyp.resize(mmListVes.size());
    int i = 0;
    for (auto& e : mmListVes) {
      mmDumpVes[i++] = e;
    }
    i = 0;
    for (auto& e : mmListModVarTyp) {
      mmDumpModVarTyp[i++] = e;
    }
    mmActL1.clear();
    mmActL2.clear();
    ix = 0;
    string rcli, rmod, rvar, rves, act;
    char rfunc;
    bool rsucc;

    while (mm.GetLog(ix++, &rfunc, &rsucc, &rcli, &rmod, &rvar, &rves)) {
      switch (rfunc) {
      case 'P': act = "Put"; break;
      case 'G': act = "Get"; break;
      case 'D': act = "Del"; break;
      case 'L': act = "Log"; break;
      case 'V': act = "Ver"; break;
      case 'F': act = "Fnd"; break;
      default: act = string() + rfunc; 
      }
      act = act + " " + rves;
      if (!rsucc) act = act + " (f)";
      mmActL1.push_back(rcli + " " + act);
      mmActL2.push_back(rmod + ":" + rvar);
    }
  }
}
