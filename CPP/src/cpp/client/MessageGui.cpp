
#include <Fl/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Check_Browser.H>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

/**
 * Copyright (c) 2019 Tim Lindquist,Alper Mencek
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
 * Purpose: C++ FLTK client UI for Message management.
 * This class creates Gui components for a UI to manage messages.
 * This software is meant to run on Linux, and MacOS using g++.
 * <p/>
 * Ser321 Principles of Distributed Software Systems
 * see http://pooh.poly.asu.edu/Ser321
 * @author Tim Lindquist (Tim.Lindquist@asu.edu) CIDSE - Software Engineering, IAFSE
 *                       ASU at the Polytechnic campus
 * @file    MessageGui.cpp
 * @author Alper Mencek amencek@asu.edu
 * @version March,2019
 * @license See above
 **/
class MessageGui: public Fl_Window {
    protected:
    /**
    * fromFI is the Fl_Input labelled from, identifying who the message is from.
    */
    Fl_Input * fromFI;

    /**
    * toIC is the Fl_Input labelled to, identifying who the message is to
    */
    Fl_Input * toFI;

    /**
    * subjectFI is the Fl_Input labeled subject, identifying the message subject
    */
    Fl_Input * subjectFI;

    /**
    * dateFI is the Fl_Input labeled date, identifying the message creation date.
    */
    Fl_Input *dateFI;

    /**
    * messageFMI is the Fl_Multiline_Input below subject and date for displaying
    * or entering the message text.
    */
    Fl_Multiline_Input *messageFMI;

    /**
    * getButt is the Fl_Button labelled Get
    * When the user clicks Get, the list of message headers on the left is refreshed.
    */
    Fl_Button * getButt;

    /**
    * deleteButt is the Fl_Button labeled Delete.
    * When the user clicks Delete, the currently displayed message is removed from the
    * message library and its header is removed from the list of message headers.
    */
    Fl_Button *deleteButt;

    /**
    * replyButt is the Fl_Button labeled Reply
    * When the user clicks Reply, the fields on the right side
    * change from a mode of displaying the contents of a message to creating a new
    * message.
    */
    Fl_Button *replyButt;

    /**
    * sendButt is the Fl_Button labeled Send.
    * Clicking this button should cause the library to add a new message from the
    * contents of the fields on the right side of the display
    */
    Fl_Button *sendButt;

    /**
    * exportButt is the Fl_Button labeled Export.
    * This button should cause the library to be serialized to Json and saved in the
    * messages.json file in the projects base directory.
    */
    Fl_Button * exportButt;

    /**
    * headerFCB is the Fl_Check_Browser on the left side of the window.
    * This area is for displaying the message headers.
    */
    Fl_Check_Browser *headerFCB;

    public:
    MessageGui(const char * name = 0) : Fl_Window(965,400,name) {
        begin();

        // create the list of message headers on the left side of the GUI
        headerFCB = new Fl_Check_Browser(25,75,345,300,"");

        toFI = new Fl_Input(400, 75, 245, 25,"To");
        fromFI = new Fl_Input(705, 75, 245, 25,"From");

        subjectFI = new Fl_Input(430, 125, 250, 25, "Subject");
        dateFI = new Fl_Input(730, 125, 220, 25, "Date");

        messageFMI = new Fl_Multiline_Input(415, 175, 525, 200,"Msg");
        // tell the message multiline to word wrap. 1=on 0=off
        messageFMI->wrap(1);

        // create the buttons across the top of the UI
        getButt = new Fl_Button(60,25,100,25,"Get");
        deleteButt = new Fl_Button(180,25,100,25,"Delete");
        replyButt = new Fl_Button(300,25,100,25,"Reply");
        sendButt = new Fl_Button(420,25,100,25,"Send");
        exportButt = new Fl_Button(540,25,100,25,"Export");

        end();
        show();
    }
};
