#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

uint32_t readFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return (uint32_t)-1;
    }

    uint32_t buffer; // 4 bytes
    size_t n = fread(&buffer, 1, sizeof(buffer), file);
    if (n != 4) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        fclose(file);
        return (uint32_t)-1;
    }
    fclose(file);
    return ntohl(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return -1;
    }

    uint32_t r1 = readFile(argv[1]);
    if (r1 == (uint32_t)-1) {
        return -1;
    }

    uint32_t r2 = readFile(argv[2]);
    if (r2 == (uint32_t)-1) {
        return -1;
    }

    uint32_t result = r1 + r2;
    // 1000(0x3e8) + 500(0x1f4) = 1500(0x5dc)
    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", r1, r1, r2, r2, result, result);

    return 0;
}