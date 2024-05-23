pi{TeamName}(Teams diff pi{TeamId, TeamName}(sigma{not(not(Accepted))}(Runs nj Sessions nj Teams)))

select TeamName from (select * from Teams left join (Runs natural join Sessions natural join Teams) r where r.TeamId is not null) where Accepted = 1;


