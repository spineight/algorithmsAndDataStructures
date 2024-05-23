
create table Seats (
    PlaneId     int not null primary key,
    SeatNo      int not null
);

create table Flights (
    FlightId    int         not null primary key,
    FlightTime  timestamp   not null,
    PlaneId     int         not null,
    foreign key (PlaneId) references Seats (PlaneId)
);

-- Table for holding users and their Pass hashes for auth
create table Users (
    UserId      int         not null primary key,
    PassHash    int         not null,
    FirstName   varchar(40) not null,
    LastName    varchar(40) not null
);

-- Table holding reservations for recognizing
-- already booked seat
create table Reservations (
    FlightId        int         not null,
    SeatNo          int         not null,
    ReservationTime timestamp   not null,
    UserId          int         not null,
    primary key (FlightId, SeatNo),
    foreign key (FlightId) references Flights (FlightId),
    foreign key (UserId) references Users (UserId)
);

-- purchased seats
create table Purchases (
    FlightId    int         not null,
    SeatNo      int         not null,
    primary key (FlightId, SeatNo),
    foreign key (FlightId) references Flights (FlightId)
);