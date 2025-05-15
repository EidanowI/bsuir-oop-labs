#include "Content.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include "../Command/AddCharCommand.h"
#include "../Command/DeleteChar.h"
#include "../Command/PasteCommand.h"



Content::Content(bool isEditable) : m_isEditable(isEditable){
    m_data = std::vector<char>();

    cursor_pos = m_data.size();
}
Content::Content(bool isEditable, std::vector<char> data) : m_isEditable(isEditable) {
    m_data = data;

    cursor_pos = m_data.size();
}
Content::~Content() {
    delete m_pFormator;
}

/*Thats shit will return true if the content was changed so we need to record date*/
bool Content::Edit() {
    m_pFormator = new UnderlineFormater(2, 4, new BoldFormater(5, 8, new Formator()));

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
                else if (in == 26) {
                    if (m_isEditable) {
                        auto u = m_history_manager.Undo();
                        if (u) {
                            u->Apply((char*)this);
                            cursor_pos = m_data.size();
                            Print();
                        }
                    }
                }
                else if (in == 24) {
                    if (m_isEditable) {
                        auto u = m_history_manager.Redo();
                        if (u) {
                            u->Apply((char*)this);
                            cursor_pos = m_data.size();
                            Print();
                        }
                    }
                }
                else if (in == 8) {
                    if (m_isEditable) {
                        ret = true;
                        DeleteCommand* command = new DeleteCommand(m_data);
                        m_history_manager.AddCommand(command);
                        command->Delete(this);
                    }
                }
                else if (in == 75) {
                    m_textSelection_highlight.Clear();

                    MoveCursorLeft();
                }
                else if (in == 77) {
                    m_textSelection_highlight.Clear();

                    MoveCursorRight();
                }
                else if (in == 72) {
                    MoveHLLeft();
                }
                else if (in == 80) {
                    MoveHLRight();
                }
                else if (in == 15) {///ctrl + o
                    CopyToClipboard();
                }
                else if (in == 16) {///ctrl + p
                    if (m_isEditable) {
                        ret = true;

                        PasteCommand* command = new PasteCommand(m_data);
                        m_history_manager.AddCommand(command);
                        command->Paste(this);
                    }
                }
                else 
                {
                    if (m_isEditable) {
                        ret = true;

                        AddCharCommand* command = new AddCharCommand(m_data);
                        m_history_manager.AddCommand(command);
                        command->AddChar(this, (char)in);
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
void Content::Paste() {
    HANDLE clip = 0;

    if (OpenClipboard(NULL)) {
        clip = GetClipboardData(CF_TEXT);
        CloseClipboard();
    }

    std::vector<char> bf;
    char* a = (char*)clip;
    if (a) {
        while (*a) {
            bf.push_back(*a);
            a++;
        }
    }

    m_data.insert(m_data.begin() + cursor_pos, bf.begin(), bf.end());

    Print();
}

void Content::Print(){
    system("CLS");

    for (int i = 0; i < cursor_pos; i++) {
        if (m_textSelection_highlight.begin != m_textSelection_highlight.end) {
            if (m_textSelection_highlight.begin == i) {
                std::cout << "\033[3;100;30m";// Texting\033[0m
            }
            if (m_textSelection_highlight.end == i) {
                std::cout << "\033[0m";
            }
        }
        m_pFormator->CharDecorate(i);
        std::cout << m_data[i];
    }

    std::cout << "\033[33m_\033[0m";

    for (int i = cursor_pos; i < m_data.size(); i++) {
        if (m_textSelection_highlight.begin != m_textSelection_highlight.end) {
            if (m_textSelection_highlight.begin == i) {
                std::cout << "\033[3;100;30m";// Texting\033[0m
            }
            if (m_textSelection_highlight.end == i) {
                std::cout << "\033[0m";
            }
        }
        m_pFormator->CharDecorate(i);
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

void Content::MoveHLLeft() {
    if (cursor_pos > 0) {
        cursor_pos--;
    }

    if (m_textSelection_highlight.end == 0) {
        m_textSelection_highlight.end = cursor_pos + 1;
    }
    m_textSelection_highlight.begin = cursor_pos;

    Print();
}
void Content::MoveHLRight() {
    if (cursor_pos < m_data.size()) {
        cursor_pos++;
    }

    if (m_textSelection_highlight.begin == 0) {
        m_textSelection_highlight.begin = cursor_pos - 1;
    }
    m_textSelection_highlight.end = cursor_pos;

    Print();
}

void Content::CopyToClipboard() {
    if (OpenClipboard(NULL)) {
        EmptyClipboard();

        std::vector<char> bb;
        int i = m_textSelection_highlight.begin;
        while (i != m_textSelection_highlight.end) {
            bb.push_back(m_data[i]);

            i++;
        }
        bb.push_back(0);

        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, bb.size() + 1);
        if (hGlobal) {
            memcpy(GlobalLock(hGlobal), bb.data(), bb.size() + 1);
            GlobalUnlock(hGlobal);
            SetClipboardData(CF_TEXT, hGlobal);
        }
        CloseClipboard();
    }
}