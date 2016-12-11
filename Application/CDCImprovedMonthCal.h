// CDCImprovedMonthCal.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDCImprovedMonthCal

class CDCImprovedMonthCal : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDCImprovedMonthCal)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x1C0B3D6D, 0xE465, 0x4325, { 0x95, 0x4F, 0xFA, 0xEA, 0xF6, 0x8, 0x7F, 0x11 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:

// Operations
public:



};
