#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>

#define PORT 8080
struct timespec a1;
int main(int argc, char const *argv[]){
	clock_gettime(CLOCK_REALTIME,&a1);
	int server_fd, new_socket;
	struct sockaddr_in sock_addr;
	int opt = 1;
	int addrlen = sizeof(sock_addr);
	char buffer[1024] = {0};
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	sock_addr.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&sock_addr,
								sizeof(sock_addr))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&sock_addr,
					(socklen_t*)&addrlen))<0){
		perror("accept");
		exit(EXIT_FAILURE);
	}

    /*To generate an array (of size 50) of strings (of length 4)*/ 
    int i=0, j=0;

    int r_key;
	char str_2[5];
	char arr[50][5];

	for (i = 0; i < 50; i++){
		for (j = 0; j < 4; j++){
			r_key = rand()%26 + 65;
			str_2[j] = (char)(r_key);
		}   
		str_2[5] = '\0';
		strcpy(arr[i], str_2);
	}

    /*Prints the contents of the array*/
    printf("P1: The contents of the array are\n");
    for (i = 0; i<50; i++){
        printf("%s\n", arr[i]);
    }

	/*Socket communication*/

	int first_id = 0;

	while(1){
		char str[24]="";

        int flag;
        if (first_id<10){
            flag = 1;
        }
        else{
            flag = 2;
        }

        char char_flag[20];
        sprintf(char_flag, "%d", flag);
        strcat(str, char_flag);

        char char_id[20];
        sprintf(char_id, "%d", first_id);
        strcat(str, char_id);

        strcat(str, arr[first_id]);
        strcat(str, arr[first_id + 1]);
        strcat(str, arr[first_id + 2]);
        strcat(str, arr[first_id + 3]);
        strcat(str, arr[first_id + 4]);

		send(new_socket, str, strlen(str), 0);

		char new_id[20];
		read(new_socket, new_id, 20);

		first_id = atoi(new_id);
        first_id++;
        printf("P1: Recieved index %i\n", first_id);

        if (first_id>48){
            break;
        }
        first_id++;  
	}
}
