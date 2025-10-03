SELECT
    stdMajor,
    MIN(stdGPA) AS Worst,
    MAX(stdGPA) AS Best,
    CONVERT(DECIMAL(0,2), AVG(stdGPA)) AS Average
FROM [mge9869].[dbo].[Student]
GROUP BY stdMajor