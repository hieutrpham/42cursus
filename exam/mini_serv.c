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

void notify_others(int testfd, char *buf_read, size_t size);
Client *get_client(int testfd);
void close_client(struct pollfd *client);

Client g_clients[Fd_Max] = {};
int g_client_id = 0;

struct pollfd g_pollfd_array[Fd_Max] = {};
int g_fds_count = 0;

void fatal()
{
	char *mes = "Fatal error\n";
	write(2, mes, strlen(mes));
	exit(1);
}

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
		fatal();
	}

	struct in_addr addr;
	if (!inet_aton("127.0.0.1", &addr))
	{
		fatal();
	}

	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = addr.s_addr;
	address.sin_port = htons(atoi(av[1]));
	memset(address.sin_zero, 0, sizeof(address.sin_zero));

	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		close(server_fd);
	    fatal();
	}

	if (listen(server_fd, 69) < 0)
	{
		close(server_fd);
	    fatal();
	}

	(*g_pollfd_array).fd = server_fd;
	(*g_pollfd_array).events = POLLIN | POLLOUT;
	g_fds_count++;

	while (1)
	{
		int ready = poll(g_pollfd_array, g_fds_count, -1);
		if (ready < 0)
			continue;
		
		int iteration = 0;
		for (int i = 0; i < Fd_Max && iteration <= ready; ++i)
		{
			struct pollfd *current_pollfd = g_pollfd_array + i; 

			if (current_pollfd->revents & POLLIN)
			{
				if (current_pollfd->fd == server_fd)
				{
					struct sockaddr addr = {};
					socklen_t addrlen;
					int clientfd = accept(server_fd, &addr, &addrlen);
					if (clientfd < 0)
						continue;
					g_pollfd_array[g_fds_count].fd = clientfd;
					g_pollfd_array[g_fds_count].events = POLLIN | POLLOUT;
					g_fds_count++;

					g_clients[g_client_id].fd = clientfd;
					g_clients[g_client_id].id = g_client_id;

					char buf_read[4096] = {};
					sprintf(buf_read, "server: client %d arrived\n", g_client_id);
					notify_others(clientfd, buf_read, strlen(buf_read));

					g_client_id++;
					continue;
				}

				Client *client = get_client(current_pollfd->fd);
				if (client && client->fd >= 0)
				{
					char buf_read[4096] = {};
					sprintf(buf_read, "client %d: ", client->id);
					int len = strlen(buf_read);
					size_t bytes_read = read(current_pollfd->fd, buf_read + len, sizeof(buf_read) - len);

					if (bytes_read <= 0)
					{
						close_client(current_pollfd);
						continue;
					}
					notify_others(current_pollfd->fd, buf_read, strlen(buf_read));
				}
				++iteration;
			}
		}
	}
}

void notify_others(int testfd, char *buf_read, size_t size)
{
	for (int i = 1; i < g_fds_count; ++i)
	{
		struct pollfd *client_pollfd = g_pollfd_array + i;
		if (client_pollfd->fd != -1 && client_pollfd->fd != testfd && client_pollfd->fd != 3)
		{
			size_t bytes_write = send(client_pollfd->fd, buf_read, size, 0);
			if (bytes_write <= 0)
			{
				return;
			}
		}
	}
}

Client *get_client(int fd)
{
	Client *result = {0};
	for (int i = 0; i < g_client_id; ++i)
	{
		if (g_clients[i].fd == fd)
		{
			result = &g_clients[i];
		}
	}
	return result;
}

void close_client(struct pollfd *client)
{
	char buf[4096] = {};
	Client *cli = get_client(client->fd);
	sprintf(buf, "server: client %d disconnected\n", cli->id);
	notify_others(client->fd, buf, strlen(buf));
	
	close(client->fd);
	client->fd = -1;
	cli->fd = -1;

	struct pollfd *last_client = g_pollfd_array + g_fds_count - 1;
	*client = *last_client;

	last_client->fd = -1;
	--g_fds_count;
}
