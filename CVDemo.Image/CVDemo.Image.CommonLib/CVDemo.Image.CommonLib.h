// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CVDEMOIMAGECOMMONLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CVDEMOIMAGECOMMONLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CVDEMOIMAGECOMMONLIB_EXPORTS
#define CVDEMOIMAGECOMMONLIB_API __declspec(dllexport)
#else
#define CVDEMOIMAGECOMMONLIB_API __declspec(dllimport)
#endif

// This class is exported from the CVDemo.Image.CommonLib.dll
class CVDEMOIMAGECOMMONLIB_API CCVDemoImageCommonLib {
public:
	CCVDemoImageCommonLib(void);
	// TODO: add your methods here.
};

extern CVDEMOIMAGECOMMONLIB_API int nCVDemoImageCommonLib;

CVDEMOIMAGECOMMONLIB_API int fnCVDemoImageCommonLib(void);
