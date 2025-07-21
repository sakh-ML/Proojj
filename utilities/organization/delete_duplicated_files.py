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


#finden duplikate in diesem Form : file_name-number.exctenction, also am ende - number
def minus_lexer(str):

    array_of_char = []    
    for i in range(0, len(str)):
        #wir übrerprüfen ob nach - nur zahlen kommen, wenn ja dann zurückgeben, sonst str[i]
        #in diesem fall str[i] appenden und weiter mit dem näcsten Zeicehn versuchen
        if str[i] == '-':
            for j in range(i + 1, len(str)):
                #wenn str[j] keien Zahl ist, dann str[i] appenden
                #und weiter mit dem näcsten Zeicehn versuchen, das Form zu finden
                if (str[j].isnumeric() == False):
                    break
                elif j == len(str) - 1:
                    file_name_without_duplicate_number = ''.join(array_of_char)
                    return file_name_without_duplicate_number

        #wir appenden hier zu dem array, das ist der echte name der file ohne den -number am Ende
        array_of_char.append(str[i])
        
    #not found
    #wenn "" zurückgebgen wird, das heisst das der Name der gebegenen File, ist kein Duplikate 
    return ""


#finden duplikate in diesem Form : file_name(number).exctenction, also am ende (number)
def parenthess_lexer(str):
    
    array_of_char = []    
    for i in range(0, len(str)):
        #sicherstellen, dass ( die j-te zeichen ist, und nicht die letzte oder vorletzte zeichen ist

        if str[i] == '(' and not(i == len(str)- 1 or i == len(str) - 2):
            
            for j in range(i + 1, len(str)):

                #hier sind wir am ende haben schon das Wort dieses Form
                #file_name(number).exctenction, dann geben wir den namen ohne die extra (number) zurück
            
                if j == len(str) - 1 and str[j] == ")":
                    file_name_without_duplicate_number = ''.join(array_of_char)
                    return file_name_without_duplicate_number
                
                #hier break, also weiter appenden und verscuhen mit dem näcsten zeichen
                elif j == len(str) and str[j] != ")":
                    break
                #hier break, also str[i] appenden in diesem Fall str[i] = (
                #und verscuhen mit dem näcsten zeichen weiter zu machen
                if str[j].isnumeric() == False:
                    break

        #wir appenden hier zu dem array, das ist der echte name der file ohne den (number) am Ende
        array_of_char.append(str[i])

    #wenn "" zurückgebgen wird, das heisst das der Name der gebegenen File, ist kein Duplikate         

    return ""


def delete_duplicates_in_file():
    
    PATH = input("Enter the path of the directory: ")
    
    if os.path.exists(PATH) == False:
        raise Exception("the path dosent exist")
    
    for file in os.listdir(PATH):
        
        _ , folder_extenction = os.path.splitext(file)
        file_name_without_extenction = file[: len(file) - len(folder_extenction)] #name ohne .x am ende
    

        #überprüfen ob file ist ein Duplikate, mit zwei Formen (number) oder -number
        file_name_without_duplicate_number_minus = minus_lexer(file_name_without_extenction)
        file_name_without_duplicate_number_parenthesse = parenthess_lexer(file_name_without_extenction)
        
        #wenn die Datei keine Duplikate ist, dann einfach weiter mit der näcsten Datei
        if(file_name_without_duplicate_number_minus == "" and file_name_without_duplicate_number_parenthesse == ""):
            continue
        #wenn die Datei ein Duplikate ist
        else:
            #wir müssen jetzt sichern ob es wirklich um ein dupliakte handelt.
            #wenn ja löschen wir es, sonst nicht !.
            
            full_file_name = f"{PATH}/{file}"
            
            if os.path.exists(full_file_name):
                #Es handelt sich wirklich also um ein Dupliakte -> file (duplikate) löschen.
                print("We found that this file is a duplikate: " + file)
                #bevor wir löscehn , müssen wir sicherstellen dass beide datei den geeichen Enhalt haben.
            else:
                continue
        

def main():
    delete_duplicates_in_file()
    
if __name__ == "__main__":
    main()
