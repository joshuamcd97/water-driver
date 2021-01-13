# Loadable Linux Kernel driver that will remind you to get your daily dose of H20


### Installing

Clone the git repository locally.

Run:

```
make clean 
make

```

And run following command to confirm drinkwater.ko is present

```
ls -al
```
Run:

```
sudo insmod drinkwater.ko 
```
After running this check 
```
tail -f /var/log/kern.log
```
Now enter the Major number where the drinkwater module has loaded in kern.log instead of ($maj) in the following.

```
cd /dev/
sudo mknod drinkwater c $maj 0
cat /dev/drinkwater 
```
Now place in all of your shell scripts to remind yourself to stay hydrated 
