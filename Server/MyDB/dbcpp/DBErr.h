#ifndef DB_ERR_H_
#define DB_ERR_H_

static const int OK=0; 
static const int UNKNOW=-1;


//sql err_code start begin 5000
static const int DBERROR=5000;

static const int SQL_NULL=5010;

static const int TYPE_ERROR=5020;

static const int NO_FREE_CONN=5030;


//account err_code start begin 6000
static const int HAD_REGIT=6000;

static const int ERR_IDENTITY=6100;

static const int ACCOUNT_PASSWD_ERROR=6200;

static const int ACCOUNT_IS_USING=6300;


//result err_code start begin 7000
static const int RESULT_NOT_EXIST=7000;

#endif
