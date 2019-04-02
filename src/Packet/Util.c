//////////////////////////////////////////////////////////////////////
// Project: pcap-ndis6
// Description: WinPCAP fork with NDIS6.x support 
// License: MIT License, read LICENSE file in project root for details
//
// Copyright (c) 2019 Change Dynamix, Inc.
// All Rights Reserved.
// 
// https://changedynamix.io/
// 
// Author: Mikhail Burilov
// 
// Based on original WinPcap source code - https://www.winpcap.org/
// Copyright(c) 1999 - 2005 NetGroup, Politecnico di Torino(Italy)
// Copyright(c) 2005 - 2007 CACE Technologies, Davis(California)
// All rights reserved.
//////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "Util.h"

BOOL IsWow64()
{
#ifdef _AMD64
	return FALSE;
#else
	BOOL b = FALSE;

	if (IsWow64Process(GetCurrentProcess(), &b) == FALSE)
	{
		return FALSE;
	}

	return b;
#endif
}


void *DisableWow64FsRedirection()
{
	void *p = NULL;

	if (IsWow64() == FALSE)
	{
		return NULL;
	}

	if (Wow64DisableWow64FsRedirection(&p) == FALSE)
	{
		return NULL;
	}

	return p;
}

void RestoreWow64FsRedirection(void *p)
{
	if (p == NULL)
	{
		return;
	}

	if (IsWow64() == FALSE)
	{
		return;
	}

	Wow64RevertWow64FsRedirection(p);
}
