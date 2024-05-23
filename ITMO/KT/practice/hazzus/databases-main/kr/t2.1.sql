select distinct TeamId from Sessions s, Runs r where r.SessionId = s.SessionId and r.Letter = :Letter and s.ContestId = :ContestId and r.Accepted = 1;

