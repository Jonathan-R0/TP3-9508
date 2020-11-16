#include "accepter.h"

#include <fstream>
#include <iostream>

#include "../common_src/socketclosedexception.h"
#include "clienthandler.h"

#define QUEUESIZE 20

Accepter::Accepter(char* port, const std::string& r) : rootfile(r) {
  server.bind(port);
  server.listen(QUEUESIZE);
}

Accepter::~Accepter() {
  for (Clienthandler* hilocliente : clientlist) {
    hilocliente->join();
    delete hilocliente;
  }
  server.stopRecv();
  server.stopSend();
  server.killfd();
  this->join();
}

void Accepter::run() {
  while (true) {
    try {
      Socket newsocket = server.accept();
      Clienthandler* handler =
          new Clienthandler(rootfile, std::move(newsocket), references);
      clientlist.push_back(handler);
      handler->start();
      this->removeDeadClients();
    } catch (SocketClosedException& e) {
      break;
    }
  }
}

void Accepter::removeDeadClients() {
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
