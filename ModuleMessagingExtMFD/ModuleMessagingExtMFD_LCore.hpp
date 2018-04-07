// ==============================================================
//
//	ModuleMessagingExtMFD (Local Core Header)
//	============================
//
//	Copyright (C) 2016-2018	Andrew (ADSWNJ) Stokes
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
#include "ModuleMessagingExtMFD_VCore.hpp"
#include <list>
#include <string>

using namespace std;

#ifndef _MMExt2MFD_LCORE_H
#define _MMExt2MFD_LCORE_H

//+++++
// Local Persistence core. One of these is instantiated per Vessel AND MFD panel location. Local defaults for that combination.
//+++++

class ModuleMessagingExtMFD_LCore {
  public:
    // Local references ... instantiation, references for vesseland mfd position, and links to the appropriate VC, MC and GC
    ModuleMessagingExtMFD_LCore(VESSEL *vin, UINT mfdin, ModuleMessagingExtMFD_GCore* gcin);
    VESSEL *v;
    UINT m;
    ModuleMessagingExtMFD_GCore* GC;
    ModuleMessagingExtMFD_VCore* VC;

    // Add local vessel+panel data here

    ModuleMessagingExtMFD_Buttons B;
    bool showMessage;
    bool okMessagePage;
    string Message;
    int mode;
    int entPerPage;

    // COLORS: BB GG RR
    //                               RR    GG          BB
    static const DWORD COL_WHITE   = 255 + 255 * 256 + 255 * 256 * 256;
    static const DWORD COL_AQUA    = 120 + 219 * 256 + 226 * 256 * 256;
    static const DWORD COL_MAGENTA = 255 +  29 * 256 + 206 * 256 * 256;


    int fontsize;
    oapi::Sketchpad *skp; // points to local sketchpad for this MFD and vessel
    int skpLoB;           // Lowest precision for skp eng numnber formatting
    char skpBuf[128];     // Formatting buffer for MFD updates
    char skpFmtBuf[128];  // Formatting buffer for MFD updates
    int skpColPix;        // X-offset pixel (top left origin)
    int skpLinePix;       // Y offsel pixel (top left origin)

};


#endif // _MMExt2MFD_CORE_CLASSES