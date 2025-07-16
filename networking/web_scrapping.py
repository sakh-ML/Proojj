import requests
URL = "https://en.wikipedia.org/wiki/List_of_highest-grossing_films"

respone = requests.get(URL)

html_web_page_code = respone.text
print(html_web_page_code)


