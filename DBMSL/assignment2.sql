create table PlacementDrive(drive_id int primary key,comp_name varchar(80),package varchar(10),location varchar(50));

create table Training(t_id int primary key,comp_name varchar(50),t_fees int,t_year int);

 create table student(s_id int primary key,drive_id int, t_id int,s_name varchar(50),cgpa decimal,s_branch varchar(20),s_dob date, foreign
 key (drive_id) references placementdrive(drive_id), foreign key(t_id) references training(t_id));

 insert into placementdrive values(101,'compA','30k','Mumbai'),
                                  (102,'compB','45k','Pune'),
                                  (103,'compC','50k','Gujarat'),
                                  (104,'compD','40k','Pune'),
                                  (105,'compE','75k','Banglore');

 insert into training values(1,'compF',10000,2022),
                            (2,'compG',2000,2020),
                            (3,'compH',1900,2021),
                            (4,'compI',8000,2023),
                            (5,'compJ',5000,2020);

select * from student where s_branch in ('CE','IT') and s_name like 'A%' or s_name like 'D%';

select count(distinct comp_name) from placementdrive;

update training set t_fees=t_fees+0.15*t_fees where t_year=2019;

delete from student where cgpa<7;

select comp_name from placementdrive where location in('Pune','Mumbai');

select s_name from student s,training t where s.t_id=t.t_id and t.t_year in (2019,2021);

select s_name from student where cgpa=(select max(cgpa) from student);

select s_name, s.t_id,t_fees from student s,training t where s.t_id=t.t_id order by t.t_fees desc;

select s_name,comp_name,location,package from student s,placementdrive p where s.drive_id=p.drive_id and package in('30k','40k','50k');

/*creating index*/
create index student_index on student(s_name);
show indexes from student;

/*creating view*/
create view student_view as select s_id,s_name,cgpa,s_branch from student;
insert into student_view values(8,'Punit',7.5,'ENTC');
