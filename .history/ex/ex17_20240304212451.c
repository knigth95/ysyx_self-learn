#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>

int max_data;
int max_rows;

struct Address{
    int id;
    int set;
    char *name;
    char *email;
};

struct Database{
    int max_data;
    int max_rows;
    struct Address *rows;
};
struct Connection{
    FILE *file;
    struct Database *db;
};
struct Connection *conn;
void die(const char *message,struct Connection *conn);
void Address_print(struct Address *addr);
void Database_close(struct Connection *conn);
void Database_create(struct Connection *conn);
void Database_delete(struct Connection *conn,int id);
void Database_get(struct Connection *conn,int id);
void Database_list(struct Connection *conn);
void Database_load();
struct Connection *Database_open(char *filename,char mode,int max_data,int max_rows);
void Database_set(struct Connection *conn,int id,char *name,char *email);
void Database_write(struct Connection *conn);

int main(int argc,char *argv[]){
    if(argc<5) printf("USAGE: ex17 <dbfile> <action> [action params]");
    char *filename=argv[1];
    char action=argv[2][0];

    // max_data=atoi(argv[argc-2]);
    // max_rows=atoi(argv[argc-1]);
    struct Connection *conn=Database_open(filename,action,max_data,max_rows);
    int id=0;
    
    if(argc>5) 
        id=atoi(argv[3]);
    //if(id>=max_rows) die("There are not that many records.",conn);
    switch(action){
        case 'c':
            max_data=atoi(argv[argc-2]);
            max_rows=atoi(argv[argc-1]);
            Database_create(conn);
            Database_write(conn);
            break;
        case 'g':
            if(argc!=4) die("Need an id to get",conn);
            Database_get(conn,id);
            break;
        case's':
            if(argc!=4) die("Need id,name,email to set",conn);
            Database_set(conn,id,argv[4],argv[5]);
            break;
        case 'd':
            if(argc!=4) die("Need an id to delete",conn);
            Database_delete(conn,id);
            Database_write(conn);
            break;
        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action,c=create, g=get, s=set, d=del, l=list",conn);
    }
    Database_close(conn);
    return 0;
}

//出现错误时终止程序
void die(const char *message,struct Connection *conn){
    if(conn){
        if(conn->file)
            fclose(conn->file);
        if(conn->db){
            for(int i=0;i<conn->db->max_rows;i++){
                free(conn->db->rows[i].name);
                free(conn->db->rows[i].email);
            }
            free(conn->db->rows);
        }
        free(conn->db);
    }
    if(errno){
        perror(message);
    }else{
        printf("ERROR:%s\n",message);
    }
    exit(1);
}

//打印地址信息
void Address_print(struct Address *addr){
    printf("id:%d\n",addr->id);
    printf("name:%s\n",addr->name);
    printf("email:%s\n",addr->email);
}

//读取数据库
void Database_load(struct Connection *conn){
    //原来时没有动态的大小信息获取，现在需要动态获取
    int rc=fread(conn->db,sizeof(struct Database),1,conn->file);
    if(rc !=1) die("Error reading database.",conn);

    max_rows=conn->db->max_rows;
    max_data=conn->db->max_data;

    struct Address *addr=malloc(max_rows*sizeof(struct Address));
    conn->db->rows=addr;
    
    for(int i=0;i<max_rows;i++){
        rc=fread(&conn->db->rows[i],sizeof(struct Address),1,conn->file);
        if(rc !=1) die("Error reading database.",conn);
        printf("再次开始------\n");
        //先分配name、email
        char *name=malloc(max_data*sizeof(char));
        char *email=malloc(max_data*sizeof(char));
        
        conn->db->rows[i].name=name;
        conn->db->rows[i].email=email;
        printf("name:%s\n",addr->name);
        printf("email:%s\n",addr->email);
        //读取id、set
        // int rc=fread(&conn->db->rows[i].id,sizeof(int),1,conn->file);
        // rc+=fread(&conn->db->rows[i].set,sizeof(int),1,conn->file);
        // if(rc!=2)
        //     die("Memory error_id/set",conn);
        
        //读取name、email
        ////////////////////////////////////
        rc=fread(conn->db->rows[i].name,max_data*sizeof(char),1,conn->file);
        if(rc!=1)
            die("Memory error_name",conn);
        rc=fread(conn->db->rows[i].email,max_data*sizeof(char),1,conn->file);
        if(rc!=1)
            die("Memory error_email",conn);
    }
    printf("max_data结束:%d\n",conn->db->max_data);
    
}

