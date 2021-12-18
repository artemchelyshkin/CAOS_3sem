#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

uint32_t size_of_buf = 4096;

int main(int argc, char* argv[])
{
    char buf[size_of_buf];
    char file2[size_of_buf];
    char file3[size_of_buf];
    uint64_t it2 = 0;
    uint64_t it3 = 0;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    int fd2 = open(argv[2], O_CREAT | O_WRONLY, 0640);
    if (fd2 == -1) {
        close(fd);
        return 2;
    }
    int fd3 = open(argv[3], O_CREAT | O_WRONLY | O_APPEND, 0640);
    if (fd3 == -1) {
        close(fd);
        close(fd2);
        return 3;
    }
    size_t pos = 0;
    ssize_t n = 0;
    while ((n = read(fd, buf, size_of_buf)) != 0) {
        for (size_t i = 0; i < n; ++i) {
            if (buf[i] <= '9' && buf[i] >= '0') {
                file2[it2] = buf[i], ++it2;
                if (it2 > size_of_buf) {
                    write(fd2, file2, it2);
                    it2 = 0;
                }
            } else {
                file3[it3] = buf[i], ++it3;
                if (it3 > size_of_buf) {
                    write(fd3, file3, it3);
                    it3 = 0;
                }
            }
        }
        pos += size_of_buf;
        lseek(fd, pos, SEEK_SET);
    }
    write(fd3, file3, it3);
    write(fd2, file2, it2);
    close(fd);
    close(fd2);
    close(fd3);
}
