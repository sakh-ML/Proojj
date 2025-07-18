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


rows = table.find_all('tr')

arr_str_arr = []
for row in rows[1 : ]:
    cells = row.find_all(['th' , 'td'])
    arr_str_arr.append([element.get_text().strip() for element in cells])
    df.loc[len(df)] = [element.get_text().strip() for element in cells]


#print(df.to_string(index=False))

