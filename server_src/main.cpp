#include <fstream>
#include <iostream>

#include "../common_src/infomanager.h"
#include "../common_src/parser.h"
#include "serversocket.h"

// DELETE THIS LATER
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#define BYTES_A_LEER 64
#define GENERIC_ERROR "A weird error just occured in the server..."

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error de argumento." << std::endl;
    return 1;
  }

  ServerSocket self;
  char* port = argv[1];
  std::string rootfile(argv[2]);

  try {
    self.bind_(port);
    self.listen_(20);
    Infomanager infomanager;
    self.accept_();

    Parser parse(rootfile);
    std::string msg;
    infomanager.recvInfo(self, msg);
    parse(msg);
    parse.seeStuff();

    // std::cout << "Server termino de recibir\n";
    infomanager.sendInfoFromStdin(self);
    // std::cout << "Server termino de enviar\n";

  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }

  return 0;
}
