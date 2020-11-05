#include <fstream>
#include <iostream>

#include "../common_src/socket.h"

// DELETE THIS LATER
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#define BYTES_A_LEER 64

static int recvInfo(Socket& self) {
  char buf[BYTES_A_LEER];
  if ((self.recv_(sizeof(buf), buf)) == -1) {
    std::cerr << "Died sending info with errno: " << hstrerror(errno)
              << std::endl;
    return -1;
  }
  std::cout << buf << std::endl;
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Error de argumento." << std::endl;
    return -1;
  }

  Socket self;
  char* port = argv[1];

  if (self.bind_(port) == -1 || self.listen_(20) == -1 ||
      self.accept_() == -1 || recvInfo(self) == -1)
    return -1;

  return 0;
}
