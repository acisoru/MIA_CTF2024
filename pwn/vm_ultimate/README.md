# Ultimate vm (PWN)
### Сложность
Medium
### Информация
```
Мы попробовали разработать собственную виртуальную машину. Можешь проверить, насколько она безопасна?

nc IP 1777
```
### Запуск 
```sh
cd deploy
docker-compose up --build -d
```

### Выдать учатникам
Содержимое папки public: архив, исполняемый файл и IP:PORT сервера

### Решение 

В командах, направленных на действия с регистрами виртуалки есть уязвимость - отсутствие проверки на отрицательное значение регистра. Передав команду с отрицательным регистром, мы можем модифицировать значения на стеке. С помощью это уязвимости получаем все лики, затем переписываем data pointer нашей вм и записываем rop на стеке с помощью in.

sploit.py

### Флаг
miactf{y0u_mu57_pr3v3n7_l0w_b0und_00b}
