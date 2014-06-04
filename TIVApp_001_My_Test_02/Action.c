Action()
{
	int iDebug;
	
	web_cleanup_cookies( );
	
	lr_start_transaction("_TIVApp_001_My_Test");
	
	fRegisterChecks("LB=class=\"scrid\">","RB=</span>", "TIVApp_001_001_Homepage");
 
	web_url("Homepage",
		"URL=http://{pURL}/", 
		"Resource=0", 
		"RecContentType=text/html",
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
	fVerifyScreen();

	lr_end_transaction("_TIVApp_001_My_Test", LR_AUTO);
	
	return 0;
}

