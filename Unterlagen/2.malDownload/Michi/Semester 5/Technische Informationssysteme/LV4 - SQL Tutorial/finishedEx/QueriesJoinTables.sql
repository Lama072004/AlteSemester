--SELECT * FROM Offering;
--SELECT * FROM Faculty;

--SELECT * FROM Offering, Faculty
--WHERE Offering.facNo = Faculty.facNo

SELECT * FROM Offering INNER JOIN Faculty
ON Offering.facNo = Faculty.facNo --is exactly the same as above
--get the Schnittmenge

