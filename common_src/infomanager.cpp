#include "infomanager.h"

#include <netdb.h>

#include <iostream>
#include <string>

#include "parser.h"
#include "socket.h"

#define BYTES_A_LEER 256

void Infomanager::recvInfo(Socket& self, std::string& msg) {
  char buf[BYTES_A_LEER] = {};
  int read;
  while ((read = self.recv_(sizeof(buf), buf)) != 0) {
    if (read == -1) {
      std::cerr << "Died receiving info with errno: " << hstrerror(errno)
                << std::endl;
    }
  }
  msg += buf;
  self.stopRecv();
}

int Infomanager::sendInfo(Socket& self, std::string& msg) {
  if (self.send_(msg.length(), msg.c_str()) == -1) {
    std::cerr << "Died sending info with errno: " << hstrerror(errno)
              << std::endl;
    return -1;
  }
  self.stopSend();
  return 0;
}

int Infomanager::sendInfoFromStdin(Socket& self) {
  std::string msg;
  std::string placeholder;
  while (std::getline(std::cin, placeholder)) msg += placeholder + "\n";
  return this->sendInfo(self, msg);
}
