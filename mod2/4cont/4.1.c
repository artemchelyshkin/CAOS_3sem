#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

const int BUF_MAX = 4096;

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int argc, char* argv[])
{
    struct stat st;
    lstat(argv[1], &st);
    uint64_t size = st.st_size;
    if (size < sizeof(struct Item)) {
        return 0;
    }
    uint64_t lenght = BUF_MAX + sizeof(struct Item);
    off_t offset = 0;
    uint64_t extention = BUF_MAX;
    uint32_t pointer = 0;
    int fd = open(argv[1], O_RDONLY);
    char* buff = mmap(NULL, lenght, PROT_READ, MAP_SHARED, fd, offset);
    struct Item* it = (struct Item*)(buff);
    pointer = it->next_pointer;
    while (it->next_pointer != 0) {
        printf("%d\n", it->value);
        munmap(buff, lenght);
        offset = 0;
        while (pointer > offset + extention) {
            offset += extention;
        }
        buff = mmap(NULL, lenght, PROT_READ, MAP_SHARED, fd, offset);
        it = (struct Item*)(buff + pointer - offset);
        pointer = it->next_pointer;
    }
    printf("%d", it->value);
    munmap(buff, lenght);
    close(fd);
}
