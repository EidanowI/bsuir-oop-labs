#include "Content.h"



Content::Content(bool isEditable) : m_isEditable(isEditable){
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
    Print();

	return true;
}

void Content::Print(){
    system("CLS");


    for (int i = 0; i < cursor_pos; i++) {
        std::cout << m_data[i];
    }
    std::cout << '_';

    for (int i = cursor_pos; i < m_data.size(); i++) {
        std::cout << m_data[i];
    }


    std::cout << "\033[50;150H";
}