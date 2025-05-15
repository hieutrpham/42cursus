#include "get_next_line.h"
int main() {
    int fd = open("hello.txt", O_RDONLY);
    t_list *head = NULL;
    t_list *node;

    while ((node = get_next_line(fd))) {
        append(&head, node);  // Add to linked list
    }

    // Print all nodes AFTER reading
    t_list *tmp = head;
    while (tmp) {
        printf("< %s >\n", (char *)tmp->content);
        tmp = tmp->next;
    }

    close(fd);
    return 0;
}
