#ifndef CLIENTSOCKET_H_
#define CLIENTSOCKET_H_

#include <string>

#include "../common_src/socket.h"

class ClientSocket : public Socket {
 public:
  int connect_(const char* port, const char* ip);
};

#endif  // CLIENTSOCKET_H_
