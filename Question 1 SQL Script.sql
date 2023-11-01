-- NOTE- I have done this on PostgreSQL, same queries might not work as intended on other SQLs


--CREATE TABLE SQLTEST1 (
--  CustomerID INT, 
--  TransDate TIMESTAMP,
--  TransType CHAR (1), 
--Amount MONEY
--); 

--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(1,To_timestamp('1/1/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'C',2000.0000);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(1,To_timestamp('2/1/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'C',2200.0000);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(1,To_timestamp('3/2/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'D',2000.0000);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(2,To_timestamp('1/1/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'C',2000.0000);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(2,To_timestamp('2/1/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'D',234.2230);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(2,To_timestamp('4/1/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'C',2000.0000);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(3,To_timestamp('2/20/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'D',200.2000);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(3,To_timestamp('2/21/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'D',NULL);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(3,To_timestamp('3/31/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'C',334.5452);
--insert into sqltest1(CustomerID, TransDate, TransType, Amount) values(4,To_timestamp('4/30/2005 12:00:00 AM','MM/DD/YYYY HH:MI:SS AM'),'C',332.4520);
--select * from sqltest1 ;

------------------------------------------------------------------------------------------------------------------------------------------------------
--xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx--
------------------------------------------------------------------------------------------------------------------------------------------------------

--Query 1: Display Trans Table records with following columns CustomerID, TransDate, WeekDay, TransType, Amount Where TransType should 
--    display “Credit” for “C” and “Debit for “D” And WeekDay is TransDate of WeekDay, e.g. Today’s Date is “Apr 17 2006” and 
--    Today WeekDay is “Monday”

select CustomerID,
		case when TransType= 'C' then 'Credit'
			 when TransType= 'D' then 'Debit'
		end as TransType,
		Amount,
		to_char(TransDate,'MM/DD/YYYY') as Transdate,
		to_char(TransDate,'Day') as WeekDay 
		from sqltest1 ;
		
--Query 2: Display Trans Table records with following columns CustomerID, TransDate, Credit Amount, Debit Amount, Where Credit Amount 
-- 	   is Amount When TransType = ‘C’ Where Debit Amount is Amount When TransType = ‘D’ Display Null Value as “0.00” Display Amount 
--	   with Two Decimal. Display TransDate with “MM/dd/yyyy” Format

select  CustomerID,  to_char(transdate, 'MM/DD/YYYY') as transdate,
	case when TransType = 'C' then Amount else '0.00' end as "Credit Amount",
	case when TransType = 'D' then Amount else '0.00' end as "Debit Amount"
from sqltest1;

-- Query 3: Same as 2, but display the records where TransDate Month belongs to “4” month And Year = 2005

select  CustomerID,  to_char(transdate, 'MM/DD/YYYY') as transdate,
	case when TransType = 'C' then Amount else '0.00' end as "Credit Amount",
	case when TransType = 'D' then Amount else '0.00' end as "Debit Amount"
from sqltest1 
	WHERE TransDate BETWEEN '2005-04-01' AND '2005-04-30';
	
-- Query 4: Same as 2, but display the records where TransDate is StartDate of the Month

select  CustomerID,  to_char(transdate, 'MM/DD/YYYY') as transdate,
	case when TransType = 'C' then Amount else '0.00' end as "Credit Amount",
	case when TransType = 'D' then Amount else '0.00' end as "Debit Amount"
from sqltest1 
	WHERE transdate = date_trunc('MONTH',transdate);

-- Query 5: 5.Same as 2, but display the records where TransDate is EndDate of the Month
select  CustomerID,  to_char(transdate, 'MM/DD/YYYY') as transdate,
	case when TransType = 'C' then Amount else '0.00' end as "Credit Amount",
	case when TransType = 'D' then Amount else '0.00' end as "Debit Amount"
from sqltest1 
	WHERE transdate = date_trunc('MONTH',transdate)+ interval '1 MONTH'- interval '1 DAY';

--Query 6:Display Trans Table records with following columns CustomerID, Year, Credit Total Amount, 
--Debit Total Amount I need Total for each CustomerID,Year Where Credit Total Amount and 
--Debit Total Amount is Sum of Amount Null Amount should display as 0.00

select  CustomerID, to_char(date_part('YEAR',transdate),'FM9999') as year,
       sum(case when TransType = 'C' then Amount else '0.00' end) as Credit_Total_Amount,
       SUM(case when TransType = 'D' then Amount else '0.00' end) as Debit_Total_Amount
from sqltest1 
group by CustomerID, year
order by CustomerID, year;
