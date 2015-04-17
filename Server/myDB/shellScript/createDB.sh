#connect to mysql and redirect the stdout and stderr 
mysql -u root -pmaildb <<EOF 2>log 1>info

#test 
#show databases;

#delete databases if exists
drop database if exists simplecs; 

#create databases
create database simplecs;

use simplecs;

#create tables
create table accounts(id int(8) not null  primary key auto_increment)ENGINE=InnoDB;
create table questions(id int(4) not null primary key auto_increment)ENGINE=InnoDB;
create table results(id int(8) not null primary key auto_increment)ENGINE=InnoDB;
create table setMsg(id int(4) not null primary key auto_increment)ENGINE=InnoDB;
create table shots(id int(4) not null primary key auto_increment)ENGINE=InnoDB;
create table booms(id int(4) not null primary key auto_increment)ENGINE=InnoDB;
create table knifes(id int(4) not null primary key auto_increment)ENGINE=InnoDB;

#alter tables accounts
#for use the memory size matching c++ and c# class struct size,every menmber size are 4 times
alter table accounts add account char(8) not null unique;
alter table accounts add passwd char(16) not null;
alter table accounts add email char(16) not null ;
alter table accounts add name char(8) default null unIque;
alter table accounts add question int(4) not null; 
alter table accounts add answer char(8) not null; 
# status 1 for accounts using,0 for free
alter table accounts add status int(8) not null default 0; 
alter table accounts add lastlanuch char(32) not null default 'Thu Jan  1 00:01:03 2015';
alter table accounts add lastIP char(16) default '127.0.0.1';
alter table accounts add times int(4) not null default 0;
alter table accounts add setting int(4) not null default 1000;
alter table accounts add flag int(4) not null default 0;
alter table accounts add result0 int(8) default 1000; 
alter table accounts add result1 int(8) default 1000; 
alter table accounts add result2 int(8) default 1000; 
alter table accounts add result3 int(8) default 1000; 
alter table accounts add result4 int(8) default 1000; 
alter table accounts add result5 int(8) default 1000; 
alter table accounts add result6 int(8) default 1000; 
alter table accounts add result7 int(8)   default 1000; 
alter table accounts add result8 int(8)   default 1000; 
alter table accounts add result9 int(8)   default 1000; 


#alter tables questions
alter table questions add question char(50) not null unique;

#alter tables results
alter table results add red1id int(8) default 1000;
alter table results add red1Kill int(4) default 0;
alter table results add red1Death int(4) default 0;
alter table results add red1Assist int(4) default 0;
alter table results add red1Harm int(8) default 0;
alter table results add red1GetHarm int(8) default 0;
alter table results add red1ReHP int(8) default 0;
alter table results add red1Null int(4) default 0;

alter table results add red2id int(8) default 1000;
alter table results add red2Kill int(4) default 0;
alter table results add red2Death int(4) default 0;
alter table results add red2Assist int(4) default 0;
alter table results add red2Harm int(8) default 0;
alter table results add red2GetHarm int(8) default 0;
alter table results add red2ReHP int(8) default 0;
alter table results add red2Null int(4) default 0;

alter table results add red3id int(8) default 1000;
alter table results add red3Kill int(4) default 0;
alter table results add red3Death int(4) default 0;
alter table results add red3Assist int(4) default 0;
alter table results add red3Harm int(8) default 0;
alter table results add red3GetHarm int(8) default 0;
alter table results add red3ReHP int(8) default 0;
alter table results add red3Null int(4) default 0;

alter table results add red4id int(8) default 1000;
alter table results add red4Kill int(4) default 0;
alter table results add red4Death int(4) default 0;
alter table results add red4Assist int(4) default 0;
alter table results add red4Harm int(8) default 0;
alter table results add red4GetHarm int(8) default 0;
alter table results add red4ReHP int(8) default 0;
alter table results add red4Null int(4) default 0;

alter table results add red5id int(8) default 1000;
alter table results add red5Kill int(4) default 0;
alter table results add red5Death int(4) default 0;
alter table results add red5Assist int(4) default 0;
alter table results add red5Harm int(8) default 0;
alter table results add red5GetHarm int(8) default 0;
alter table results add red5ReHP int(8) default 0;
alter table results add red5Null int(4) default 0;


