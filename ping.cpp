#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <string>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std;

 string Getdestination(){
	string theaddress;
	cout << "Where do you want to check?" << endl;
	cout <<"Type \"google\" for google.com or \"cmu\" for coloradomesa.edu"<<endl;
		cout<< "Enter the IP: ";
	cin >> theaddress;
	if(theaddress == "google" || theaddress == "cmu"){
		if(theaddress == "google") theaddress = "74.125.225.180";
		else theaddress = "10.0.3.167";
	}
	return theaddress;
}

void main(){
	HANDLE MyHandle;
	string theaddress;
	char Randomdata[20] = "Stuff to send away!";
	DWORD mainint,lenofbuffer;
	ICMP_ECHO_REPLY reply; //ICMP_ECHO_REPLY data structure
	IPAddr address;
	lenofbuffer = strlen(Randomdata) + sizeof(ICMP_ECHO_REPLY) + 8; //Make buffer large enough to contain data sent and the size of the ICMP_ECHO_REPLY data structure
	char* bufferpointer = new char[lenofbuffer];
	MyHandle = IcmpCreateFile(); //Create Handle
	theaddress = Getdestination(); //Get IP address
	address = inet_addr(theaddress.c_str()); // convert IP address into IPAddr object
	mainint = IcmpSendEcho(MyHandle, address, Randomdata, strlen(Randomdata), NULL, bufferpointer, lenofbuffer, 2000); //Perform the operation!
	memcpy(&reply, bufferpointer, sizeof(reply)); //Copy the returned information to an ICMP_ECHO_REPLY
	if(mainint != 0){ //If the status of the ICMP_ECHO_REPLY structures stored in bufferpointer is more than 0
		cout<<"Success! The ping returned a reply from "<< theaddress<<endl;
		cout<<"It took "<<reply.RoundTripTime<<" milliseconds."<<endl;
		cout<<"The program sent "<< sizeof(Randomdata)-1 <<" bytes and "<<theaddress<<" sent back "<<reply.DataSize<< " bytes."<<endl;
	}
	else cout <<"Received no response from the address" << " with error code " << GetLastError() <<endl;
	
	IcmpCloseHandle(MyHandle);
}