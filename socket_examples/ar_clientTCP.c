#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define CHUNK_SIZE 4096

void error(char *msg) {
    perror(msg);  // Print the provided error message and the corresponding errno description
    exit(1);      // Exit with status 1 to indicate an error condition
}

void send_file_to_socket(int sockfd, char *filename) {
    struct stat st;
    if (stat(filename, &st) < 0) {
        fprintf(stderr, "Could not stat file: %s\n", filename); // Get file metadata for size and existence
        return;
    }

    // Prepare File Header (60 bytes)
    char header[60], name_buf[17], size_buf[11];
    memset(header, ' ', 60);  // Initialize the header buffer with spaces
    snprintf(name_buf, 17, "%.15s/", filename);  // Format the file name into 16 bytes, ending with '/'
    memcpy(header, name_buf, strlen(name_buf));   // Copy filename field into header
    memcpy(header + 16, "0           ", 12);    // Timestamp field placeholder
    memcpy(header + 28, "0     ", 6);           // UID field placeholder
    memcpy(header + 34, "0     ", 6);           // GID field placeholder
    memcpy(header + 40, "644     ", 8);         // Mode field: file permissions
    snprintf(size_buf, 11, "%-10ld", (long)st.st_size); // File size as a left-justified 10-byte string
    memcpy(header + 48, size_buf, 10);          // Copy size field into header
    header[58] = '`'; header[59] = '\n';        // Header terminator for ar archive format
    // Send Header
    write(sockfd, header, 60);
    // Send File Contents
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return;
    }

    char buffer[CHUNK_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, fp)) > 0) {
        write(sockfd, buffer, bytes_read);  // Write file chunks to the TCP socket
    }
    fclose(fp);

    // Padding (if size is odd)
    if (st.st_size % 2 != 0) {
        char pad = '\n';
        write(sockfd, &pad, 1);  // Add newline padding for odd-sized file alignment
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <server_ip> <port> <file1> [<file2> ...]\n", argv[0]);
        exit(1);
    }

    int sockfd, portno;
    struct sockaddr_in serv_addr;

    portno = atoi(argv[2]);  // Convert port argument from string to integer
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    if (sockfd < 0) error("ERROR opening socket");

    memset(&serv_addr, 0, sizeof(serv_addr)); // Zero out the address structure
    serv_addr.sin_family = AF_INET;           // Use IPv4
    serv_addr.sin_port = htons(portno);       // Convert port number to network byte order
    inet_aton(argv[1], &serv_addr.sin_addr);  // Convert IP string to binary form

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting"); // Establish a TCP connection to the server
    }

    // Send Archive Global Header (8 bytes)
    write(sockfd, "!<arch>\n", 8);
    // Loop through provided files and send each one
    for (int i = 3; i < argc; i++) {
        send_file_to_socket(sockfd, argv[i]);
    }
    close(sockfd); // Close the socket after sending all files
    return 0;
}
