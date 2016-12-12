#ifndef __IMPROVED_MONTHCAL_H
#define __IMPROVED_MONTHCAL_H

#include <SDKDDKVer.h>
#include <afx.h>
#include <Windows.h>
#include <stdarg.h>
#include <assert.h>
#include <windef.h>
#include <winbase.h>
#include <wingdi.h>
#include <winuser.h>
#include <winreg.h>
#include <objbase.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <atltrace.h>
#include "unicode.h"

#ifndef TRACE
#define TRACE ATLTRACE
#endif

#define Alloc(s) malloc((s))
#define ReAlloc(s,t) realloc((s),(t))
#define Free(s) free((s))
#define GetSize(s) GetSize((s));

#define MCS_RANGESELECT     MCS_MULTISELECT
#undef  MCS_MULTISELECT
#define MCS_MULTISELECT     0x1000

#define MCSC_SELECTEDTEXT 6       // selection text color
#define MCSC_SELECTEDBK 7         // selection background color
#define MCSC_ABBREVIATIONSTEXT 8  // abbreviations text color
#define MCSC_ABBREVIATIONSBK 9    // abbreviations background color

void MONTHCAL_Register(void);
void MONTHCAL_Unregister(void);

int MONTHCAL_MonthLength(int month, int year);
int MONTHCAL_CalculateDayOfWeek(SYSTEMTIME *date, BOOL inplace);
LONG MONTHCAL_CompareSystemTime(const SYSTEMTIME *first, const SYSTEMTIME *second);

#endif  /* __IMPROVED_MONTHCAL_H */
