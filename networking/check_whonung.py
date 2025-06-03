import requests
from bs4 import BeautifulSoup
import time
from plyer import notification

URL = 'https://example.com/wohnungen'
CHECK_INTERVAL = 300  # alle 5 Minuten

def get_offers():
    response = requests.get(URL)
    soup = BeautifulSoup(response.text, 'html.parser')

    # Hier musst du anpassen, was genau du suchst!
    offers = soup.find_all('div', class_='wohnung')  # Beispiel
    return [offer.text.strip() for offer in offers]

def notify(title, message):
    notification.notify(
        title=title,
        message=message,
        timeout=10
    )

def main():
    print("Starte Wohnungsüberwachung...")
    previous_offers = get_offers()

    while True:
        time.sleep(CHECK_INTERVAL)
        current_offers = get_offers()

        if current_offers != previous_offers:
            notify("Neue Wohnung!", "Es gibt neue Wohnungsangebote!")
            print("Neue Angebote gefunden!")
            previous_offers = current_offers
        else:
            print("Keine Änderungen...")

if __name__ == '__main__':
    main()

