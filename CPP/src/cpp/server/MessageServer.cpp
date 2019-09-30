/**
 * Copyright 2016 Tim Lindquist,
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * <p/>
 * Purpose: C++ class which serves as server for a collection of students. This
 * class is part of a student collection distributed application that uses JsonRPC.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist Tim.Lindquist@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version July 2016
 */

#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
// the include below requires that you've built the jsonrpccpp package manually
// with the switchs as follows:
// cmake ../ -DTCP_SOCKET_SERVER=YES -DTCP_SOCKET_CLIENT=YES
// make
// make doc    // this will build html docs in the build/doc/html directory
// sudo make install
//#include <jsonrpccpp/server/connectors/tcpsocketserver.h>
#include <json/json.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <csignal>


#include "messageserverstub.h"
#include "MessageLibrary.hpp"


using namespace jsonrpc;
using namespace std;

class MessageServer : public messageserverstub {
public:
   MessageServer(AbstractServerConnector &connector, int port);
   virtual Json::Value getMessageFromHeaders(const std::string& username);
   virtual Json::Value getMessage(const std::string& header, const std::string& curuser);
   virtual bool deleteMessage(const std::string& header, const std::string& touser);
   virtual bool initGroupFromJsonFile();
   virtual bool sendClearText(const std::string& id, const std::string& name, const std::string& date, const std::string& to, const std::string& from, const std::string& header, const std::string& subj, const std::string& mesg , const std::string& touser);
   
private:
   MessageLibrary * library;
   int portNum;
};

MessageServer::MessageServer(AbstractServerConnector &connector, int port) :
                             messageserverstub(connector){
   library = new MessageLibrary();
   library->initGroupFromJsonFile();
   portNum = port;
}

// string MessageServer::serviceInfo(){
//    std::string msg =
//                 "Student collection management service.";
//    stringstream ss;
//    ss << portNum;
//    cout << "serviceInfo called. Returning: Student collection management service."
//         << endl;
//    return  msg.append(ss.str());
// }


bool MessageServer::initGroupFromJsonFile(){
   cout << "restoring collection from messages.json" << endl;
   bool ret = library->initGroupFromJsonFile();
   return ret;
}

bool MessageServer::deleteMessage(const std::string& header, const std::string& touser) {
   cout << "Deleting message :" << header << endl;
   bool ret = library->deleteMessage(header,touser);
   return ret;
}


Json::Value MessageServer::getMessageFromHeaders(const string& studentName){
   cout << "Getting " << studentName << endl;
   return library->getMessageFromHeaders(studentName);
}

Json::Value MessageServer::getMessage(const std::string& header, const std::string& curuser){
  
   cout << "Getting message " << endl;
   return library->getMessage(header, curuser);
}

bool MessageServer::sendClearText(const std::string& id, const std::string& name, const std::string& date, const std::string& to, const std::string& from, const std::string& header, const std::string& subj, const std::string& mesg , const std::string& touser){
   cout << "Getting message " << endl;
   return library->sendClearText(id,name,date,to,from,header,subj,mesg,touser);
}

void exiting(){
   std::cout << "Server has been terminated. Exiting normally" << endl;
   //ss.StopListening();
}

int main(int argc, char * argv[]) {
   // invoke with ./bin/studentRPCServer 8080
   int port = 8080;
   if(argc > 1){
      port = atoi(argv[1]);
   }
   HttpServer httpserver(port);
   MessageServer ss(httpserver, port);
   // to use tcp sockets instead of http uncomment below (comment above), and the include
   // for tcpsocketserver.h above. If not running locally, you will need to input ip & port
   // from command line for both server and client programs.
   //TcpSocketServer tcpserver("localhost",port);
   //StudentServer ss(tcpserver, port);
   std::atexit(exiting);
   auto ex = [] (int i) {cout << "server terminating with signal " << i << endl;
                         // ss.StopListening();
                         exit(0);
                         //return 0;
                        };
   // ^C
   std::signal(SIGINT, ex);
   // abort()
   std::signal(SIGABRT, ex);
   // sent by kill command
   std::signal(SIGTERM, ex);
   // ^Z
   std::signal(SIGTSTP, ex);
   cout << "Student collection server listening on port " << port
      //<< " press return/enter to quit." << endl;
        << " use ps to get pid. To quit: kill -9 pid " << endl;
   ss.StartListening();
   while(true){
   }
   //int c = getchar();
   ss.StopListening();
   return 0;
}
