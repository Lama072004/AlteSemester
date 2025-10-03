USE AdventureWorksDW2020
GO
SELECT 
    FORMAT(f.amount, 'C', 'en-US')
    ,a.AccountDescription
FROM FactFinance as f
INNER JOIN DimAccount as a
ON f.AccountKey = a.AccountKey
