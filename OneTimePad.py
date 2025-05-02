import os, random, string



def encrypte_message() -> None:
    
    try:
        file_name = input("File name without extenction: ") #test
        file_extension = input("Extension of the file: ") #txt
        full_file_name = file_name + "." + file_extension#test.txt
        encrypted_file_name = "encrypted_" + full_file_name#encrypted_test.txt
        key_file_name = "key_" + encrypted_file_name#key_encrypted_test.txt)
        
        with open(full_file_name, "r") as file:
            counter = 0
            while True:
                char = file.read(1)
                if not char:
                    break
                if char.isalpha():
                    counter+=1
            if counter != 0:
                
                 encrypted_file = open(encrypted_file_name, "a")
                 key_file = open(key_file_name, "a")
                 
                 while counter > 0:
                     key_file.write(random.choice(string.ascii_lowercase))
                     counter -= 1
                     
                 file.seek(0)
                 key_file.seek(0)
                 
                 while True:
                     
                    char = file.read(1)
                    char_key = key_file.read(1)
                    if not char:
                        break
                    if char.isalpha():
                        if char.islower():
                            pass
                        
                        else:
                            pass
                        char_to_write = char(ord(char) ^ ord(char_key))
                        encrypted_file.write(char_to_write)
                    else:
                        encrypted_file.write(char)
            else:
                print("There is nothing in the file to be encrypted !!")
    except FileNotFoundError as e:
        
        print("Error: " + str(e))
    
    except Exception as e:
        print("Error: " + str(e))


def decrypt_message()-> None:
    pass


