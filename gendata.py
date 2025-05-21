import random
import pandas as pd


countries = ["Россия", "Германия", "Англия", "Испания", "Италия"]

clubs = {
    "Россия": [("Зенит", "Санкт-Петербург"), ("Спартак", "Москва"), ("ЦСКА", "Москва")],
    "Германия": [("Бавария", "Мюнхен"), ("Боруссия", "Дортмунд"), ("Лейпциг", "Лейпциг")],
    "Англия": [("Манчестер Сити", "Манчестер"), ("Арсенал", "Лондон"), ("Челси", "Лондон")],
    "Испания": [("Реал Мадрид", "Мадрид"), ("Барселона", "Барселона"), ("Атлетико", "Мадрид")],
    "Италия": [("Ювентус", "Турин"), ("Милан", "Милан"), ("Интер", "Милан")]
}

trainers = {
    "Зенит" : "Семак Сергей Богданович", 
    "Спартак" : "Деян Станкович", 
    "ЦСКА" : "Марко Николич", 
    "Бавария" : "Венсан Компани",
    "Боруссия" : "Нико Ковач",
    "Лейпциг" : "Жолт Лев",
    "Манчестер Сити" : "Пеп Гвардиола", 
    "Арсенал" : "Микель Артета",
    "Челси" : "Энцо Мареска",
    "Реал Мадрид" : "Карло Анчелотти",
    "Барселона" : "Ханс‑Дитер Флик",
    "Атлетико" : "Диего Симеоне",
    "Ювентус" : "Игор Тудор",
    "Милан" : "Сержиу Консейсан",
    "Интер" : " Симоне Индзаги"
}


sizes = [100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000]


def generate_teams(n):
    teams = []
    for _ in range(n):
        country = random.choice(countries)
        club, city = random.choice(clubs[country])
        year = random.randint(2000, 2025)
        trainer = trainers[club]
        points = random.randint(0, 100)
        team = {
            "country": country,
            "club": club,
            "city": city,
            "year": year,
            "trainer": trainer,
            "points" : points
        }
        teams.append(team)
    return teams

#print(generate_teams(3))

def saveCSV(data, filename):
    df = pd.DataFrame(data)
    file_path = f"/home/install/pm1_lab/datasets/{filename}"

    df.to_csv(file_path, index=False)

for i in sizes:
    data = generate_teams(i)
    filename = f"dataset_{i}.csv"
    saveCSV(data, filename)