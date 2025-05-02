####TODO####
# Digital Clock #
# Abu Saleh #

from tkinter import Label, Tk
import time

def digital_clock(): 
   time_live = time.strftime("%H:%M:%S")
   label.config(text=time_live) 
   label.after(200, digital_clock)

app_window = Tk()
app_window.title("Digital Clock")
app_window.geometry("782x300")
app_window.resizable(1,1)

text_font= ("Boulder", 68, 'bold')
background = "#f2e750"
foreground= "#363529"
border_width = 25

label = Label(app_window, font=text_font, bg=background, fg=foreground, bd=border_width) 
label.grid(row=0, column=1)


digital_clock()
app_window.mainloop()
