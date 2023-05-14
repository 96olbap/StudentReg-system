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

// Client stub
class StudentRegistrationClient {
public:
  void registerStudent(const std::string& studentDetails) {
    // Open a TCP connection to the server
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // assuming server is running on the same machine | if on separate machines change the addr
    servaddr.sin_port = htons(8080);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Send the request to the server
    std::string request = "register " + studentDetails;
    send(sockfd, request.c_str(), request.length(), 0);

    // Receive the reply from the server
    char buffer[1024];
    int n = recv(sockfd, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    std::string reply(buffer);

    // Print the reply
    std::cout << reply << std::endl;

    // Close the connection
    close(sockfd);
  }
};

// Client program
int main() {
  // Instantiate the client stub
  StudentRegistrationClient client;

  // Read student details from the user
  std::cout << "Enter student details: ";
  std::string studentDetails;
  std::getline(std::cin, studentDetails);

  // Register the student through the client stub
  client.registerStudent(studentDetails);

  return 0;
}