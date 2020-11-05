#include "socket.h"

#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

Socket::~Socket() {
  if (fd != -1) {
    shutdown(fd, SHUT_RDWR);
    close(fd);
  }
}

int Socket::accept_() {
  char addressBuf[INET_ADDRSTRLEN];
  struct sockaddr_in address;
  socklen_t addressLength = (socklen_t)sizeof(address);

  int extra_fd = accept(fd, (struct sockaddr*)&address, &addressLength);
  inet_ntop(AF_INET, &(address.sin_addr), addressBuf, INET_ADDRSTRLEN);
  close(fd);
  fd = extra_fd;
  return 0;
}

// CLIENT ONLY
int Socket::connect_(const char* port, const char* ip) {
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

struct addrinfo* Socket::get_addr_info(const char* port, const char* ip) {
  struct addrinfo* address_list;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = (ip == nullptr) ? AI_PASSIVE : 0;

  if (getaddrinfo(ip, port, &hints, &address_list) != 0) return nullptr;
  return address_list;
}

// SERVER ONLY
int Socket::bind_(const char* port) {
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

// SERVER ONLY
int Socket::listen_(unsigned int queueSize) {
  return (listen(fd, queueSize) == -1);
}

int Socket::send_(std::string& msg) {
  if (msg.empty()) return -1;
  unsigned int len = msg.length();
  unsigned int already_sent = 0;
  unsigned int remaining = msg.length();
  while (already_sent < len) {
    int just_sent = 0;
    if ((just_sent = send(fd, &msg[already_sent], remaining, MSG_NOSIGNAL)) ==
        -1) {
      return -1;
    }
    already_sent += just_sent;
    remaining -= just_sent;
  }
  return already_sent;
}

int Socket::recv_(unsigned int len, char buf[]) {
  unsigned int already_read = 0;
  unsigned int remaining = len;
  while (already_read < len) {
    int just_read = 0;
    if ((just_read = recv(fd, &buf[already_read], remaining, 0)) == -1) {
      return -1;
    } else if (just_read == 0) {
      break;
    }
    already_read += just_read;
    remaining -= just_read;
  }
  buf[len] = 0;
  return already_read;
}
