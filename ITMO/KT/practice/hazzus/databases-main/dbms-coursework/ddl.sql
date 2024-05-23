create table ClericGrade (
    GradeId int not null,
    GradeName varchar(30) not null,
    GradeLevel int not null,
    primary key (GradeId),
    check (GradeLevel >= 0),
    check (GradeLevel < 7)
);

create table Cleric (
    ClericId int not null,
    ClericName varchar(30) not null,
    Surname varchar(30) not null,
    Patronymic varchar(30) not null,
    ClericType boolean not null,
    GradeId int not null,
    ParishId int,
    primary key (ClericId),
    foreign key (GradeId) references ClericGrade(GradeId)
);

create table Mitropoly (
    MitropolyId int not null,
    MitropolyName varchar(30) not null,
    MainEparchyId int,
    MitropolitId int not null,
    primary key (MitropolyId),
    foreign key (MitropolitId) references Cleric(ClericId)
);
-- Священник должен быть епископом, чтобы быть митрополитом, а так же до этого быть архиереем здесь мы
-- не можем этого проверить, поэтому будем проверять это в запросе назначения на руководство,
-- то же касается епархий (архиереев (до того настоятелей)) и приходов (настоятелей)

create table Eparchy (
    EparchyId int not null,
    EparchyName varchar(30) not null,
    ArchiereiId int,
    MitropolyId int not null,
    primary key (EparchyId),
    foreign key (ArchiereiId) references Cleric(ClericId),
    foreign key (MitropolyId) references Mitropoly(MitropolyId)
);

create table Parish (
    ParishId int not null,
    ParishName varchar(30) not null,
    Address varchar(100) not null,
    ParishType int not null,
    AbbotId int not null,
    EparchyId int not null,
    primary key (ParishId),
    foreign key (AbbotId) references Cleric(ClericId),
    foreign key (EparchyId) references Eparchy(EparchyId),
    check (ParishType >= 0),
    check (ParishType <= 3)
);

create table Assembly (
    AssemblyId int not null,
    AssemblyName varchar(30) not null,
    NextDate date not null,
    Description text not null,
    primary key (AssemblyId)
);

create table Participation (
    IsConstant boolean not null,
    AssemblyId int not null,
    ParticipantId int not null,
    primary key (AssemblyId, ParticipantId),
    foreign key (AssemblyId) references Assembly(AssemblyId),
    foreign key (ParticipantId) references Cleric(ClericId)
);

create table CourtCase (
    CaseId int not null,
    Description text not null,
    Status int not null,
    Verdict text,
    SubmitterId int not null,
    primary key (CaseId),
    foreign key (SubmitterId) references Cleric(ClericId),
    check (status >= 0),
    check (status < 3)
);

create table Donation (
    DonationId serial not null,
    Service varchar(30) not null,
    Amount decimal(9, 2) not null,
    ExecutorId int not null,
    primary key (DonationId),
    foreign key (ExecutorId) references Cleric(ClericId),
    check (Amount > 0)
);

-- Ограничения добавляю в конце, потому что образуется цикл из внешних ключей в 2 местах

alter table Cleric add foreign key (ParishId) references Parish(ParishId);
alter table Mitropoly add foreign key (MainEparchyId) references Eparchy(EparchyId);


-- Таблица с уровнями священников на самом деле создается один раз и редко поддается изменению, но
-- я вынес ее для удобства, изначальные ее значения константные, поэтому имеет смысл заполнять эту таблицу здесь
insert into ClericGrade (GradeId, GradeName, GradeLevel)
values (0, 'Диакон', 0),
       (1, 'Иеродиакон', 0),
       (2, 'Протодиакон', 1),
       (3, 'Архидиакон', 1),
       -- Персвитеры:
       (4, 'Иерей', 2),
       (5, 'Иеромонах', 2),
       (6, 'Протоиерей', 3),
       (7, 'Игумен', 3),
       -- Епископы:
       (8, 'Епископ', 4),
       (9, 'Архиепископ', 5),
       (10, 'Патриарх', 6);

-- Индексы


-- индекс чтобы быстро искать пожертвования по исполнителю,
-- т.к. чаще всего мы хотим собрать некоторую статистику по человеку и кол-ву выполненной им работы
create index donation_executor_fk_index on Donation using hash(ExecutorId);

-- индекс чтобы быстро искать настоятеля, т.к. при всех повышениях до митрополитов и архиереев необходимо знать
-- является ли священник настоятелем
create index parish_abbot_fk_index on Parish using hash(AbbotId);

-- для быстрой фильтрации по должностям (актуально для узнавания епископа), а чаще всего мы вообще сравниваем на
-- > или < для узнавания привелегий, так что используем дерево (чтобы было упорядочено)
create index cleric_grade_fk_index on Cleric using btree(GradeId);