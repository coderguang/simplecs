mysql -u root<<EOF  2>>log  1>>info
use simplecs;

#insert into questions
insert into questions values(1000,'what\'s your primary school\'s name');
insert into questions values(null,'what\'s your father\'s name');
insert into questions values(null,'what\'s your mother\'s name');
insert into questions values(null,'who\'s you love');

#insert into shots
insert into shots values(1000,'auto shots','auto shots:have many boms,but hard is small');
insert into shots values(null,'hand shots','hand shots:less boms,big hard'); 


#insert into booms
insert into booms values(1000,'harm booms','can harm other\'s');
insert into booms values(null,'dark booms','can make world dark');


#insert into knifes
insert into knifes values(1000,'normal knifes','normal knifes,normal harm');
insert into knifes values(null,'vip knifes','more harm,but need money to open it'); 

#insert into setMsg
insert into setMsg values(1000,1000,1000,1000);

#insert into results
insert into results values(1000,null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0,
		             null,0,0,0,0,0,0,0);
			     	
#insert into accounts
insert into accounts values(1000,'sg','sgpasswd','coderguang@gmail.com','sg',1000,'sganswer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);
insert into accounts values(null,'sg1','sg1passwd','coderguang@gmail.com','sg1',1000,'sg1answer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);
insert into accounts values(null,'sg2','sg2passwd','coderguang@gmail.com','sg2',1000,'sg2answer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);
insert into accounts values(null,'sg3','sg3passwd','coderguang@gmail.com','sg3',1000,'sg3answer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);
insert into accounts values(null,'sg4','sg4passwd','coderguang@gmail.com','sg4',1000,'sg4answer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);
insert into accounts values(null,'sg5','sg5passwd','coderguang@gmail.com','sg5',1000,'sg5answer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);
insert into accounts values(null,'sg6','sg6passwd','coderguang@gmail.com','sg6',1000,'sg6answer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);
insert into accounts values(null,'sg7','sg7passwd','coderguang@gmail.com','sg7',1000,'sg7answer',true,null,null,0,1000,0,null,null,null,null,null,null,null,null,null,null);



