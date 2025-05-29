import tkinter as tk

# Global variable to store the current calculation
calculation = ""

def add_to_calculation(symbol):
    """Add a symbol to the calculation string and update the display."""
    global calculation
    calculation += str(symbol)
    text_result.delete(1.0, "end")
    text_result.insert(1.0, calculation)

def evaluate_calculation():
    """Evaluate the current calculation and display the result."""
    global calculation
    try:
        calculation = str(eval(calculation))
        text_result.delete(1.0, "end")
        text_result.insert(1.0, calculation)
    except:
        clear_field()
        text_result.insert(1.0, "Error")

def clear_field():
    """Clear the calculation string and the display."""
    global calculation
    calculation = ""
    text_result.delete(1.0, "end")

# Initialize the main application window
root = tk.Tk()
root.geometry("600x735")
root.title("Beautiful Calculator")
root.configure(bg="#F5F5F5")  # Light gray background

# Text box to display the calculation and result
text_result = tk.Text(root, height=2, width=16, font=("Arial", 24), bg="white", fg="black", bd=0, padx=10, pady=10)
text_result.grid(columnspan=5, pady=20)

# Button style parameters
button_style = {
    "font": ("Arial", 14),
    "width": 5,
    "height": 2,
    "bd": 0,
    "relief": "flat",
}

# Number buttons
number_bg = "#E3F2FD"
number_fg = "black"
number_active = "#BBDEFB"

btn_1 = tk.Button(root, text="1", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(1))
btn_1.grid(row=2, column=1, padx=5, pady=5)

btn_2 = tk.Button(root, text="2", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(2))
btn_2.grid(row=2, column=2, padx=5, pady=5)

btn_3 = tk.Button(root, text="3", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(3))
btn_3.grid(row=2, column=3, padx=5, pady=5)

btn_4 = tk.Button(root, text="4", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(4))
btn_4.grid(row=3, column=1, padx=5, pady=5)

btn_5 = tk.Button(root, text="5", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(5))
btn_5.grid(row=3, column=2, padx=5, pady=5)

btn_6 = tk.Button(root, text="6", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(6))
btn_6.grid(row=3, column=3, padx=5, pady=5)

btn_7 = tk.Button(root, text="7", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(7))
btn_7.grid(row=4, column=1, padx=5, pady=5)

btn_8 = tk.Button(root, text="8", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(8))
btn_8.grid(row=4, column=2, padx=5, pady=5)

btn_9 = tk.Button(root, text="9", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(9))
btn_9.grid(row=4, column=3, padx=5, pady=5)

btn_0 = tk.Button(root, text="0", bg=number_bg, fg=number_fg, activebackground=number_active, **button_style, command=lambda: add_to_calculation(0))
btn_0.grid(row=5, column=2, padx=5, pady=5)

# Operator buttons
operator_bg = "#B0BEC5"
operator_fg = "white"
operator_active = "#90A4AE"

btn_plus = tk.Button(root, text="+", bg=operator_bg, fg=operator_fg, activebackground=operator_active, **button_style, command=lambda: add_to_calculation('+'))
btn_plus.grid(row=2, column=4, padx=5, pady=5)

btn_minus = tk.Button(root, text="-", bg=operator_bg, fg=operator_fg, activebackground=operator_active, **button_style, command=lambda: add_to_calculation('-'))
btn_minus.grid(row=3, column=4, padx=5, pady=5)

btn_mul = tk.Button(root, text="*", bg=operator_bg, fg=operator_fg, activebackground=operator_active, **button_style, command=lambda: add_to_calculation('*'))
btn_mul.grid(row=4, column=4, padx=5, pady=5)

btn_div = tk.Button(root, text="/", bg=operator_bg, fg=operator_fg, activebackground=operator_active, **button_style, command=lambda: add_to_calculation('/'))
btn_div.grid(row=5, column=4, padx=5, pady=5)

# Special buttons
btn_eqaul = tk.Button(root, text="=", bg="#66BB6A", fg="white", activebackground="#388E3C", width=12, height=2, font=("Arial", 14), command=evaluate_calculation)
btn_eqaul.grid(row=6, column=1, columnspan=2, padx=5, pady=5)

btn_clear = tk.Button(root, text="C", bg="#EF5350", fg="white", activebackground="#D32F2F", width=12, height=2, font=("Arial", 14), command=clear_field)
btn_clear.grid(row=6, column=3, columnspan=2, padx=5, pady=5)

# Run the main application loop
root.mainloop()

