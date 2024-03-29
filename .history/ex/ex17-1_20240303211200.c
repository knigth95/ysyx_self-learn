#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    int max_data;
    int max_rows;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char *message, struct Connection *conn)
{
    if(conn) {
        Database_close(conn);
    }

    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to load database.",conn);
}

struct Connection *Database_open(const char *filename, char mode, int max_data, int max_rows)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error", NULL);

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error", conn);

    conn->db->max_data = max_data;
    conn->db->max_rows = max_rows;
    conn->db->rows = malloc(sizeof(struct Address) * max_rows);
    for(int i = 0; i < max_rows; i++) {
        conn->db->rows[i].name = malloc(max_data);
        conn->db->rows[i].email = malloc(max_data);
    }

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file", conn);

    return conn;
}
void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) die("Failed to write database.",conn);

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.",conn);
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for(i = 0; i < conn->db->max_rows; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first",conn);

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_data);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed",conn);

    res = strncpy(addr->email, email, conn->db->max_data);
    if(!res) die("Email copy failed",conn);
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if(addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set",conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

// 实现一个简单的 find 功能
void Database_find(struct Connection *conn, const char *name)
{
    for(int i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &conn->db->rows[i];
        if(cur->set && strcmp(cur->name, name) == 0) {
            Address_print(cur);
            return;
        }
    }
    printf("Record not found.\n");
}

int main(int argc, char *argv[])
{
    //if(argc < 6) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

    char *filename = argv[1];
    char action = argv[2][0];
    int max_data = 512 ;//atoi(argv[argc-2]);
    int max_rows = 100 ;//atoi(argv[argc-1]);

    struct Connection *conn = Database_open(filename, action, max_data, max_rows);
    int id = 0;

    if(argc > 6) id = atoi(argv[6]);
    if(id >= max_rows) die("There's not that many records.", conn);

    switch(action){
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;
        case 'g':
            if(argc!=4) die("Need an id to get",conn);
            Database_get(conn,id);
            break;
        case's':
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
