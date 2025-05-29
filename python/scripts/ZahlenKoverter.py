'''
Dieses Programm ist ein universeller Zahlenkonverter, der Zahlen zwischen verschiedenen Zahlensystemen (Basen) umwandeln kann. 
Es unterstützt Basen von mindestens 2 bis 16 und berücksichtigt dabei auch hexadezimale Ziffern (A-F).
Der Benutzer kann wählen, ob er von Dezimal (Basis 10) in eine andere Basis, von einer beliebigen Basis in Dezimal oder 
zwischen zwei beliebigen Basen konvertieren möchte.
Das Programm prüft die Gültigkeit der eingegebenen Zahlen in Bezug auf die jeweilige Basis und gibt entsprechende Fehlermeldungen aus.
'''

def check_basis_with_number(number, basis) -> bool:
    hexa_dezimal_numbers = {
        'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15
    }

    if basis < 2:
        return False

    for i in range(len(number)):
        if number[i].isalpha():
            if hexa_dezimal_numbers[number[i]] > basis - 1:
                return False
        else:
            if int(number[i]) > basis - 1:
                return False

    return True


def convert_from_basis_b_to_10(number, b) -> int:
    hexa_dezimal_numbers = {
        'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15
    }

    count_result = 0
    check_valid = check_basis_with_number(number, b)

    if not check_valid:
        print(f"This is an invalid number with the basis {b}")
        return

    for i in range(len(number)):
        if number[i].isalpha():
            count_result += hexa_dezimal_numbers[number[i]] * (b ** (len(number) - 1 - i))
        else:
            count_result += int(number[i]) * (b ** (len(number) - 1 - i))

    return count_result


def convert_from_10_to_basis_b(number, to_b) -> str:
    hexa_dezimal_numbers_inverses = {
        10: 'A', 11: 'B', 12: 'C', 13: 'D', 14: 'E', 15: 'F'
    }

    number = int(number)
    result_array = []

    while number > 0:
        divide_rest = number % to_b
        result_array.insert(0, divide_rest)
        number //= to_b

    for i in range(len(result_array)):
        if result_array[i] > 9:
            result_array[i] = hexa_dezimal_numbers_inverses[result_array[i]]

    joined_string = ''.join(str(item) for item in result_array)

    return joined_string


def convert_bettwen_bases(number, from_b, to_b):
    
    decimal_number = convert_from_basis_b_to_10(number, from_b)
    if decimal_number is not None:
        result = convert_from_10_to_basis_b(decimal_number, to_b)
        return result
    else:
        return "Ungültige Eingabe!"
    

def main():
    
    while True:
        print("###############################")
        print("Welcome to Abu Salehs Converter")
        print("1. Convert a number from basis 10 to basis b")
        print("2. Convert a number from basis b to basis 10")
        print("3. Convert a number between any two bases")
        print("Q for quit")
        choise = input("Enter please your choise: ")
        if choise == '1':
            number = input("Enter please the number: ")
            basis = int(input("Please enter the basis: "))
            print(convert_from_10_to_basis_b(number, basis))
            break
            
        elif choise == '2':
            number = input("Enter please the number: ")
            basis = int(input("Please enter the basis: "))
            print(convert_from_basis_b_to_10(number , basis))
            break
        
        elif choise == '3':
            number = input("Enter please the number: ")
            from_basis = int(input("Please enter the from basis: "))
            to_basis = int(input("Please enter the to basis: "))
            print(convert_bettwen_bases(number, from_basis, to_basis))
            break
            
        elif choise.upper() == 'Q':
            print("Goodbye")
            break
            
        else:
            print("Invaild input !!!")
            
        print("###############################")        
    

if __name__ == "__main__":
    main()
