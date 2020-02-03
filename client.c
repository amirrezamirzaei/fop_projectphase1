#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <conio.h>
#define MAX 5000
#define PORT 12345
#define SA struct sockaddr
int client_socket, server_socket,menustate;
char javabserver[1000],authtoken[32];
void makesocket();
void registeruser();
void loginuser();
void logout();
void joinchannel();
void createchannel();
void leavechannel();
void channelmembers();
void sendmessage();
void refresh();
void searchmember();
void searchmessage();
void menu1();
void menu2();
void menu3();
int main()
{
    system("color F2");
    menu1();
    int n;
   while(1)
   {
       scanf("%d%*c",&n);
       if ((menustate==1)&&(n==1)) {
        registeruser();
        continue;
                                   }
        if ((menustate==1)&&(n==2)) {
        loginuser();
        continue;
                                   }
        if ((menustate==2)&&(n==1)) {
        createchannel();
        continue;
                                   }
        if ((menustate==2)&&(n==2)) {
        joinchannel();
        continue;
                                   }
        if ((menustate==2)&&(n==3)) {
        logout();
        continue;
                                   }
        if ((menustate==3)&&(n==1)) {
        sendmessage();
        continue;
                                   }
        if ((menustate==3)&&(n==2)) {
        refresh();
        continue;
                                   }
        if ((menustate==3)&&(n==3)) {
        channelmembers();
        continue;
                                   }
        if ((menustate==3)&&(n==4)) {
        leavechannel();
        continue;
                                   }
        if ((menustate==3)&&(n==5)) {
        searchmember();
        continue;
                                   }
       if ((menustate==3)&&(n==6)) {
        searchmessage();
        continue;
                                   }
   }
}
void makesocket()
{
     char* buffer[80];

	struct sockaddr_in servaddr, cli;

	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return ;
    }

	// Create and verify socket

	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		//exit(0);
	}
		//else printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
       // else
    //printf("Successfully connected to the server..\n");
}
void menu1()
{
    system("cls");
    printf("Account menu\n1-register:\n2-login:\n");

    menustate=1;
}
void menu2()
{
    system("cls");
    printf("\n1-create channel\n2-join channel\n3-logout\n");
    menustate=2;
}
void menu3()
{
     system("cls");
    printf("\n1-send message\n2-refresh\n3-channel members\n4-leave channel\n5-search member\n6-search message\n");
    menustate=3;
}
void registeruser()
{
     char username[MAX],password[MAX],buffer[MAX]="register ";
  puts("please enter username");
  scanf("%s",username);
  puts("please enter password");
  scanf("%s",password);
  strcat(password,"\n");
  strcat(buffer, username);
  strcat(buffer,", ");
  strcat(buffer,password);
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
   if (javabserver[9]=='S')
    puts("your account has been registered");
   else
    puts("please try again");
    puts("press any key to continue");
    getchar();   getchar();
    menu1();
}
void loginuser()
{
  char username[MAX],password[MAX],buffer[MAX]="login ";
  puts("please enter username");
  scanf("%s",username);
  puts("please enter password");
  scanf("%s",password);
  strcat(buffer,username);
  strcat(buffer,", ");
  strcat(buffer,password);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
    closesocket(client_socket);
   if(javabserver[9]=='E')
   {
       puts("ERROR YOU SHALL NOT PASS!\npress any key to continue.");
       getchar();  getchar();
       menu1();
       return;
   }
    printf("login successful press any key to continue.\n");
   int counter=0;
   memset(authtoken,1,sizeof(authtoken));
   for(int i=31;i<63;i++)
    authtoken[counter++]=javabserver[i];
    authtoken[32]='\0';
    getchar();
    getchar();
    menu2();
}
void logout()
{
   char buffer[MAX]="logout ";
   authtoken[32]='\0';
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
   closesocket(client_socket);
   authtoken[32]='\0';
    if(javabserver[9]=='S')
    {
        puts("logout succesful press any key to continue");
        getchar();
        menu1();
        return;
    }
    else
    {
        puts("logout unsuccesful press any key to continue");
        getchar();
        menu2();
        return;
    }
}
void createchannel()
{
    char channelname[MAX],buffer[MAX]="create channel ";
    authtoken[32]='\0';
  puts("please enter channel name");
  scanf("%s",channelname);
  strcat(buffer,channelname);
  strcat(buffer,", ");
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
   //printf("FROM SERVER:%s",javabserver);
    closesocket(client_socket);
    authtoken[32]='\0';
    if(javabserver[9]=='E')
    {
        puts("channel coudnt be made, press any key to continue");
        getchar();  getchar();
        menu2();
        return;
    }
    else
    {
        puts("channel made, press any key to continue");
        getchar();  getchar();
        menu3();
        return;
    }
}
void joinchannel()
{
   char channelname[MAX],buffer[MAX]="join channel ";
    authtoken[32]='\0';
  puts("please enter channel name");
  scanf("%s",channelname);
  strcat(buffer,channelname);
  strcat(buffer,", ");
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
    closesocket(client_socket);
    if(javabserver[9]=='E')
    {
        puts("there is no channel with the name you entered,press any key to continue");
        getchar();  getchar();
        menu2();
        return;
    }
    else
    {
        puts("you joined this channel,press any key to continue");
        getchar();  getchar();
        menu3();
        return;
    }
}
void leavechannel()
{
   char buffer[MAX]="leave ";
   authtoken[32]='\0';
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
   //printf("FROM SERVER:%s",javabserver);
   closesocket(client_socket);
   authtoken[32]='\0';
    if(javabserver[9]=='S')
    {
        puts("you have left this channel,press any key to continue");
        getchar();
        menu2();
        return;
    }
    else
    {
         puts("please try again,press any key to continue");
        getchar();
        menu3();
        return;
    }
}
void channelmembers()
{
     char buffer[MAX]="channel members ";
   authtoken[32]='\0';
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
   printf("FROM SERVER:\n%s",javabserver);
   closesocket(client_socket);
   authtoken[32]='\0';
   printf("\npress any key to continue");
   getchar();
   menu3();
}
void sendmessage()
{
    char message[MAX],buffer[MAX]="send ";
    authtoken[32]='\0';
  puts("please enter your message");
  scanf("%[^\n]%*c", message);
  strcat(buffer,message);
  strcat(buffer,", ");
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
   //printf("FROM SERVER:%s",javabserver);
    closesocket(client_socket);
    authtoken[32]='\0';
     if(javabserver[9]=='S')
    {
        puts("your message has been sent,press any key to continue");
         getchar();
        menu3();
        return;
    }
    else
    {
         puts("ERROR,press any key to continue");
        getchar(); getchar();
        menu3();
        return;
    }
}
refresh()
{
    char buffer[MAX]="refresh ";
   authtoken[32]='\0';
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
   recv(client_socket,javabserver,sizeof(javabserver),0);
  printf("FROM SERVER:\n%s\n",javabserver);
   closesocket(client_socket);
   authtoken[32]='\0';
   puts("PRESS ANY KEY TO CONTINUE");
   getchar();
   menu3();
}
searchmember()
{
 char name[MAX],buffer[MAX]="searchmember ";
    authtoken[32]='\0';
  puts("please enter the username you want to search");
  scanf("%s",name);
  strcat(buffer,name);
  strcat(buffer,", ");
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
  recv(client_socket,javabserver,sizeof(javabserver),0);
  if(javabserver[0]=='T')
    printf("%s is in this channel.",name);
  else
     printf("%s is not in this channel.",name);
  closesocket(client_socket);
  getchar();  getchar();
  menu3();
}
void searchmessage()
{
 char name[MAX],buffer[MAX]="searchmessage ";
    authtoken[32]='\0';
  puts("please enter the message you want to search");
  scanf("%s",name);
  strcat(buffer,name);
  strcat(buffer,", ");
  strcat(buffer,authtoken);
  strcat(buffer,"\n");
  makesocket();
  send(client_socket,buffer,strlen(buffer),0);
  memset(javabserver,0,sizeof(javabserver));
  recv(client_socket,javabserver,sizeof(javabserver),0);
  printf("\nFROM SERVER:%s",javabserver);
  closesocket(client_socket);
  getchar();  getchar();
  menu3();
}
