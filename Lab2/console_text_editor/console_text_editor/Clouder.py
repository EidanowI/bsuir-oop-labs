import sys
import shutil
import os

#pip install google-api-python-client
from googleapiclient.discovery import build
from google.oauth2 import service_account

SCOPES = ['https://www.googleapis.com/auth/drive']
SERVICE_ACCOUNT_FILE = 'service_account.json'
PARENT_FOLDER_ID = "1IumnN5VNU8Kc0GRHxFFy3ResXJnROmqD"

def authenticate():
    creds = service_account.Credentials.from_service_account_file(SERVICE_ACCOUNT_FILE, scopes=SCOPES)
    return creds

def upload_photo(file_path):
    creds = authenticate()
    service = build('drive', 'v3', credentials=creds)

    file_metadata = {
        'name' : file_path,
        'parents' : [PARENT_FOLDER_ID]
    }

    file = service.files().create(
        body=file_metadata,
        media_body=file_path
    ).execute()



if __name__ == "__main__":
    print(sys.argv[1])
    upload_photo(sys.argv[1])
    # Проверяем, передана ли строка
    if len(sys.argv) > 1:
        input_string = ' '.join(sys.argv[1:])  # Объединяем все аргументы в одну строку
        
    else:
        print("Пожалуйста, введите строку.")