--Find for each offering the number of students assigned to it

SELECT * FROM Offering;
SELECT * FROM Enrollment;

SELECT o.offerNo, o.offTerm, o.offYear, o.courseNo, c.crsDesc AS 'Description', COUNT(*) AS '# Student' 
FROM Offering o
INNER JOIN Enrollment e 
ON o.offerNo = e.offerNo
INNER JOIN Course c 
ON o.courseNo = c.courseNo 
GROUP BY o.offerNo, o.offTerm, o.offYear, o.courseNo, c.crsDesc