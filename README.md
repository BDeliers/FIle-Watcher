# File-Watcher
### Simple file watcher which executes a script each time this file is modified. The previous instance of the script is killed.

When you call the script, you specify the path of the file to watch. Each time it's modified on the disk, the specified script is started and the provious instance is killed  
### By BDeliers, June 2018

---

Compile the file (I used GCC) and you're ready !

*CALL SAMPLE :*  
```bash
file-watcher /home/myname/somewhere/somefile /home/myname/somewhere/someExecutableFile /path/to/executer commandToExecute
```
*REAL EXAMPLE :*  
```bash
file-watcher /home/server/myDataBase /home/server/myscript.py /usr/bin/python3 python3
```
*REAL EXAMPLE II :*
```bash
file-watcher /home/server/myDataBase /home/server/myscript.sh /bin/sh sh
```

##### Uses 0% ram and 0% cpu for me  

---

How it looks :
![Call Example](./Exmaple.png)

Computer's resources usage :
![Resource Example](./Exmaple2.png)
