create table PlacementDrive(drive_id int primary key,comp_name varchar(80),package varchar(10),location varchar(50));

create table Training(t_id int primary key,comp_name varchar(50),t_fees int,t_year int);

 create table student(s_id int primary key,drive_id int, t_id int,s_name varchar(50),cgpa decimal,s_branch varchar(20),s_dob date, foreign
 key (drive_id) references placementdrive(drive_id), foreign key(t_id) references training(t_id));

 insert into placementdrive values(101,'A','30k','Mumbai'),(102,'B','45k','Pune'),(103,'C','50k','Gujarat'),(104,'D','40k','Pune'),(105,'E','75k','Banglore');
