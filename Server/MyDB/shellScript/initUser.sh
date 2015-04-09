mysql -u root -pmaildb<<EOF 2>>log 1>>info 

#regitUser for regit
grant insert,select(account) on simplecs.accounts to 'regitUser'@'localhost' identified by 'regiter';

#lanuchUser for lanuch and update the setMsg
grant select(account,passwd,name,status,lastlanuch,lastIP,times,setting),update(status,lastlanuch,lastIP,times,setting) on simplecs.accounts to 'lanuchUser'@'localhost' identified by 'lanucher';

#secureUser for reset passwd 
grant select(account,email,question,answer),update(passwd) on simplecs.accounts to 'secureUser'@'localhost' identified by 'securer';

#resultUser for insert  result
grant insert on simplecs.results to 'resultUser'@'localhost' identified by 'resulter';
grant update(flag,result0,result1,result2,result3,result4,result5,result6,result7,result8) on simplecs.accounts to 'resultUser'@'localhost' identified by 'resulter';

#getResultUser for getResult
grant select on simplecs.results to 'getResultUser'@'localhost' identified by 'getResulter';
grant select(id,name) on simplecs.accounts to 'getResultUser'@'localhost' identified by 'getResulter';

EOF



