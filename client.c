#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include "world.h"
#include "camera.h"
SOCKET client_socket;
int size_data=0;
int client_UID=-1;
enum ClientAction {
    RenderingWorld,
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    MoveForward,
    MoveBack,
    SetBlock,
    RotateLeft,
    RotateRight,
    GetCameraPosition,
    Jump
};
int connect_to_server() {
  WSADATA ws;
    WSAStartup( MAKEWORD(2,2), &ws);
    SOCKET s;
    client_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    SOCKADDR_IN adr;
    memset(&adr,0,sizeof(adr));
    adr.sin_family=AF_INET;
    adr.sin_port=htons(1243);
    adr.sin_addr.S_un.S_addr=inet_addr("88.85.171.249");

    return connect(client_socket,&adr,sizeof(adr));


}
void send_state(int state){
int stat;
stat=state;

if(stat!=1)
send(client_socket,&stat,sizeof(stat),0);
if(stat==0)
	recv(client_socket,&client_UID,sizeof(client_UID),0);
if(stat==1){
	int n=0;
	do{
	float data[15];
	send(client_socket,&stat,sizeof(stat),0);
	recv(client_socket,data,sizeof(data),0);
	int isNull=1;
	for(int i=0;i<15;i+=1){
		if(data[i]!=0)
			isNull=0;
	}
	if(isNull==1)
		break;
	add_object(data);

	}while(n==0);
}
}
