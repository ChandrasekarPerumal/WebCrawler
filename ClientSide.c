

/* Socket Program: Client Side */
/*
 * Web Crawler..
 *
 * */


#include <stdio.h> 
#include <sys/socket.h> //This header file includes a number of definitions of structures needed for sockets.
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>

extern int h_errno; // Get the error thrown by the GetHostByName...

#define H 65536
#define LSIZ 128 
#define RSIZ 10 
#define CLIENT_PORT 80 

	char Serv_reply[40000];
	int check=0;
	int sock=0;
	int i=0,link_count=0;
	int count=0;
	char Get_buffer[40000]={0};
	char pattern[]="<a href=";	
	char url[50];
	char *ip;
	int valread; 
	int size=0;	
	struct sockaddr_in adrr; 
	char *hello = "Hello from client"; 
	char buffer[40000] = {0}; 
	char Resource_path[]="/";
        int cnt=0;
       	char lnk[40000];
	char arr_link[20000]={'\0'};
	int Link_i=0;
	int q=0;	
	int iin=0;
	int check_flag=1;
	//hashtable_t *hashtable = NULL;




int CreateSocket()
{
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                printf("\n Socket creation error \n");
                return -1;
        }
        else
        {
                printf("\nSocket created\n");
        }
	
	/* Intialize the Structure */
	adrr.sin_family = AF_INET; 
	adrr.sin_port = htons(CLIENT_PORT); // Service port: 16-bit port number
	adrr.sin_addr.s_addr=inet_addr(ip); // IP address: 32-bit ip address
	
	/* Connect the socket */
	if (connect(sock, (struct sockaddr *)&adrr, sizeof(adrr)) < 0) 
	{		
		perror("Err:");
		printf("\nConnection Failed \n"); 
		return -1; 
	}
	else
	{
		//printf("%s %d",ip,ntohl(adrr.sin_addr.s_addr));
		printf("\nConnection done\n\n");
	}
	/* Write the client reqest to the socket */
	sprintf(Get_buffer, "GET %s HTTP/1.1\r\nHost: %s \r\nContent-Type:text/plain\r\n\r\n", Resource_path,ip);
	write(sock,Get_buffer,strlen(Get_buffer)); 
	printf("\nCreated Get Request:");
}

void Download_page()
{
        puts(Serv_reply); /* Write the response to console */
        printf("\nSize:%3d",size);
        Serv_reply[19999] = '\0';
}


void getUrl(char arrr[])
{
	
		struct hostent *ghbn=gethostbyname(arrr);
		if(ghbn==NULL)
		{
			perror("Link-Error:");
			printf("%s",hstrerror(h_errno));
		}		
		else
		{
			printf("Host Name->%s\n", ghbn->h_name);
        		printf("IP ADDRESS->%s\n",inet_ntoa(*(struct in_addr *)ghbn->h_addr_list[0]));
        		ip=inet_ntoa(*(struct in_addr *)ghbn->h_addr_list[0]);
		}     
}



void create(char t[])
{
	int len=strlen(t);
	while(q!=len){
	arr_link[Link_i]=t[q];
	q++;
	Link_i++;
	}
	arr_link[Link_i]='\0';
}


void disp()
{
	printf("\n List\n ");
	int d=0;
	while(d!=Link_i)
	{
		printf("%c",arr_link[d]);
		d++;
	}
}


