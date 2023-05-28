#include <linux/kernel.h>

asmlinkage long sys_info(int argc, char* argv[])
{
	char line[2000];
	char output[4][10000];
	FILE *fp;
	int counter=0;
	int i=0;

	fp = fopen("/proc/cpuinfo", "r"); // read mode

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	strcat(output[0], "***************information of CPU*********************\n");

	while(fgets(line, sizeof(line), fp) != 0)
	{
		strcat(output[0], line);
		counter++;
		if(counter>4)
		{
			break;
		}
	}

	fclose(fp);
	
	if(argc== 3 || argc==4)
	{
		strcat(output[2], "***************Process information*********************\n");
		char line4[2000];
		counter=0;
		
		FILE *fp4;
		char filename[50];
		strcat(filename, "/proc/");
		if(argc==3)
			strcat(filename, argv[2]);
		if(argc==4)
			strcat(filename, argv[3]);
		strcat(filename, "/status");
		fp4 = fopen(filename, "r");
		
		if (fp4 == NULL)
		{
			perror("Error while opening the file.\n");
			exit(EXIT_FAILURE);
		}
		
		while(fgets(line4, sizeof(line4), fp4) != 0)
		{
			counter++;
			if(counter==1 || counter==3 || counter==9 || counter==6 || counter==7)
			{
				strcat(output[2], line4);
			}
		}
		
		fclose(fp4);
	}
	
	if(argc== 2 || argc==4)
	{
		strcat(output[1], "***************System Statistics*********************\n");
		strcat(output[1], "system was booted since : ");   
		char line2[2000];
		char line3[2000];
		char num1[30], num2[30], task[30], process[30];
		int control=0;

		FILE *fp2;
		fp2 = fopen("/proc/uptime", "r");
		FILE *fp3;
		fp3 = fopen("/proc/loadavg", "r");

		if (fp2 == NULL)
		{
			perror("Error while opening the file.\n");
			exit(EXIT_FAILURE);
		}
		if (fp3 == NULL)
		{
			perror("Error while opening the file.\n");
			exit(EXIT_FAILURE);
		}

		while(fgets(line2, sizeof(line2), fp2) != 0)
		{
			break;
		}
		while(fgets(line3, sizeof(line3), fp3) != 0)
		{
			break;
		}
		
		fclose(fp2);
		fclose(fp3);
		
		for(i=0; i<strlen(line2); i++)
		{
			if(line2[i]==' ')
				control=1;
			else if(control==0)
				strncat(num1, &line2[i], 1);
			else
				strncat(num2, &line2[i], 1);
		}
		
		counter=0;
		control=0;
		for(i=0; i<strlen(line3); i++)
		{
			if(line3[i]=='/')
				control++;
			else if(line3[i]==' ')
				counter++;
			else if(counter==0)
				strncat(task, &line3[i], 1);
			else if(counter==3 && control==1)
				strncat(process, &line3[i], 1);
		}
		
		strcat(output[1], num1);
		strcat(output[1], "\n");
		strcat(output[1], "System has been idle since : ");
		strcat(output[1], num2);
		strcat(output[1], "The number of active tasks : ");
		strcat(output[1], task);
		strcat(output[1], "\n");
		strcat(output[1], "The total number of processes : ");
		strcat(output[1], process);
		
	}
	
	printf("%s\n%s\n%s\n", output[0], output[1], output[2]);

	return 0;
}
