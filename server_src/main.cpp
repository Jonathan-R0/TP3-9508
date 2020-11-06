#include <fstream>
#include <iostream>

#include "serversocket.h"

// DELETE THIS LATER
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#define BYTES_A_LEER 64
#define GENERIC_ERROR "A weird error just occured in the server..."

static void recvInfo(Socket& self) {
  char buf[BYTES_A_LEER];
  if ((self.recv_(sizeof(buf), buf)) == -1) {
    std::cerr << "Died sending info with errno: " << hstrerror(errno)
              << std::endl;
  }
  std::cout << buf << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error de argumento." << std::endl;
    return 1;
  }

  ServerSocket self;
  char* port = argv[1];
  char* htmlfile = argv[2];

  htmlfile++; // Unused variable error. 

  try {
    self.bind_(port);
    self.listen_(20);
    self.accept_();
    recvInfo(self);
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }

  return 0;
}