void links()
{
	FILE *fp;
	char str1[50];
	int kk=0;
	int j=1;
        if((fp=(fopen("t1.txt","a+")))==NULL)
        {
                printf("ERROR\n");
        }
        else
        {
                printf(" File Open success\n");
        }

	while(Serv_reply[i] != '\0'){
		check++; 		
		if(Serv_reply[i] == pattern[0]){
			i++;
			// Check for "ahref" ..
		/*	for(j=1;j<=7;j++)
			{
				if(Serv_reply[i]!=pattern[j])
				{
					count=0;
					break;
				}
			} */


if( Serv_reply[i-1] == pattern[j-1] && Serv_reply[i] == pattern[j] && Serv_reply[i+1] == pattern[j+1] && Serv_reply[i+2]==pattern[j+2]&&Serv_reply[i+3] == pattern[j+3]&&Serv_reply[i+4] == pattern[j+4]&& Serv_reply[i+5] == pattern[j+5]&&Serv_reply[i+6] == pattern[j+6]    ){
					count=1;  // Flag:True 
			
				}		
				
				if(count==1){	
				i=i+8;
				int w=0,set_flag=0,it=0;
				char buf1[20];
				char pattern1[4]="http";			
				while(Serv_reply[i] != '"'&&Serv_reply[i+1]!='>')
					{
						lnk[w++]=Serv_reply[i];
						i++;
					}
					if(pattern1[0]==lnk[0]&&pattern1[1]==lnk[1]&&pattern1[2]==lnk[2]&&pattern1[3]==lnk[3])
					{	
						while(it!=w)
						{
							printf("%c",lnk[it]);
							it++;
						}
						printf("\n");
					
						if(check_flag==1){
								create(lnk);
								check_flag=0;
						}
			
						 // Append the Links to File called Links...
                                                 FILE *IN = fopen("t1.txt", "a");
                                                 if(IN==NULL){
                                                 perror("File Open :");}
						 link_count++;
						 //printf("Check Point:%d\n",link_count);
                                                
						 fprintf(IN, "%s\n", lnk);

						 //snprintf(buf1, 12, "Link%d", link_count); // puts string into buffer
						 //printf("%s\n", buf1);						 
      						 //transfer(buf1,lnk);
                                                 fclose(IN);
					}
				}	
			}count=0;
	i++;
		}
		printf("\nLink Count=%2d",link_count);	
}


void display(char arr[])
{
        for(int i = 0; i < strlen(arr); ++i)
        {
                if(i==0)
                {
                        printf("\n Called me-- ");
                }
                printf("%c", arr[i]);

        }
}



int chek=1;
int inc=-1;

int main() 
{ 
	char buff[50];
        FILE *fp;

        if((fp=(fopen("t1.txt","r+")))==NULL)
        {
                printf("ERROR\n");
        }
        else
        {
                printf(" File Open success\n");
        }

        char line[LSIZ][RSIZ];
	int presv;

while(fgets(line[iin], LSIZ, fp))
{
                                line[iin][strlen(line[iin]) - 1] = '\0';
                                presv=iin;
			display(line[presv]);
				iin++;
	getUrl(line[presv]);
	CreateSocket(); // User-defined Function to create socket
	/* Receive server response */
	size=recv(sock,Serv_reply,40000,0);		
	Download_page();
	/*puts(Serv_reply); // Write the response to console 
	printf("\nSize:%3d",size);
	Serv_reply[19999] = '\0';*/
	printf("\n Links::\n\n"); /* Link Extraction from the downloaded document and print  */
	links();
	printf("\n\n\n%s",Get_buffer);
}
	fclose(fp);
	return 0;
}


/*
void get2Url()
{
	char c[1000];
	FILE *fptr;
    if ((fptr = fopen("links.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

        char *line=NULL;
        size_t len=0;
        ssize_t read;

    // reads text until newline is encountered
    while((read=getline(&line,&len,fptr))!=-1 )
    {
        fscanf(fptr, "%[^\n]", c);
        printf("%s\n", c);
        int i=0;
        while(c[i]!='/')
        {
                i++;
        }   
        i=i+2;
        while(c[i]!='/')
        {
                printf("%c",c[i]);i++;
        }
        //printf("\n");

           }
                int ik=0;
                while(ik!=strlen(c))
                {
                        url[ik]=c[ik];
                        ik++;
                }
                url[ik-1]='\0';
                struct hostent *ghbn=gethostbyname(url);
                if(ghbn==NULL)
                {
                        perror("Error:");
                        printf("%s",hstrerror(h_errno));

		}
		else
  		{
                        printf("Host Name->%s\n", ghbn->h_name);
                        printf("IP ADDRESS->%s\n",inet_ntoa(*(struct in_addr *)ghbn->h_addr_list[0]));
                        ip=inet_ntoa(*(struct in_addr *)ghbn->h_addr_list[0]);
                }
        }
        fclose(fp);

	CreateSocket();
        size=recv(sock,Serv_reply,20000,0);
	Download_page();
	printf("\nLinks::\n\n");
	links();
	printf("\n\n%s",Get_buffer);
}

*/

