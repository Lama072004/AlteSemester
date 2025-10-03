SELECT * FROM Offering
SELECT * FROM Course
SELECT * FROM Faculty

SELECT o.offerNo, 
    c.crsDesc, 
    CONCAT(f.facFirstName, ' ', f.facLastName) AS 'Faculty Member', 
    TRIM(o.offTerm) + ' ' + o.offYear AS 'Schedule'
FROM Offering o 
INNER JOIN Course c 
ON o.courseNo = c.courseNo  
INNER JOIN Faculty f 
ON o.facNo = f.facNo
