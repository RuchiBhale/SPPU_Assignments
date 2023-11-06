create table Library(book_id int,bname varchar(50),author varchar(35));
create table Library_Audit(action_type varchar(100),book_id int,bname varchar(50),author varchar(35));

 insert into Library values(1,'Macbeth','William Shakespeare'),
   (2,'The India Story','Bimal Jalal'),
   (3,'A place called Home','Preeti Shenoy');
/* before update*/
create trigger before_update
before update on Library
for each row
begin
insert into Library_audit values("Before update",old.book_id,old.bname,old.author);
end;
//

/*after update*/
create trigger after_update
after update on Library
for each row
begin
insert into Library_audit values("After update",new.book_id,new.bname,new.author);
end;
//

/*before insert*/
create trigger before_insert
before insert on Library
for each row
begin
if new.bname LIKE '1%' then
insert into Library_audit values("Before insert",new.book_id,new.bname,new.author);
signal sqlstate '45000' set message_text="Incorrect Name";
end if;
end;
//

/*after insert*/
create trigger after_insert
after insert on Library
for each row
begin
insert into Library_audit values("After insert",new.book_id,new.bname,new.author);
end//


/*delete trigger*/
create trigger del_trigger
before delete on Library
for each row
begin
insert into Library_audit values("Before Delete",old.book_id,old.bname,old.author);
end//

