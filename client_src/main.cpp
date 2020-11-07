#include <fstream>
#include <iostream>

#include "../common_src/infomanager.h"
#include "clientsocket.h"

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
    return 1;
  }

  ClientSocket sender;
  //  ClientSocket recver;

  char* port = argv[1];
  char* ip = argv[2];
  Infomanager infomanager;

  try {
    sender.connect_(port, ip);
    //  recver.connect_(port, ip);

    infomanager.sendInfoFromStdin(sender);
    // std::cout << "Client termino de enviar\n";
    std::string msg;
    infomanager.recvInfo(sender, msg);
    std::cout << msg << std::endl;
    // std::cout << "Client termino de recibir\n";

  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }
  return 0;
}
