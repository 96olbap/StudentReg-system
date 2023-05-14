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

    // Listen for incoming connections
    listen(listenfd, 5);  //maximum number of connections that can be queued is 5

    // Instantiate the server stub
    StudentRegistrationServer server;

    // Process incoming requests
    while (true) {
    // Accept a new connection
    int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

    // Read the request from the client
    char buffer[1024];
    int n = recv(connfd, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    std::string request(buffer);

    // Parse the request and call the appropriate server method
    if (request.substr(0, 8) == "register") {
      std::string studentDetails = request.substr(9);
      server.registerStudent(studentDetails);

      // Send a reply to the client
      std::string reply = "Registration successful";
      send(connfd, reply.c_str(), reply.length(), 0);
    }

    // Close the connection
    close(connfd);
  }

  // Close the listening socket
  close(listenfd);

  return 0;
}