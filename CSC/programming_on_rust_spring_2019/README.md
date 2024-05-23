https://github.com/matklad
https://github.com/matklad/rust-course

https://compscicenter.ru/courses/rustprogramming/2019-spring/


181,395 views  Feb 16, 2019  Программирование на Rust (весна 2019)
Первая лекция курса «Программирование на Rust» (весна 2019).
Преподаватель — Алексей Александрович Кладов.
Страница лекции на сайте CSC: http://bit.do/csc-rust-1
Ссылка на материалы: https://github.com/matklad/rust-course
Все лекции курса: http://bit.ly/2QfWama

### 1. Введение (Программирование на Rust)
https://youtu.be/Oy_VYovfWyo?si=LMWtubx5732cH7PD
22:02 - Hello, World
24:50 - Hello, Cargo
25:35 - Основные Типы
25:58 --- Целые числа
29:13 --- Арифметика
36:05 --- Переполнение в С++
40:10 --- Польза UB (Undefined Behavior)
43:01 --- UB в Rust
44:17 --- Арифметика в стиле С++
46:40 --- Числа с плавающей точкой (IEEE-754)
48:17 --- Логический тип
48:57 --- Кортежи
53:00 --- Массивы
54:28 --- Ссылки
55:36 --- Указатели
56:27 --- Box
57:34 --- Стек
58:56 --- Куча
1:06:07 --- Как узнать, когда можно делать free?
1:11:17 --- Присваивание (move)
1:14:11 --- drop
1:15:30 --- Аффинные типы
1:17:46 --- Обычные типы
1:18:43 --- Аффинные типы
1:21:17 --- Drop flags
1:21:34 --- Vec
1:29:09 --- Виды присваивания
1:33:22 --- Представление обьектов в памяти
1:36:17 --- Rust/C++

### 2. Время жизни, ADT. Программирование на Rust (весна 2019)
https://youtu.be/WV-m7xRlXMs?si=wjDBJyueteU6GaL7
@qewolf
@qewolf
3 years ago
00:00:37 - Ссылки
00:04:40 - Move
00:06:38 - Copy
00:11:20 - Жизнь без ссылок
00:13:37 - Время жизни ссылки
00:14:57 - Ссылки на значения
00:16:57 - Именовынные время жизни
00:19:36 - Ссылки на подобьекты
00:21:38 - Что такое 'a?
00:24:16 - Заморозка
00:28:16 - mut
00:30:02 - Shared ^ Mutable
00:33:50 - Ссылки в С++ и Rust
00:39:44 - Итого
00:47:04 - Выражения
00:48:17 - Блоки
00:49:38 - Инициализация блоком
00:51:25 - if
00:54:08 - while
00:54:45 - break и continue
00:55:07 - loop
00:58:40 - Гарантированная инициализация
01:00:26 - !
01:01:40 - panic!()
01:03:08 - break со значением
01:03:26 - for
01:04:01 - ranges
01:04:55 - Ещё раз о ;
01:06:00 - Два слова о функциях
01:08:32 - Алгебраические типы данных
01:08:42 - Структуры
01:09:48 - Методы
01:12:50 - Ассоциированные функции
01:13:53 - Deref
01:14:49 - Структуры-кортежи
01:16:44 - Паттерн newtype
01:19:10 - Zero Sized Types (ZST)
01:20:30 - Type Tags
01:21:14 - Виды структур
01:21:28 - Dynamically Sized Types (DST)
01:23:35 - Slices
01:26:56 - Enums
01:32:12 - Полезные enumы
01:34:39 - Newtype Variant
01:35:25 - Void
01:37:06 - Result
01:38:40 - Представление в памяти 


### 3. Трейты. Программирование на Rust (весна 2019)
https://youtu.be/m9lH5wIV3rQ?si=1Aoliw5eINd2NPfK
@qewolf
@qewolf
3 years ago
00:00:15 - Сопоставления с Образцом
00:04:09 - Range Patterns
00:05:32 - Binding Modes
00:08:22 - Сахар
00:09:10 - Всё -- Паттерны
00:10:00 - Параметричский Полиморфизм
00:12:00 - Параметризованные функции
00:13:08 - Traits
00:16:03 - impl MyTrait for YourType
00:17:36 - Return type polymorphism
00:19:24 - Static Dispatch
00:20:30 - Мономорфизация
00:22:56 - Дженерики в Java
00:25:55 - Мономорфизация
00:28:23 - Inlining
00:32:42 - Мономорфизация vs. Стирание Типа
00:38:17 - Трейты в Rust vs. Шаблоны в С++
00:38:40 - Проверка типов
00:40:32 - Swift Generics
00:41:02 - Fully Qualified Syntax
00:45:53 - Where clauses
00:46:41 - "Наследование" трейтов
00:48:46 - Полезные Трейты
00:49:03 - Default
00:52:21 - Clone
00:54:57 - Copy
00:56:48 - Derive
01:00:17 - PartialEq, Eq
01:05:34 - PartialOrd, Ord
01:12:01 - std::hash::Hash
01:18:10 - Drop
01:24:01 - std::mem Tricks
01:27:49 - Эмуляция Линейных Типов
01:30:52 - Порядок Drop
01:32:10 - dropck
01:34:48 - Deref
01:39:03 - DerefMut
01:39:13 - std::ops::Index / IndexMut
01:41:24 - Мораль 

### 4. Модули. Программирование на Rust (весна 2019)
https://youtu.be/U6VN5g57oAM?si=Vwhlvadw2r8cEUAJ

### 5. Функции и итераторы. Программирование на Rust (весна 2019)
https://youtu.be/HNCzUA1TFbo?si=5jZMIcGBPbZTAvax

### 6. Управление ошибками. Программирование на Rust (весна 2019)
https://youtu.be/57M2hUnnLCE?si=sNUkgz1XM90ZYv9n

### 7. Объекты, строки. Программирование на Rust (весна 2019)
https://youtu.be/XUKbpnf2bR4?si=ZVZLR5ffYQ0fFUvs

### 8. Время жизни II (Программирование на Rust)
https://youtu.be/lQyYAmjblt0?si=M1usm5g9z1hW-Nar

### 9. Умные Указатели, static. Программирование на Rust (весна 2019)
https://youtu.be/32cSLAe4aOw?si=uobwY6o7i4MNLd2V

### 10. Многопоточность. Программирование на Rust (весна 2019).
https://youtu.be/EDlU2UjljrY?si=2JP4A7uGDGPfN2Cg

### 11. unsafe. Программирование на Rust (весна 2019).
https://youtu.be/vz1_aRlF2TI?si=md1j269MRrC1nqZu

### 12. Коллекции. Программирование на Rust (весна 2019)
https://youtu.be/C-BpSwZOnNE?si=chXk8jjtHDkIsfP5

### 13. Макросы. Программирование на Rust (весна 2019)
