package ser321.assign3.amencek.client;

import java.rmi.*;
import java.io.*;
import javax.swing.*;
import ser321.assign3.amencek.server.*;
import ser321.assign2.lindquis.client.*;
import javax.swing.DefaultListModel;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;

import java.awt.Cursor;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.util.Date;
import java.text.SimpleDateFormat;
import ser321.assign3.amencek.server.messageLibServer;
/**
 * Copyright (c) 2019 Alper Mencek,
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
 * Purpose: demonstrate using the RMI API with gui client
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * @see <a href="http://pooh.poly.asu.edu/Ser321">Ser321 Home Page</a>
 * @author Alper Mencek (amencek@asu.edu) CIDSE - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic
 * @date    January, 2019
 * @license See above
 */

public class RMIClientGui extends MessageGui
                           implements ActionListener, ListSelectionListener {

   private String user;   // originator of all message sent by this client.
   private String serverHostPort; // such as lindquisrpi.local:8080
   private static final String patt = "EEE MMM d K:mm:ss yyyy";
   //
   private String username;
    String to ="";
    String from="";
    String Msg="";
    String MesSubj ="";
    String Date="";
    int selected = 0;
    private messageLibServer newlibrary;

  

   public RMIClientGui(String host, String port, String username) {
 super("localhost", username);
 try{

      this.user = host;
      this.serverHostPort = port;
      this.username = username;
  

    //messageLibServer newlibrary;
         newlibrary = (messageLibServer) Naming.lookup( "rmi://"+host+":"+port+"/messageLibServer");
                             //System.out.println((newlibrary==null) + user);
                             System.out.println(" Connect to Server , rmi://"+host+":"+port+"/"+username);


      // add this object as an action listener for all menu items.
      for(int j=0; j<userMenuItems.length; j++){
         for(int i=0; i<userMenuItems[j].length; i++){
            userMenuItems[j][i].addActionListener(this);
         }

      }

      }catch (Exception e) {
         e.printStackTrace();}

     // newlibrary = new messageLibrary("messages.json");

      // add this object as an action listener for the view buttons
      deleteJB.addActionListener(this);
      replyJB.addActionListener(this);
      sendTextJB.addActionListener(this);
      sendCipherJB.addActionListener(this);

      // listen for the user to select a row in the list of messages.
      // When a selection is made, the method valueChanged will be called.
     // DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();

        String [] headers = null;
        //test try


      try{
      DefaultListModel dlm = (DefaultListModel)messageListJL.getModel();
      messageListJL.addListSelectionListener(this);

       headers = newlibrary.getMessageFromHeaders(username); // user

       for ( int i = 0; i < headers.length ; i++){
        dlm.addElement(headers[i]);
            }
      }catch(Exception e){
      e.printStackTrace();
      }

      setVisible(true);
   }

   public void valueChanged(ListSelectionEvent e) {

      if (!e.getValueIsAdjusting()){
      //test try 2
      try{
         messageContentJTA.setText(" You selected messageList item: "
                                   + messageListJL.getSelectedIndex());
         System.out.println("You selected messageList item: "
                            + messageListJL.getSelectedIndex());

         if(messageListJL.getSelectedIndex()>-1){    
            //System.out.println("--------------------client 1.7");
            DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();
             selected = messageListJL.getSelectedIndex();
           // System.out.println("--------------------client 1.9");

            message msgObj = newlibrary.getMessage((String)dlm.getElementAt(messageListJL.getSelectedIndex()), username);
            
           // System.out.println("------------------client 2.4 " + msgObj.toString());

             fromJTF.setText(msgObj.getuserfrom());
             toJTF.setText(msgObj.getuserto());
             subjectJTF.setText(msgObj.getsubj());
             dateJTF.setText(msgObj.getuserdate());
             messageContentJTA.setText(msgObj.getmsg());
         }else{
             fromJTF.setText("");
             toJTF.setText("");
             subjectJTF.setText("");
             dateJTF.setText("");
             messageContentJTA.setText("");

         }

    } catch(Exception x){
        x.printStackTrace();
      }
    }
   }

   public void actionPerformed(ActionEvent e) {

      setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
      //test try 3 
      try{
      if(e.getActionCommand().equals("Exit")) {
         System.exit(0); //close window w no errors
      }else if(e.getActionCommand().equals("Reply")) { // if reply is selected, jimmy buffet mail gets generated.
      // selected = messageListJL.getSelectedIndex();
         DefaultListModel<String> dlm = (DefaultListModel<String>)messageListJL.getModel();

         int selected = messageListJL.getSelectedIndex();
         messageListJL.setSelectedIndex(selected);

        message msgObj = newlibrary.getMessage(dlm.getElementAt(messageListJL.getSelectedIndex()), username);

         Date today = new Date();
         SimpleDateFormat form = new SimpleDateFormat(patt);
         String todayStr = form.format(today);
         messageListJL.setSelectedIndex(0);
         fromJTF.setText(username);
         toJTF.setText(msgObj.getuserfrom());
         subjectJTF.setText("re: "+msgObj.getsubj());
         dateJTF.setText(todayStr);

      }else if(e.getActionCommand().equals("Delete")) { // needs another else if for get mail
         DefaultListModel dlm = (DefaultListModel)messageListJL.getModel();
         int selected = messageListJL.getSelectedIndex();

         try {
         if(selected>-1){

   System.out.println("-----------" + dlm.getElementAt(messageListJL.getSelectedIndex())); newlibrary.deleteMessage((String)dlm.getElementAt(messageListJL.getSelectedIndex()), username);
         }
            dlm.removeElementAt(selected);
            } catch (Exception ex) {
                ex.printStackTrace();
            }
         //dlm.clear(); //use this to clear the entire list.
         fromJTF.setText("");
         toJTF.setText("");
         subjectJTF.setText("");
         messageContentJTA.setText("");
         messageStatusJTA.setText("");
         
      }else if (e.getActionCommand().equals("Send Text")){
      
        DefaultListModel dlm = (DefaultListModel)messageListJL.getModel();
        message msgObj = new message(" ", " ", " ", " ", " ", " ", " ", " ");
        Date today = new Date();
        SimpleDateFormat form = new SimpleDateFormat(patt);
         String todayStr = form.format(today);
         String toUser = toJTF.getText();
         msgObj.setuserId(toUser);
         msgObj.setusername(toJTF.getText());
         msgObj.setuserdate(todayStr);
         msgObj.setuserto(toUser);
         msgObj.setuserfrom(fromJTF.getText());
         msgObj.setsubj(subjectJTF.getText());
         msgObj.setmsg(messageContentJTA.getText());
        System.out.println("Message sent to: "+toUser);

        newlibrary.sendClearText(msgObj, toUser);
        
             fromJTF.setText("");
             toJTF.setText("");
             subjectJTF.setText("");
             dateJTF.setText("");
             messageContentJTA.setText("");
      
      }else if (e.getActionCommand().equals("Get Mail")){
      
          DefaultListModel dlm = (DefaultListModel)messageListJL.getModel();
          dlm.clear();
    
      String [] headers = newlibrary.getMessageFromHeaders(username); // user

       for ( int i = 0; i < headers.length ; i++){
        dlm.addElement(headers[i]);
      
      }
}


      }catch(Exception x){
      x.printStackTrace();
      }
   


      // get rid of the waiting cursor
      setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
}
   public static void main(String args[]) {
      String hostId="localhost";
      String regPort="2222";
      String username = "Test";

      if (args.length >= 2){
         hostId=args[0];
         regPort=args[1];
         username=args[2];
      }
      


      //System.setSecurityManager(new RMISecurityManager());
      RMIClientGui rmiclient = new RMIClientGui(hostId, regPort, username);
   }
}

