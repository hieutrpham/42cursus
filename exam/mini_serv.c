#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

#define Fd_Max 4096
#define Client_Max 1024
#define Assert(exp) if(!(exp)) (*(int*)0 = 0)
typedef struct client {
	int id;
	int fd;
	bool is_pending;
	char buf[256];
} Client;

void ft_memcpy(char *dest, char *src, size_t size);
void notify_others(int testfd, char *buf_read, size_t size);
Client *get_client(int testfd);
void close_client(struct pollfd *client);

Client g_clients[Client_Max] = {};
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

	printf("Server listening\n");

	(*g_pollfd_array).fd = server_fd;
	(*g_pollfd_array).events = POLLIN | POLLOUT;
	g_fds_count++;

	while (1)
	{
		int ready = poll(g_pollfd_array, g_fds_count, -1);
		if (ready < 0)
			continue;
		
		int iteration = 0;
		for (int i = 0; i < Fd_Max && iteration != ready; ++i)
		{
			struct pollfd *current_pollfd = g_pollfd_array + i; 

			if (current_pollfd->revents & POLLIN)
			{
				if (current_pollfd->fd == server_fd)
				{
					struct sockaddr addr = {};
					socklen_t addrlen = 0;
					int clientfd = accept(server_fd, &addr, &addrlen);
					if (clientfd < 0)
					{
						fprintf(stderr, "%m: accept fail, clientfd = %d\n", clientfd);
						fprintf(stderr, "%s\n", strerror(errno));
						continue;
					}
					g_pollfd_array[g_fds_count].fd = clientfd;
					g_pollfd_array[g_fds_count].events = POLLIN;
					g_fds_count++;

					g_clients[g_client_id].fd = clientfd;
					g_clients[g_client_id].id = g_client_id;

					char buf_read[4096] = {};
					sprintf(buf_read, "server: client %d arrived\n", g_client_id);
					notify_others(clientfd, buf_read, strlen(buf_read));

					g_client_id++;
					++iteration;
					continue;
				}

				Client *client = get_client(current_pollfd->fd);
				if (client && client->fd >= 0)
				{
					char mes[4096] = {};

					// read all the messages from client to the pending buffer
					char *buf = client->buf;
					size_t bytes_read = recv(current_pollfd->fd, mes, sizeof(mes), 0);

					if (bytes_read <= 0)
					{
						close_client(current_pollfd);
						++iteration;
						continue;
					}

					char *start = mes;
					char *old_nl = start - 1;
					char *new_nl = strstr(start, "\n");
					if (!new_nl)
					{
						close_client(current_pollfd);
						++iteration;
						continue;
					}

					while (1)
					{
						if (!client->is_pending)
							sprintf(buf, "client %d: ", client->id);
						Assert(new_nl - start + 1 >= 0);
						ft_memcpy(buf + strlen(buf), start, new_nl - start + 1);
						notify_others(current_pollfd->fd, buf, strlen(buf));

						old_nl = new_nl;
						new_nl = strstr(old_nl + 1, "\n");
						if (!new_nl) break;
						start = old_nl + 1;
					}

					if (strlen(old_nl + 1) > 0)
					{
						client->is_pending = true;
						sprintf(buf, "client %d: ", client->id);
						ft_memcpy(buf + strlen(buf), old_nl + 1, strlen(old_nl + 1));
						notify_others(current_pollfd->fd, buf, strlen(buf));
						continue;
					}
				}
				++iteration;
			}
		}
	}
}

void ft_memcpy(char *dest, char *src, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		// dest[i] = src[i];
		*dest++ = *src++;
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
	memset(buf_read, 0, size);
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
