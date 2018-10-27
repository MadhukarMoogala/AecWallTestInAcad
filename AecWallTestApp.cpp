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
//----- AecWallTestApp.cpp : Defines the initialization routines for the DLL.
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "AecWallTestApp.h"
#include "eoktest.h"

AcDbEntity* selectEntity(const ACHAR* prompt,
	AcDbObjectId& id,
	AcGePoint3d& pick,
	AcDb::OpenMode openMode)
{
	AcDbEntity* ent = NULL;
	ads_name ename;

	if (acedEntSel(prompt, ename, asDblArray(pick)) == RTNORM)
	{
		if (acdbGetObjectId(id, ename) == Acad::eOk)
		{
			if (acdbOpenAcDbEntity(ent, id, openMode) == Acad::eOk)
				return ent;
		}
	}
	return ent;
}
void getAecWall()
{
	// TODO: Implement the command
	AcDbEntity* pWallEntity;
	AcGePoint3d pick;
	AcDbObjectId id;
	Acad::ErrorStatus es;
	AcGePoint3dArray is;

	if ((pWallEntity = selectEntity(_T("\nSelect Window Entity : "),
		id, pick, AcDb::kForRead)) == NULL)
	{
		acutPrintf(L"\nSelection failed");
		return;
	}

	AecDbWall* pWall = AecDbWall::cast(pWallEntity);
	AecDbWallStyle* pWallStyle = pWall->openWallStyle();
	if (pWallStyle != nullptr) {
		
		AecRmCString pszWallStyleName = _T("");
		if(!eOkVerify(pWallStyle->getName(pszWallStyleName))) return;
		acutPrintf(_T("\nWall Style Name:%s"), pszWallStyleName);
		AcGeIntArray ids;
		AecRmCStringArray compNames;
		AcDbObjectIdArray materialIds;
		pWallStyle->getMaterialComponents(ids, compNames, materialIds);
		pWall->closeWallStyle();
	}
	
}

//-----------------------------------------------------------------------------
CAecWallTestApp *pThisOmfApp =NULL ;
extern AFX_EXTENSION_MODULE asdkAecWallTestDLL ;
HINSTANCE _hdllInstance =NULL ;

//-----------------------------------------------------------------------------
ACRX_NO_CONS_DEFINE_MEMBERS(CAecWallTestApp, AecAppArx)
AEC_CLASS_DECORATOR(CAecWallTestApp, AecAppArx, asdkAecWallTest, -1, -1)

//-----------------------------------------------------------------------------
CAecWallTestApp::CAecWallTestApp ()
	: AecAppArx (_DNT("asdkAecWallTest"), _hdllInstance, asdkAecWallTestDLL) {
}

//-----------------------------------------------------------------------------
AcRx::AppRetCode CAecWallTestApp::initApp () {
	acrxRegisterAppMDIAware (acadAppPtr ()) ;
	// TODO: add your initialization functions
	acedRegCmds->addCommand(_T("TestCmd"), _T("testWall"), _T("testWall"), ACRX_CMD_MODAL, getAecWall);
	return (AecAppArx::initApp ()) ;
}

AcRx::AppRetCode CAecWallTestApp::exitApp () {
	// TODO: add your initialization functions

	return (AecAppArx::exitApp ()) ;
}

//-----------------------------------------------------------------------------
void CAecWallTestApp::getRequiredModules (AecRmCStringArray &reqApps) {
	reqApps.Add (_DNT("AecBase60")) ;
	reqApps.Add (_DNT("AecUiBase60")) ;
}

//-----------------------------------------------------------------------------
Acad::ErrorStatus CAecWallTestApp::registerServices () {
	Acad::ErrorStatus es =AecBaseServices::registerService (this);
	return es;
	//if ( es != Acad::eOk )
	//	return (es) ;
	//return es (AecUiBaseServices::registerService (this)) ;
}

void CAecWallTestApp::unRegisterServices () {
	AecBaseServices::unRegisterService (this) ;
	//AecUiBaseServices::unRegisterService (this) ;
}

//-----------------------------------------------------------------------------
CAecWallTestApp *CAecWallTestApp::getApp () {
	return (pThisOmfApp) ;
}

//-----------------------------------------------------------------------------
void CAecWallTestApp::getRegistryInfo (AecRmCString &regCompanyName, AcadApp::LoadReasons &reasons) {
	regCompanyName =_DNT("Your Company Name") ;
	reasons =static_cast<AcadApp::LoadReasons> (AcadApp::kOnLoadRequest | AcadApp::kOnCommandInvocation) ;
}

//-----------------------------------------------------------------------------
void CAecWallTestApp::registerCommandObjects () {
	// TODO: add your command objects here
}

//-----------------------------------------------------------------------------
void CAecWallTestApp::initRegistryInfo () {
    //----- Add the resource only Dll info
	AecRegistryInfo *reginfo =appRegistryInfo () ;
	if ( reginfo != NULL ) {
		reginfo->getRegistryString (_DNT("Language"), _DNT("CurrentLanguage"), _DNT("English"), TRUE) ;
		CString locale ("Language\\English") ;
		CString dllName =appName () + _DNT("Enu.dll") ;
		reginfo->writeRegistryString (locale, (LPCTSTR)(CAecWallTestApp::getApp ()->appName ()), dllName) ;
	}
}
