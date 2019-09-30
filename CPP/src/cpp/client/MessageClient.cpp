/**
 * Copyright (c) 2016 Tim Lindquist,
 * Software Engineering,
 * Arizona State University at the Polytechnic campus
 * <p/>
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation version 2
 * of the License.
 * <p/>
 * This program is distributed in the hope that it will be useful,
 * but without any warranty or fitness for a particular purpose.
 * <p/>
 * Please review the GNU General Public License at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 * see also: https://www.gnu.org/licenses/gpl-faq.html
 * so you are aware of the terms and your rights with regard to this software.
 * Or, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,USA
 * <p/>
 * Purpose: C++ command line student collection client using json-rpc-cpp.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu),ASU-IAFSE,Software Engineering
            Alper Mencek amencek@asu.edu 
 * @file    MessageClient.cpp
 * @date    July, 2015
 * @license See above
 **/
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Check_Browser.H>
#include <stdio.h>

#include <chrono>
#include <ctime>

#include <cstring>
#include <string>


#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <jsonrpccpp/client/connectors/httpclient.h>
// the include below requires that you've built the jsonrpccpp package manually
// with the switchs as follows:
// cmake ../ -DTCP_SOCKET_SERVER=YES -DTCP_SOCKET_CLIENT=YES
// make
// make doc    // this will build html docs in the build/doc/html directory
// sudo make install
//#include <jsonrpccpp/client/connectors/tcpsocketclient.h>
#include <json/json.h>
#include "MessageGui.cpp"
#include "messagelibrarystub.h"
#include "../server/Message.hpp"


using namespace jsonrpc;
using namespace std;

class MessageClient : public MessageGui {
    messagelibrarystub * newLibrary;
    HttpClient * httpclient;




    static void ClickedX(Fl_Widget * w, void * userdata) {
        std::cout << "You clicked Exit" << std::endl;
        exit(1);
    }

    static void ClickedGet(Fl_Widget * w, void * userdata) {
        // since this is a static method, it does not have access to any instance variables.
        // get access through the userdata argument which is the instance.
        MessageClient* anInstance = (MessageClient*)userdata;

        jsonrpc::HttpClient httpclient(anInstance->host);
        messagelibrarystub * newLibrary = new messagelibrarystub(httpclient);
       
        std::cout << "You clicked Get" << std::endl;
        //instance declaration
        Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
        Fl_Input * dateFI = anInstance->dateFI;
        Fl_Input * subjectFI = anInstance->subjectFI;
        Fl_Input * toFI = anInstance->toFI;
        Fl_Input * fromFI = anInstance->fromFI;
        Fl_Check_Browser * headers = anInstance->headerFCB;
        std::string userId = anInstance->userId;
        //MessageLibrary newLibrary = anInstance->newLibrary;
        //Message * msg = anInstance->Message;
        
        // clear all existing entries from the list of Message headers
        headers->clear();
        //newLibrary->initGroupFromJsonFile();

        // lets setup some sample entries in the FCB
        // first get the date and place its string form into dateFI
        // get the time in a string
        //       auto aClk = std::chrono::system_clock::now();
        //       auto aTime = std::chrono::system_clock::to_time_t(aClk);
        //       std::string aDateStr(ctime(&aTime));
        // //      // the conversion to string adds a new line at the end of the string. Trim it.
        //      std::string trimmed(trimMe(aDateStr));
  
        
        
       //std::vector<std::string> userHeaders = newLibrary->getMessageFromHeaders(userId);
             cout<<userId<<endl;
             cout<<"right before getting messagefrom headers"<<endl;
      Json::Value jHeaders = newLibrary->getMessageFromHeaders(userId);

      std::vector<std::string> userHeaders;
      for( int x = 0 ;  x < jHeaders.size(); x++){
         userHeaders.push_back(jHeaders[x].asString());
      }

      cout << "STC::getMail 11111" << endl;
        for( int i = 0 ;  i < userHeaders.size(); i++){
             headers->add(trimMe(userHeaders.at(i)).c_str());
        }
        headers->checked(1,1);
        
        
        cout << "STC::getMail 22222" << endl;

        toFI->value("");
        fromFI->value("");
        dateFI->value("");
        subjectFI->value("");
        messageFMI->value("");
       

    }

