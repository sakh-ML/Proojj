import os
import shutil

file_types = {
    "Photos" : ["png","webp"],
    "Files" : ["pdf"]
    #etc .....
}

#PATH = input("Write the directory path: ")
PATH = "/home/ml-abu-saleh-ml/Downloads"

if os.path.exists(PATH) == False:
    raise Exception("the path dosent exist")

for file in os.listdir(PATH):
    
     #print(str(file.split(".")[-1]))
    _, folder_extenction = os.path.splitext(file)
    if folder_extenction == "":
        continue
    folder_extenction = folder_extenction[1:]
    
