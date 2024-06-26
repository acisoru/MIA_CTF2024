# Easy points

### Сложность
easy

### Информация
Предлагаю тебе простенькую задачку. Решишь?

### Выдать участникам
Все, что внутри папки public: encrypt.py и encrypt.txt

### Решение
Посмотрим, как преобразуются символы флага. Есть сид, который выбирается случайным образом от 1 до 1337. Далее выбирается "случайным" образом из списка primes какие-то простые числа в количестве трех штук, и в качестве результата отдаются остатки от деления символа флага на выбранные простые число. Вспомним, что если используется фукция random.seed(), то результаты randint являются строго детерминированными. План восстановления флага следующий: 

1. Перебираем сид от 1 до 1337
2. Получаем индексы выбранных простых чисел
3. С помощью китайской теоремы об остатках собираем ответ
4. Формат флага miactf{. Мы можем его использовать, чтобы определить, когда был найден нужный сид.

Напомним, как формулируется китайская теорема остатках: если натуральные числа $a_1, a_2,\ldots, a_n$ попарно взаимно просты, то система сравнений $$ x \equiv r_1 \mod a_1 \\ x \equiv r_2 \mod a_2, \\ \ldots \\ x \equiv r_n \mod a_n$$
имеет единственно решение по модулю $a_1 \cdot a_2 \cdot \ldots \cdots a_n$. Минимальное произведение из списка простых чисел $5 \cdot 7 \cdot 11 = 385 > 255$, то есть, мы получим корректные числа, которые затем можно перевести в печатаемые символы.

```
sage sploit.sage
```

### Флаг
miactf{I_l0v3_CRT_S0_much}