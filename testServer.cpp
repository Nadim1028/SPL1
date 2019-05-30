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

void error(const char *msg){
	perror(msg);
	exit(1);
}

int main(){

	int sockfd, ret,n;

	 struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[255];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");

	bzero((char *) &serverAddr , sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("Error in binding.\n");
		exit(1);
	}
	printf("Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("Listening....\n");
	}else{
		printf("Error in binding.\n");
	}


	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		int count = newSocket-4;
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);			
				
			

			bzero(buffer , 256);
			printf("Recvng..\n");
			n = read(newSocket , buffer , 255);
		//	printf("Recvd..\n");
			if(n<0)
				error("Error in reading");
	//		printf("Client : %s\n" , buffer);
			
			string recPacket = "";
			string senPacket = "";
			
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
   			 
   			// for(int i=0; i<j; i++)
   			// cout << "data is: " << arr[i] << endl;
   			// int count;
   			 string del = "~";
			  string Password[1000];
			 string Username[1000];
			
			 if(arr[2] == "signUp"){
			 	
				
				Username[count] = arr[3];
				Password[count] = arr[4];
				 senPacket = arr[0] + del + arr[1] + del + arr[2] + del + "true" + del;
			//	cout<<Username[count]<<endl;
			//	cout<<Password[count]<<endl;
			//	cout<<count<<endl;
				
			 }
			 
			  
   			 else if(arr[2] == "login")
   			 {
   			 //	cout << "Command is login" << endl;
       			//cout<<count<<endl;
       			for(int i=0;i<=count;i++){  
	   			 	if(arr[3].compare(Username[i])>0 && arr[4].compare(Password[i])>0)
	   			 		{
		   					 senPacket = arr[0] + del + arr[1] + del + arr[2] + del + "true" + del;
	   			 		}
	   			 		else
	   			 		senPacket = arr[0] + del + arr[1] + del + arr[2] + del + "false" + del;
   				 }
   			 
   			 }
   			 
			
			
			bzero(buffer , 256);
			//fgets(buffer , 255 , stdin);
			
			//printf("Buffer is: %s\n", buffer);
		//	cout << senPacket << endl;
		
			for(int i=0; i<senPacket.length(); i++)
				buffer[i] = senPacket[i];
        
			n = write(newSocket , buffer , strlen(buffer));
			if(n<0)
				error("Error on Writing");	
			
		while(1){
			bzero(buffer , 256);
			n = read(newSocket , buffer , 255);
			if(n<0)
				error("Error in reading");
			cout<<arr[3]<<": ";
			printf("%s\n" , buffer);
			bzero(buffer , 256);
			fgets(buffer , 255 , stdin);
		
			n = write(newSocket , buffer , strlen(buffer));
			if(n<0)
				error("Error on Writing");
			
			int i = strncmp("Bye" , buffer , 3);
		  	int y = strncmp("bye" , buffer , 3);
			if(i == 0 || y == 0)		
				break;
		}
	}		
		
}		

	


	close(newSocket);
	close(sockfd);

	return 0;
}
