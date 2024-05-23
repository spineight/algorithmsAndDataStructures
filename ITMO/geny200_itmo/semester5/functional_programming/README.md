### 1 lecture - Type theory + FP | Введение и лямбда исчисление
https://youtu.be/Zg27mo9tRZU?si=zftHCr0TxLb7as4v

### 2 lecture - Type theory + FP | Лямбда исчисление
https://youtu.be/oL9JnfiXLe0?si=qr99ZhoZ0l4B4Zgw

### 3 lecture - Functional programming | Введение в Haskell
https://youtu.be/PqoEG0_qi8U?si=lworeY1ywhCDTj9L
00:00 Организационные вопросы
06:34 Сборка проекта Haskell
21:44 Базовый синтаксис Haskell
56:23 List
1:13:44 let
1:15:57 where
1:17:55 if
1:18:51 guards
1:22:03 case
1:24:45 Higher of functions
1:27:28 Lambdas: anonymous fun
1:28:49 Polymorphism
1:40:58 Currying
1:55:26 Flip
1:56:27 Pattern matching
2:02:01 Расширения языка
2:11:55 $ (Function application)
2:15:17 . (Function composition)
2:19:02 List comprehension
2:20:16 Lazy evaluation
2:23:37 Expression graph
2:24:46 Lazy evaluation of graph
2:29:03 Weak head normal form
2:36:07 thunk
2:38:07 Time & Space
2:42:50 Infinite lists
2:44:14 Types + lazy evaluation
2:47:36 Classical lazy examples
2:48:47 End

### 4 lecture - Functional programming | Data types; Monoid, Functor, Applicative
https://youtu.be/nsdRDzDbdhE?si=i0zTSWscZcyD_SbH
00:00 Начало (lecture 3)
01:03 Custom types
04:39 ADT's
10:23 ADT's - enums
14:54 ADT's - structures
17:50 ADT's - parametric
29:21 ADT's - sum
38:12 ADT's - maybe
45:28 ADT's - either
50:51 ADT's - recursive
54:09 Record syntax
55:58 Record patterns and updates
58:42 Records and sum types
1:02:08 DuplicateRecordFields
1:03:58 RecordWildCards
1:07:29 newtype
1:13:29 Type classes
1:19:12 Eq
1:23:19 Ord
1:25:55 Num
1:28:04 Show
1:29:14 Read
1:30:42 Polymorphic examples
1:34:40 undefined
1:40:36 deriving
1:46:01 GeneralizedNewtypeDeriving
1:46:39 Modules cheatsheet
1:47:49 Links & questions
1:49:45 Lecture 4
1:50:30 Semigroups & Monoids
1:52:20 Semigroup instances
1:55:34 Monoid
1:58:51 foldr & foldl
2:06:11 Foldable
2:12:28 fmap
2:15:07 Functor
2:18:39 Maybe Functor
2:25:13 List Functor
2:25:55 Arrow Functor
2:28:56 Applicative Functors
2:31:48 Maybe Applicative
2:33:26 List Applicative
2:34:20 Arrow Applicative
2:35:22 Applicative laws
2:35:38 Applicative vs. Functor
2:37:05 Applicative style programming
2:41:15 questions

### 5 lecture - Functional programming | Monads; Alternative
https://youtu.be/h0-ajtlzM1Y?si=iVHw5zBjOsPKKaYa
00:00 Начало
00:54 Alternative
06:07 Traversable
12:28 Deriving
13:27 Type classes diagram
13:53 Q&A
17:53 Lecture 5 Monads
19:15 Typed holes
24:52 Type wildcards
25:59 Monads
39:01 Identity monad
40:36 Maybe monad
45:08 Maybe monad in practice
50:55 Either monad
53:40 Either monad in practice
56:40 Monad composition
1:00:18 List monad
1:04:33 Monad zen
1:13:27 Joinings monads
1:16:35 Make a monad
1:21:17 Functions of monads
1:22:56 Monads laws
1:25:54 Equational reasoning
1:27:33 Proving laws
1:29:20 End & List monad nondeterminism (task for hw)

### 1 practice - Functional programming | HW (lecture 4)
https://youtu.be/eWCPdzQq5Gw?si=nf7V8yRg4nRF9_Zn
00:00 Как проходят практики
03:43 Задание 1
07:10 Задание 2
11:54 Задание 3
14:18 Задание 4
16:07 Задание 5
21:34 Задание 5 (другой вариант)
23:58 Задание 5*
32:26 Задание 6
40:51 Задание 7
55:25 Задание 8 (1 попытка)
58:23 Задание 9
1:08:25 Задание 8 (2 попытка)
1:11:35 Задание 10
1:13:04 Торжественное завершение практики + Q&A

