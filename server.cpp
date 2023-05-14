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