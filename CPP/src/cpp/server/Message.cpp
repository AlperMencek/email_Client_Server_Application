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
 * Purpose: C++ class to represent a student. This class is part of a
 * student collection distributed application that uses JsonRPC.
 * Meant to run on OSX, Debian Linux, and Raspberry Pi Debian.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu),ASU-IAFSE,Software Engineering
 * @file    Student.cpp
 * @date    July, 2016
 * @license See above
 **/

#include "Message.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>

Message::Message(){
        userId = "Null";
        username = "Null";
        userdate ="Null";
        userto= "Null";
        userfrom = "Null";
        userHeader="Null";
        usersubj = "Null";
        usermsg = "Null";
}

Message::Message(string id, string name, string date, string to, string from, string header, string subj, string mesg ) {
        userId = id;
        username = name;
        userdate =date;
        userto= to;
        userfrom = from;
        userHeader=header;
        usersubj = subj;
        usermsg = mesg;
}
//json value constructor
Message::Message( Json::Value msg){
        userId = msg.get("userId","").asString();
        username = msg.get("username","").asString();
        userdate =msg.get("userdate","").asString();
        userto= msg.get("userto","").asString();
        userfrom =msg.get("userfrom","").asString();
        userHeader=msg.get("userHeader","").asString();
        usersubj =msg.get("usersubj","").asString();
        usermsg = msg.get("usermsg","").asString();
}

Message::~Message() {
   //cout << "User destructor.\n";
        userId = "";
        username = "";
        userdate ="";
        userto= "";
        userfrom = "";
        userHeader="";
        usersubj = "";
        usermsg = "";
}

void Message::setValues(string id, string name, string date, string to, string from, string header, string subj, string msg ){
        userId = id;
        username = name;
        userdate =date;
        userto= to;
        userfrom = from;
        userHeader=header;
        usersubj = subj;
        usermsg = msg;
}
string Message::getuserId(){
    return userId;
}
string Message::getuserName(){
    return username;
}
string Message::getuserDate(){
    return userdate;
}
string Message::getuserTo(){
    return userto;
}
string Message::getuserFrom(){
    return userfrom;
}
string Message::getuserHeader(){
    return userHeader;
}
string Message::getuserSubj(){
    return usersubj;
}
string Message::getuserMsg(){
    return usermsg;
}
void Message::print(){
  cout << "User " << userId << " " << username << usersubj<< "\n";
}
Json::Value Message::toJson(){
       Json::Value jsonLib;
   jsonLib["userId"] = Json::Value(userId);
   jsonLib["username"] = Json::Value(username);
   jsonLib["userdate"] = Json::Value(userdate);
   jsonLib["userto"] = Json::Value(userto);
   jsonLib["userfrom"] = Json::Value(userfrom);
   jsonLib["userHeader"] = Json::Value(userHeader);
   jsonLib["usersubj"] = Json::Value(usersubj);
   jsonLib["usermsg"] = Json::Value(usermsg);
   
   
   return jsonLib;

}