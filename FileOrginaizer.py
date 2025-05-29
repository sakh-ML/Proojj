"""
Dieses Programm organisiert Dateien in einem angegebenen Verzeichnis,
indem es sie basierend auf ihrer Dateiendung in vordefinierte Ordner verschiebt.
Unterstützte Dateitypen sind z.B. Bilder, Dokumente, Videos und ZIP-Dateien.
Dateien, die keiner Kategorie zugeordnet werden, landen im Ordner 'Others'.
"""


import os
import shutil


file_types = {
    "Images": [".png", ".jpg", ".jpeg", ".gif"],
    "Documents": [".pdf", ".docx", ".txt"],
    "Videos": [".mp4", ".mkv", ".avi"],
    "Hapra": [".zip"],
}


def organize_files() -> None:
    
    path_directoy = input("Enter the path of the directory: : ")
    everything_in_a_directory = os.listdir(path_directoy) 
    for thing_name in everything_in_a_directory:
        file_path = os.path.join(path_directoy, thing_name)
        _,folder_extenction = os.path.splitext(thing_name) 
        
        if not os.path.isfile(file_path):
            continue
        matched = False
        for new_folder_name, extenstion in file_types.items():

            if folder_extenction in extenstion:
                exte_path = os.path.join(path_directoy, new_folder_name)
                new_path = os.path.join(exte_path , thing_name)
                if os.path.exists(file_path):
                    if not os.path.exists(exte_path):
                        os.makedirs(exte_path) 
                    shutil.move(file_path, new_path)
                    matched = True
                    break
                    
        if not matched :
            exte_path = os.path.join(path_directoy, "Others")
            new_path = os.path.join(exte_path , thing_name)
            if os.path.exists(file_path):
                if not os.path.exists(exte_path):
                    os.makedirs(exte_path)
                shutil.move(file_path, new_path)
    

def main() -> None:
    organize_files()


if __name__ == '__main__':
    main()
