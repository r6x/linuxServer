#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h> 
#include <netinet/in.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
struct sockaddr_in addr;
int main ()
{
	char buf[100],log[10]="admin",pas[10]="123";
	time_t rawtime;
	struct tm * timeinf;
	int i,sockfd,sockfd1,len,len1;
	addr.sin_family=AF_UNIX;
	addr.sin_port=htons(50251);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockfd=socket(AF_UNIX,SOCK_STREAM,0);
	if (sockfd<0) {printf("error1\n"); exit(0);}
	if(bind(sockfd,(struct sockaddr *)&addr,sizeof(addr))<0) {printf("error2\n"); exit(0);}
	if(listen(sockfd,5)<0) {printf("error3\n"); exit(0);}
	while(1)
	{
		sockfd1=accept(sockfd,NULL,NULL);
		if (sockfd1<0) {printf("error4 %d\n",sockfd1); close(sockfd1); continue;}
		len=sprintf(buf,"Enter login\n");
		send(sockfd1,buf,len+1,0);
		len1=recv(sockfd1,buf,10,0);
		if(strncmp(buf,log,len1-2)!=0) {close(sockfd1); continue;}
		len=sprintf(buf,"Enter password\n");
		send(sockfd1,buf,len+1,0);
		len1=recv(sockfd1,buf,10,0);
		if(strncmp(buf,pas,len1-2)!=0) {close(sockfd1); continue;}
		time(&rawtime);
		timeinf=localtime(&rawtime);
		len=sprintf(buf,"Time is %d:%d\n",timeinf->tm_hour,timeinf->tm_min);
		send(sockfd1,buf,len+1,0);
		close(sockfd1);
	}
return(0);
}