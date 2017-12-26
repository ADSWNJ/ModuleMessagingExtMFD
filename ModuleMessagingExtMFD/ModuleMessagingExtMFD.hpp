// ==============================================================
//
//	ModuleMessagingExtMFD Headers
//	====================
//
//	Copyright (C) 2016-2017	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================


#ifndef __SCRAM_ATT_H
#define __SCRAM_ATT_H

#include "ModuleMessagingExtMFD_GCore.hpp"   
#include "ModuleMessagingExtMFD_VCore.hpp" 
#include "ModuleMessagingExtMFD_LCore.hpp" 


extern "C" 
class ModuleMessagingExtMFD: public MFD2
{
public:
	ModuleMessagingExtMFD (DWORD w, DWORD h, VESSEL *vessel, UINT mfd);
	~ModuleMessagingExtMFD ();

  char *ButtonLabel (int bt);
	int ButtonMenu (const MFDBUTTONMENU **menu) const;
  bool ConsumeKeyBuffered (DWORD key);
  bool ConsumeButton (int bt, int event);
  
  bool Update (oapi::Sketchpad *skp);
  bool DisplayMessageMode();

  // Button Press Handlers
  void Button_AP();
  void Button_DN();
  void Button_UP();

  // Persistence functions
  void ReadStatus(FILEHANDLE scn);
  void WriteStatus(FILEHANDLE scn) const;

protected:
  ModuleMessagingExtMFD_GCore* GC;
  ModuleMessagingExtMFD_LCore* LC;
  ModuleMessagingExtMFD_VCore* VC;

  oapi::IVECTOR2 iv[10000];

  int _Line(const int row );
  int _Col(const int pos );
  int _Col2(const int pos );
  void skpFormatText(const int col, const int line, const char* fmt, ...);
  void skpFmtColText(const int col, const int line, const bool test, const DWORD truecol, const DWORD falsecol, const char* fmt, ...);
  void skpFmtEngText(const int col, const int line, const char* fmt, const char* sfx, const double val, const int dloB = 0);
  void skpFmtEngText(const int col, const int line, const char* fmt, const unsigned char* sfx, const double val, const int dloB = 0);
  void skpTitle(const char* title);
  void skpColor(DWORD col);
  void showMessage();

  oapi::Font *font;

};

#endif // !__SCRAM_ATT_H