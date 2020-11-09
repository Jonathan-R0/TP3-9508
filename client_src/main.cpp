#include <fstream>
#include <iostream>

#include "../common_src/infomanager.h"
#include "../common_src/socket.h"

#define GENERIC_ERROR "A weird error just occured in the client..."

// DELETE THIS LATER
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error de argumento." << std::endl;
    return 0;
  }

  Socket self;
  //  ClientSocket recver;

  char* port = argv[2];
  char* ip = argv[1];
  Infomanager infomanager;

  try {
    self.connect_(port, ip);
    //  recver.connect_(port, ip);

    infomanager.sendInfoFromStdin(self);
    // std::cout << "Client termino de enviar\n";
    std::string msg;
    infomanager.recvInfo(self, msg);
    std::cout << msg << std::endl;
    // std::cout << "Client termino de recibir\n";

  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }
  return 0;
}