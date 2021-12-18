#include <stdint.h>
#include <stdio.h>
#include <windef.h>
#include <windows.h>

struct Item {
    int value;
    uint32_t next_pointer;
};

int main(int args, char* argv[])
{
    struct Item it;
    it.next_pointer = 1;
    union _LARGE_INTEGER pointer;
    pointer.LowPart = 0;
    HANDLE file = CreateFileA(
        argv[1],
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (file < 0) {
        CloseHandle(file);
        return 1;
    }
    DWORD bytes_read;
    int bytes = ReadFile(file, &it, sizeof(it), &bytes_read, NULL);
    if (!bytes_read) {
        CloseHandle(file);
        return 0;
    }
    pointer.LowPart = it.next_pointer;
    while (it.next_pointer != 0) {
        printf("%d\n", it.value);
        SetFilePointerEx(file, pointer, NULL, FILE_BEGIN);
        ReadFile(file, &it, sizeof(it), NULL, NULL);
        pointer.LowPart = it.next_pointer;
    }
    printf("%d", it.value);
    CloseHandle(file);
}
