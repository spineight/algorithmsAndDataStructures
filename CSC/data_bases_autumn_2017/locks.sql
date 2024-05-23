-- неявные блокировки
CREATE TABLE T(value INT);

-- Смотрим на блокировки
select locktype, relation::regclass, mode, granted from pg_locks;


-- RowExclusiveLock
BEGIN;
INSERT INTO T(value) VALUES (1), (2);


-- AccessExclusiveLock
BEGIN;
DROP TABLE T;


-- AccessShareLock
BEGIN;
SELECT * FROM T;




-- явные блокировки таблицы
-- Заблокируем таблицу от изменений
BEGIN;
LOCK TABLE T IN SHARE MODE;
SELECT sum(value) FROM T;

-- Важные неявные режимы
-- Режим            Требуется при                       Конфликтует с
-- ACCESS SHARE     SELECT                              ACCESS EXCLUSIVE
-- ROW SHARE        SELECT FOR UPDATE, SELECT FOR SHARE EXCLUSIVE, ACCESS EXCLUSIVE
-- ROW EXCLUSIVE    INSERT, UPDATE, DELETE              SHARE, SHARE ROW EXCLUSIVE, EXCLUSIVE, ACCESS EXCLUSIVE
-- ACCESS EXCLUSIVE DROP TABLE                          со всеми


BEGIN;
INSERT INTO T(value) VALUES (3);

-- Блокировки строк
-- FOR UPDATE/FOR NO KEY UPDATE -- автоматически выдаются при DELETE/UPDATE
-- Можно потребовать указав после SELECT
SELECT * FROM T WHERE value=2 FOR SHARE;



-- Рекомендательные блокировки на уровне приложения
pg_advisory_lock(42);

pg_advisory_lock_xact(239);