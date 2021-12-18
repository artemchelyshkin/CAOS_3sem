#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int args, char* argv[])
{
    struct Item it;
    it.next_pointer = 1;
    uint32_t pointer = 0;
    int file = open(argv[1], O_RDONLY);
    if (file < 0) {
        close(file);
        return 1;
    }
    ssize_t bytes = read(file, &it, sizeof(it));
    if (bytes <= 0) {
        close(file);
        return 0;
    }
    pointer = it.next_pointer;
    while (it.next_pointer != 0) {
        printf("%d\n", it.value);
        lseek(file, pointer, SEEK_SET);
        read(file, &it, sizeof(it));
        pointer = it.next_pointer;
    }
    printf("%d", it.value);
    close(file);
}