//初始信息
struct Connection *Database_open(char *filename,char mode){
    //struct Address *addr=malloc(sizeof(struct Address)*max_rows);
    struct Connection *conn=malloc(sizeof(struct Connection));
    if(!conn) die("Memory error",conn);
    conn->db=malloc(sizeof(struct Database));
    
    if(!conn->db) die("Memory error",conn);
    // conn->db->max_data=max_data;
    // conn->db->max_rows=max_rows;
    if(mode=='c'){
        conn->file=fopen(filename,"w");
    }
    else{
        conn->file=fopen(filename,"r+");
        if(conn->file)
            Database_load(conn);
    }
    if(!conn->file) die("Failed to open the file",conn);
    return conn;
}

//关闭数据库
void Database_close(struct Connection *conn){
    if(conn){
        if(conn->file) fclose(conn->file);
        if(conn->db){
            for(int i=0;i<conn->db->max_rows;i++){
                free(conn->db->rows[i].name);
                free(conn->db->rows[i].email);
            }
            free(conn->db->rows);
        }
        free(conn->db);
    }
    free(conn);
}

//数据库写入
void Database_write(struct Connection *conn){
    rewind(conn->file);
    int rc=fwrite(conn->)
    // 写入max_data和max_rows
    int rc = fwrite(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file);
    rc += fwrite(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file);
    rc+=fwrite(conn->db->rows,sizeof((conn->db->rows)),1,conn->file);
    if(rc!=3) die("Failed to write database configureation.",conn);

    // if(rc!=1) die("Failed to write database configureation.",conn);
    // printf("rc:%d\n",rc);
    
    for(int i=0;i<conn->db->max_rows;i++){
        struct Address *addr=&conn->db->rows[i];
        //address基础数据
        //rc=fwrite(addr,sizeof(struct Address)-sizeof(char*)*2,1,conn->file);
        rc=fwrite(addr,sizeof(struct Address),1,conn->file);
        if(addr->set){
            rc=fwrite(addr->id,conn->db->max_data,1,conn->file);
            rc+=fwrite(addr->set,conn->db->max_data,1,conn->file);
            rc+=fwrite(addr->name,conn->db->max_data,1,conn->file);
            rc+=fwrite(addr->email,conn->db->max_data,1,conn->file);
            if(rc!=4) die("Failed to write database configureation.",conn);
        }
    }
    rc=fflush(conn->file);
    if(rc==-1) die("Cannot flush database.",conn);
}

//数据库创建
void Database_create(struct Connection *conn){
    int i;
    for(i=0;i<conn->db->max_rows;i++){
        struct Address addr={.id=i,.set=0};
        conn->db->rows[i]=addr;
    }
    printf("max_rows:%d\n",conn->db->max_rows);
}

void Database_set(struct Connection *conn,int id,char *name,char *email){
    struct Address *addr=&conn->db->rows[id];
    printf("max_data:%d\n",conn->db->max_data);
    if(addr->set) die("Already set,delete it first",conn);
    printf("max_data:%d\n",conn->db->max_data);
    addr->set=1;
    
    addr->name=malloc(sizeof(char)*conn->db->max_data);
    addr->email=malloc(sizeof(char)*conn->db->max_data);
    
    if(!addr->name || !addr->email) die("Memory error.",conn);
    memset(addr->name,0,conn->db->max_data);
    memset(addr->email,0,conn->db->max_data);
    printf("ok:name:%s\naddr->name:%s",name,addr->name);
    char *res=strncpy(addr->name,name,conn->db->max_data-1);
    
    addr->name[conn->db->max_data-1]='\0';
    if(!res) die("Name copy failed",conn);
    res=strncpy(addr->email,email,conn->db->max_data-1);
    addr->email[conn->db->max_data-1]='\0';
    if(!res) die("Email copy failed",conn);
    // char *res=strncpy(addr->name,name,conn->db->max_data);
    // if(!res) die("Name copy failed",conn);

    // res=strncpy(addr->email,email,conn->db->max_data);
    // if(!res) die("Email copy failed",conn);
}

void Database_get(struct Connection *conn,int id){
    struct Address *addr=&conn->db->rows[id];
    if(!addr->set)
        Address_print(addr);
    else
        die("ID is not set",conn);
}

void Database_delete(struct Connection *conn,int id){
    struct Address addr={.id=id, .set=0};
    conn->db->rows[id]=addr;
}

void Database_list(struct Connection *conn){
    int i;
    struct Database *db=conn->db;
    for(i=0;i<conn->db->max_rows;i++){
        struct Address *cur=&db->rows[i];
        if(cur->set)
            Address_print(cur);
    }
}
