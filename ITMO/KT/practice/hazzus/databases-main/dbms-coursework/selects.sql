
-- Все селекты имеют read committed уровни изоляции.
-- Uncommited не подходит, потому что неподтвержденные данные могут быть невалидны
-- и не отражать действительность.

create or replace function getParishTypeName(ParishType int)
returns varchar(10)
as $$
begin
    return case
                when ParishType = 0
                    then 'Храм'
                when ParishType = 1
                    then 'Собор'
                else 'Церковь'
            end;
end;
$$ language plpgsql;


create or replace view BishopsInfo as
    select
        ClericId,
        ClericName,
        Surname,
        Patronymic,
        case
            when ClericType
                then 'Белое'
                else 'Черное'
        end,
        GradeName as FullGradeName,
        getParishTypeName(ParishType) as TypeOfPlace,
        ParishName as PlaceOfServing
    from Cleric C natural join ClericGrade CG join parish p on C.parishid = p.parishid
    where CG.GradeLevel > 3;

create or replace function getClericsByLevel(ReqLevel int)
    returns table (
        ClericId int,
        ClericName varchar(30),
        ClericSurname varchar(30),
        ClericPatronymic varchar(30),
        FullGradeName varchar(30),
        TypeOfPlace varchar(10),
        PlaceOfServing varchar(30)
    )
as $$
begin
    return query (
        select
            C.ClericId,
            C.ClericName,
            C.Surname,
            C.Patronymic,
            CG.GradeName,
            getParishTypeName(ParishType),
            P.ParishName
        from Cleric C natural join ClericGrade CG join Parish P on C.ParishId = P.ParishId
        where CG.GradeLevel = ReqLevel
    );
end;
$$ language plpgsql;


create or replace view DonationSums as
    select
        ClericId,
        ClericName,
        Surname,
        Patronymic,
        DS.SumDonation
    from (
        select
            ExecutorId,
            sum(Amount) as SumDonation
        from Donation D join Cleric C on D.ExecutorId = C.ClericId
        group by ExecutorId
    ) DS join Cleric C on C.ClericId = DS.ExecutorId;

create or replace function getTotalDonationsForCleric(ClericId int)
    returns table (
        DonationSum decimal(9, 2)
    )
as $$
begin
    return query (
        select
            sum(Amount)
        from Donation D
        where D.ExecutorId = ClericId
        group by ClericId
    );
end;
$$ language plpgsql;


create or replace function getAllParishesByEparchy(ReqEparchyId int)
    returns table (
        ParishId int,
        ParishType varchar(10),
        ParishName varchar(30),
        Address varchar(100),
        AbbotName varchar(30),
        AbbotSurname varchar(30),
        AbbotGradeName varchar(30)
    )
as $$
begin
    return query (
        select
            P.ParishId,
            getParishTypeName(P.ParishType),
            P.ParishName,
            P.Address,
            C.ClericName,
            C.Surname,
            CG.GradeName
        from Parish P join Cleric C on P.AbbotId = C.ClericId join ClericGrade CG on C.gradeid = CG.gradeid
        where P.EparchyId = ReqEparchyId
    );
end;
$$ language plpgsql;