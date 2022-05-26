export test=42 | echo 99
/bin/echo $test

/bin/echo $mini_test
env | grep mini_test
export mini_test=
/bin/echo $mini_test
env | grep mini_test

### UNSET ###
unset ""

unset =

unset "="

unset ""=

unset =""

unset ==

unset ?

unset "?"

unset $

unset "$"

unset $""

/bin/echo $HOME
unset $HOME
/bin/echo $HOME

/bin/echo $HOME
unset HOME
/bin/echo $HOME

/bin/echo $HOME
unset HOME
unset HOME
unset HOME
/bin/echo $HOME

/bin/echo $HOME
unset HOME
unset HOME
unset HOME
unset HOME
/bin/echo $HOME

###  EXIT ###
exit

exit ""

exit 0

exit 10

exit 42

exit 1

exit +++++

exit ++++++

exit +1

exit ++1

exit ++12560

exit -----

exit ------

exit -1

exit --1

exit -12560

exit --12560

exit 255

exit 1 2

exit 1 2 3

exit A

exit A 2 3

exit "A"

exit "+++"

exit ++++3193912939

exit 01

exit 001

exit 0001

exit +++000

exit ++++000

exit ---000

exit ----000

exit "something"

exit x

exit echo

exit cd ..

exit exit
