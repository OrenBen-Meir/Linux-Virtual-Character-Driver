#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/solidusdevice"

#define DEV_DATA_SIZE 200 // size of device

int main()
{
    int i, fd;
    char cmd, write_buf[DEV_DATA_SIZE], read_buf[DEV_DATA_SIZE];

    fd = open(DEVICE_FILE, O_RDWR); //open for reading and writing

    if (fd == -1)
    {
        printf("file %s is either used by another process or doesn't exist\n", DEVICE_FILE);
        exit(-1);
    }

    int is_continue = 1; // sets

    while (is_continue)
    {
        printf("r = read from device\nw = write to device\nAny other key exits the program\nEnter command: ");
        scanf("%c", &cmd);
        switch (cmd)
        {
        case 'w':
            printf("Enter data: ");
            scanf(" %[^\n]", write_buf);
            write(fd, write_buf, sizeof(write_buf));
            break;
        case 'r':
            read(fd, read_buf, sizeof(read_buf));
            printf("device contents:\n%s\n", read_buf);
            break;

        default:
            printf("Exiting program\n");
            is_continue = 0;
            break;
        }
    }
    close(fd);
    return 0;
}