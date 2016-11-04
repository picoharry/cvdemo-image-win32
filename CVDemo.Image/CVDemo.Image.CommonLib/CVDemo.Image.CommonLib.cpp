// CVDemo.Image.CommonLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CVDemo.Image.CommonLib.h"


// This is an example of an exported variable
CVDEMOIMAGECOMMONLIB_API int nCVDemoImageCommonLib=0;

// This is an example of an exported function.
CVDEMOIMAGECOMMONLIB_API int fnCVDemoImageCommonLib(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see CVDemo.Image.CommonLib.h for the class definition
CCVDemoImageCommonLib::CCVDemoImageCommonLib()
{
    return;
}
