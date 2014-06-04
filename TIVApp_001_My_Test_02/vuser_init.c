/* 
 *  Add any GLOBAL variables beore your custom include files
 *  If not these cause compilation errors when encountered in your library functions.
 */

// What version of the app are we expecting to be testing against?
char sAppVersion[6] = "V0.2";

// Define our local test function library
// If it hasn't already been inclided
#ifndef _LIB_HPD_H
	#include "..\includes\Lib-hpd-01.c"
#endif //_LIB_HPH_H


vuser_init()
{	 
	char sBuf[254];
	int iid;
	int	isid;
	char* sGroupname;
	
	lr_whoami(&iid, &sGroupname, &isid);

	sprintf(sBuf,"%s:%d",sGroupname, iid);
	lr_save_string(sBuf,"pVUID");
	
	return 0;
}
