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

void Socket::setFd(int newFd) {
  if (fd != -1) fd = newFd;
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
