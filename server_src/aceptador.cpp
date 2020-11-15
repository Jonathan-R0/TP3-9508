#include "aceptador.h"

#include <fstream>
#include <iostream>

#include "../common_src/socketclosedexception.h"
#include "clienthandler.h"

#define QUEUESIZE 20

Aceptador::Aceptador(char* port, const std::string& r) : rootfile(r) {
  server.bind(port);
  server.listen(QUEUESIZE);
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
      int newfd = server.accept();
      Clienthandler* handler = new Clienthandler(rootfile, newfd, references);
      clientlist.push_back(handler);
      handler->start();
      this->removeDeadClients();
    } catch (SocketClosedException& e) {
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
