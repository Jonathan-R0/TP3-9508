#ifndef SOCKET_H_
#define SOCKET_H_

#include <string>

class Socket {
 private:
  int fd;
  struct addrinfo* get_addr_info(const char* port, const char* ip);

 public:
  Socket() : fd(-1) {}
  explicit Socket(int fdGiven) : fd(fdGiven) {}
  ~Socket();
  void stopRecv();
  void stopSend();
  int send(unsigned int len, const char* msg);
  int recv(unsigned int len, char* buf);
  int bind(const char* port);
  int listen(unsigned int queueSize);
  void connect(const char* port, const char* ip);
  int accept();
  Socket(Socket&& other);
  Socket& operator=(Socket&& other);
  void killfd();
};

#endif  // SOCKET_H_
