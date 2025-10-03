SELECT 
    DISTINCT CONCAT(s.stdFirstName, ' ', s.stdLastName) AS [Student Name] ,
    CONCAT(f.facFirstName, ' ', f.facLastName) AS [Lecturer Name],
    COUNT(*) as [Number of Classes]
FROM Student s
INNER JOIN Enrollment e
ON s.stdNo = e.StdNo
INNER JOIN Offering o 
ON e.offerNo =  o.offerNo
INNER JOIN Faculty f
ON o.facNo = f.facNo
GROUP BY 
    CONCAT(s.stdFirstName, ' ', s.stdLastName),
    CONCAT(f.facFirstName, ' ', f.facLastName)
ORDER BY [Number of Classes] DESC, [Student Name] ASC, [Lecturer Name] ASC

--Count the classes a student has with a lecturer
