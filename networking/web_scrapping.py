import requests
from bs4 import BeautifulSoup

URL = 'https://en.wikipedia.org/wiki/List_of_highest-grossing_films'

response = requests.get(URL)
soup = BeautifulSoup(response.content, 'html.parser')

table_2 = soup.find('table', class_ = "wikitable plainrowheaders")

colunms = table_2.find('tr').text
colunms = [line.strip() for line in colunms.split('\n') if line.strip()]

print(type(colunms))
print(colunms)
