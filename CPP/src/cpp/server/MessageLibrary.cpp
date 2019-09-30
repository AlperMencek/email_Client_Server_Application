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
 * 
 * Purpose: StudentCollection is a class defining the interface between clients
 * and the server. The server implementation of StudentCollection
 * provides storage for description of multiple students
 *
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist, Alper Mencek Tim.Lindquist@asu.edu, amencek@asu.edu
 *         Software Engineering, CIDSE, IAFSE, ASU Poly
 * @version July 2016
 */

#include "MessageLibrary.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <jsoncpp/json/json.h>
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <json/writer.h>



MessageLibrary::MessageLibrary(){
}

//bool MessageLibrary::initGroupFromJsonFile(string jsonFileName){
bool MessageLibrary::initGroupFromJsonFile(){
    cout<<"In IGFJ"<<endl;
    ifstream jsonFile("messages.json");
    string line;
    cout << "The content of the Json file as a string: " << endl;
    if(jsonFile.is_open()){
        while(getline(jsonFile,line)){
            cout << line << endl;
        }
    }else{
        cout << "Json file not opened properly" << endl;
    }
    jsonFile.close();
    Json::Reader reader;
    Json::Value root;
    std::ifstream json("messages.json", std::ifstream::binary);
    bool parseSuccess = reader.parse(json,root,false);
    if(parseSuccess){

        for(Json::Value::ArrayIndex i = 0; i != root.size(); i++){

            Json::Value jsonUser = root[i];

                string id = jsonUser["userId"].asString();
                string name = jsonUser["username"].asString();
                string date = jsonUser["userdate"].asString();
                string to = jsonUser["userto"].asString();
                string from = jsonUser["userfrom"].asString();
                string header = jsonUser["userHeader"].asString();
                string subj = jsonUser["usersubj"].asString();
                string mesg = jsonUser["usermsg"].asString();
                //cout << "pwd: " << userPwd << " user: " << userId << endl;
                Message * msg = new Message(id, name, date, to,from, header, subj,mesg) ;
              
                msgs[id].push_back(*msg);
 
        }
    }
return true;
}

MessageLibrary::~MessageLibrary() {
    //cout << "Group destructor.\n";
    msgs.clear();
}


Json::Value MessageLibrary::getMessageFromHeaders(string toUserName){
    //cout<<"ind GMFH ************"<<endl;
    vector<string> headers;
    //cout<<"ind GMFH before ************"<<endl;
    vector <Message> nlist = msgs.at(toUserName);
    string tmp = "";
    Json::Value ret(Json::arrayValue);
    cout<<"ind GMFH ************"<<endl;
    for ( int i = 0 ; i < nlist.size(); i++){
       
        tmp = nlist.at(i).getuserFrom()+" "+ nlist.at(i).getuserDate();
        headers.push_back(tmp);
        
        }
    for (int i = 0; i < headers.size(); i++) {
        cout << "headers: " << headers.at(i) << endl;
    }
cout<<"after 1forloop ************"<<endl;
    for(std::vector<string>::iterator it = headers.begin(); it!=headers.end();it++) {
      ret.append(Json::Value(*it));
   }
   return ret;
  
}

Json::Value MessageLibrary::getMessage(string header, string curUser){
    string first = header;
    string second = "";
    string::size_type pos = first.find(' ');
    vector <Message> nlist = msgs.at(curUser);

    if(first.npos != pos) {
        second = first.substr(pos + 1);
        first = first.substr(0, pos);
    }


    for( int i = 0 ; i < nlist.size(); i++){

        if ( second.compare(nlist.at(i).getuserDate()) == 0 ){
            return nlist.at(i).toJson();
        }
    }
    // return "nullptr";

}



bool MessageLibrary::deleteMessage(string header, string toUser){
    string first = header;
    string second = "";
    string::size_type pos = first.find(' ');
    vector <Message> nlist = msgs.at(toUser);
//cout<<"IN DELETE!!!!!!"<<endl;
    if(first.npos != pos) {
        second = first.substr(pos + 1);
        first = first.substr(0, pos);
    }

    for( int i = 0 ; i< msgs.at(toUser).size(); i++){
        if(second.compare(msgs.at(toUser).at(i).getuserDate()) == 0){
            msgs.at(toUser).erase(nlist.begin()+i);
            return 1;

        }

    }
    return 0;


}

bool MessageLibrary::sendClearText(string id, string name, string date, string to, string from, string header, string subj, string mesg , string touser){
      //  Message * newmsg = new Message(msg);
    Message * msg = new Message(id, name, date, to,from, header, subj,mesg) ;
        if(msgs.find(touser)==msgs.end()){
            msgs[touser].push_back(*msg);
                    
        }else{
            // vector<Message> nlist; 
            // nlist.push_back(*msg);
            // msgs[touser].push_back(nlist);
            msgs[touser].push_back(*msg);
        }
        return 0;
}
