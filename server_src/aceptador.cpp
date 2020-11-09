#include "aceptador.h"

#include <fstream>
#include <iostream>

#include "../common_src/infomanager.h"
#include "../common_src/parser.h"
#include "clienthandler.h"
#include "response.h"

// DELETE THIS LATER
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <sys/socket.h>
#include <unistd.h>

Aceptador::Aceptador(char* p, std::string r) : port(p), rootfile(r) {
  server.bind_(port);
  server.listen_(20);
}

Aceptador::~Aceptador() {
  for (Clienthandler* hilocliente : clientlist) {
    hilocliente->join();
    delete hilocliente;
  }
  server.stopRecv();
  server.stopSend();
  server.killfd();
  this->join();
}

void Aceptador::run() {
  while (true) {
    try {
      int newfd = server.accept_();
      Clienthandler* handler = new Clienthandler(rootfile, newfd, references);
      clientlist.push_back(handler);
      handler->start();
      this->removeDeadClients();
    } catch (std::invalid_argument& e) {
      break;
    }
  }
}

void Aceptador::removeDeadClients() {
  for (iterator_t i = clientlist.begin(); i != clientlist.end();) {
    if ((*i)->isDead()) {
      (*i)->join();
      delete (*i);
      i = clientlist.erase(i);
    } else {
      ++i;
    }
  }
}
