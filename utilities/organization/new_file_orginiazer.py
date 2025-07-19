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
    
    for key, array_value in file_types.items():
        #the extcteion of the file, is in our files_types
        if folder_extenction in array_value:
            print("Pingo, add it to the right key!!")
        #the excteion of this file is not found in the files_types. add it to a folder other (platzhalter)
        else:
            print("!!!, lets add it for now to the other folder")
        
    #if :
    #    asdasd
    #else:
           
