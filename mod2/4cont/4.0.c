#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

const int BUF_SIZE = 4096;

int template_found(
    int fd,
    char* buff,
    char* template,
    uint64_t curr_pos,
    uint64_t tmpl_lenght,
    off_t offset)
{
    uint64_t j = curr_pos;
    for (; j < curr_pos + tmpl_lenght && j < BUF_SIZE; ++j) {
        if (buff[j] != template[j - curr_pos]) {
            return 0;
        }
    }
    if (j == BUF_SIZE) {
        char* buff2 =
            mmap(NULL, BUF_SIZE, PROT_READ, MAP_SHARED, fd, offset + BUF_SIZE);
        if (buff2 == MAP_FAILED) {
            return -1;
        }
        for (; j < curr_pos + tmpl_lenght; ++j) {
            if (buff2[j - BUF_SIZE] != template[j - curr_pos]) {
                if (munmap(buff2, BUF_SIZE) != 0) {
                    return -1;
                }
                return 0;
            }
        }
        if (munmap(buff2, BUF_SIZE) != 0) {
            return -1;
        }
    }
    return 1;
}

int main(int argc, char* argv[])
{
    struct stat st;
    lstat(argv[1], &st);
    uint64_t size = st.st_size;
    char* template = argv[2];
    uint64_t template_lenght = strlen(template);
    off_t offset = 0;
    int fd = open(argv[1], O_RDONLY);
    while (offset < size) {
        char* buff = mmap(NULL, BUF_SIZE, PROT_READ, MAP_SHARED, fd, offset);
        if (buff == MAP_FAILED) {
            goto close;
        }
        for (uint64_t i = 0; i < BUF_SIZE; ++i) {
            if (template_found(
                    fd, buff, template, i, template_lenght, offset) == 1) {
                printf("%ld ", offset + i);
            }
        }
        offset += BUF_SIZE;
        if (munmap(buff, BUF_SIZE) != 0) {
            goto close;
        }
    }
close:
    close(fd);
    return 0;
}
