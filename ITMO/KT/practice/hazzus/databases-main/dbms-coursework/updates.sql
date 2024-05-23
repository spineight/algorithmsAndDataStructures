
create or replace function isBishop(Cleric int)
returns boolean
as $$
begin
    return (select GradeLevel > 3
                  from Cleric C join ClericGrade CG on C.GradeId = CG.GradeId
                  where C.ClericId = Cleric);
end;
$$ language plpgsql;

drop function getParish(Cleric int);
create or replace function getParish(Cleric int)
returns int
as $$
begin
    return (select C.ParishId from Cleric C where C.ClericId = Cleric);
end;
$$ language plpgsql;


create or replace function AddDonation(Service varchar(30), DonationAmount decimal(9, 2), Executor int)
returns boolean
as $$
declare
begin
    if (isBishop(Executor)) then
        insert into Donation (service, amount, executorid)
        values (Service, DonationAmount, Executor);
        return true;
    else
        return false;
    end if;
end;
$$ language plpgsql;

create or replace function PromoteToAbbot(PossiblyAbbot int)
returns boolean
as $$
begin
    if (isBishop(PossiblyAbbot)) then
        update Parish set AbbotId = PossiblyAbbot where ParishId = getParish(PossiblyAbbot);
        return true;
    else
        return false;
    end if;
end;
$$ language plpgsql;

-- Аналогично пишутся promote to archierei, mitropolit, but with checks on being an abbot

create or replace function isAbbot(PossiblyAbbot int)
returns boolean
as $$
begin
    return (select AbbotId = PossiblyAbbot from Parish where ParishId = getParish(PossiblyAbbot));
end;
$$ language plpgsql;


create or replace function PromoteToArchierei(PossiblyAbbot int)
    returns boolean
as $$
declare ClericEparchy int;
begin
    -- abbot is confirmed bishop
    if (isAbbot(PossiblyAbbot)) then
        ClericEparchy := (select EparchyId from Parish where ParishId = getParish(PossiblyAbbot));
        update Eparchy set ArchiereiId = PossiblyAbbot where EparchyId = ClericEparchy;
        return true;
    else
        return false;
    end if;
end;
$$ language plpgsql;