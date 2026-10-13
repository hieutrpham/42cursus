#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

#define Fd_Max 4096*100
typedef struct client {
	int id;
	int fd;
} Client;

void send_message(int testfd, char *buf_read, size_t size);
Client *get_client(int testfd);
void close_client(struct pollfd *client);

Client clients[Fd_Max] = {};
int client_id = 0;

struct pollfd fds[Fd_Max] = {};
int fds_count = 0;

int main(int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, "invalid arguments\n");
		exit(1);
	}
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		fprintf(stderr, "fatal error\n");
		exit(1);
	}

	struct in_addr addr;
	if (!inet_aton("127.0.0.1", &addr))
	{
		fprintf(stderr, "fatal error\n");
		exit(1);
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = addr.s_addr;
	address.sin_port = htons(atoi(av[1]));
	memset(address.sin_zero, 0, sizeof(address.sin_zero));

	int yes = 0;
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(address));

	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		close(server_fd);
	}

	if (listen(server_fd, 69) < 0) {
		close(server_fd);
	}

	(*fds).fd = server_fd;
	(*fds).events = POLLIN | POLLOUT;
	fds_count++;

	while (1)
	{
		int ready = poll(fds, fds_count, -1);
		if (ready < 0)
			continue;
		
		int iteration = 0;
		for (int i = 0; i < Fd_Max && iteration <= ready; ++i)
		{
			struct pollfd *current_pollfd = fds + i; 

			if (current_pollfd->revents == 0)
				continue;

			if (current_pollfd->revents & (POLLHUP|POLLERR|POLLNVAL))
			{
				Client *client = get_client(current_pollfd->fd);
				fprintf(stdout, "client %d disconnected\n", client->id);
				close_client(current_pollfd);
			}

			if (current_pollfd->revents & POLLIN)
			{
				if (current_pollfd->fd == server_fd)
				{
					struct sockaddr addr = {};
					socklen_t addrlen;
					int clientfd = accept(server_fd, &addr, &addrlen);
					if (clientfd < 0)
						continue;
					fds[fds_count].fd = clientfd;
					fds[fds_count].events = POLLIN | POLLHUP;
					fds_count++;

					clients[client_id].fd = clientfd;
					clients[client_id].id = client_id;

					char buf_read[4096] = {};
					sprintf(buf_read, "server: client %d arrived\n", client_id);
					send_message(clientfd, buf_read, strlen(buf_read));

					fprintf(stdout, "new client %d\n", client_id);
					client_id++;
					continue;
				}

				Client *client = get_client(current_pollfd->fd);
				char buf_read[4096] = {};
				if (client->id >= 0)
				{
					sprintf(buf_read, "client %d: ", client->id);
					int len = strlen(buf_read);
					size_t bytes_read = read(current_pollfd->fd, buf_read + len, sizeof(buf_read) - len);

					if (bytes_read <= 0)
					{
						fprintf(stdout, "client %d disconnected\n", client->id);
						close_client(current_pollfd);
						continue;
					}
					send_message(current_pollfd->fd, buf_read, strlen(buf_read));
				}
			}
			iteration++;
		}
	}
}

void send_message(int testfd, char *buf_read, size_t size)
{
	for (int i = 1; i < fds_count; ++i)
	{
		struct pollfd *client_pollfd = fds + i;
		if (client_pollfd->fd != -1 && client_pollfd->fd != testfd && client_pollfd->fd != 3)
		{
			size_t bytes_write = write(client_pollfd->fd, buf_read, size);
			if (bytes_write <= 0)
			{
				close_client(client_pollfd);
				return;
			}
		}
	}
}

Client *get_client(int fd)
{
	Client *result = {0};
	for (int i = 0; i < client_id; ++i)
	{
		if (clients[i].fd == fd)
			result = &clients[i];
	}
	return result;
}

void close_client(struct pollfd *client)
{
	char buf[4096] = {};
	Client *client_pollfd = get_client(client->fd);
	sprintf(buf, "server: client %d disconnected\n", client_pollfd->id);
	send_message(client->fd, buf, strlen(buf));
	close(client->fd);
	client->fd = -1;

	struct pollfd *last_client = fds + fds_count - 1;
	last_client->fd = -1;
	*client = *last_client;
	--fds_count;
}
