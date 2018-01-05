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
#if 0
static int callback(void* arg, int f_num , char ** f_value  , char ** f_name)
{
    int i = 0;
    printf("f_num = %d \n", f_num);
    for (i = 0; i < f_num; i++)
    {
        printf("%s\t", f_value[i]);
    }
    putchar(10);

    return 0;
}
  #endif
int creat_database()
{   
    sqlite3 *db;
	int rc=0;
	rc=sqlite3_open(DATABASE,&db);
	if (rc != SQLITE_OK)
    {
        sqlite3_errmsg(db);
    }
    else
    {
        printf("database open success!\n");
    }
	
}

int creat_table_config_env()
{
	sqlite3 *db;
	char *errmsg=NULL;
 
	char *sql = "create table config_env(temperatureMax float not null,temperatureMin float not null,humidityMax float not null,\
humidityMin float not null,illuminationMax float not null,illuminationMin float not null);";
 if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
        printf("config_env table fail:\n");  
         
        return(-1);  
    }  
	printf("create table config_env success.\n");
}
int creat_table_collect_env()
{
	sqlite3 *db;
	char *errmsg=NULL;
    
	char *sql="create table collect_env(stationID int,\
	stationName varchar(20),\
	telephoneNum varchar(11),\
	temperature float,\
	username varchar(20),\
	humidity float,\
	illumination float,\
	latitude varchar(20),\
	longitude varchar(20),\
	date timestamp not null default current_timestam);";
	#if 0	
	char *sql="create table collect_env(stationID int,\
		stationName varchar(20),\
		telephoneNum varchar(11),\
		temperature float,\
		username varchar(20),\
		humidity float,\
		illumination float,\
		latitude varchar(20),\
		longitude varchar(20),\
		year int,\
		month int,\
		day int,\
		minute int,\
		second int);";
    #endif
	if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
        printf("collect_env fail:\n");  
         
        return(-1);  
    }  
	printf("create table collect_env success.\n");
}
int init_table_env()
{
	sqlite3 *db;
	
	char *errmsg = NULL;
	char *sql="insert into config_env(temperatureMax,temperatureMin,humidityMax,humidityMin,illuminationMax,illuminationMin) values (50,5,50,10,500,10);"; 
	
	if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
        printf("Init_table_env  error:\n");  
         
        return(-1);  
    }  
	printf("Init_table_env ok:\n");
	
}
int display_table_env()
{
	sqlite3 *db;
	char **aresult=NULL;  
  
    int i=0;  
    int nrow=0;  
    int ncol=0;  
	char *errmsg=NULL;  
	
	char *sql="select * from config_env;";
 #if 1
	if(SQLITE_OK != sqlite3_get_table(db,sql,&aresult,&nrow,&ncol,&errmsg))//判断sqlite3_get_table是否运用成功，成功返回SQLITE_OK  
    {  
        printf("fail:%s\n",errmsg);  
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
    #endif
  #if 0
	 if (sqlite3_exec(db, sql,callback, NULL, &errmsg)!= SQLITE_OK)
    {
        printf("%s\n", errmsg);
    }
    else
    {
        printf("Select done!\n");
    }
    #endif	
}

int set_env(float val, Type_info no)
{
	sqlite3 *db;
	char **aresult=NULL;  
  
    int i=0;  
    int nrow=0;  
    int ncol=0;  
	char *errmsg=NULL;  
    char sql[1024];
	
	switch(no)
	{
		case TEMPERATURE_MAX:
		sprintf (sql, "update config_env set temperatureMax = '%f';", val);
		break;
		case TEMPERATURE_MIN:
		sprintf (sql, "update config_env set temperatureMin = '%f';", val);
		break;
		case HUMIDITY_MAX:
		sprintf (sql, "update config_env set humidityMax = '%f';", val);
		break;
		case HUMIDITY_MIN:
		sprintf (sql, "update config_env set humidityMin = '%f';", val);
		break;
		case ILLUMINATION_MAX:
		sprintf (sql, "update config_env set illuminationMax = '%f';", val);
		break;
		case ILLUMINATION_MIN:
		sprintf (sql, "update config_env set illuminationMin = '%f';", val);
		break;
		
	}
	if(SQLITE_OK != sqlite3_exec(db,sql,NULL,NULL,&errmsg))//判断是否成功成功返回SQLITE_OK  
    {  
        printf("set_env  error:\n");  
         
        return(-1);  
    }  
	printf("set_env ok:\n");
	
	
	
}

int main()
{
		
	creat_database();
	creat_table_config_env();
	creat_table_collect_env();
    init_table_env (); 
    display_table_env();
	//set_env(50.2,TEMPERATURE_MAX );
	//display_table_env();
    return 0;
}
