#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

class Socket {
 private:
  int fd;
  struct addrinfo* get_addr_info(const char* port, const char* ip);

 public:
  Socket() : fd(-1) {}
  Socket(int fdGiven) : fd(fdGiven) {}
  ~Socket();
  void stopRecv();
  void stopSend();
  int send_(unsigned int len, const char* msg);
  int recv_(unsigned int len, char* buf);
  void setFd(int newFd);
  int bind_(const char* port);
  int listen_(unsigned int queueSize);
  void connect_(const char* port, const char* ip);
  int accept_();
  Socket(Socket&& other);
  Socket& operator=(Socket&& other);
  void killfd();
};

#endif  // SOCKET_H_
