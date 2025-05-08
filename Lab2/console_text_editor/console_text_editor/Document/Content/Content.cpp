#include "Content.h"



Content::Content(bool isEditable) : m_isEditable(isEditable){

}
Content::Content(bool isEditable, std::vector<char> data) : m_isEditable(isEditable) {

}
Content::~Content() {

}

/*Thats shit will return true if the content was changed so we need to record date*/
bool Content::Edit() {
	return true;
}