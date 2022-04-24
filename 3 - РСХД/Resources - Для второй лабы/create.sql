--Объявление всех таблиц БД

--Кварталы
CREATE TABLE Квартал
(
    ID       SERIAL PRIMARY KEY,
    Название TEXT NOT NULL
);

--Соседние кварталы
CREATE TABLE Квартал_Квартал
(
    ID          SERIAL PRIMARY KEY,
    Квартал1_ID INTEGER REFERENCES Квартал ON DELETE CASCADE ON UPDATE CASCADE NOT NULL,
    Квартал2_ID INTEGER REFERENCES Квартал ON DELETE CASCADE ON UPDATE CASCADE NOT NULL check (Квартал2_ID != Квартал1_ID)
);

--Улицы
CREATE TABLE Улица
(
    ID         SERIAL PRIMARY KEY,
    Имя        TEXT                                                           NOT NULL,
    Квартал_ID INTEGER REFERENCES Квартал ON DELETE CASCADE ON UPDATE CASCADE NOT NULL
);