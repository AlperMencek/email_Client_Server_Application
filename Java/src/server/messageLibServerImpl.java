
package ser321.assign3.amencek.server;

import java.rmi.server.*;
import java.rmi.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Set;
import org.json.*;


import java.util.Vector;
import java.util.Enumeration;
import java.io.Serializable;

import java.util.ArrayList;
//port personnel.messageLibServer;

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
 * Implementation of employee server - create a remote server object 
 * (with a couple of employees). Register the remote server object with the
 * rmi registry.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * @see <a href="http://pooh.poly.asu.edu/Ser321">Ser321 Home Page</a>
 * @author Alper Mencek (amencek@asu.edu) CIDSE - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic

 * @date    February 19,2019
 * @license See above
 */
public class messageLibServerImpl extends UnicastRemoteObject implements JSONString, Serializable,messageLibServer 
{
private String name; 
       private static final long serialVersionUID = 6982142948226029575L;

/*
   protected Emp empList[] = {new Emp("Bob", 100), new Emp("Sue"
   , 200),
                              new Emp("Jen", 300), new Emp("Tom", 400)};
*/
//   protected Hashtable<String,Emp> empList;
//   protected static int empNo;
    private Hashtable<String, ArrayList<message>> users =  new Hashtable<String, ArrayList<message>>();
    public messageLibServerImpl() throws RemoteException{
      this.name = "unknown";
   }

  public messageLibServerImpl(String fileName) throws RemoteException{
      try{ //take in from json file into a hash table  perferablly 
         FileInputStream in = new FileInputStream(fileName);
         JSONArray obj = new JSONArray(new JSONTokener(in));
          users = new Hashtable<String,ArrayList<message>>();
          for( int i = 0 ; i < obj.length(); i++){

                message aUser = new message((JSONObject)obj.get(i));

                if(users.containsKey(aUser.getuserId())){
                    users.get(aUser.getuserId()).add(aUser);
                    continue;
                }



                ArrayList<message> nlist = new ArrayList<message>();
                nlist.add(aUser);
                users.put(aUser.getuserId(),nlist);
          } 
          in.close();
      }catch (Exception ex) {
         System.out.println("Exception importing from json: "+ex.getMessage());
      }

   }




 public String getName()throws RemoteException{
      return name;
   }

 public void setName(String aName)throws RemoteException{
      name = aName;
   }

 public Vector<String> getUserNames()throws RemoteException {
          return new Vector <String>(users.keySet());  
   }

 public boolean isMember(String id, String pwd)throws RemoteException {
//      boolean match = false;
//      for (Enumeration e = users.elements() ; e.hasMoreElements() ;) {
//         if(((message)e.nextElement()).check(id,pwd)){
//            match = true;
//            break;
//         }
//      }
      return true;
  }

 public void printGroup()throws RemoteException{
      System.out.print("Group: "+name+" has users: ");
      for (Enumeration e = users.elements() ; e.hasMoreElements() ;) {
         System.out.print(((message)e.nextElement()).getId()+", ");
      }
      System.out.println();
   }

  public String[] getMessageFromHeaders(String toAUserName){
       String [] headers;
       ArrayList<message> nlist = users.get(toAUserName);
       String tmp = "";
       headers = new String [nlist.size()];
   
       for ( int i =0 ; i < headers.length; i++ ){
           tmp = nlist.get(i).getuserfrom()+" "+ nlist.get(i).getuserdate();
           headers[i] = tmp;

       }
       
   return headers;
   }



   public message getMessage(String header, String curUser)throws RemoteException{
       String [] name = header.split(" ", 2) ;
       String hname = name[0];
       String hdate = name[1];


       ArrayList<message> nlist = users.get(curUser);
        for( int i = 0 ; i< nlist.size(); i++){
            //System.out.println("--------------------mlsimpl 3.5");

            if ( hdate.equals(nlist.get(i).getuserdate())){
                
                return nlist.get(i);
            }
        }
        return null;
   }



       public boolean deleteMessage(String header, String toAUserName)throws RemoteException{
          String [] name = header.split(" ", 2) ;
       String hname = name[0];
       String hdate = name[1];

        for( int i = 0 ; i< users.get(toAUserName).size(); i++){
            if (hdate.equals(users.get(toAUserName).get(i).getuserdate())){
              users.get(toAUserName).remove(i);
              System.out.println("------------------mlsImpl" + header + toAUserName);
                return true;
            }

   }
        return false;
   }
   public String toJSONString(){
      /*String ret;
      JSONObject obj = new JSONObject();
      obj.put("name",name);
      for (Enumeration<message> e = users.elements(); e.hasMoreElements();){
         message usr = (message)e.nextElement();
         obj.put(usr.getId(),usr.toJSONObject());
      }
      ret = obj.toString();
      //System.out.println("group tojsonstring returning string: "+ret);
      */
      return null;
   }

 public void sendClearText(message msg, String touser) throws RemoteException{
        if(users.containsKey(touser)){
            users.get(touser).add(msg);
                    
        }else{
            ArrayList<message> nlist = new ArrayList<message>();
            nlist.add(msg);
            users.put(touser,nlist);
        }
           
 
 }


   public static void main(String args[]) {
      try {
         String hostId="localhost";
         String regPort="1099";

         //String username ="test";
         if (args.length >= 2){
	    hostId=args[0];
            regPort=args[1];
         }
         

         messageLibServer obj = new messageLibServerImpl("messages.json");

         Naming.rebind( "rmi://"+hostId+":"+regPort+"/messageLibServer", obj);
         System.out.println("Server bound in registry as: "+
                            "rmi://"+hostId+":"+regPort+"/EmployeeServer");
      }catch (Exception e) {
         e.printStackTrace();
      }
   }
}

