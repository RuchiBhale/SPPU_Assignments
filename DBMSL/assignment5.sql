create table stud_marks(name varchar(100),total_marks int);
create table result(rollno int auto_increment,name varchar(100),class varchar(100));
insert into stud_marks values('Alex',900),('Robin',1000),('Peter',850),('Susan',950);

/*stored procedure*/
delimiter //
create procedure category(sname varchar(100),marks int)
begin
declare s_class varchar(100);
if (marks>=990 and marks<=1500) then
set s_class:='Distinction';
elseif(marks>=900 and marks<=989) then
set s_class:='First Class';
elseif(marks>=825 and marks<=899) then
set s_class:='Higher Second Class';
else 
select 'Out of range';
end if;
insert into result(name,class)values(sname,s_class);
end //

/*using function*/
create function calculate_grade(marks int) 
RETURNS varchar(100)
deterministic
begin
declare s_class varchar(100);
if (marks>=990 and marks<=1500) then
set s_class:='Distinction';
elseif(marks>=900 and marks<=989) then
set s_class:='First Class';
elseif(marks>=825 and marks<=899) then
set s_class:='Higher Second Class';
else 
set s_class:= 'Out of range';
end if;
return s_class;
end //

create procedure display(in name varchar(100),in marks int,out grade varchar(100))
begin
set grade:=calculate_grade(marks);
insert into result(name,class) values(name,grade);
end;
//

