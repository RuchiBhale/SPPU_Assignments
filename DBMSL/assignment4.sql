/*schema*/
create table fine(roll_no int,date date,amount float);
create table borrower(roll_no int,name varchar(50),doi date,nbname varchar(100));

create procedure calculate_fine(rollno int)
begin
declare issuedate date;
declare amt float;
declare diff int;
declare curr_date date;
set curr_date:=curdate();
select doi into issuedate from borrower where roll_no=rollno;
set diff=datediff(curr_date,issuedate);
if exists(select 1 from borrower where roll_no=rollno) then
if(diff>=15 and diff<=30) then
set amt:=diff*5;
elseif(diff>30) then 
set amt:=50*diff;
else 
set amt:=0;
end if;
insert into fine values(rollno,curr_date,amt);
update borrower set status='R' where roll_no=rollno;
else
select 'Roll No does not exist';
end if;
end //


/*with table not found exception*/
create procedure calculate_fine1(rollno int)
begin
declare issuedate date;
declare amt float;
declare diff int;
declare curr_date date;
declare exit handler for SQLEXCEPTION
begin
select 'Table not found';
end;
set curr_date:=curdate();
select doi into issuedate from borrower where roll_no=rollno;
set diff=datediff(curr_date,issuedate);
if exists(select 1 from borrower where roll_no=rollno) then
if(diff>=15 and diff<=30) then
set amt:=diff*5;
elseif(diff>30) then 
set amt:=50*diff;
else 
set amt:=0;
end if;
insert into fine values(rollno,curr_date,amt);
update borrower set status='R' where roll_no=rollno;
else
select 'Roll No does not exist';
end if;
end //
