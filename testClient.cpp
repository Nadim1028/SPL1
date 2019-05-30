#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<bits/stdc++.h>
#define PORT 9454

using namespace std;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


int main(){

	int clientSocket, ret,n;
	struct sockaddr_in serverAddr;
	char buffer[256];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
	//	cout<<"signUp or log in?"<<endl;		
		
		string del = "~";
        string command;
 		
        string from ;
        string to ;
        
        string username ;
        string password;
        
        cout<<"From: "<<endl;
        cin>>from;
        
        cout<<"To: "<<endl;
        cin>>to;
        
        cout<<"Command: "<<endl;
        cin>>command;
       
        cout<<"Username: "<<endl;
		cin>>username;
				
		cout<<"pass: "<<endl;
		cin>>password;
				
				
				string packet = from + del + to + del + command + del + username + del + password + del;
				
				for(int i=0; i<packet.length(); i++)
				buffer[i] = packet[i];
				
				n = write(clientSocket,buffer,strlen(buffer));
				if (n < 0) 
				     error("ERROR writing to socket");
    
    	
    	
        bzero(buffer,256);
        n = read(clientSocket,buffer,255);
        if (n < 0) 
             error("ERROR reading from socket");
             
        string recPacket = "";
        for(int i=0; i<strlen(buffer); i++)
			recPacket = recPacket + buffer[i];
			
			
			string arr[100];
    		int j = 0;
   			string tmp = "";
    
   			 for(int i=0; i<recPacket.length(); i++)
   			 {
    	
    			if(recPacket[i]=='~')
    			{
    				arr[j] = tmp;
    				tmp = "";
    				j++;
    	
    			}
    			else
    			{
    				tmp = tmp+recPacket[i];
    			}
    
   			 }
   			 
   			 if(arr[3]=="true"){
   			 	cout << "Login ok" << endl;
   			 	 cout<<username<<": ";
   			 	 bzero(buffer,256);
				 fgets(buffer,255,stdin);
   			 	 
   			 	 while(1)
   				 {
							 
						fgets(buffer,255,stdin);
						n = write(clientSocket,buffer,strlen(buffer));
						if (n < 0) 
							 error("ERROR writing to socket");

						bzero(buffer,256);
						n = read(clientSocket,buffer,255);
						if (n < 0) 
							 error("ERROR reading from socket");
						cout<<arr[1]<<":";
						printf("%s\n",buffer);
						int i = strncmp("Bye" , buffer , 3);
		  				int y = strncmp("bye" , buffer , 3);
						if(i == 0 || y == 0)
							   break;
				}
				   			 	 
   			 	 
   			 }
   			 else
   			 cout << "Invalid login" << endl;	
	

	return 0;
}
