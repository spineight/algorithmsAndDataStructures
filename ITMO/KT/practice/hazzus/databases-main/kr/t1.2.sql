select RunId, SessionId, Letter, SubmitTime from Runs natural join Sessions where Accepted = 1 and ContestId = :ContestId;

