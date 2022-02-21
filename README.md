**PHILOSOPHERS**<hr>
In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.<br>
<br>***Overview***<br>
 One or more philosophers sit at a round table.<br>
There is a large bowl of spaghetti in the middle of the table.<br>
• The philosophers alternatively eat, think, or sleep.<br>
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;<br>
and, of course, while sleeping, they are not eating nor thinking.<br>
• There are also forks on the table. There are as many forks as philosophers.<br>
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.<br>
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.<br>
• Every philosopher needs to eat and should never starve.<br>
• Philosophers don’t speak with each other.<br>
• Philosophers don’t know if another philosopher is about to die.<br>
• No need to say that philosophers should avoid dying<br>

<br>***Arguments***<br>
1) number_of_philosophers
2) time_to_die time_to_eat
3) time_to_sleep
4) number_of_times_each_philosopher_must_eat



<br>Compiling commands<br>
```
make - compile
make re - re compile
make clean - clean *.o files
make fclean - clean all
```

<br>Example<br>
```
./philo 5 800 200 200 - no one should die!
./philo 5 800 200 200 7 - no one should die and the simulation should stop when all the philosopher has eaten atleast 7 times each.
./philo 4 410 200 200 - no one should die!
./philo 4 310 200 100 - a philosopher should die!
```


