https://www.youtube.com/@ivansorokin7672

### Advanced C++ (лекция 1): передача параметров по значению, RVO, NRVO
https://youtu.be/FJgeHwAlv6g?si=pgTNegArMEf5IZ3b
Лекция 1. 3 сентября 2022, передача параметров по значению, RVO, NRVO
Плейлист:    • Advanced C++ (осень 2022)

00:00 Приветствие
06:13 Мотивация
26:14  Где копирования не делаются
32:10 Передача параметров по значению
47:23 (повторение) lvalue и rvalue
57:18 Возврат структур
1:07:45 Return Value Optimization (RVO)
1:13:57  Named Return Value Optimization (NRVO)

### Advanced C++ (лекция 2): rvalue-ссылки, move-семантика, xvalue, copy elision, lifetime extension
https://youtu.be/XmC7mNQF_K8?si=Uc1hgDHEjF2GYWV5
Лекция 2. 3 сентября 2022, rvalue-ссылки, move-семантика, xvalue, copy elision, lifetime extension.
Плейлист:    • Advanced C++ (осень 2022)

00:00 Обзор предыдущей части
01:44 Операция move
17:11 rvalue-ссылки
26:02 Функция std::move
36:30 Именованные переменные всегда lvalue
39:50 Обсуждение, что две перегрузки (T const&) и (T&&) могу быть заменены на функцию принимающую по значению (T).
50:27 Обсуждение почему не надо пытаться возвращать rvalue-ссылку, когда необходимо вернуть новое значение
58:28 Пессимизирующий move
1:02:44 xvalue
1:12:08 Copy elision при конструировании объектов
1:20:03 lifetime extension
1:29:50 Ответы на вопросы

### Advanced C++ (лекция 3): intrusive контейнеры
https://youtu.be/arcYfeOe1_0?si=c0vkd1LBkCfft4uv
447 views  Oct 15, 2022
Лекция 3. 10 сентября 2022, intrusive контейнеры.
Плейлист:    • Advanced C++ (осень 2022)

00:00 Приветствие
01:34 Наблюдение про двусвязные списки
05:43 Описание задачи и попытка решения
40:17 C-style попытка вынести общий код
50:18 Использование базовых классов
1:01:23 Упоминание про P0406
1:04:02 Упоминание про Boost.Intrusive
1:07:17 Сравнение intrusive и не-intrusive контейнеров
1:15:22 Упоминание про Boost.MultiIndex

Ссылки:
Ссылки:
Tough times on the road to Starcraft https://www.codeofhonor.com/blog/tough-times-on-the-road-to-starcraft
Avoiding game crashes related to linked lists https://www.codeofhonor.com/blog/avoiding-game-crashes-related-to-linked-lists
Intrusive linked lists https://www.data-structures-in-practice.com/intrusive-linked-lists/
P0406 Intrusive Containers https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0406r1.html
Boost.Intrusive https://www.boost.org/doc/libs/1_80_0/doc/html/intrusive.html
Сравнение intrusive и не-intrusive контейнеров https://www.boost.org/doc/libs/1_80_0/doc/html/intrusive/intrusive_vs_nontrusive.html
Boost.MultiIndex https://www.boost.org/doc/libs/1_80_0/libs/multi_index/doc/index.html

### Advanced C++ (лекция 4): shared_ptr
https://youtu.be/zeFDf2BC1iU?si=RqA4Kdvcwn6v1PVb
Лекция 4. 10 сентября 2022, shared_ptr.
Плейлист:    • Advanced C++ (осень 2022)

00:00 Приветствие
01:40 Умные указатели
9:40 Custom deleter'ы
11:26 Aliasing-конструктор
21:00 *_pointer_cast
23:20 std::make_shared
27:41 std::weak_ptr
36:40 Herb Sutter's favorite 10-liner
47:21 Проблема unbounded-роста кеша
53:13 Разбор решения
1:03:47 Улучшенное решение
1:14:15 Разделение счётчиков ссылок
1:18:57 std::enable_shared_from_this

### [s3 | 2022] Advanced C++, Лев Довжик, практика 2
Практика по std::shared_ptr
https://www.youtube.com/live/z-0mJtMWhlc?si=-GHvfTc3ySojlurQ

### Advanced C++ (Лекция 5): perfect forwarding, universal ссылки, variadic шаблоны
https://youtu.be/TdEr9J21ie0?si=Txo4W_E_nw9W0hUu
Лекция 5. 1 октября 2022, perfect forwarding, universal ссылки, правило схлопывания ссылок, variadic шаблоны.
Плейлист:    • Advanced C++ (осень 2022)

