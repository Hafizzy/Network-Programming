# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>



const char* help_string = "Usage: simple-http [-h] [-4|-6] [-p PORT] [-o OUTPUT_FILE] SERVER FILE\n";

void errExit(const char* str, char p)
{
	if ( p != 0 )
	{
		perror(str);
	} else
	{
		fprintf(stderr,str);
	}
	exit(1);
}

int main (int argc, char** argv)
{
	struct addrinfo *result, hints;
	int srvfd, rwerr = 42, outfile, ai_family = AF_UNSPEC;
	char *request, buf[16], port[6],c;

	memset(port,0,6);

	if ( argc < 3 )
		errExit(help_string,0);
	
	strncpy(port,"80",2);

	while ( (c = getopt(argc,argv,"p:ho:46")) >= 0 )
	{
		switch (c)
		{
			case 'h' :
				errExit(help_string,0);
			case 'p' :
				strncpy(port,optarg,5);
				break;
			case 'o' :
				outfile = open(optarg,O_WRONLY|O_CREAT,0644);
				close(1);
				dup2(outfile,1);
				break;
			case '4' :
				ai_family = AF_INET;
				break;
			case '6' :
				ai_family = AF_INET6;
				break;
		}
	}

	memset(&hints,0,sizeof(struct addrinfo));

	hints.ai_family = ai_family;
	hints.ai_socktype = SOCK_STREAM;

	if ( 0 != getaddrinfo(argv[optind],port,&hints,&result))
		errExit("getaddrinfo",1);


	srvfd = socket(result->ai_family,SOCK_STREAM,0);

	if ( srvfd < 0 )
		errExit("socket()",1);

	if ( connect(srvfd,result->ai_addr,result->ai_addrlen) == -1)
		errExit("connect",1);
	
	

	request = calloc(53+strlen(argv[optind+1])+strlen(argv[optind]),1);

	sprintf(request,"GET %s HTTP/1.1\nHost: %s\nUser-agent: simple-http client\n\n",argv[optind+1],argv[optind]);

	write(srvfd,request,strlen(request));
	
	shutdown(srvfd,SHUT_WR);

	while ( rwerr > 0 )
	{
		rwerr = read(srvfd,buf,16);
		write(1,buf,rwerr);
	}
	
	close(srvfd);

	return 0;

}