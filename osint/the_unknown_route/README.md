# The Unknown Route | Easy | Osint

## Информация

> Сотрудникам отдела по поиску пропавших лайнеров поступило экстренное задание. Воздушное судно, выполнявшее регулярный маршрут, внезапно исчезло с радаров и совершило незапланированную посадку. Укажите IATA код места посадки в качестве флага.


## Выдать участинкам

Фотография из директории [public/](public/)

## Описание

Найти место экстренной посадки самолета при помощи инструментов поиска.

## Решение

Дана фотография лайнера компании JetBlue. На самолете имеется индификационный номер, позволяющий узнать историю полетов и экстренных посадок. Используя сервис `aviation-safety.ne` узнаем аэропорт экстренной посадки лайнера, который случился 21 сентября 2005 года в Лос-Анджелесе. В задании нужно указать IATA код аэропорта - это LAX.


## Флаг

miactf{lax}

