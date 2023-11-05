/*Find the Student details and Placement details using NATURAL JOIN.*/
select * from student natural join placementdrive;

/* Find all the student details with company_name who have conducted in same drive*/
 select Group_concat(s_name),comp_name from student s inner join placementdrive using (drive_id) group by comp_name;

/*List all the Student name and Student branch of Student having package 5 LPA*/
select s_name,s_branch from student s inner join placementdrive using (drive_id) where package='5L';

/*List all the student names ,company_name having T_fee more than 10000*/
select s_name,comp_name from student s inner join training t using(t_id) where t.t_fees>10000;

/*Display all training details attended by “shantanu” in year 2011*/
 select * from training t left join student s using(t_id) where s.s_name='Shantanu' and t_year=2020;

/* list the total number of companies who conduct training before 2022*/
select count(comp_name) from training where t_year<2022;

/*List the students name with company ‘B’ and location Pune*/
select s_name from student s left join placementdrive p using(drive_id) where comp_name='B' and location='Pune';

/* Find the names of all Students who have joined J training in 2020 */
select s_name from training t right join student s using (t_id) where t.comp_name='J' and t.t_year=2020;

/*Create a view showing the Student and Training details. */
create view complex_view as select s.s_name,s.s_branch,s.cgpa,t.t_id,t.comp_name,t_fees from student s left join training t on s.t_id = t.t_id;

/*Perform Manipulation on simple view-Insert, update, delete, drop view*/
insert into complex_view values('Ridhima','CE',9.2,2,'H',7000);
ERROR 1471 (HY000): The target table simple_view of the INSERT is not insertable-into

update complex_view set t_fees=20000 where s_name ='Shantanu';

delete from simple_view where s_name='Shantanu';
ERROR 1288 (HY000): The target table simple_view of the DELETE is not updatable

