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
    
    struct sockaddr_in addr,sender;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(atoi(port));
    int sender_len = sizeof(sender);
    if (bind(receiver, (struct sockaddr *)&addr, sizeof(addr)) ==-1 ){
        printf("bind failed");
        return 0;
    }
    
    char buf[256];
    char *pos=NULL;
    char *senderName=NULL;
    char *fileName=NULL;
    char *fileContent=NULL;
    while (1){
        int ret = recvfrom(receiver, buf,sizeof(buf), 0,
        NULL,NULL);
        if (ret < 0){
            break;
        }
        buf[ret] = '\0';
        pos = strchr(buf,' ');
    // printf("%s",buf);
        if (pos == NULL){
            printf("Khong tim thay");
            break;

        }
        int senderName_len = pos - buf;
        senderName= malloc(senderName_len);
        memcpy(senderName,buf,senderName_len);
        //  printf("%s",senderName);
        //  break;
        pos = strchr(buf+senderName_len+1,' ');
        int fileName_len = pos - buf-senderName_len-1;
        fileName= malloc(fileName_len);
        memcpy(fileName,buf+senderName_len+1,fileName_len);
        fileContent= malloc(ret-senderName_len-fileName_len-2);
        memcpy(fileContent,pos+1,ret-senderName_len-fileName_len-2);
        FILE *file = fopen(fileName,"a");
        if (file == NULL){
        printf("open file failed");
        return 0;
    }
        
        fprintf(file,"%s",fileContent);
        fflush(file);
        
        printf("%d bytes received from Sender Name: %s and to file: %s content : %s\n",ret,senderName,fileName,fileContent);
        fclose(file);
    }
    
    close(receiver);
}
