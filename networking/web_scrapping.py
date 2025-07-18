import requests
from bs4 import BeautifulSoup

import pandas as pd

URL = 'https://en.wikipedia.org/wiki/List_of_highest-grossing_films'

response = requests.get(URL)
soup = BeautifulSoup(response.content, 'html.parser')

table = soup.find('table', class_ = "wikitable plainrowheaders")

headers = table.find('tr').text
headers = [line.strip() for line in headers.split('\n') if line.strip()]

df = pd.DataFrame(columns=headers)


rows = table.find_all('tr')[1:]

#arr_str_arr = []

for row in rows:
    cells = row.find_all(['th' , 'td'])
    clean_row = []
    #delete all tje sups
    for cell in cells:
        for sup in cell.find_all('sup'):
            sup.decompose()
        clean_row.append(cell.get_text(strip=True))
    df.loc[len(df)] = clean_row
        
    #print(cells)
    #arr_str_arr.append([element.get_text().strip() for element in cells])
    #df.loc[len(df)] = [element.get_text().strip() for element in cells]


#print(df.to_string(index=False))

print(df.to_string(index=False))
