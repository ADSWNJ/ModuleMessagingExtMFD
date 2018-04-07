// ==============================================================
//
//	ModuleMessagingExtMFD (MFD Update)
//	=====================
//
//	Copyright (C) 2016-2018	Andrew (ADSWNJ) Stokes
//                   All rights reserved
//
//	See ModuleMessagingExtMFD.cpp
//
// ==============================================================

#include "ModuleMessagingExtMFD.hpp"
#include "DisplayEngUnitFunctions.h"
#include <math.h>
#include <stdarg.h>


bool ModuleMessagingExtMFD::Update(oapi::Sketchpad *skp)
{
  LC->skp = skp;

  //LC->skp->SetTextColor(CLR_DEF);
  skpSetFont(fontM);
  if (LC->showMessage) return DisplayMessageMode();
  skpTitle("MMExtMFD v1.2");

  int l = 2;
  if (GC->mmVer != "") {
    skpFormatText(0, l++, GC->mmVer.c_str());
  } else {
    skpFormatText(0, l++, "Core not installed");
    return true;
  }

  switch (LC->mode) {
  case 0:
    skpFormatText(0, l++, "Variables:");
    break;
  case 1:
    skpFormatText(0, l++, "Activity:");
    break;
  case 2:
    skpFormatText(0, l++, "Data:");
    break;
  }
  unsigned int *p = (LC->mode == 1 ? &(GC->ofsA) : &(GC->ofsV));
  const vector<string> *vec1 = (LC->mode == 1 ? &(GC->mmActL1) : &(GC->mmDumpVesTyp));
  const vector<string> *vec2 = (LC->mode == 1 ? &(GC->mmActL2) : &(GC->mmDumpModVar));

  unsigned int i;
  char buf[128];

  if (LC->fontsize == 1) skpSetFont(fontS);

  l = 5;
  for (i = *p; i < vec1->size() && i < *p + LC->entPerPage; i++) {
    skpColor(LC->COL_WHITE);
    sprintf(buf, "%2u. %s", i+1, (*vec1)[i].c_str());
    skpFormatText(0, l++, buf);
    skpColor(LC->COL_AQUA);
    sprintf(buf, "    %s", (*vec2)[i].c_str());
    skpFormatText(0, l++, buf);
    if (LC->mode == 2) {
      skpColor(LC->COL_MAGENTA);
      sprintf(buf, "    %s", GC->mmDumpData[i].c_str());
      skpFormatText(0, l++, buf);
    }
  }
  skpColor(LC->COL_WHITE);
  if (vec1->size()>*p + LC->entPerPage) skpFormatText(0, l, "...");

  return true;
};


bool ModuleMessagingExtMFD::DisplayMessageMode() {
  skpTitle("ModuleMessagingExtMFD");
  showMessage();
  return true;
};


// MFD Line formatting helper
void ModuleMessagingExtMFD::showMessage() {

  char localMsg[750];
  strcpy_s(localMsg,750, LC->Message.c_str());
  char *bp = localMsg;
  char *bp2 = localMsg;
  char *bp3 = localMsg;
  char c1, c2;
  int i = 0;
  int j;
  int l = 4;
  bool eol = false;

  do {
    if ((*bp2 == '\n') || (*bp2 == '\0')) {     // Look for user newline or end of buffer
      eol = true;
      c1 = *bp2;
      *bp2 = '\0';
    } else {
      if (i==34) {                              // 34 chars no newline ... need to break the line
        eol=true;
        bp3 = bp2;
        for (j=34; j>20; j--) {                 // look for a space from 21 to 34
          if (*bp3==' ') break;
          bp3--;
        }
        if (j>20) {                             // space found
          bp2 = bp3;
          c1 = *bp2;
          *bp2 = '\0';
        } else {                                // no space ... insert hyphen
          bp3 = bp2 + 1;
          c1 = *bp2;
          c2 = *bp3;
          *bp2 = '-';
          *bp3 = '\0';
        }
      } else {                                  // Scan forward      
        i++;
        bp2++;
      }
    }

    if (eol) {                                  // EOL flag ... write out buffer from bp to bp2.
  	  LC->skp->Text (_Col(0), _Line(l++), bp, strlen(bp));
      eol = false;
      if (c1 == '\0') {
        bp = bp2;     // End of buffer
      } else if ((c1 == '\n') || (c1 == ' ')) {
        bp = bp2+1;   // Reset for next line of the buffer
        bp2++;
        i=0;
      } else {
        bp = bp2;     // Put back the chars we stomped
        *bp2 = c1;
        *bp3 = c2;
        i=0;
      }
    }
  } while (*bp);

  return;
}

