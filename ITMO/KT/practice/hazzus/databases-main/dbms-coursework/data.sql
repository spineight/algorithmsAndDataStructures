
-- добавляем настоятелей
insert into cleric (clericid, clericname, surname, patronymic, clerictype, gradeid, parishid)
values (0, 'Кирилл', 'Гундяев', 'Михайлович', true, 10, null),
       (1, 'Виктор', 'Полеткин', 'Моисеевич', true, 9, null),
       (2, 'Анатолий', 'Судаков', 'Владимирович', true, 9, null),
       (3, 'Василий', 'Козлов', 'Владимирович', true, 9, null),
       (4, 'Игорь', 'Пунин', 'Иванович', true, 9, null),
       (5, 'Михаил', 'Осяк', 'Александрович', true, 9, null),
       (6, 'Леонид', 'Сидоров', 'Михайлови', true, 8, null);

insert into mitropoly (mitropolyid, mitropolyname, maineparchyid, mitropolitid)
values (0, 'Московская', null, 0),
       (1, 'Самарская', null, 1),
       (2, 'Санкт-Петербургская', null, 2);

insert into eparchy (eparchyid, eparchyname, archiereiid, mitropolyid)
values (0, 'Московская (городская)', 0, 0),
       (1, 'Московская (областная)', 0, 0),
       (2, 'Cамарская', 1, 1),
       (3, 'Сызранская', 3, 1),
       (4, 'Выборгская', 4, 2),
       (5, 'Санкт-Петербургская', 2, 2),
       (6, 'Гатчинская', 5, 2);

-- обновим митрополии (что-бы главные было видно)
update mitropoly as m
set maineparchyid = tmp.eparchyid
from (values (0, 0),
             (1, 2),
             (2, 5)
      ) as tmp(mitropolyid, eparchyid)
where tmp.mitropolyid = m.mitropolyid;


insert into parish (parishid, parishname, address, parishtype, abbotid, eparchyid)
values (0, 'Христа Спасителя', 'Москва, ул. Волхонка, 15', 0, 0, 0), -- 0 храм
       (1, 'Рождество-Богородничий', 'с. Винновка, ул.Кремлевская, 10', 1, 1, 2), -- 1 собор
       (2, 'Казанский', 'Сызрань, пер. Достоевского, 17', 1, 3, 3),
       (3, 'Казанский', 'Санкт-Петербург, пл. Казанская, 2', 1, 2, 5),
       (4, 'Богородицы', 'Выборг, ул. Пушкина, 42', 2, 4, 4), -- 2 церковь
       (5, 'Иоанна-Богослова', 'с. Гатчина, ул. Лермонотова, 102', 2, 5, 6),
       (6, 'Иискаиевский', 'Санкт-Петербург, пл. Сенатаская, 1', 1, 6, 5);

-- обновим настоятелей
update cleric as c
set parishid = tmp.parishid
from (values (0, 0),
             (1, 1),
             (2, 3),
             (3, 2),
             (4, 4),
             (5, 5),
             (6, 6)
     ) as tmp(clericid, parishid)
where c.clericid = tmp.clericid;

-- добавим обычных служащих
insert into cleric (clericid, clericname, surname, patronymic, clerictype, gradeid, parishid)
values (7, 'Михаил', 'Сидоров', 'Валерьевич', true, 4, 0),
       (8, 'Николай', 'Валерьев', 'Петрович', false, 0, 2),
       (9, 'Микола', 'Квасов', 'Павлович', true, 1, 5),
       (10, 'Григорий', 'Умников', 'Андреевич', true, 7, 3);

--
insert into assembly (assemblyid, assemblyname, nextdate, description)
values (0, 'Священный Синод', '12.05.2023', 'Выбор патриарха, иерархические решения'),
       (1, 'Поместный Собор', '23.09.2024', 'Законодательная и судебная церковная власть'),
       (2, 'Архиерейский собор', '03.11.2022', 'Церковный суд над Патриархом, отправка на покой служащих, дела синода');

insert into participation (isconstant, assemblyid, participantid)
values (true, 0, 0), (true, 0, 1), (true, 0, 3), (false, 0, 10),
       (true, 1, 7), (true, 1, 2), (false, 1, 4),
       (true, 2, 10), (true, 2, 6), (false, 1, 9);

--

insert into courtcase (caseid, description, status, verdict, submitterid)
values (0, 'Прошение о повышении', 0, null, 7),
       (1, 'Прошение об уходе на покой', 2, 'Удовлетворить в течение года в связи с преклонным возрастом', 9),
       (2, 'Жалоба на непослушание', 1, 'Непослушания не замечено', 8);

insert into donation (donationid, service, amount, executorid)
values (0, 'Молитва', 1000, 10),
       (1, 'Отпевание', 5000, 8),
       (2, 'Причащение', 20000, 6),
       (3, 'Исповедь', 300000, 0);
