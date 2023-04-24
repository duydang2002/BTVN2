#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void removeChar(char *str, char c) {
    int i, j;
    int len = strlen(str);
    for (i = j = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int checkDecrease (char* buf,int pos){
char*buf2 = malloc(buf[pos]-'0'+1);
memcpy(buf2,buf,sizeof(buf2));
removeChar(buf2,10);
removeChar(buf2,13);
    for (int i=pos;i>=pos+1-(buf2[pos]-'0');i--){
        if (buf2[i]!=buf2[i-1]+1) 
        {   
            return 0;
            }
    }
    return 1;
}
int checkIncrease (char* buf,int startNumber){
    
    for (int i=0;i<=9-startNumber-1;i++){
        if (buf[i]!=buf[i+1]-1) return 0;
    }
    return 1;
}
int main()
{
    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener < 0){
        perror("socket error");
        return 1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9000);
    if (bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("bind error");
        return 1;
    }
    if (listen(listener, 5) < 0){
        perror("listen error");
        return 1;
    }
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int client = accept(listener, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client <0){
        perror("accept error");
        return 1;
    }
printf("Accepted socket %d from IP: %s:%d \n",client,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    int ret;
    char buf[15];
    FILE *file = fopen("Receive.txt","wb");
    int count=0,end=-2,splash=0;
    while (1){
        ret = recv(client, buf, sizeof(buf),0);
        if (ret <= 0) break;
            if (ret < sizeof(buf))
            buf[ret] = 0;  
             printf("Receive %d byte %s\n",ret,buf);
            removeChar(buf,10);
            removeChar(buf,13);
            if (strstr(buf,"0123456789")){
                count++;
            }
            if (end == buf[0] -'0'-1){
                    if (checkIncrease(buf,end+1)){
                        count++;
                        end=-2;
                    }
                }
                if (buf[strlen(buf)-1]>=48 && buf[strlen(buf)-1]<=57){
                    if (checkDecrease(buf,strlen(buf)-1)){
                        end =buf[strlen(buf)-1]-'0';
                        printf("\n");
                    }     
    }
}
 printf("last count =  %d\n",count);
}
