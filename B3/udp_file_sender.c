#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char  *argv[])
{
    if (argc != 4) {
        printf("Nhap sai tham so ");
        return 0;
    }
    int i;
int n=0;
char *temp = NULL;
temp = malloc(strlen(argv[1]) + 1); 
strcpy(temp, argv[1]);
char *p = strtok(temp,".");

if (p == NULL){
    return 0;
    } 
while (p!=NULL){
    i= atoi(p);
    if (isdigit(*p)==0) {
        printf("Sai dinh dang ip  \n");
        return 0;
    }
    if (i<0 || i>255){
        printf("Sai dinh dang ip \n");
        return 0;
    }
    p = strtok(NULL,".");
    n++;
}

if (n!=4) {
    printf("Sai dinh dang ip  \n");
    return 0;
}

if (!isdigit(*argv[2])){
    printf("Sai dinh dang port \n");
    return 0;
}
char *fileName = argv[3];
char *port = argv[2];
char *ip = argv[1];
int sender=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr(ip);
addr.sin_port = htons(atoi(port));

char buf[256];
FILE *file = fopen(fileName,"rb");
if (file == NULL) {
    printf("File not found \n");
    return 0;
}
    sendto(sender, fileName,strlen(fileName),0,
    (struct sockaddr *)&addr,sizeof(addr));
     sendto(sender, "\n",1,0,
    (struct sockaddr *)&addr,sizeof(addr));
while (1){
    int ret = fread(buf,1,sizeof(buf),file);
     if (ret <= 0){
        break;
        } 
    if (ret < sizeof(buf))
        buf[ret] = 0;
    sendto(sender, buf,ret,0,
    (struct sockaddr *)&addr,sizeof(addr));
    printf("\n%d bytes sent : %s\n",ret,buf);
   
}
fclose(file);
}
