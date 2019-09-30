package ser321.assign3.amencek.server;

import java.rmi.*;
import java.util.*;
import ser321.assign2.lindquis.client.*;
import org.json.*;

import java.io.FileInputStream;
import java.util.Vector;
import java.util.Enumeration;
import java.io.Serializable;
import java.util.Hashtable;
import java.util.ArrayList;
//port .mess;
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
 * remote interface for the employee server.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * @see <a href="http://pooh.poly.asu.edu/Ser321">Ser321 Home Page</a>
 * @author Alper Mencek (amencek@asu.edu) CIDSE - Software Engineering
 *                       Ira Fulton Schools of Engineering, ASU Polytechnic
 * @date    January, 2019
 * @license See above
 */
public interface messageLibServer extends Remote {
    //   public Emp getEmp(int id) throws RemoteException;
    //   public Emp addEmp(String name) throws RemoteException;
    //   public String[] getNames() throws RemoteException;

    public String getName()throws RemoteException;
    public void setName(String name)throws RemoteException;
    public Vector<String> getUserNames()throws RemoteException;
    public boolean isMember(String id, String pwd)throws RemoteException;
    public void printGroup()throws RemoteException;
    public String[] getMessageFromHeaders(String toAUserName)throws RemoteException;
    public message getMessage(String header, String curUser)throws RemoteException;
    public boolean deleteMessage(String header, String toAUserName)throws RemoteException;
    
    public void sendClearText(message msg, String touser) throws RemoteException;
    







}
