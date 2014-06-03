// Define our connection to VTS

char  *VtsServer1 = "127.0.0.1";
int   nPort1 = 8888;


vuser_init()
{
	// The init section sounds like a good place to open the connection to the server
	
	lrvtc_connect(VtsServer1, nPort1, 1);
	
	//Server Name , network port serving the data, keep alive
	
	return 0;
}
