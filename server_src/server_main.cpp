#include <fstream>
#include <iostream>

#include "../common_src/infomanager.h"
#include "../common_src/socket.h"
#include "accepter.h"
#include "parser.h"

#define GENERIC_ERROR "A weird error just occured in the server..."

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error de argumento." << std::endl;
    return 1;
  }
  const std::string file = argv[2];
  Accepter worker(argv[1], file);
  try {
    worker.start();
    std::string quit;
    while (true) {
      std::cin >> quit;
      if (quit == "q") {
        break;
      }
    }
  } catch (std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << GENERIC_ERROR << std::endl;
  }
  return 0;
}
