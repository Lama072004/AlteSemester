SELECT c.crsDesc AS 'Course',
    CONCAT(f.facFirstname, ' ', f.facLastName) AS 'Teacher',
    CONCAT(o.offTerm, o.offYear, ' ', o.offDays) AS 'Time'
FROM Offering o
INNER JOIN Course c
ON c.courseNo=o.courseNo
RIGHT OUTER JOIN Faculty f
ON f.facNo=o.facNo
ORDER BY o.offYear, o.offTerm, o.offDays;