    static void ClickedDelete(Fl_Widget * w, void * userdata) {
        MessageClient* anInstance = (MessageClient*)userdata;
        Fl_Check_Browser * headers = anInstance->headerFCB;
        Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
        Fl_Input * dateFI = anInstance->dateFI;
        Fl_Input * subjectFI = anInstance->subjectFI;
        Fl_Input * toFI = anInstance->toFI;
        Fl_Input * fromFI = anInstance->fromFI;
        int howMany = headers->nitems();
        int which = headers->value();
        std::string userId = anInstance->userId;
       jsonrpc::HttpClient httpclient(anInstance->host);
        messagelibrarystub * newLibrary = new messagelibrarystub(httpclient);
        
        // which=1;
        std::cout << "You clicked Delete" << std::endl;
        try{
        if(headers->value()>0 && which > 0){
         
            
        newLibrary->deleteMessage(headers->text(which),userId);
            
         
        }
          headers->remove(which);  
        headers->remove(headers->value());
        //headers->checked(1,1);
    
         }catch (...) {  }
        toFI->value("");
        fromFI->value("");
        dateFI->value("");
        subjectFI->value("");
        messageFMI->value("");
    }
    
    static void ClickedReply(Fl_Widget * w, void * userdata) {
        MessageClient* anInstance = (MessageClient*)userdata;
        auto aClk = std::chrono::system_clock::now();
        auto aTime = std::chrono::system_clock::to_time_t(aClk);
        std::string aDateStr(ctime(&aTime));
        std::string trimmed(trimMe(aDateStr));
        Fl_Check_Browser * headers = anInstance->headerFCB;
        Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
        Fl_Input * dateFI = anInstance->dateFI;
        Fl_Input * subjectFI = anInstance->subjectFI;
        Fl_Input * toFI = anInstance->toFI;
        Fl_Input * fromFI = anInstance->fromFI;
        int howMany = headers->nitems();
        int which = headers->value();
        std::string userId = anInstance->userId;
       
          try{
        if(headers->value()>0){
         jsonrpc::HttpClient httpclient(anInstance->host);
        messagelibrarystub * newLibrary = new messagelibrarystub(httpclient);
        Json::Value msg = newLibrary->getMessage(headers->text(which),userId);
        std::string subj =msg["usersubj"].asString().c_str();
        std::string replysubj = "re: "+subj;
        std::string rMessage =msg["usermsg"].asString().c_str();
        std::string replyMessage ="\n------------------------------------------------------------------------------------------------\n"+rMessage;
        toFI->value(msg["userfrom"].asString().c_str());
        fromFI->value(msg["userto"].asString().c_str());
        dateFI->value(aDateStr.c_str());
        subjectFI->value(replysubj.c_str());
        messageFMI->value(replyMessage.c_str());


        // toFI->value(msg.getuserFrom().c_str());
        // fromFI->value(msg.getuserTo().c_str());
        // dateFI->value(aDateStr.c_str());
        // subjectFI->value(replysubj.c_str());
        // messageFMI->value(replyMessage.c_str());
        }
         }catch (const std::exception& e) {  std::cout << e.what();}
    
    }
    
  
    static std::string& trimMe (std::string& str) {
        // right trim
        while (str.length() > 0 && (str[str.length()-1] == ' ' || str[str.length()-1] == '\t'
                                    || str[str.length()-1] == '\n' ||  str[str.length()-1] == '\r')){
            str.erase(str.length ()-1, 1);
        }
        // left trim
        while (str.length () > 0 && (str[0] == ' ' || str[0] == '\t')){
            str.erase(0, 1);
        }
        return str;
    }

