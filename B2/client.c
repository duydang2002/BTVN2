#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main()
{   

    
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_in.sin_port = htons(9000);

    int con = connect(client,(struct sockaddr *)&addr_in,sizeof(addr_in));

    int ret;
    FILE *file = fopen("Data.txt","r");
    char buffer[16];
    while (!feof(file)){
        ret = fread(buffer,1,sizeof(buffer),file);
        if (ret <= 0 )break;
        if (ret < sizeof(buffer))
        buffer[ret] = 0;
        printf("%s\n",buffer);
        send(client,buffer,strlen(buffer),0);
}
}
