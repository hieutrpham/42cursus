#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <poll.h>

#define Array_Count(a) sizeof((a))/sizeof(*(a))
#define Assert(exp) if(!(exp)) (*(int*)0 = 0)

typedef struct client {
	int id;
	int fd;
	bool is_pending;
	char buf[1024*1024];
} Client;

Client clients[1024] = {};
int client_id = 0;
int client_index = 0;

struct pollfd polls[1024] = {};
int poll_count = 0;

void ft_memcpy(char *dest, char *src, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		*dest++ = *src++;
	}
}

void notify_others(int testfd, char *buf_read, size_t size)
{
	for (int i = 1; i < poll_count; ++i)
	{
		struct pollfd *client_pollfd = polls + i;
		if (client_pollfd->fd != -1 && client_pollfd->fd != testfd && client_pollfd->fd != 3)
		{
			int bytes_write = send(client_pollfd->fd, buf_read, size, 0);
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
	for (int i = 0; i < client_count; ++i)
	{
		if (clients[i].fd == fd)
		{
			result = &clients[i];
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

	Client *last_client = clients + client_index;
	*cli = *last_client;
	last_client->fd = -1;
	last_client->id = -1;
	client_index--;
	
	close(client->fd);

	struct pollfd *last_client = polls + poll_count - 1;
	*client = *last_client;
	last_client->fd = -1;
	last_client->revents = 0;
	--poll_count;
}

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
	if (server_fd < 0) { fatal(); }

	struct in_addr addr;
	if (!inet_aton("127.0.0.1", &addr)) { fatal(); }

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

	(*polls).fd = server_fd;
	(*polls).events = POLLIN;
	poll_count++;

	while (1)
	{
		int ready = poll(polls, poll_count, -1);
		if (ready < 0)
			continue;
		
		int iteration = 0;
		for (int i = 0; i < Array_Count(polls) && iteration != ready; ++i)
		{
			struct pollfd *curr = polls + i; 

			if (curr->revents & POLLIN)
			{
				if (curr->fd == server_fd)
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
					polls[poll_count].fd = clientfd;
					polls[poll_count].events = POLLIN;
					poll_count++;

					clients[client_count].fd = clientfd;
					clients[client_count].id = client_count;

					char buf_read[4096] = {};
					sprintf(buf_read, "server: client %d arrived\n", client_count);
					notify_others(clientfd, buf_read, strlen(buf_read));

					client_count++;
					++iteration;
					continue;
				}

				Client *client = get_client(curr->fd);
				if (client && client->fd >= 0)
				{
					char buf_write[1024*1024] = {};
					int bytes_read = recv(curr->fd, buf_write, sizeof(buf_write), 0);
					if (bytes_read <= 0)
					{
						close_client(curr);
						++iteration;
						continue;
					}

					char *buf = client->buf;
					char *start = buf_write;
					char *old_nl = start - 1;
					char *new_nl = strstr(start, "\n");
					if (!new_nl)
					{
						if (strlen(start) > 0)
						{
							client->is_pending = true;
							sprintf(buf, "client %d: ", client->id);
							ft_memcpy(buf + strlen(buf), start, strlen(start));
						}
						continue;
					}

					while (1)
					{
						if (!client->is_pending)
							sprintf(buf, "client %d: ", client->id);
						Assert(new_nl - start + 1 >= 0);
						ft_memcpy(buf + strlen(buf), start, new_nl - start + 1);
						notify_others(curr->fd, buf, strlen(buf));

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
						continue;
					}
				}
				++iteration;
			}
		}
	}
}
