#include <fstream>
#include <iostream>

#include "../common_src/infomanager.h"
#include "../common_src/parser.h"
#include "../common_src/socket.h"
#include "aceptador.h"

// DELETE THIS LATER
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

#define GENERIC_ERROR "A weird error just occured in the server..."

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error de argumento." << std::endl;
    return 1;
  }
  std::string file = argv[2];
  Aceptador* worker = new Aceptador(argv[1], file);

  try {
    worker->start();
    std::string quit;
    while (true) {
      std::cout << "ENTRO AL CICLO MAIN\n";
      std::cin >> quit;
      if (quit == "q") {
        std::cout << "EXIT CODE\n";
        delete worker;
        break;
      }
    }
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }
  std::cout << "MATANDO AL MAIN\n";

  return 0;
}
