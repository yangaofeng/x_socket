#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <errno.h> 


int main(int argc, char *argv)
{
	int s;
	struct sockaddr_in s_in;

	int c;
	socklen_t c_addr_len;
	struct sockaddr c_addr;

	int f;
	ssize_t bytes;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
		perror("socket");
		return -1;
	}

	s_in.sin_family = AF_INET;
	s_in.sin_addr.s_addr = INADDR_ANY;
	s_in.sin_port = htons(9527);

	if (bind(s, (struct sockaddr *)&s_in, sizeof(struct sockaddr_in)) == -1) {
		perror("bind");
		return -1;
	}

	if (listen(s, 10) == -1) {
		perror("listen");
		return -1;
	}

	f = open("a.txt", O_RDONLY);
	if (f == -1) {
		perror("open");
		return -1;
	}

	while (1) {
		c_addr_len = sizeof(struct sockaddr);
		c = accept(s, &c_addr, &c_addr_len);
		if (c == -1) {
			perror("accept");
			return -1;
		}

		if(lseek(f, 0, SEEK_SET) == -1) {
			perror("lseek");
			return -1;
		}

		do {
			bytes = sendfile(c, f, NULL, 1024);
			if (bytes > 0) {
				printf("send %d bytes\n", bytes);
			}
			else if (bytes == 0) {
				printf("send ok\n");
				break;
			}
			else if (bytes == -1) {
				perror("sendfile");
				return -1;
			}
		} while (1);
	
		close(c);
	}

	close(f);
	close(s);

	return 0;
}

