#include <fstream>
#include <iostream>

#include "clientsocket.h"

#define BYTES_A_LEER 64
#define GENERIC_ERROR "A weird error just occured in the client..."

// DELETE THIS LATER
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

void read_from_file_to_buf(std::string& buf, const std::string& filename) {
  std::ifstream reader;
  std::string placeholder;
  reader.open(filename, std::ifstream::in);
  while (reader.good()) {
    std::getline(reader, placeholder, '\n');
    if (!placeholder.empty()) buf += placeholder;
  }
  reader.close();
}

static int sendInfo(Socket& self, std::string file) {
  std::string msg;
  read_from_file_to_buf(msg, file);
  if (self.send_(msg) == -1) {
    std::cerr << "Died sending info with errno: " << hstrerror(errno)
              << std::endl;
    return -1;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Error de argumento." << std::endl;
    return -1;
  }

  ClientSocket self;
  char* port = argv[1];
  char* ip = argv[2];
  std::string file(argv[3]);

  try {
    self.connect_(port, ip);
    sendInfo(self, file);
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }
  


  return 0;
}
