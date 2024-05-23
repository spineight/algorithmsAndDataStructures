-- section starts with some utility functions
-- stupid hash function, possible to replace with better one
create or replace function
    GetHash(Pass varchar(50))
    returns int as
$$
begin
    return 0;
end;
$$ language plpgsql security invoker;

-- verification function checks rather pass matches user
create or replace function
    VerifyUser(UserIdArg int, PassArg varchar(50))
    returns boolean as
$$
begin
    return exists (
        select UserId
        from Users
        where UserId = UserIdArg and
              PassHash = GetHash(PassArg)
    );
end;
$$ language plpgsql security invoker;

-- function returning all seats in plane
create or replace function
    AllSeats(FlightIdArg int)
    returns table (SeatNo int) as
$$
declare
    MaxSeat int := (
        select s.SeatNo
        from Seats s
        where PlaneId in (
            select PlaneId
            from Flights
            where FlightId = FlightIdArg
        )
    );
begin
    return query (
        select generate_series as SeatNo
        from generate_series(1, MaxSeat)
    );
end;
$$ language plpgsql security invoker;

-- FreeSeats from task
create or replace function
    FreeSeats(FlightIdArg int)
    returns table (FreeSeatNo int) as
$$
declare
    Now timestamp := now();
begin
    return query (
        select a.SeatNo as FreeSeatNo
        from AllSeats(FlightIdArg) a
        where a.SeatNo not in (
            select SeatNo
            from Reservations
            where FlightId = FlightIdArg and
                  ReservationTime + interval '1 day' > Now
        ) and a.SeatNo not in (
            select SeatNo
            from Purchases
            where FlightId = FlightIdArg
        )
    );
end;
$$ language plpgsql security invoker;

create or replace function
    Reserve(UserIdArg int,
            PassArg varchar(50),
            FlightIdArg int,
            SeatNoArg int)
    returns boolean as
$$
declare
    Now timestamp := now();
begin
    if not VerifyUser(UserIdArg, PassArg) then
        return false;
    end if;
    if SeatNoArg in (select FreeSeats(FlightIdArg)) then
        insert into Reservations (FlightId, SeatNo, ReservationTime, UserId)
        values (FlightIdArg, SeatNoArg, Now, UserIdArg)
        on conflict (FlightId, SeatNo)
        do update set ReservationTime = Now,
                      UserId = UserIdArg;
        return true;
    end if;
    return false;
end;
$$ language plpgsql security invoker;

create or replace function
    ExtendReservation(UserIdArg int,
                      PassArg varchar(50),
                      FlightIdArg int,
                      SeatNoArg int)
    returns boolean as
$$
declare
    Now timestamp := now();
begin
    if not VerifyUser(UserIdArg, PassArg) then
        return false;
    end if;
    update Reservations
    set ReservationTime = Now
    where FlightId = FlightIdArg and
          SeatNo = SeatNoArg and
          UserId = UserIdArg and
          ReservationTime + interval '1 day' >= Now;
    return FOUND;
end;
$$ language plpgsql security invoker;

create or replace function
    BuyFree(FlightIdArg int,
            SeatNoArg int)
    returns boolean as
$$
begin
    if SeatNoArg not in (select FreeSeats(FlightIdArg)) then
        return false;
    end if;
    insert into Purchases (FlightId, SeatNo)
    values (FlightIdArg, SeatNoArg);
    return true;
end;
$$ language plpgsql security invoker;

create or replace function
    BuyReserved(UserIdArg int,
                PassArg varchar(50),
                FlightIdArg int,
                SeatNoArg int)
    returns boolean as
$$
declare
    Now timestamp := now();
begin
    if not VerifyUser(UserIdArg, PassArg) then
        return false;
    end if;
    delete from Reservations
    where FlightId = FlightIdArg and
          SeatNo = SeatNoArg and
          UserId = UserIdArg and
          ReservationTime + interval '1 day' >= Now;
    if not FOUND then
        return false;
    end if;
    insert into Purchases (FlightId, SeatNo)
    values (FlightIdArg, SeatNoArg);
    return true;
end;
$$ language plpgsql security invoker;

-- utility function for finding purchased
create or replace function
    PurchasedSeats(FlightIdArg int)
    returns table (PurchasedSeats int) as
$$
begin
    return query (
        select SeatNo
        from AllSeats(FlightIdArg)
        where SeatNo in (
            select SeatNo
            from Purchases
            where FlightId = FlightIdArg
        )
    );
end;
$$ language plpgsql security invoker;

-- utility function for finding reserved
create or replace function
    ReservedSeats(FlightIdArg int)
    returns table (PurchasedSeats int) as
$$
begin
    return query (
        select SeatNo
        from AllSeats(FlightIdArg)
        where SeatNo in (
            select SeatNo
            from Reservations
            where FlightId = FlightIdArg
        )
    );
end;
$$ language plpgsql security invoker;

create or replace function
    FlightsStatistics(UserIdArg int, PassArg varchar(50))
    returns table (FlightId int,
                   CanReserve boolean,
                   CanBuy boolean,
                   FreeSeat int,
                   Reserved int,
                   Purchased int) as
$$
declare Now timestamp = now();
begin
    if VerifyUser(UserIdArg, PassArg) then
        return query (
            select f.FlightId,
                   Free > 0,
                   Free > 0 or exists(
                        select UserId
                        from Reservations
                        where UserId = UserIdArg and
                              ReservationTime + interval '1 day' >= Now
                   ),
                   Free,
                   (select count(*)::int from ReservedSeats(f.FlightId)),
                   (select count(*)::int from PurchasedSeats(f.FlightId))
            from Flights f, lateral (select count(*)::int from FreeSeats(f.FlightId)) q(Free) -- WTF should I use q
        );
    end if;
end;
$$ language plpgsql security invoker;

create or replace function
    FlightStats(UserIdArg int, PassArg varchar(50), FlightIdArg int)
    returns table (CanReserve boolean,
                   CanBuy boolean,
                   FreeSeat int,
                   Reserved int,
                   Purchased int) as
$$
begin
    if VerifyUser(UserIdArg, PassArg) then
        return query (
            select fs.CanReserve, fs.CanBuy, fs.FreeSeat, fs.Reserved, fs.Purchased
            from FlightsStatistics(UserIdArg, PassArg) fs
            where fs.FlightId = FlightIdArg
        );
    end if;
end;
$$ language plpgsql security invoker;

create or replace function
    InteractSeat(ActionType varchar(10),
                 UserIdArg int,
                 PassArg varchar(50),
                 FlightIdArg int,
                 SeatNoArg int)
    returns boolean as
$$
begin
    start transaction read write isolation level serializable;
    if ((ActionType = 'BUY')) then
        return (select BuyFree(FlightIdArg, SeatNoArg));
    else
        if ((ActionType = 'RESERVE')) then
            return (select Reserve(UserIdArg, PassArg, FlightIdArg, SeatNoArg));
        end if;
    end if;
    commit;
end;
$$ language plpgsql security invoker;



