#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

class Socket {
 protected:
  int fd;
  struct addrinfo* get_addr_info(const char* port, const char* ip);

 public:
  Socket() : fd(-1) {}
  ~Socket();
  void stopRecv();
  void stopSend();
  int send_(unsigned int len, const char* msg);
  int recv_(unsigned int len, char* buf);
  void setFd(int newFd);
};

#endif  // SOCKET_H_
