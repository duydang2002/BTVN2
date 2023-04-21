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
    if (argc != 2){
        printf("Nhap sai tham so!");
        return 0;
    }
    char *port = argv[1];
    if (!isdigit(*port)){
        printf("Nhap sai ten cong :");
    }
    int receiver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(port));
    if (bind(receiver, (struct sockaddr *)&addr, sizeof(addr)) ==-1 ){
        printf("bind failed");
        return 0;
    }
    FILE *file = fopen("receive.txt","a");
    if (file == NULL){
        printf("open file failed");
        return 0;
    }
    char buf[256];
    while (1){
        int ret = recvfrom(receiver, buf,sizeof(buf), 0,
        NULL,NULL);
        if (ret < 0){
            break;
        }
        buf[ret] = '\0';
        fprintf(file,"%s",buf);
        fflush(file);
        
        printf("%d bytes received: %s\n",ret,buf);
    }
    fclose(file);
    close(receiver);
}
