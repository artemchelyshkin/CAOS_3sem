#define _GNU_SOURCE
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

void write_number(
    size_t position,
    char* place,
    int fd,
    char* buff,
    size_t W,
    size_t N)
{
    size_t j = position;
    for (size_t i = position; i < position + W; ++i) {
        if (position + W - strlen(place) <= i) {
            buff[i] = place[i - j];
        } else {
            buff[i] = ' ';
            j++;
        }
    }
}

void write_number_with_eol(
    size_t position,
    char* place,
    int fd,
    char* buff,
    size_t W,
    size_t N)
{
    size_t j = position;
    size_t i = position;
    for (; i < position + W; ++i) {
        if (position + W - strlen(place) <= i) {
            buff[i] = place[i - j];
        } else {
            buff[i] = ' ';
            j++;
        }
    }
    buff[i] = '\n';
}

void make_circle(
    size_t* start,
    size_t width,
    int fd,
    char* buff,
    size_t W,
    size_t N)
{
    size_t count_offset = 0;
    char* place = malloc(W);
    size_t position = (W * N + 1) * ((N - width) / 2) + ((N - width) / 2 * W);
    snprintf(place, W, "%ld", *start);
    write_number(position, place, fd, buff, W, N);
    position += W;
    (*start)++;
    if (width == 1) {
        return;
    }
    for (size_t j = 0; j < width - 1; ++j) {
        snprintf(place, W, "%ld", *start);
        write_number(position, place, fd, buff, W, N);
        position += W;
        (*start)++;
    }
    position -= W;
    position += N * W + 1;
    for (size_t j = 0; j < width - 1; ++j) {
        snprintf(place, W, "%ld", *start);
        write_number(position, place, fd, buff, W, N);
        position += N * W + 1;
        (*start)++;
    }
    position -= N * W + 1;
    position -= W;
    for (size_t j = 0; j < width - 1; ++j) {
        snprintf(place, W, "%ld", *start);
        write_number(position, place, fd, buff, W, N);
        position -= W;
        (*start)++;
    }
    position += W;
    position -= N * W + 1;
    for (size_t j = 0; j < width - 2; ++j) {
        snprintf(place, W, "%ld", *start);
        write_number(position, place, fd, buff, W, N);
        position -= N * W + 1;
        (*start)++;
    }
    free(place);
}

void make_first_circle(
    size_t* start,
    size_t width,
    int fd,
    char* buff,
    size_t W,
    size_t N)
{
    size_t count_offset = 0;
    char* place = malloc(W);
    int64_t position = (W * N + 1) * ((N - width) / 2) + ((N - width) / 2 * W);
    snprintf(place, W, "%ld", *start);
    write_number(position, place, fd, buff, W, N);
    position += W;
    (*start)++;
    if (width == 1) {
        return;
    }
    for (size_t j = 0; j < width - 1; ++j) {
        snprintf(place, W, "%ld", *start);
        if (j == width - 2) {
            write_number_with_eol(position, place, fd, buff, W, N);
        } else {
            write_number(position, place, fd, buff, W, N);
        }
        position += W;
        (*start)++;
    }
    position -= W;
    position += N * W + 1;
    for (size_t j = 0; j < width - 1; ++j) {
        snprintf(place, W, "%ld", *start);
        write_number_with_eol(position, place, fd, buff, W, N);
        position += N * W + 1;
        (*start)++;
    }
    position -= N * W + 1;
    position -= W;
    for (size_t j = 0; j < width - 1; ++j) {
        snprintf(place, W, "%ld", *start);
        write_number(position, place, fd, buff, W, N);
        position -= W;
        (*start)++;
    }
    position += W;
    position -= N * W + 1;
    for (size_t j = 0; j < width - 2; ++j) {
        snprintf(place, W, "%ld", *start);
        write_number(position, place, fd, buff, W, N);
        position -= N * W + 1;
        (*start)++;
    }
    free(place);
}

int main(int argc, char* argv[])
{
    int exit_code = 0;
    size_t W = atoi(argv[3]);
    size_t N = atoi(argv[2]);
    int fd;
    if (0 > (fd = open(argv[1], O_RDWR | O_CREAT))) {
        exit_code = 4;
        perror("Cannot open file");
        goto ret;
    }
    fallocate(fd, 0, 0, (N * W + 1) * N);
    char* buff =
        mmap(NULL, (N * W + 1) * N, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (buff == MAP_FAILED) {
        exit_code = 6;
        perror("Cannot mmap file");
        goto close;
    }
    int64_t start = 1;
    make_first_circle(&start, N, fd, buff, W, N);
    for (size_t i = 0; i < (N - 1) / 2; ++i) {
        make_circle(&start, N - i * 2 - 2, fd, buff, W, N);
    }
    if (0 != munmap(buff, (N * W + 1) * N)) {
        exit_code = 7;
        perror("Error during memory unmapping");
        goto close;
    }
close:
    close(fd);
ret:
    return exit_code;
}