00:00 Приветствие
2:00 Мотивация
4:51 Определение forwarding'а
6:38 Почему просто шаблонного параметра T не достаточно
14:20 Почему не подходит T const&
15:08 Почему не подходит T&
15:44 Perfect forwarding
17:58 Правило схлопывания ссылок
23:18 Правила вывода типов для T&&
31:51 Пример perfect forwarding'а.
37:49 std::forward
54:42 Variadic шаблоны

### Advanced C++ (Лекция 6): возврат значения при perfect forwarding'е, decltype, auto, nullptr
https://youtu.be/4vwzNvfgirk?si=8GQUjyBun9cy8aRo
Лекция 6. 1 октября 2022, возврат значения при perfect forwarding'е, decltype, std::declval, unevaluated contexts, trailing-return тип, auto, decltype(auto), nullptr.
Плейлист:    • Advanced C++ (осень 2022)

0:00 Замечание о правиле схлопывания ссылок с предыдущей пары
3:20 Задача возврата значения при perfect forwarding'е
5:39 decltype
19:56 std::declval
22:26 unevaluated context
25:44 отступление про квалификацию return-типов при out-of-class определении функции
15:35 trailing return тип
35:02 auto
44:36 decltype(auto)
46:46 nullptr
58:40 ответ на вопрос: "сделать структуру фиксированного размера и без полей"
1:08:59 как написать функцию принимающую rvalue любого типа
1:14:00 написать функцию форвардящую возвращаемое значение, сначала сохранив её в локальную переменную https://quuxplusone.github.io/blog/2018/09/25/perfect-backwarding/

### Advanced C++ (лекция 7): статический и динамический полиморфизм, анонимные функции
https://youtu.be/UlJXMfP0Ln4?si=XY-RnnBfopfOalRQ
Лекция 7. 8 октября 2022, статический и динамический полиморфизм, анонимные функции
Плейлист:    • Advanced C++ (осень 2022)

0:00 Приветствие, проверка связи
1:17 Пример сортировки со статически и динамически переданными компараторами
23:47 Определение статического и динамического полиморфизма
33:48 Возможные оптимизации компилятора
1:07:01 Анонимные функции, мотивация
1:16:46 Захватываемые значения

### Advanced C++ (лекция 8): анонимные функции (продолжение), std::function, type erasure
https://youtu.be/VmwatinWqUE?si=aws5nht_K9ZvdY1E
Лекция 8. 8 октября 2022, анонимные функции (продолжение), std::function, type erasure
Плейлист:    • Advanced C++ (осень 2022)

0:00 Продолжаем
0:58 Тип возвращаемого значения
2:41 mutable
4:51 Шаблоны
18:25 Конструкторы, операторы, конверсии
32:33 std::function, мотивация
40:17 обсуждаем как std::function устроен внутри

### Advanced C++ (лекция 9): сигналы, реентерабельность
https://youtu.be/tYAR_lnkPZs?si=l-8rWXBobxRbIHd6
Лекция 9. 15 октября 2022, сигналы, реентерабельность
Плейлист:    • Advanced C++ (осень 2022)

0:00 Приветствие
2:55 Мотивация
15:25 Пытаемся написать свой signal
18:55 Добавляем disconnect
30:58 Проблема, что vector при удалении сдвигает элементы
34:51 Проблема disconnect'а внутри слота
1:00:34 Попытка решения с помощью копирования
1:08:58 Попытка помечать слоты как пустые и потом почищать в конце emit'а
1:20:15 Рекурсивный emit
1:24:45 Удаление сигнала внутри emit
1:34:53 Выводы
1:39:39 Поняние reentrancy
1:48:55 Ответы на вопросы

### [s3 | 2022] Advanced C++, Денис Воркожоков, практика 3
https://youtu.be/T8QM7GPcf9U?si=d6j3ukvacMzry2rC
Практика по std::function

### Advanced C++ (лекция 10): обработка ошибок
https://youtu.be/U9g7_M0TWgg?si=YWLpxnBfrsFp6DMs
Advanced C++ (лекция 10): обработка ошибок

### Advanced C++ (лекция 11): обработка ошибок (продолжение)
https://youtu.be/JTAzl4Uzyf8?si=qjQ_V62CZQCXBFFE
Лекция 11. 22 октября 2022, обработка ошибок (продолжение)

### Advanced C++ (лекция 12): optional, noexcept, тривиальные операции
https://youtu.be/y1W5WF0qVv0?si=M13WokiS4-A_fX5w
Лекция 12. 29 октября 2022, optional, noexcept, тривиальные операции

