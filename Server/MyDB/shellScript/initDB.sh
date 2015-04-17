mysql -u root -pmaildb <<EOF  2>>log  1>>info
use simplecs;

#insert into questions
insert into questions values(1000,'what\'s your primary school\'s name');
insert into questions values(DEFAULT,'what\'s your father\'s name');
insert into questions values(DEFAULT,'what\'s your mother\'s name');
insert into questions values(DEFAULT,'who\'s you love');

#insert into shots
insert into shots values(1000,'auto shots','auto shots:have many boms,but hard is small');
insert into shots values(DEFAULT,'hand shots','hand shots:less boms,big hard'); 


#insert into booms
insert into booms values(1000,'harm booms','can harm other\'s');
insert into booms values(DEFAULT,'dark booms','can make world dark');


#insert into knifes
insert into knifes values(1000,'normal knifes','normal knifes,normal harm');
insert into knifes values(DEFAULT,'vip knifes','more harm,but need money to open it'); 

#insert into setMsg
insert into setMsg values(1000,1000,1000,1000);

#insert into results
insert into results values(1000,DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0,
		             DEFAULT,0,0,0,0,0,0,0);
			     	
#insert into accounts
#insert into accounts values(1000,'sg','sgpasswd','coderguang@gmail.com','sg',1000,'sganswer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg1','sg1passwd','coderguang@gmail.com','sg1',1000,'sg1answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg2','sg2passwd','coderguang@gmail.com','sg2',1000,'sg2answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg3','sg3passwd','coderguang@gmail.com','sg3',1000,'sg3answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg4','sg4passwd','coderguang@gmail.com','sg4',1000,'sg4answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg5','sg5passwd','coderguang@gmail.com','sg5',1000,'sg5answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg6','sg6passwd','coderguang@gmail.com','sg6',1000,'sg6answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg7','sg7passwd','coderguang@gmail.com','sg7',1000,'sg7answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg8','sg8passwd','coderguang@gmail.com','sg8',1000,'sg8answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
#insert into accounts values(DEFAULT,'sg9','sg9passwd','coderguang@gmail.com','sg9',1000,'sg9answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);


insert into accounts values(1000,'sg','sg','coderguang@gmail.com','sg',1000,'sganswer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg1','sg1','coderguang@gmail.com','sg1',1000,'sg1answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg2','sg2','coderguang@gmail.com','sg2',1000,'sg2answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg3','sg3','coderguang@gmail.com','sg3',1000,'sg3answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg4','sg4','coderguang@gmail.com','sg4',1000,'sg4answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg5','sg5','coderguang@gmail.com','sg5',1000,'sg5answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg6','sg6','coderguang@gmail.com','sg6',1000,'sg6answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg7','sg7','coderguang@gmail.com','sg7',1000,'sg7answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg8','sg8','coderguang@gmail.com','sg8',1000,'sg8answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
insert into accounts values(DEFAULT,'sg9','sg9','coderguang@gmail.com','sg9',1000,'sg9answer',DEFAULT,DEFAULT,DEFAULT,0,1000,0,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT,DEFAULT);
EOF

