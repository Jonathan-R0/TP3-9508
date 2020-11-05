#include "clientsocket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#include "../common_src/socket.h"

int ClientSocket::connect_(const char* port, const char* ip) {
  struct addrinfo* address_list = nullptr;
  if ((address_list = this->get_addr_info(port, ip)) == nullptr) return -1;

  for (struct addrinfo* conex = address_list; conex != nullptr;
       conex = conex->ai_next) {
    int extra_fd =
        socket(conex->ai_family, conex->ai_socktype, conex->ai_protocol);
    if (extra_fd == -1) {
      continue;
    } else if (connect(extra_fd, conex->ai_addr, conex->ai_addrlen) == -1) {
      close(extra_fd);
      continue;
    } else {
      fd = extra_fd;
      break;  // I'm in...
    }
  }
  freeaddrinfo(address_list);

  return (fd == -1);
}