### 6 lecture - Functional programming | Monads; IO; do notation
https://youtu.be/Mf0g-xSV1I4?si=SWHjdfNf1QXKb3DB
00:00 Monads повторение Maybe, Either
20:45 Monad IO
21:10 getChar проблема грязной функции
24:40 getChar решение проблемы
34:39 IO
43:05 IO (real definition)
44:05 State# RealWorld
47:44 instance Monad IO
52:52 do notation
57:26 do as sequence of actions
58:36 do as monad bind
1:01:37 example how convert to do notation
1:03:33 return
1:05:56 let inside do
1:08:18 do without monads
1:09:24 do with partially applied functions
1:11:05 problem - lazy IO
1:15:35 lazy IO
1:19:38 how to live with lazy IO
1:22:05 unsafePerfomIO
1:26:52 why you shouldn't use unsafePerfomIO
1:28:03 ForeignFunctionInterface
1:30:35 mutable data in IO
1:31:12 mutable IO Arrays
1:31:55 IO Exceptions

### 2 practice - Functional programming | HW (lecture 5) Monoid
https://youtu.be/rfujn42ndA4?si=f3UW_--xVMeWE9L2
00:00 начало
00:10 задание 1
09:09 задание 2
12:02 задание 3
17:54 задание 4
22:52 задание 5
41:47 задание 7
50:06 задание 6
1:01:51 задание 8
1:09:49 Q&A

### 7 lecture - Functional programming | Trans Monads; Monads; IO;
https://youtu.be/VzNVwaWv17c?si=c2cx8R_iYD75vbWt
00:00 Q&A
01:01 IO Exceptions
07:07 More pattern guard (like do-notation)
08:56 String - наивная реализация
11:40 Text
12:55 ByteString
15:30 What to use? (String | Text | ByteString)
19:16 Monads as effects
20:36 Translation of effects
21:32 Composition of Reader and State (ReaderT and StateT)
23:52 Problem with composition of Monads
25:48 Maybe and IO (MaybeIO)
29:47 MaybeT
33:08 Ex. using MaybeT
40:37 ReaderT
44:41 ReaderT monad
46:48 Transformers table
50:05 IOT - does not exist (but but there is MonadIO)
52:44 Composition of Monads
57:32 Parser Combinators
58:34 MonadThrow
1:01:20 MonadError
1:04:06 mtl-style transformers
1:10:20 Constraints in Haskell
1:10:47 Recommended patterns
1:13:47 Anti-patterns
1:16:32 Custom Monad in mtl style
1:17:34 Other solutions
1:18:03 Something from Idris
1:19:14 End
1:20:10 Q&A

### 8 lecture - Functional programming | Performance and acceleration
https://youtu.be/4p1oJ_hswkE?si=jMJ4ek0Ia4R_LhBy

### 3 practice - Functional programming | part 1 | HW (lecture 5, 6, 7)
https://youtu.be/Yu9BB3SdKu4?si=h4oEiDcn1JNayGHd
00:00 Информация про коллоквиум
05:54 task 5 (sort)
13:08 Вопросы к аудитории
13:43 Обсуждение переноса практики

### 3 practice - Functional programming | part 2 | HW (lecture 5, 6, 7)
https://youtu.be/A_0LU0WcVgg?si=IPWKxVw7GHIif40k

### 9 lecture - Functional programming | Concurrency, Exceptions and parallelism
https://youtu.be/EQwgGDNcCvg?si=0xHoOMzVP73u4Ggu

### 4 practice - Functional programming | HW (lecture 8)
https://youtu.be/KUpvf0-wC38?si=KgZpjAjS_0Wa0WQP

### 10 lecture - Functional programming | Lens; Macros
https://youtu.be/ECfppbuKtJQ?si=o_UxeaLBn1mNKxs-

### 11 lecture - Functional programming | DSLs
https://youtu.be/5Qpy8qgiHEo?si=JZcAPFErJC-hvOqy

### 5 practice - Functional programming | HW (lecture 9, 10)
https://youtu.be/9-Xz8ZQ3hCE?si=uri7inIxpOHC5TzH


### 12 lecture - Functional programming | Kinds
https://youtu.be/cQzqgCzNNn0?si=j-vJ-kpgsZMR2_8g

### 6 practice - Functional programming | HW (lecture 11, 12)
https://youtu.be/S7r3xEFPgNk?si=Xmn3moPPTDKkaK5f

### 13 lecture - Functional programming | Comonad
https://youtu.be/AFStwQcRu7Q?si=TMZrb6vOS7eA8qzd