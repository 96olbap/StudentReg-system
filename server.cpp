#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

// RPC interface
class StudentRegistration {
public:
  void registerStudent(const std::string& studentDetails);
};

// Server stub
class StudentRegistrationServer {
public:
  void registerStudent(const std::string& studentDetails) {
    static int serialNumber = 1;
    std::ofstream outFile("registered_students.txt", std::ios_base::app);
    outFile << serialNumber << " " << studentDetails << std::endl;
    ++serialNumber;
  }
};

// Server program
int main() {
    // Create a TCP socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //Bind the socket to the server address
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);
    bind(listenfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
}