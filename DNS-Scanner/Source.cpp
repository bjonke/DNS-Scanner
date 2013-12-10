#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
using namespace std;
// link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

int num = 0;

// Create random ipv4 addreses
void ipv4(string& createdAddress)
{
 	ofstream myfile;
   int count = 0;
   time_t t;
   time(&t);
   srand((unsigned) t);
   ostringstream addressOut;
   std::string looky;

   myfile.open ("ip.txt");

   while(count < num)
   {
	 addressOut.str(std::string());
      for(int i = 0; i < 4; i++)
      {
         addressOut << rand() % 255;
		 if( i < 3 )
			addressOut << ".";
      };
      //addressOut << endl;

	myfile << addressOut.str()  << endl;
	
	string look("nslookup " + addressOut.str() ); 
	looky =  addressOut.str();
	system(look.c_str());
	
      count++;

	  createdAddress += addressOut.str();
//-----------------------------------------
    // Declare and initialize variables
    WSADATA wsaData = {0};
    int iResult = 0;

    DWORD dwRetval;

    struct sockaddr_in saGNI;
    char hostname[NI_MAXHOST];
    char servInfo[NI_MAXSERV];
    u_short port = 53;
 // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
    }
    //-----------------------------------------
    // Set up sockaddr_in structure which is passed
    // to the getnameinfo function
    saGNI.sin_family = AF_INET;
	saGNI.sin_addr.s_addr = inet_addr(looky.c_str());
    saGNI.sin_port = htons(port);

    //-----------------------------------------
    // Call getnameinfo
    dwRetval = getnameinfo((struct sockaddr *) &saGNI,
                           sizeof (struct sockaddr),
                           hostname,
                           NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);

    if (dwRetval != 0) {
        printf("getnameinfo failed with error # %ld\n", WSAGetLastError());
    } else {
        printf("getnameinfo returned hostname = %s\n", hostname);
		myfile << hostname << endl;
		cout << hostname << endl;
		myfile << "---------------------------------" << endl;
    }
   };
   




   myfile.close();
};

int main()
{
	cout << "Number of addresses to create: " << endl;
	cin >> num;
	string createdAddress = ""; 
	ipv4(createdAddress); 
	cout << createdAddress << endl;

   
	cin.get();
	cin.get();
	return 0;
};