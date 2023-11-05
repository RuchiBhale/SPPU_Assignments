create table o_emp(e_id int, name varchar(100));
create table n_emp(e_id int, name varchar(100));

insert into o_emp values(1,'Robin'),(2,'Simran'),(3,'Richard'),(4,'Rohan'),(5,'Pushkar');

insert into n_emp values(2,'Simran'),(5,'Pushkar');

/*explicit cursor*/
create procedure use_cursor1()
begin
declare n_name varchar(100);
declare n_id int;
declare done int default false;
declare emp_cursor cursor for select e_id,name from o_emp;
declare continue handler for not found set done=1;
open emp_cursor;
read_loop:loop
if done then
leave read_loop;
end if;
fetch emp_cursor into n_id,n_name;
if not exists (select 1 from n_emp where e_id=n_id and name=n_name) then
insert into n_emp values(n_id,n_name);
end if;
end loop;
close emp_cursor;
end //

/*parameterized cursor*/
create procedure parameterized_cursor(lower_limit int, upper_limit int)
begin
declare n_id int;
declare n_name varchar(100);
declare done int default false;
declare p_cursor cursor(p_lower int,p_upper int) for select e_id, name from o_emp where e_id between p_lower and p_upper;
declare continue handler for not found set done=1;
open p_cursor(lower_limit,upper_limit);
read_loop:loop
if done then
leave read_loop;
end if;
fetch p_cursor into n_id,n_name;
if not exists (select 1 from n_emp where e_id=n_id and name=n_name) then
insert into n_emp values(n_id,n_name);
end if;
end loop;
close p_cursor;
end//

