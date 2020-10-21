default:shell ls rm mkdir date cat

shell:
	gcc task2.c -o shell

rm: 
	gcc rm.c -o rm

mkdir:
	gcc mkdir.c -o mkdir

ls:
	gcc ls.c -o ls

cat:
	gcc cat.c -o cat

clean:
	rm shell mkdir ls rm date cat 