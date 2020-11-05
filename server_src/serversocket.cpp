#include "serversocket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#include "../common_src/socket.h"

int ServerSocket::accept_() {
  char addressBuf[INET_ADDRSTRLEN];
  struct sockaddr_in address;
  socklen_t addressLength = (socklen_t)sizeof(address);

  int extra_fd = accept(fd, (struct sockaddr*)&address, &addressLength);
  inet_ntop(AF_INET, &(address.sin_addr), addressBuf, INET_ADDRSTRLEN);
  close(fd);
  fd = extra_fd;
  return 0;
}

int ServerSocket::bind_(const char* port) {
  struct addrinfo* address_list;

  if ((address_list = this->get_addr_info(port, nullptr)) == nullptr) return -1;

  int val = 1;
  for (struct addrinfo* conex = address_list;
       conex != nullptr;  // ESTO PUEDE HACER COPIAS PELIGROSAS
       conex = conex->ai_next) {
    int extra_fd =
        socket(conex->ai_family, conex->ai_socktype, conex->ai_protocol);
    setsockopt(extra_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (extra_fd == -1) {
      continue;
    } else if (bind(extra_fd, conex->ai_addr, conex->ai_addrlen) == -1) {
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

int ServerSocket::listen_(unsigned int queueSize) {
  return (listen(fd, queueSize) == -1);
}
