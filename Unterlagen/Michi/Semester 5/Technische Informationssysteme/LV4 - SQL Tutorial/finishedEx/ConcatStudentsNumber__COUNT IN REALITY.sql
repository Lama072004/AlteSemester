
SELECT  
    CONCAT(s.stdFirstName, ' ', s.stdLastName),
    COUNT(e.offerNo) AS [Count]
FROM Enrollment e 
RIGHT OUTER JOIN Student s 
ON e.StdNo = s.stdNo
GROUP BY CONCAT(s.stdFirstName, ' ', s.stdLastName)
ORDER BY COUNT(offerNo)
