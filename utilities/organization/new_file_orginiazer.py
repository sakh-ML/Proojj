# -----------------------------------------------------------
#  File Organizer Script by Mohammad Abu Saleh
#  © 2025 sakh-ML — All rights reserved.
#  This script is my original work.
#  You may use this code for personal use only.
#  Distribution, reproduction, or commercial use without 
#  my explicit permission is prohibited.
# -----------------------------------------------------------


import os
import shutil


file_types = {
    "Photos": ["png", "jpg", "jpeg", "webp", "bmp", "gif", "tiff", "svg", "heic"],
    "Documents": ["pdf", "doc", "docx", "odt", "txt", "rtf", "md", "tex"],
    "Spreadsheets": ["xls", "xlsx", "ods", "csv"],
    "Presentations": ["ppt", "pptx", "odp"],
    "Archives": ["zip", "rar", "7z", "tar", "gz", "bz2", "xz", "iso"],
    "Videos": ["mp4", "mkv", "mov", "avi", "flv", "wmv", "webm"],
    "Audio": ["mp3", "wav", "flac", "aac", "ogg", "m4a"],
    "Code": ["py", "c", "cpp", "java", "js", "ts", "html", "css", "php", "rb", "go", "rs", "swift", "kt", "cs", "pl", "lua", "scala", "h", "hpp"],
    "Scripts": ["sh", "bat", "ps1", "cmd"],
    "Executables": ["exe", "msi", "apk", "bin", "appimage", "jar", "deb", "rpm"],
    "Fonts": ["ttf", "otf", "woff", "woff2"],
    "Database": ["sql", "db", "sqlite", "mdb", "accdb"],
    "3DModels": ["obj", "fbx", "stl", "blend", "dae"],
    "Design": ["psd", "ai", "xd", "sketch", "fig"],
    "Ebooks": ["epub", "mobi", "azw3", "djvu"]
}


def organize_files():

    PATH = input("Write the directory path: ")

    if os.path.exists(PATH) == False:
        raise Exception("the path dosent exist")

    for file in os.listdir(PATH):
        
        #print(str(file.split(".")[-1]))
        _, folder_extenction = os.path.splitext(file)
        #this means there no extention at the end, maybe like this is a folder inside the folder path.so skip.
        if folder_extenction == "":
            continue
        
        folder_extenction = folder_extenction[1:]
        full_file_path = f"{PATH}/{file}"

        for key, array_value in file_types.items():
            #the extcteion of the file, is in our files_types
            if folder_extenction in array_value:
                
                #erstelle ein Folder Path/key wenn es nicht exist und file da moven.
                folder_destentation = f"{PATH}/{key}"
                where_to_move_the_file = f"{PATH}/{key}/{file}"
                
                #print(folder_destentation)
                #print(where_to_move_the_file)
                if os.path.exists(folder_destentation):
                    shutil.move(full_file_path, where_to_move_the_file)
                    break
                
                #erstelle where_to_move_the_file if not exists, und dann file da bewegen
                else:
                    os.mkdir(folder_destentation)
                    shutil.move(full_file_path, where_to_move_the_file)
                    break
                    
        #the excteion of this file is not found in the files_types. add it to a folder other (platzhalter)
        #erstelle ein folder Others wenn es nicht existiert, und da file bewegen
        else:
            
            new_directry_path = f"{PATH}/Others"
            where_to_move_file = f"{PATH}/Others/{file}"

            if os.path.exists(new_directry_path):
                
                shutil.move(full_file_path, where_to_move_file)
            else:
                os.mkdir(new_directry_path)
                shutil.move(full_file_path, where_to_move_file)
                

def main():
    organize_files()
    
if __name__ == "__main__":
    main()                                
