vuser_end()
{
	// If we open a connection we should close it
	
	lrvtc_disconnect();
	
	return 0;
}
