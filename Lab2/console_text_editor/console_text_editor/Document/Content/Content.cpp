#include "Content.h"
#include <conio.h>
#include <iostream>
#include <windows.h>



Content::Content(bool isEditable) : m_isEditable(isEditable){
    m_data = std::vector<char>();

    cursor_pos = m_data.size();
}
Content::Content(bool isEditable, std::vector<char> data) : m_isEditable(isEditable) {
    m_data = data;

    cursor_pos = m_data.size();
}
Content::~Content() {

}

/*Thats shit will return true if the content was changed so we need to record date*/
bool Content::Edit() {
    bool ret = false;

    Print();

    while (true) {
        if (_kbhit()) {
            int in = _getch();

            if (in != 224) {
                if (in == 27) {
                    system("CLS");
                    return ret;
                }
                else if (in == 8) {
                    if (m_isEditable) {
                        ret = true;
                        DeleteChar();
                    }
                }
                else if (in == 75) {
                    MoveCursorLeft();
                }
                else if (in == 77) {
                    MoveCursorRight();
                }
                else 
                {
                    if (m_isEditable) {
                        ret = true;
                        AddChar(in);
                    }
                }
            }
            
        }
    }
}

void Content::AddChar(char ch) {
    if (cursor_pos == m_data.size()) {
        m_data.push_back(ch);
    }
    else {
        m_data.insert(m_data.begin() + cursor_pos, ch);
    }
    cursor_pos++;

    Print();
}
void Content::DeleteChar() {
    if (cursor_pos >= 1) {
        cursor_pos--;
        m_data.erase(m_data.begin() + cursor_pos);
        Print();
    }
}

void Content::Print(){
    system("CLS");


    for (int i = 0; i < cursor_pos; i++) {
        std::cout << m_data[i];
    }
    std::cout << "\033[33m_\033[0m";

    for (int i = cursor_pos; i < m_data.size(); i++) {
        std::cout << m_data[i];
    }


    std::cout << "\033[50;150H";
}

void Content::MoveCursorLeft() {
    cursor_pos--;

    if (cursor_pos < 0) {
        cursor_pos = 0;
    }
    Print();
}
void Content::MoveCursorRight() {
    cursor_pos++;

    if (cursor_pos > m_data.size()) {
        cursor_pos = m_data.size();
    }
    Print();
}