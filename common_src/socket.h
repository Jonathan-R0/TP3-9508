#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#include <stddef.h>

#include <string>

class Socket {
 private:
  int fd;
  struct addrinfo* get_addr_info(const char* port, const char* ip);

 public:
  Socket() : fd(-1) {}
  ~Socket();
  int connect_(const char* port, const char* ip);
  int bind_(const char* port);
  int listen_(unsigned int queueSize);
  int accept_();
  int send_(std::string& msg);
  int recv_(unsigned int n, char buf[]);

  // TEST ONLY
};

#endif  // COMMON_SOCKET_H_
