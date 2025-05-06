####TODO####
#ROCK , PAPIER, SCISSORS GAME#
# Abu Saleh #

import random

choises = ["ROCK", "PAPIER", "SCISSORS"]

def check_end_status(player_one: str, player_two: str) -> str:
    
    if player_one == player_two:
        return "DRAW"
    
    if player_one == 'ROCK':
        if player_two == 'PAPIER':
            return "PLAYER_TWO"
        else:
            return "PLAYER_ONE"
    
    if player_one == "PAPIER":
        if player_two == "ROCK":
            return "PLAYER_ONE"
        else:
            return "PLAYER_TWO"
    
    if player_one == 'SCISSORS':
        if player_two == "ROCK":
            return "PLAYER_TWO"
        else:
            return "PLAYER_ONE"


def get_input_player() -> str:
    
    while True:
        result = input("Enter: ROCK, PAPIER, SCISSORS: ").upper()
        if result in choises:
            break
        else:
            print("Invalid input!!")
    return result

def play_again() -> bool:
    while True:
        result = input("Do you want to play again? 1 for yes, 2 for no: ")
        if result == "1":
            return True
        
        elif result == "2":
            return False
        
        else:
            print("Invalid input!!")

def play_game() -> None:
    
    print("+" * 15)
    while True:
        
        player_one = get_input_player()
        computer = random.choice(choises)
        print("+" * 15)
        print("You have entered: " + player_one)
        print("The computer entered: " + computer)
        end_result = check_end_status(player_one, computer)
        if end_result == 'DRAW':
            print("IT IS A DRAW!!")
        
        elif end_result == "PLAYER_ONE":
            print("YOU WON!!")
        
        else:
            print("YOU LOST!!")
        
        result_play_again = play_again()
        
        if not result_play_again:
            break
        
        
        
play_game()

