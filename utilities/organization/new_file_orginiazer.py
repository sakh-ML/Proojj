import os
import shutil

file_types = {
    "Photos" : ["png","webp", "jpeg"],
    "Docu" : ["pdf"]
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
    print(file)
    folder_extenction = folder_extenction[1:]
    print(folder_extenction)
    
    for key, array_value in file_types.items():
        #the extcteion of the file, is in our files_types
        if folder_extenction in array_value:
            
            #erstelle ein Folder Path/key wenn es nicht exist und file da moven.
            where_to_move_the_file = f"{PATH}/{key}/{file}" 
            full_file_path = f"{PATH}/{file}"
            
            if os.path.exists(where_to_move_the_file):
                shutil.move(full_file_path, where_to_move_the_file)
                break
            
            #erstelle where_to_move_the_file if not exists, und dann file da bewegen
            else:
                #to fix
                os.mkdir(where_to_move_the_file)
                shutil.move(full_file_path, where_to_move_the_file)
                break
                
        
    #the excteion of this file is not found in the files_types. add it to a folder other (platzhalter)
    #erstelle ein folder Others wenn es nicht existiert, und da file bewegen
    else:
        
        new_directry_path = f"{PATH}/Others"
        where_to_move_file = f"{PATH}/Others/{file}"
        where_file_was = f"{PATH}/{file}" 
        
        if os.path.exists(new_directry_path):
            
            shutil.move(where_file_was, where_to_move_file)
            break
        else:
            os.mkdir(new_directry_path)
            shutil.move(where_file_was, where_to_move_file)
            
    
                  
