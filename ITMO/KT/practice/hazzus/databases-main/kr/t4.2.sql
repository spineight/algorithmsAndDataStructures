select TeamId, count(1) as Solved from Runs natural join Sessions where Accepted = 1 group by TeamId;

