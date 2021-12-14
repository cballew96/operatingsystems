/*
 PART 2.2 (MMIN) IS SHOWN IN THE FILE FINDMMIN.C
 PARTS SHOWN IN THIS FILE
 1
 2.1
 2.3
 3

 * Input: ./find -w testdir (1 -- FIND WHERE-TO LOOK)
 * Output: print all the files in testdir
 *
 * Input: ./find -w testdir -n test5 (2.1 -- FIND WHERE-TO-LOOK -n <specified name>)
 * Output: print the path of the file with name test5
 *
 * (2.2 -- FIND WHERE-TO-LOOK -m <specified number of minutes> IS SHOWN  IN THE FILE FINDMMIN.C*****)
 *
 * Input: ./find -w testdir -i 57278526 (2.3 -- FIND WHERE-TO-LOOK -i <specified i-node number>)
 * Output: print the path of the file with inode number 57278526
 *
 * Input: ./find -w testdir -n test5 -a delete (3 -- FIND WHERE-TO-LOOK -n <specified name> -a delete>)
 * Ouput: deletes the file named test5
 *
 * Input: ./find -w testdir -i 57278526 -a delete (3 -- FIND WHERE-TO-LOOK -i <specified inode> -a delete>)
 * Output: deletes the file with inode 57278526
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
char *full_path;
int w, n, m, i, a;
struct stat buf;
//struct tm t;
time_t seconds;

void read_sub(char *sub_dir, char *where, char *name, char *inum, char *action)
{
  //printf("%s, %s, %s, %s", where, name, inum, action);
  DIR *sub_dp=opendir(sub_dir);
  struct dirent *sub_dirp;
  struct stat buf;
  if(sub_dp!=NULL)
    {
       		
       while((sub_dirp=readdir(sub_dp))!=NULL)
        {
	/*
         if (n==0){
		if(m==0){
			if(i==0){
		i		if(a==0){
	 		
         //printf("%s\n",sub_dirp->d_name);
				}
			}
		}
	 }
	 */
	 //printf("time stamp = %9jd ", buf.st_atime); //print time stamp
	 char * temp =sub_dirp->d_name;
         char temp1[]=".";
	 char temp2[]="..";
	 char str1[] = "/";
	 char str2[] = "delete";
	 char minus[] = "-";
	 char plus[] = "+";

        if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)//recurcively loop into the sub-directory
        {
	char temp3[]="/";
	char *temp_sub=temp3;

	//printf("temp_sub = %s \n", temp_sub);

	temp_sub=strcat(temp_sub,temp);

	//printf("temp_sub = %s \n", temp_sub);

	char *temp_full_path=malloc(sizeof(char)*2000);
	temp_full_path=strcpy(temp_full_path,sub_dir);

	//printf("temp_full_path = %s \n", temp_full_path);

	temp = strcat(temp_full_path,temp_sub);
	//printf("temp_sub appended to temp_full_path = %s \n", temp);
	
	if(stat(temp,&buf)==0) {				//finds file with same inode number entered
		if(a==0){
			if ((int)buf.st_ino == atoi(inum)){
			printf("%s \n", temp);
			}
		}
		if(a==1){
			if ((int)buf.st_ino == atoi(inum)){	//removes a file with the inode that was entered
			remove(temp);
			printf("File with inode %s was removed. \n", inum);
			}	
		} 
	}
	if(n==0){						//prints the directories full path
		if(m==0){
			if(i==0){
				if(a==0){ 
				printf("%s \n", temp_full_path);
				}
			}
		}
	}
	
	/*
	int sec;
	int min;	
	seconds = time(NULL);	
	if(stat(temp,&buf)==0) {				
		if (m==1) {
			printf("Tme of day - time of modification = %d\n", (int)seconds-(int)buf.st_mtime);
			sec = (int)seconds-(int)buf.st_mtime;
			min = sec/60; 
			printf("SECONDS: %d \n", sec);
			printf("MINUTES SINCE LAST MOD: %d\n", min);
			printf("%s\n", temp_full_path);

			if(strncmp(mmin, plus, 1)==0) {
				if (min > atoi(mmin)) {
					printf("%s\n", temp_full_path);
				}
			}
			else if(strncmp(mmin, minus, 1)==0) {
				if (min < atoi(mmin)) {
					printf("%s\n", temp_full_path);
				}
			}
			else if(min = atoi(mmin)) {
				printf("%s\n", temp_full_path);
			}
		}
	}
	*/
		
	strcat(str1,name);					
	//printf("name appended to str1: %s \n", str1);
	//printf("Value of temp_sub = %s \n", temp_sub);

	if(a == 1){						//removing a file with name that was entered
		if(n == 1) {
			if(strcmp(action,str2) == 0) {
			//printf("The action was %s", action);
				if(strcmp(str1,temp_sub) == 0){
				remove(temp_full_path);
				printf("The file %s was removed.\n", name);
				}		
			}
		}	
	}
	
								//finds name of file entered
	if(n==1){
		if(a==0){
			if (strcmp(temp_sub, str1) == 0){
			printf("%s \n", temp);
			}	
		}  	
	}

 	DIR *subsubdp=opendir(temp_full_path);
	if(subsubdp!=NULL){
	closedir(subsubdp);
	//printf("Value of temp_full_path sent to read_sub = %s \n", temp_full_path);
        read_sub(temp_full_path, where, name, inum, action);
        }
        }
        }
       closedir(sub_dp);
    }
    else
    {
        printf("cannot open directory\n");
        exit(2);
    }

}

int main(int argc, char **argv)
{
    char * dir;
    char  *where, *name, *mmin, *inum, *action;
   
    while (1) {
		char		c;

		c = getopt(argc, argv, "w:n:m:i:a:");	/* A colon (‘:’) to
							 * indicate that it
							 * takes a required
							 * argument, e.g, -w
							 * testdir */
		if (c == -1) {
			/* We have finished processing all the arguments. */
			break;
		}
		switch (c) {
		case 'w':
			w = 1;
			where = optarg;
			//printf("where: %s\n", optarg);
			break;
		case 'n':
			n = 1;
			name = optarg;
			//printf("name: %s\n", optarg);
			break;
		case 'm':
			m = 1;
			mmin = optarg;
			//printf("mmin: %s\n", optarg);
			break;
		case 'i':
			i = 1;
			inum = optarg;
			//printf("inum: %s\n", optarg);
			break;
		case 'a':
			a = 1;
			action = optarg;
			//printf("action: %s\n", optarg);
			break;
		case '?':
		default:
			printf("An invalid option detected.\n");
		}
	}
    if(argc <3){
    dir = ".";
    }
    else {
    dir = argv[2];
    }
    read_sub(dir, where, name, inum, action);
    
    exit(0);
}