alter table results add blue1id int(8) default 1000;
alter table results add blue1Kill int(4) default 0;
alter table results add blue1Death int(4) default 0;
alter table results add blue1Assist int(4) default 0;
alter table results add blue1Harm int(8) default 0;
alter table results add blue1GetHarm int(8) default 0;
alter table results add blue1ReHP int(8) default 0;
alter table results add blue1Null int(4) default 0;

alter table results add blue2id int(8) default 1000;
alter table results add blue2Kill int(4) default 0;
alter table results add blue2Death int(4) default 0;
alter table results add blue2Assist int(4) default 0;
alter table results add blue2Harm int(8) default 0;
alter table results add blue2GetHarm int(8) default 0;
alter table results add blue2ReHP int(8) default 0;
alter table results add blue2Null int(4) default 0;

alter table results add blue3id int(8) default 1000;
alter table results add blue3Kill int(4) default 0;
alter table results add blue3Death int(4) default 0;
alter table results add blue3Assist int(4) default 0;
alter table results add blue3Harm int(8) default 0;
alter table results add blue3GetHarm int(8) default 0;
alter table results add blue3ReHP int(8) default 0;
alter table results add blue3Null int(4) default 0;

alter table results add blue4id int(8) default 1000;
alter table results add blue4Kill int(4) default 0;
alter table results add blue4Death int(4) default 0;
alter table results add blue4Assist int(4) default 0;
alter table results add blue4Harm int(8) default 0;
alter table results add blue4GetHarm int(8) default 0;
alter table results add blue4ReHP int(8) default 0;
alter table results add blue4Null int(4) default 0;

alter table results add blue5id int(8) default 1000;
alter table results add blue5Kill int(4) default 0;
alter table results add blue5Death int(4) default 0;
alter table results add blue5Assist int(4) default 0;
alter table results add blue5Harm int(8) default 0;
alter table results add blue5GetHarm int(8) default 0;
alter table results add blue5ReHP int(8) default 0;
alter table results add blue5Null int(4) default 0;


#alter tables setMsg
alter table setMsg add shot int(4) not null default 1000;
alter table setMsg add boom int(4) not null default 1000;
alter table setMsg add knife int(4) not null default 1000;

#alter tables shots
alter table shots add name char(16) not null unique;
alter table shots add descs char(128) not null;

#alter tables booms
alter table booms add name char(16) not null unique;
alter table booms add descs char(128) not null;

#alter tables knifes
alter table knifes add name char(16) not null unique;
alter table knifes add descs char(128) not null;

#alter accounts foreign key
alter table accounts add constraint Question_ID foreign key(question) references questions(id) on update cascade ;
alter table accounts add constraint Set_ID foreign key(setting) references setMsg(id) on update cascade; 
alter table accounts add constraint Result_0 foreign key(result0) references results(id) on update cascade;
alter table accounts add constraint Result_1 foreign key(result1) references results(id) on update cascade;
alter table accounts add constraint Result_2 foreign key(result2) references results(id) on update cascade;
alter table accounts add constraint Result_3 foreign key(result3) references results(id) on update cascade;
alter table accounts add constraint Result_4 foreign key(result4) references results(id) on update cascade;
alter table accounts add constraint Result_5 foreign key(result5) references results(id) on update cascade;
alter table accounts add constraint Result_6 foreign key(result6) references results(id) on update cascade;
alter table accounts add constraint Result_7 foreign key(result7) references results(id) on update cascade;
alter table accounts add constraint Result_8 foreign key(result8) references results(id) on update cascade;
alter table accounts add constraint Result_9 foreign key(result9) references results(id) on update cascade;



#alter setMsg foreign key
alter table setMsg add constraint SetMsg_shot foreign key(shot) references shots(id) on update cascade;
alter table setMsg add constraint SetMsg_boom foreign key(boom) references booms(id) on update cascade;
alter table setMsg add constraint SetMsg_knife foreign key(knife) references knifes(id) on update cascade;

EOF


