#include "parse_path.h"

int valid_path_check(const char *filepath){
    int len = strlen(filepath);
    if(len>MAX_FILE_PATH){
        len=MAX_FILE_PATH;
    }
    return ( len>=3 && ( isdigit(filepath[0])) && (memcmp((void *)&filepath[1],":/",2)) ==0 );
}

int get_drive_num(const char **filepath_ptr){       //input will be a ptr to the filepath
    if(!valid_path_check(*filepath_ptr)){
        return ERROR_PATH_ERROR;
    }
    int drive_num = todigit(*filepath_ptr[0]);
    *filepath_ptr+=3;                               // path+3bytes = path [{0/:}{file.txt}]
    return drive_num;
}

struct root* create_root(int drive_number){
    struct root *root_path = kzalloc(sizeof(struct root));
    root_path->drive_num = drive_number;
    root_path->first = 0;
    return root_path;
}

const char *get_path(const char **path){
    char *path_part = kzalloc(MAX_FILE_PATH);
    int i=0;
    while(**path!='/' && **path!=0){
        path_part[i] = **path;
        *path+=1;
        i++;
    }
    if(**path=='\0'){
        *path+=1;
    }
    if(i==0){
        kfree(path_part);
        path_part = 0;
    }
    return path_part;
}

struct path *parse_path(struct path *last, const char **path){
    const char *path_str = get_path(path);
    if(!path_str){
        return 0;
    }
    struct path * path_part = kzalloc(sizeof(struct path));
    path_part->first = path_str;
    path_part->next=0;

    if(last){
        last->next = path_part;
    }
    return path_part;
}


void parser_free(struct root *root_part){
    struct path *path_part = root_part->first;
    while(root_part){
        struct path *next_path = path_part->next;
        kfree((void *)path_part->first);
        kfree(path_part);
        path_part=next_path;
    }
    kfree(root_part);
}

struct root *pathparser_parse(const char* path, const char* current_directory_path)
{
    int res = 0;
    const char* tmp_path = path;
    struct root* path_root = 0;

    if (strlen(path) > MAX_FILE_PATH){
        goto out;
    }

    res = get_drive_num(&tmp_path);
    if (res < 0){
        goto out;
    }

    path_root = create_root(res);
    if (!path_root){
        goto out;
    }

    struct path* first_part = parse_path(NULL, &tmp_path);
    if (!first_part){
        goto out;
    }

    path_root->first = first_part;
    struct path* part = parse_path(first_part, &tmp_path);
    while(part){
        part = parse_path(part, &tmp_path);
    }

out:
    return path_root;
}