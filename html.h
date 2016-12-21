#ifndef _HTML_UTILITY_H
#define _HTML_UTILITY_H

#include "DoublyLinkedList.h"
#include <string>
#include <fstream>
//this file refers to github. And I change it to fit my project
using std::ofstream;
using std::string;

//Output file of html
class HTMLFile {
    public:
        HTMLFile();
        ~HTMLFile();
        HTMLFile(string fileName, string title);
        HTMLFile(HTMLFile&);
        void begin();
        void end();
        void openTag(const char tagName[], const char className[]="");//add header
        void closeTag();//add ender
        void writeString(string content);//add content
        enum state {
            ready = 0,
            opened,
            closed
        };
        state getState() {return fstate;}

    private:
        string file, html_title;
        ofstream os;
        state fstate;
        DoublyLinkedList<string> tag_stack;
};

class HTMLTable {//the table in html file
    public:
        HTMLTable();
        ~HTMLTable();
        HTMLTable(HTMLFile *_file, string _title = "", bool index = true);
        HTMLTable(HTMLTable&);
        void insertHead(string _head);//insert string in header
        void begin();
        void end();
        void beginRow();//begin a row in table
        void endRow();//end a row in table
        void insertCell(string content);//add content
        enum state {
            ready = 0,
            opened,
            closed
        };
        state getState() {return fstate;}

    private:
        HTMLFile *file;
        string title;
        state fstate;
        int idx;
        DoublyLinkedList<string> heads;
};

#endif


