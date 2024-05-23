select RunId, Runs.SessionId, Letter, SubmitTime, Accepted from Runs natural join Sessions natural join Problems where TeamId = :TeamId and ContestId = :ContestId;
