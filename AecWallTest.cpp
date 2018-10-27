// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//- AecWallTest.cpp : Initialization functions
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include <afxdllx.h>

//-----------------------------------------------------------------------------
//- Define the sole extension module object.
AFX_EXTENSION_MODULE asdkAecWallTestDLL ={ NULL, NULL } ;
#include "AecWallTestApp.h"
extern CAecWallTestApp *pThisOmfApp ;

//-----------------------------------------------------------------------------
//- DLL Entry Point
extern "C"
BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	//- Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved) ;

	if ( dwReason == DLL_PROCESS_ATTACH ) {
        _hdllInstance =hInstance ;
		//- Extension DLL one time initialization
		if ( !AfxInitExtensionModule (asdkAecWallTestDLL, hInstance) )
			return (0) ;
		//- Insert this DLL into the resource chain
		//- NOTE: If this Extension DLL is being implicitly linked to by
		//- an MFC Regular DLL (such as an ActiveX Control)
		//- instead of an MFC application, then you will want to
		//- remove this line from DllMain and put it in a separate
		//- function exported from this Extension DLL. The Regular DLL
		//- that uses this Extension DLL should then explicitly call that
		//- function to initialize this Extension DLL. Otherwise,
		//- the CDynLinkLibrary object will not be attached to the
		//- Regular DLL's resource chain, and serious problems will result.
		new CDynLinkLibrary (asdkAecWallTestDLL) ;
		pThisOmfApp =new CAecWallTestApp ;
		InitAcUiDLL () ;
	} else if ( dwReason == DLL_PROCESS_DETACH ) {
		delete pThisOmfApp ;
		//- Terminate the library before destructors are called
		AfxTermExtensionModule (asdkAecWallTestDLL) ;
	}
	return (TRUE) ;
}