    static void SelectedHeader(Fl_Widget * w, void * userdata) {

        MessageClient* anInstance = (MessageClient*)userdata;
        jsonrpc::HttpClient httpclient(anInstance->host);
        messagelibrarystub * newLibrary = new messagelibrarystub(httpclient);
        Fl_Check_Browser * headers = anInstance->headerFCB;
        int howMany = headers->nitems();
        int which = headers->value();
        Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
        Fl_Input * dateFI = anInstance->dateFI;
        Fl_Input * subjectFI = anInstance->subjectFI;
        Fl_Input * toFI = anInstance->toFI;
        Fl_Input * fromFI = anInstance->fromFI;
        
        
        std::cout << "You selected a new Message header. Index: " << which << std::endl;
        std::string userId = anInstance->userId;
        
        // MessageLibrary newLibrary = anInstance->newLibrary;
        
        Message msg = newLibrary->getMessage(headers->text(which),userId);
        // unselect all but the item just selected. Note, first item is item 1 not 0
        std::string msgto = msg.getuserTo();
        cout<<msgto<<endl;
        toFI->value(msg.getuserTo().c_str());
        fromFI->value(msg.getuserFrom().c_str());
        dateFI->value(msg.getuserDate().c_str());
        subjectFI->value(msg.getuserSubj().c_str());
        messageFMI->value(msg.getuserMsg().c_str());
        
        for(int i=1; i<howMany+1; i++){
            if(i != which ){
                headers->checked(i,0);
                std::cout << "calling checked("<< i << ")" << std::endl;
            }
        }
        std::cout << "You selected item " << which << " text " << headers->text(which)
            << "\nbrowser size is " << howMany
            << std::endl;
    }

    static void ClickedSend(Fl_Widget * w, void * userdata){
        MessageClient* anInstance = (MessageClient*)userdata;
        Fl_Check_Browser * headers = anInstance->headerFCB;
        Fl_Multiline_Input * messageFMI = anInstance->messageFMI;
        Fl_Input * dateFI = anInstance->dateFI;
        Fl_Input * subjectFI = anInstance->subjectFI;
        Fl_Input * toFI = anInstance->toFI;
        Fl_Input * fromFI = anInstance->fromFI;
        int howMany = headers->nitems();
        int which = headers->value();
        std::string userId = anInstance->userId;
       jsonrpc::HttpClient httpclient(anInstance->host);
        messagelibrarystub * newLibrary = new messagelibrarystub(httpclient);
        
        // which=1;
        std::cout << "You clicked Send" << std::endl;
        // std::string userId = anInstance->userId;
        std::string username = fromFI->value();
        std::string date = dateFI->value();
        std::string to = toFI->value();
        std::string from = fromFI->value();
        
        std::string subj = subjectFI->value();
        std::string msg = messageFMI->value();
        std::string header = subj+" "+date;

        newLibrary->sendClearText(userId,username,date,to,from,header,subj,msg,to);
   
        toFI->value("");
        fromFI->value("");
        dateFI->value("");
        subjectFI->value("");
        messageFMI->value(to.c_str());
    }

    public:
    string host = "http://localhost:8080";

    std::string userId;
    MessageClient(const char * name = 0,string h ="http://localhost:8080",string user="AlperMencek" ) : MessageGui(name) {
      // host = "http://localhost:8080";
      userId = user;
      host = h;
        std::string filen("messages.json");
 cout<<"Error 4"<<endl;
   //       HttpClient httpclient(host);
   // messagelibrarystub sc(httpclient);
 cout<<"Error 5"<<endl;
        
        cout<<"Error 4"<<endl;
       cout<<"readin file **************"<<endl;

        getButt->callback(ClickedGet, (void*)this);
        deleteButt->callback(ClickedDelete, (void*)this);
        replyButt->callback(ClickedReply,(void*)this);
        sendButt->callback(ClickedSend,(void*)this);

        headerFCB->callback(SelectedHeader, (void*)this);
         
        headerFCB->when(FL_WHEN_CHANGED);

        callback(ClickedX);

        
        //cout<< userHeaders.at(1).getuserMsg()<<endl;
        //userId = "AlperMencek";
        
        
    }
};

int main(int argc, char*argv[]) {
   string host = "http://localhost:8080";
   string port = "";
   string userId ="AlperMencek";

   if(argc>1){
      host = string(argv[1]);
      port = string(argv[2]);
      userId = string(argv[3]);
   }
   string inhost ="http://"+host+":"+port;
   // the server is communicating via http requests, so create a stub object.
  
   // to use tcp sockets instead of http uncomment below (comment above), and the include
   // for tcpsocketclient.h above. If not running locally, you will need to input ip & port
   // from command line for both server and client programs.
   //TcpSocketClient tcpclient("localhost",8080);
   //messageserverstub sc(tcpclient);
 
   MessageClient cm(userId.c_str(),inhost,userId);
   return (Fl::run());
   // try {
   //    string inLine;
   //    while(true){
   //       MessageClient cm("Alper Mencek's Message Browser");
   //  return (Fl::run());

   //    }
   // } catch (JsonRpcException e) {
   //    cerr << e.what() << endl;
   // }
}


