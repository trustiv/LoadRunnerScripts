Action()
{	char sTemp[100];
	
	fGetVUID();
	
	fCaptureScreen("<title>","</title>");
	
	strcpy(sTemp,"Foobar");
	
	fTestMe(sTemp);

	return 0;
}
