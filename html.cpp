#include "html.h"
#include "DoublyLinkedList.h"
#include <cstring>
#include <string>
#include <stdexcept>
using std::string;
using std::string;
using std::runtime_error;


static const char header_first[] = 
"<HTML>\n"
"<HEAD>\n";

static const char header_final[] = 
"</HEAD>\n"
"<BODY bgColor=#ffffcc>\n";

static const char html_final[] = 
"</BODY>\n"
"</HTML>\n"
"\n";

static string escape(string str) {
    size_t i = 0;
    while(i < str.length()) {
        switch(str[i]) {
            case '&':
                str.replace(i, 1, "&amp;");
                i += 5;
                break;
            case '<':
                str.replace(i, 1, "&lt;");
                i += 4;
                break;
            case '>':
                str.replace(i, 1, "&rt;");
                i += 4;
                break;
            default:
                i++;
        }
    }
    return str;
}

HTMLFile::HTMLFile()
:fstate(ready) {
    os.exceptions(ofstream::failbit | ofstream::badbit);
}

HTMLFile::~HTMLFile() {
    if(os.is_open()) {
        os.close();
    }
}

HTMLFile::HTMLFile(string fileName, string title)
:file(fileName),
 html_title(title),
 fstate(ready) {
    os.exceptions(ofstream::failbit | ofstream::badbit);
 }

void HTMLFile::begin() {
    if(file.length() == 0) {
        throw "No file name specified";
    }
    os.open(file.c_str(), ofstream::out | ofstream::trunc);

    fstate = opened;

    os << header_first;
    os << "<TITLE>" << html_title << "</TITLE>\n";
    os << header_final;
    os << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>\n";
}

void HTMLFile::end() {
    if(fstate != opened) {
        throw "File is not opened";
    }
    if(!tag_stack.isEmpty()) {
        throw "Tag corrupted";
    }
    os << html_final;

    os.close();

    fstate = closed;
}

void HTMLFile::openTag(const char tagName[], const char className[]) {
    if(fstate != opened) {
        throw "File not opened";
    }
    if(!tagName || strlen(tagName) == 0) {
        throw "Empty Tag";
    }
    os << "<" << escape(tagName) << " ";
    if(className && strlen(className) > 0) {
        os << className ;
    }
    os << ">";

    tag_stack.addLast(tagName);
}

void HTMLFile::closeTag() {
    if(tag_stack.isEmpty()) {
        throw "Tag corrupted";
    }
    os << "</" << tag_stack.removeLast() << ">\n";
}

void HTMLFile::writeString(string content) {
    os << escape(content);
}

HTMLTable::HTMLTable() {
    throw runtime_error("Using default constructor");
}

HTMLTable::~HTMLTable() {
}

HTMLTable::HTMLTable(HTMLFile *_file, string _title, bool index)
:file(_file),
 title(_title), fstate(ready),
 idx(index?(1):(0)) {
    if(file->getState() != HTMLFile::opened) {
        throw runtime_error("File not opened");
    }
}

void HTMLTable::insertHead(string _head) {
    if(fstate != ready) {
        throw runtime_error("Cannot insert head at this state");
    }
    //Add to heads
    heads.addLast(_head);
}

void HTMLTable::begin() {
    int i;
    DoublyLinkedList<string>::Iterator itr=heads.begin();
    if(fstate != ready) {
        throw runtime_error("Cannot insert head at this state");
    }
    fstate = opened;
    //The open of a table
    file->openTag("TABLE", "cellSpacing=1 cellPadding=1 border=1");
    //Writing head 
    file->openTag("TR");
    if(idx) {
        file->openTag("TH");
        file->writeString("#");
        file->closeTag();
    }
    for(i = 0; i < heads.size(); i++, ++itr) {
        file->openTag("TD");
        file->writeString((*itr));
        file->closeTag();
    }
    file->closeTag();
}

void HTMLTable::end() {
    if(fstate != opened) {
        throw runtime_error("File is not opened");
    }
    file->closeTag();

    fstate = closed;
}

void HTMLTable::beginRow() {
    char buff[16];
    if(fstate != opened) {
        throw runtime_error("Cannot insert row at this state");
    }
    file->openTag("TR");
    //Insert a index field if necessary
    if(idx > 0) {
        sprintf(buff, "%d", idx);
        insertCell(buff);
    }
}

void HTMLTable::endRow() {
    if(fstate != opened) {
        throw runtime_error("Cannot end row at this state");
    }
    file->closeTag();
    //Increase index
    idx++;
}

void HTMLTable::insertCell(string content) {
    file->openTag("TD");
    file->writeString(content);
    file->closeTag();
}