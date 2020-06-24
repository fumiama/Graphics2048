#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
union number
{
	int num;
	char i[4];
};
typedef union number number;
#define PORT 12345
static const char smeg = 'w';
static const char rmeg = 'r';
static const char rlist = 'l';
static char cid;
static char cid_fri;
static const char zero = 0;
static char leng1;
static number num_t;
static WSADATA wsaData;
static SOCKET sockClient;//客户端Socket
static struct sockaddr_in addrServer;//服务端地址
static struct hostent* ht = NULL;
void init() {
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	ht = gethostbyname("www.xxx.com");
	addrServer.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr*)ht->h_addr_list[0])));
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(PORT);
}

int recvscore() {
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	send(sockClient, &cid, 1, 0);
	send(sockClient, &rmeg, 1, 0);
	send(sockClient, &cid_fri, 1, 0);
	recv(sockClient, num_t.i, sizeof(int), 0);
	closesocket(sockClient);
	return num_t.num;
}

void sendscore() {
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	send(sockClient, &cid, 1, 0);
	send(sockClient, &smeg, 1, 0);
	send(sockClient, num_t.i, sizeof(int), 0);
	num_t.num = htonl(num_t.num);
	closesocket(sockClient);
}

int getnewcid() {
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	send(sockClient, &cid, 1, 0);
	recv(sockClient, &cid, 1, 0);
	closesocket(sockClient);
	return cid;
}

void getlist() {
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
	send(sockClient, &cid, 1, 0);
	send(sockClient, &rlist, 1, 0);
	recv(sockClient, &leng1, 1, 0);
	printf("The total id:\n");
	while (leng1--) {
		char ch;
		recv(sockClient, &ch, 1, 0);
		printf("%d ", ch);
	}
	putchar('\n');
}

void setfrid() {
	scanf_s("%d", &cid_fri);
}