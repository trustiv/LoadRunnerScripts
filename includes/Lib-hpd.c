//#This library is an example of an include file
// Author: Gordon Appleby
// Purpose - HP discovery Deep Dive

#ifndef _LIB_HPD_H
#define _LIB_HPD_H

void fRegisterChecks(){
	web_reg_save_param("cVersion",
		"LB=version\">",
		"RB=<",
		"Notfound=warning",
		LAST);

	web_reg_save_param("cErr",
	    "LB=class='err'>",
	    "RB=<",
	    "Notfound=warning",
	    LAST);

}
#endif //_LIB_HPH_H