### Advanced C++ (лекция 13): optional, SFINAE-friendly функции, условно-explicit конструкторы
https://youtu.be/bwTvsaTG3To?si=neanLcBWnO_cmEgh
Лекция 13. 29 октября 2022, optional, SFINAE-friendly функции, условно-explicit конструкторы

### Advanced C++ (лекция 14): constexpr
https://youtu.be/sufLv9O3KSA?si=mKTr55EFZBFEYlLy
Лекция 14. 5 ноября 2022, constexpr

### [s3 | 2022] Advanced C++, Лев Довжик, практика 4
https://www.youtube.com/live/fBDUkzWsUyc?si=Ft6O4iQQeBj6i5fx
Практика по std::optional

### Advanced C++ (лекция 15): constexpr (продолжение), variant
https://youtu.be/w0ZYV7SnkCw?si=EbaY7HDKO_OUTvK2
Лекция 15. 12 ноября 2022, constexpr (продолжение), variant

### Advanced C++ (лекция 16): variant (продолжение)
https://youtu.be/wjBG2iM0mIk?si=uq916HajqLTwzdOe
Лекция 16. 12 ноября 2022, variant (продолжение)

### Advanced C++ (лекция 17): концепты
https://youtu.be/nVm5Ek6tZsE?si=z0F55sWxRTznGXkH
Advanced C++ (лекция 17): концепты

### Advanced C++ (лекция 18): концепты (часть 2)
https://youtu.be/25U6btXHrM4?si=bStKzG-4L-hQUI6r
Advanced C++ (лекция 18): концепты (часть 2)

### Advanced C++ (лекция 19): кодировки
https://youtu.be/0ylXOa5Z7SE?si=C3NJCEGH0K2hGiWQ

### [s3 | 2022] Advanced C++, Денис Воркожоков, практика 5
https://youtu.be/Pp_VfjhkKaM?si=MU4f3xny_JZSr_ZT
Практика по сигналам
Лекция 13. 26 ноября 2022, кодировки

### Advanced C++ (лекция 20): многопоточность, std::thread, std::mutex
https://youtu.be/vohtoYKvc8A?si=099tnlI9wfG4rhl1
Лекция 20. 3 декабря 2022, многопоточность, std::thread, std::mutex

### Advanced C++ (лекция 21): многопоточность, std::condition_variable
https://youtu.be/sj3dUN9IVXo?si=Ea38RMjjO5KmZeau
Лекция 21. 3 декабря 2022, многопоточность, std::condition_variable

### Advanced C++ (лекция 22): многопоточность, std::atomic
https://youtu.be/dQfXqa6iGKg?si=aRUBC0gGvQUPOAys
Лекция 22. 10 декабря 2022, многопоточность, std::atomic

### Advanced C++ (лекция 23): многопоточность, std::atomic (продолжение)
https://youtu.be/5i11FI_GwYU?si=iqQ50SstGXlDoVZP
Лекция 23. 3 декабря 2022, многопоточность, std::atomic

### Advanced C++ (лекция 24): многопоточность, relaxed-atomic'и
Лекция 24. 10 декабря 2022, многопоточность, relaxed-atomic'и
https://youtu.be/d2pHhX7dSyg?si=a4qxi5DdBZR7TfQf

### Advanced C++ (лекция 25): многопоточность
https://youtu.be/qK8eXiom9kU?si=f41xCgW66Qnnfr2J
Лекция 25. 10 декабря 2022, многопоточность

### Advanced C++ (лекция 26): многопоточность, cancellation, асинхронные операции
https://youtu.be/8RTw9pg4Isc?si=3yJFnBK0qgKa1c-K
Лекция 26. 17 декабря 2022, многопоточность, cancellation, асинхронные операции

### Advanced C++ (лекция 27): введение в Qt
https://youtu.be/uCorj8Jpzfc?si=4ftDGjc8jhpMYO2i
Лекция 27. 17 декабря 2022, введение в Qt

### Advanced C++ (лекция 28): введение в Qt, рисуем фрактал Мандельброта
https://youtu.be/tBkn4MaMJVI?si=aCeIwa3_rVr3U6sA
Лекция 28. 17 декабря 2022, введение в Qt, рисуем фрактал Мандельброта

### Advanced C++ (лекция 29): C++20 модули
https://youtu.be/LrqTCdLD0cU?si=U6FB_Ndpj0bCumRy
Лекция 29. 24 декабря 2022, C++20 модули

### Advanced C++ (лекция 30): кодировки (продолжение)
https://youtu.be/9uMkY1cSI_M?si=OEecYEHFIX8J3cJM
Лекция 30. 24 декабря 2022, кодировки (продолжение лекции 19    • Advanced C++ (лекция 19): кодировки  )