#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#define  DATABASE   "station.db"


typedef enum
{
  TEMPERATURE_MAX =1,   //温度
  TEMPERATURE_MIN,   
  HUMIDITY_MAX,      //湿度
  HUMIDITY_MIN,
  ILLUMINATION_MAX, //光照
  ILLUMINATION_MIN,  
  TELEPHONE_NUM,     
  STATION_ID,              
  STATION_NAME,  
  USER_NAME         	
} Type_info;

int creat_database(sqlite3 *db)
{
	char *errmsg=NULL;
	int rc=0;
	rc=sqlite3_open(DATABASE,&db);
	if (rc != SQLITE_OK)
    {
       printf ("Can't Open Database:%s!\n",sqlite3_errmsg(db));
		 
		sqlite3_close(db);
    }
    else
    {
        printf("database open success!\n");
    }	
	
	
}


int creat_table_config_env(sqlite3 *db)
{
	
	char *errmsg=NULL;
 
	char *sql = "create table config_env(temperatureMax float not null,\
	temperatureMin float not null,\
	humidityMax float not null,\
	humidityMin float not null,\
	illuminationMax float not null,\
	illuminationMin float not null);";
	if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
        printf("operate failed: %s\n",errmsg);
         
        return(-1);  
    }  
	printf("create table config_env success.\n");
}
int creat_table_collect_env(sqlite3 *db)
{

	char *errmsg=NULL;
    
	char *sql="create table collect_env(stationID varchar(20),\
	stationName varchar(20),\
	telephoneNum varchar(11),\
	temperature float,\
	username varchar(20),\
	humidity float,\
	illumination float,\
	latitude varchar(20),\
	longitude varchar(20),\
	sampletime varchar(25));";
	
	if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
        printf("operate failed: %s\n",errmsg); 
         
        return(-1);  
    }  
	printf("create table collect_env success.\n");
}
int init_table_env(sqlite3 *db)
{
	
	
	char *errmsg = NULL;
	char *sql="insert into config_env(temperatureMax,temperatureMin,humidityMax,humidityMin,illuminationMax,illuminationMin) values (50.0,5.0,51.0,10.5,500.6,10.8);"; 
	
	if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
       printf("operate failed: %s\n",errmsg); 
         
        return(-1);  
    }  
	printf("Init_table_env ok:\n");
	
}
int display_table_env(sqlite3 *db)
{

	char **aresult=NULL;  
  
    int i=0;  
    int nrow=0;  
    int ncol=0;  
	char *errmsg=NULL;  
	
	char *sql="select * from config_env;";

	if(SQLITE_OK != sqlite3_get_table(db,sql,&aresult,&nrow,&ncol,&errmsg))//判断sqlite3_get_table是否运用成功，成功返回SQLITE_OK  
    {  
        printf("operate failed: %s\n",errmsg);
        printf("\n");  
        return(-1);  
    }  
  
    for(i = 0; i < (nrow + 1) * ncol; i++)//将表中的数据打印出来  
    {  
        printf("%-12s",aresult[i]);  
  
        if((i + 1) % ncol == 0)  
        {  
            printf("\n");  
        }  
    }  
  
    sqlite3_free_table(aresult);//释放aresult   		

	
	
}

int set_env(float val, Type_info no,sqlite3 *db)
{
	
	char **aresult=NULL;  
  
    int i=0;  
    int nrow=0;  
    int ncol=0;  
	char *errmsg=NULL;  
    char sql[1024];
	
	switch(no)
	{
		case TEMPERATURE_MAX:
		sprintf (sql, "update config_env set temperatureMax = '%6.1f';", val);
		break;
		case TEMPERATURE_MIN:
		sprintf (sql, "update config_env set temperatureMin = '%6.1f';", val);
		break;
		case HUMIDITY_MAX:
		sprintf (sql, "update config_env set humidityMax = '%6.1f';", val);
		break;
		case HUMIDITY_MIN:
		sprintf (sql, "update config_env set humidityMin = '%6.1f';", val);
		break;
		case ILLUMINATION_MAX:
		sprintf (sql, "update config_env set illuminationMax = '%6.1f';", val);
		break;
		case ILLUMINATION_MIN:
		sprintf (sql, "update config_env set illuminationMin = '%6.1f';", val);
		break;
		
	}
	if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
        printf("operate failed: %s\n",errmsg);
         
        return(-1);  
    }  
	printf("set_env ok:\n");
	
	
	
}

int main()
{
	sqlite3 *db;
	int rc=0;
	rc=sqlite3_open(DATABASE,&db);
	if (rc != SQLITE_OK)
    {
       printf ("Can't Open Database:%s!\n",sqlite3_errmsg(db));
		 
		sqlite3_close(db);
    }
    else
    {
        printf("database open success!\n");
    }	
	//creat_database(db);
	creat_table_config_env(db);
	creat_table_collect_env(db);
    init_table_env (db); 
    //display_table_env(db);
	set_env(60.2,TEMPERATURE_MAX,db);
	display_table_env(db);
	sqlite3_close(db);
    return 0;
}
