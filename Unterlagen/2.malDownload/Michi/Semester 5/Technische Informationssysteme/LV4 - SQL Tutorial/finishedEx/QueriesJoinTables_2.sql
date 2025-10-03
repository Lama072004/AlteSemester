

SELECT 
    c.crsDesc AS 'Course Description',
    CONCAT(o.offTerm, ' ', o.offYear) AS Semester
FROM Offering o 
INNER JOIN Course c
ON o.courseNo = c.courseNo 
WHERE o.facNo IS NULL