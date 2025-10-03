SELECT o.offerNo, 
    c.crsDesc, 
    CONCAT(f.facFirstName, ' ', f.facLastName) AS 'Faculty Member', 
    CONCAT(TRIM(o.offTerm), ' ', o.offYear) AS 'Schedule'
FROM Offering o, Course c, Faculty f
WHERE o.courseNo = c.courseNo 
AND o.facNo = f.facNo  
