SELECT * FROM Offering
SELECT * FROM Faculty

SELECT * FROM Offering o FULL OUTER JOIN Faculty f
    ON o.facNo=f.facNo;

SELECT * FROM Offering o LEFT OUTER JOIN Faculty f
    ON o.facNo=f.facNo;

SELECT * FROM Offering o RIGHT OUTER JOIN Faculty f
    ON o.facNo=f.facNo;

SELECT * FROM Offering o INNER JOIN Faculty f
    ON o.facNo=f.facNo;