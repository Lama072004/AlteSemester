SELECT 
      s.[stdFirstName]
      ,s.[stdLastName]
      ,f.facFirstName
      ,f.facLastName
      ,COUNT(*)
FROM Student as s
INNER JOIN Enrollment as e
ON e.StdNo = s.StdNo
INNER JOIN Offering as o
ON e.offerNo = o.offerNo
INNER JOIN Faculty as f
ON o.facNo = f.facNo
GROUP BY s.[stdFirstName] ,s.[stdLastName] ,f.facFirstName ,f.facLastName
ORDER BY COUNT(*) DESC, s.stdLastName, f.facLastName