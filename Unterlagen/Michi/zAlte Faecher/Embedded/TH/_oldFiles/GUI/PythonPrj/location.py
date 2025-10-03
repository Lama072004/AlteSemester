import requests

URL = "https://nominatim.openstreetmap.org/search?format=json&q="

def getLocation(address):
    """determines the location"""
    r = requests.get(URL + address)
    print(__name__)
    return r.json()

