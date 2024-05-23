select
	distinct TeamName
from 
	Sessions s, 
	Runs r, 
	Teams t
where
	r.SessionId = s.SessionId and
	s.TeamId = t.TeamId and
	s.ContestId = :ContestId and
	r.Letter = :Letter and
	r.Accepted = 1;
