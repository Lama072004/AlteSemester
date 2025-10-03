SELECT  
    dg.DepartmentGroupName,
    FORMAT(SUM(ff.amount), 'C', 'en-US')
FROM [DimDepartmentGroup] as dg
INNER JOIN FactFinance as ff
ON dg.DepartmentGroupKey = ff.DepartmentGroupKey
GROUP BY dg.DepartmentGroupName
