#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include <string>

#include "../common_src/socket.h"

class ServerSocket : public Socket {
 public:
  int bind_(const char* port);
  int listen_(unsigned int queueSize);
  int accept_();
};

#endif  // SERVERSOCKET_H_
