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


def minus_lexer(str):

    array_of_char = []    
    for i in range(0, len(str)):
        if str[i] == '-':
            for j in range(i + 1, len(str)):
                if (str[j].isnumeric() == False):
                    break
                elif j == len(str) - 1:
                    file_name_without_duplicate_number = ''.join(array_of_char)
                    return file_name_without_duplicate_number

        array_of_char.append(str[i])
        
    #not found
    
    return ""


def parenthess_lexer(str):
    array_of_char = []    
    for i in range(0, len(str)):
        if str[i] == '(' and not(i == len(str)- 1 or i == len(str) - 2):
            
            for j in range(i + 1, len(str)):
                
                if j == len(str) - 1 and str[j] == ")":
                    file_name_without_duplicate_number = ''.join(array_of_char)
                    return file_name_without_duplicate_number
                elif j == len(str) and str[j] != ")":
                    break
                
                if str[j].isnumeric() == False:
                    break
            else:
                file_name_without_duplicate_number = ''.join(array_of_char)
                return file_name_without_duplicate_number

        array_of_char.append(str[i])

    #not found          

    
    return ""


def delete_duplicates_in_file():
    
    PATH = input("Enter the path of the directory: ")
 
    if os.path.exists(PATH) == False:
        raise Exception("the path dosent exist")
    
    for file in os.listdir(PATH):
        
        _ , folder_extenction = os.path.splitext(file)
        file_name_without_extenction = file[: len(file) - len(folder_extenction)]
        #print(file)
        #print(file_name_without_extenction)
        
        file_name_without_duplicate_number_minus = minus_lexer(file_name_without_extenction)
        file_name_without_duplicate_number_parenthesse = parenthess_lexer(file_name_without_extenction)
        
        if(file_name_without_duplicate_number_minus == "" and file_name_without_duplicate_number_parenthesse == ""):
            continue
        else:
            #wir müssen jetzt sichern ob es wirklich um ein dupliakte handelt.
            #wenn ja löschen wir es, sonst nicht !.
            
            full_file_name = f"{PATH}/{file}"
            
            if os.path.exists(full_file_name):
                #Es handelt sich wirklich also um ein Dupliakte -> file (duplikate) löschen.
                print("We found that this file is a duplikate: " + file)
                #file löschen :)
            
            else:
                continue
        

def main():
    delete_duplicates_in_file()
    
if __name__ == "__main__":
    main()
