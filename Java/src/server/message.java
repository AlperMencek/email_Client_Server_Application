package ser321.assign3.amencek.server;
import java.util.*;
import ser321.assign2.lindquis.client.*;
import java.io.Serializable;
import org.json.JSONObject;
import java.util.ArrayList;
/**
 * Copyright (c) 2019 Tim Lindquist,
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
 * Purpose: demonstrate using the RMI API
 * a simple serializable employee class including name and id number.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * @see <a href="http://pooh.poly.asu.edu/Ser321">Ser321 Home Page</a>
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic
 * @date    January, 2019
 * @license See above
 */
public class message implements java.io.Serializable {
    private String userId, username, userdate, userto, userfrom, userHeader, usersubj, usermsg;

    public message(String id, String name, String date, String to, String from, String header, String subj, String msg ) {

        userId = id;
//        userPwd = pwd;
        username = name;
        userdate =date;
        userto= to;
        userfrom = from;
        userHeader=header;
        usersubj = subj;
        usermsg = msg;

    }

    public message(JSONObject obj){
        userId = obj.getString("userId");
//        userPwd = obj.getString("userPwd");
        username = obj.getString("username");
        userdate =obj.getString("userdate");
        userto = obj.getString("userto");
        userfrom = obj.getString("userfrom");
        userHeader = obj.getString("userHeader");
        usersubj = obj.getString("usersubj");
        usermsg = obj.getString("usermsg");
    }

    public JSONObject toJSONObject(){
        JSONObject obj = new JSONObject();
        obj.put("userId",userId);
//        obj.put("userPwd",userPwd);
        //System.out.println("User toJSONObject returning: "+obj.toString());
        obj.put("username",username);
        obj.put("userdate",userdate);
        obj.put("userto",userto);
        obj.put("userfrom",userfrom);
        obj.put("userHeader",userHeader);
        obj.put("usersubj",usersubj);
        obj.put("usermsg",usermsg);
        System.out.println(obj.toString());

        return obj;
    }

    protected String getId() {
        return userId;
    }

//    protected boolean check(String id, String pwd) {
//        return (userId.equals(id) && userPwd.equals(pwd));
//    }
    public String tostring(){
        String str = "";
        str+= "userId" + userId+"\n";
        str+= "userdate" + userdate+"\n";
        str+= "userto" + userto+"\n";
        str+= "userfrom" + userfrom+"\n";
        str+="userHeader" + userHeader+"\n";
        str+= "usersubj" + usersubj+"\n";
        str+= "usermsg" + usermsg+"\n";
        return str;
    }

    public String getuserId(){
        return userId;
    }
    public String getusername(){
        return username;
    }
    public String getuserdate(){
        return userdate;
    }
    public String getuserto(){
        return userto;
    }
    public String getuserfrom(){
        return userfrom;
    }
    public String getuserHeader(){
        String userHeader = userfrom+" "+userdate;
        return userHeader;
    }
    public String getsubj(){
        return usersubj;
    }
    public String getmsg(){
        return usermsg;
    }
    
    // Setters
    
        public void setuserId(String uId){
        userId = username;
    }
    public void setusername(String uname){
         username = uname;
    }
    public void setuserdate(String date){
         userdate = date;
    }
    public void setuserto(String uto){
         userto = uto;
    }
    public void setuserfrom(String ufrom){
         userfrom = ufrom;
    }
    public void setuserHeader(String uheader){
       userHeader = uheader;
    }
    public void setsubj(String subj){
         usersubj = subj;
    }
    public void setmsg(String msg){
         usermsg = msg;
    }
}		
