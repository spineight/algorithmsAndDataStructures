create table Contests (
                          ContestId int primary key not null,
                          ContestName varchar(100)
);


create table Teams (
                       TeamId int not null primary key,
                       TeamName varchar(100)
);

create table Sessions (
                          ContestId int not null,
                          TeamId int not null,
                          SessionId int not null primary key,
                          Start int not null,
                          foreign key (ContestId) references Contests (ContestId),
                          foreign key (TeamId) references Teams (TeamId)
);

create table Problems (
                          ContestId int not null,
                          Letter char not null,
                          ProblemName varchar(100),
                          primary key (ContestId, Letter),
                          foreign key (ContestId) references Contests (ContestId)
);

create table Runs (
    ContestId int not null,
                      ProblemLetter char not null,
                      SessionId int not null,
                      RunId int not null primary key,
                      SubmitTime int not null,
                      Accepted boolean,
                      foreign key (ProblemLetter) references Problems (Letter),
                      foreign key (SessionId) references Sessions (SessionId)
);

