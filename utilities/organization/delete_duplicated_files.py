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


def lexing(str):

    array_of_char = []    
    for i in range(0, len(str)):
        if str[i] == '-':
            for j in range(i + 1, len(str)):
                if (str[j].isnumeric() == False):
                    break
            else:
                
                file_name_without_duplicate_number = ''.join(array_of_char)
                return file_name_without_duplicate_number
        array_of_char.append(str[i])
        
    #not found
    
    return ""
    
def test():
    
    string = "04-Parsing - TopDown-5.pdf"
    
    print(lexing(string))


def delete_duplicates_in_file():
    
    #PATH = input("Enter the path of the directory: ")
    PATH = "/home/ml-abu-saleh-ml/Downloads/Documents"
    
    if os.path.exists(PATH) == False:
        raise Exception("the path dosent exist")
    
    for file in os.listdir(PATH):
        
        _ , folder_extenction = os.path.splitext(file)
        file_name_without_extenction = file[: len(file) - len(folder_extenction)]
        print(file)
        print(file_name_without_extenction)
        print(lexing(file_name_without_extenction))
        
    

def main():
    test()
    
if __name__ == "__main__":
    main()
