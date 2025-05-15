#pragma once
#include <string>
#include <fstream>
#include "../File/FileDialog.h"
#include "../Document/Document.h"



class ISaverStrategy {
public:
	virtual void Save(char* pDoc) = 0;
};


class LocalSaver : public ISaverStrategy {
public:
	void Save(char* pDoc) override {
       //Document* pDoc = (Document*)pDoc;
        auto path = FileDialog::FileDialogSave("Save doc");

        std::ofstream ofs(path, std::ios::binary);

        int perm_cout = ((Document*)pDoc)->m_permisionLayers.size();
        ofs.write((char*)&perm_cout, 4);

        for (int i = 0; i < ((Document*)pDoc)->m_permisionLayers.size(); i++) {
            ofs.write((char*)&((Document*)pDoc)->m_permisionLayers[i], sizeof(EditPermisionLayer));
        }

        int data_size = ((Document*)pDoc)->m_content.m_data.size();

        ofs.write((char*)&data_size, 4);
        ofs.write(((Document*)pDoc)->m_content.m_data.data(), data_size);

        ofs.close();
	}
};



/*bool uploadToGoogleDrive(const std::string& filePath, const std::string& accessToken) {
    CURL* curl = curl_easy_init();
    if (!curl) return false;

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        curl_easy_cleanup(curl);
        return false;
    }

    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string uploadUrl = "https://www.googleapis.com/upload/drive/v3/files?uploadType=media";

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: Bearer " + accessToken).c_str());
    headers = curl_slist_append(headers, "Content-Type: application/octet-stream");
    headers = curl_slist_append(headers, ("Content-Length: " + std::to_string(fileSize)).c_str());

    curl_easy_setopt(curl, CURLOPT_URL, uploadUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &file);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    file.close();

    return res == CURLE_OK;
}*/
